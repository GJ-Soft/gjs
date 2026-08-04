# SArgumentos

| Dato         | Valor                                                    |
| ------------ | -------------------------------------------------------- |
| Cabecera     | `src/main/include/SArgumentos.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SArgumentos.c` (274 líneas) |
| Prefijo      | `SArg`                                                   |
| Struct       | `SArgumentos`                                            |
| Funciones    | 10                                                       |
| Incluido por | `CCommon.h`                                              |
| Test         | `SArgumentosTest.c` → `TestSArgumentos()`                |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los argumentos de la línea de órdenes como objeto, ya limpios y con conversión
numérica.

```c
typedef struct
{
    SSecuenciaLiterales * p_seclitArgumentos;
} SArgumentos;
```

## El convenio de `SArgCrear`

```c
SArgumentos * p_argObj = SArgCrear ( argc, argv );
```

Se le pasa el `argc` y el `argv` **crudos**, tal como los recibe `main`. El
módulo se encarga de:

1. **Descartar `argv[0]`**, el nombre del ejecutable. Por eso exige `argc > 1`:
   con un solo elemento no hay argumentos que guardar y la secuencia queda a
   `NULL`.
2. Duplicar cada argumento.
3. Quitarle los caracteres no imprimibles y **todos** los espacios.

De modo que `SArgNumArgumentos` devuelve `argc - 1`, y `SArgArgumento ( p_argObj, 0 )`
es el primer argumento de verdad, no el nombre del programa.

## API

| Función                                                     | Descripción                             |
| ----------------------------------------------------------- | --------------------------------------- |
| `SArgumentos * SArgCrearDef ()`                             | **Sólo Windows**: los toma del sistema. |
| `SArgumentos * SArgCrear ( int iNumArg, char ** p_p_cArg )` | Desde `argc` y `argv`.                  |
| `void SArgDestruir ( SArgumentos ** )`                      | Destrucción.                            |
| `int SArgNumArgumentos ( SArgumentos * )`                   | Cuántos hay.                            |
| `char * SArgArgumento ( SArgumentos *, int iArg )`          | El argumento como texto.                |
| `int SArgEsArgumentoNumerico ( SArgumentos *, int iArg )`   | 1 si se puede convertir.                |
| `int SArgArgumentoEntero ( SArgumentos *, int iArg )`       | Como `int`.                             |
| `long SArgArgumentoEnteroLargo ( SArgumentos *, int iArg )` | Como `long`.                            |
| `float SArgArgumentoReal ( SArgumentos *, int iArg )`       | Como `float`.                           |
| `double SArgArgumentoRealDoble ( SArgumentos *, int iArg )` | Como `double`.                          |

```c
if ( SArgNumArgumentos ( p_argObj ) > 0 )
{
    if ( SArgEsArgumentoNumerico ( p_argObj, 0 ) == 1 )
    {
        int iPuerto = SArgArgumentoEntero ( p_argObj, 0 );
    }
}
```

`SArgEsArgumentoNumerico` antes de convertir es obligado: los cuatro
convertidores no distinguen un cero legítimo de un texto no numérico.

## Dependencias

[SSecuenciaLiterales](../../gjs-c-common-base-types/doc/Secuencias.md) y
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md).

## Test

`SArgumentosTest.c` → `TestSArgumentos()`.

## Los dos constructores no son equivalentes

`SArgCrearDef` no crea un objeto vacío: **en Windows obtiene los argumentos del
propio sistema**, con `GetCommandLineW` y `CommandLineToArgvW`, y los convierte
de Unicode con `CadUnicodeAAsciiz`. Fuera de Windows el cuerpo entero está bajo
`#if ( defined ( WIN ) )` y la función devuelve un objeto con la secuencia a
`NULL`.

Es la forma de construir el objeto sin que `main` pase `argc` y `argv`, y sólo
funciona en Windows.

## Observaciones

- **`CadEliminarBlancos` quita *todos* los espacios, no los de los extremos.**
  Un argumento entrecomillado como `"informe mensual"` se guarda como
  `informemensual`. Para recortar sólo los bordes el stack tiene
  `CadEliminarBlancosLaterales`, que es lo que se usa en
  [VariablesEntorno](../../gjs-c-common-system/doc/Entorno.md). Es el mismo
  descuido que deja inservible a [SMsjCargar](SMensajes.md).

- **No hay opciones ni modificadores.** El módulo trata todo como argumentos
  posicionales: no hay nada para `-v`, `--fichero=x` ni `-n 3`. Un programa que
  las quiera tiene que recorrer la secuencia y compararlas a mano.

- **`SArgArgumento` devuelve el puntero interno**, no una copia, y sin `const`:
  modificarlo cambia el argumento guardado.

- **`SArgCrear` no comprueba `p_p_cArg` con `ES_VALIDO`**, y el comentario del
  código explica por qué: *"en Unix/Linux suelen pertenecer al espacio de
  direcciones reservado"*. Compara con `NULL` directamente, que es lo correcto
  aquí.

- **Con `argc == 1` la secuencia queda a `NULL`**, no vacía. Es el mismo estado
  en el que deja el objeto `SArgCrearDef` fuera de Windows, y el objeto no tiene
  `SArgEsValido` con el que distinguir "sin argumentos" de "no se pudo
  construir".

### Corregido el 2026-08-02

- **El filtro de argumentos vacíos de `SArgCrear`** era
  `CadLongitud ( p_cArg ) >= 0`, condición siempre cierta que dejaba
  inalcanzable la rama `else` y metía en la secuencia los argumentos vacíos.
  Ahora es `> 0`, igual que en `SArgCrearDef`.
- **`SArgCrearDef` no liberaba el vector de `CommandLineToArgvW`**, que Windows
  reserva con `LocalAlloc`. Se ha añadido el `LocalFree`, sacando el bucle a un
  `if` interior para que también se suelte cuando no hay argumentos que
  procesar.
