# SNombre

| Dato         | Valor                                   |
| ------------ | --------------------------------------- |
| Cabecera     | `src/main/include/SNombre.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SNombre.c` |
| Prefijo      | `SNom`                                  |
| Struct       | `SNombre`                               |
| Funciones    | 11                                      |
| Incluido por | `Texto.h`                               |
| Test         | `SNombreTest.c` → `TestSNombre()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una cadena corta con el papel de **nombre o identificador**: el rótulo de un
campo, de una tabla o de una variable. Es una [SCadena](SCadena.md) con un tope
por defecto pensado para eso.

```c
typedef struct
{
    SCadena * p_cadValor;
} SNombre;
```

El tope por defecto es `NOM_MAX_TAM_DEF`, **35 caracteres**
(`TextoConstantes.h`).

## API

| Función                                          | Descripción                          |
| ------------------------------------------------ | ------------------------------------ |
| `SNombre * SNomCrearDef ()`                      | Nombre con el tope por defecto (35). |
| `SNombre * SNomCrear ( int iMaxTam )`            | Nombre con el tope indicado.         |
| `void SNomDestruir ( SNombre ** )`               | Destruye y anula el puntero.         |
| `int SNomMaxLongitud ( SNombre * )`              | Longitud máxima.                     |
| `int SNomLongitud ( SNombre * )`                 | Longitud actual.                     |
| `SCadena * SNomValor ( SNombre * )`              | Cadena interna.                      |
| `const char * SNomValorConstante ( SNombre * )`  | Contenido de sólo lectura.           |
| `int SNomEstablecerCad ( SNombre *, SCadena * )` | Fija el valor desde una `SCadena`.   |
| `int SNomEstablecer ( SNombre *, const char * )` | Fija el valor desde un literal.      |
| `int SNomLimpiar ( SNombre * )`                  | Vacía el nombre.                     |
| `int SNomEstaVacio ( SNombre * )`                | 1 si está vacío.                     |

```c
SNombre * p_nomObj = SNomCrearDef ();

SNomEstablecer ( p_nomObj, "importe_total" );
printf ( "%s (%d)\n", SNomValorConstante ( p_nomObj ), SNomLongitud ( p_nomObj ) );

SNomDestruir ( &p_nomObj );
```

## Dependencias

- [SCadena](SCadena.md) — el almacenamiento y todas las operaciones.

## Test

`SNombreTest.c` → `TestSNombre()`.

## Observaciones

- **Es idéntico a [SDescripcion](SDescripcion.md) salvo en el tope por
  defecto** (35 frente a 255) y en el prefijo. Mismos once métodos, misma
  estructura de un solo campo, misma delegación. Son dos módulos donde bastaría
  uno con el tope como parámetro.
- **No valida que el nombre sea un identificador válido**, pese a que
  [Cadenas](Cadenas.md) ofrece `CadEsIdentificadorValido`. Un `SNombre` acepta
  espacios, signos y cualquier carácter que quepa.
- `SNomValor` devuelve la `SCadena` interna modificable, así que se puede
  saltar el tope escribiendo directamente sobre ella.
- No hay comparación: para saber si dos nombres son iguales hay que bajar a las
  cadenas con `SNomValor` y usar `SCadEsIgual`.
