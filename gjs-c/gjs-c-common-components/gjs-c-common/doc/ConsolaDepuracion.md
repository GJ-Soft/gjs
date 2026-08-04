# ConsolaDepuracion

| Dato         | Valor                                                          |
| ------------ | -------------------------------------------------------------- |
| Cabecera     | `src/main/include/ConsolaDepuracion.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/ConsolaDepuracion.c` (192 líneas) |
| Prefijo      | `ConDep`                                                       |
| Funciones    | 7 + 2 macros                                                   |
| Incluido por | `CCommon.h`                                                    |
| Test         | `ConsolaDepuracionTest.c` → `TestConsolaDepuracion()`          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Trazas de depuración por consola que **sólo salen en modo test**.

Las siete funciones empiezan igual:

```c
if ( EntEstaEnModoTest () == 1 )
{
    … escribir …
}
else
{
    iRes = 1;      /* fuera del modo test, no hace nada y no falla */
}
```

Ésa es la idea del módulo: se llenan de `ConDepEscribirLinea` los sitios que
interesa vigilar, se ejecuta la suite con
[`EntActivarModoTest`](Entorno.md) y las trazas aparecen; en producción el mismo
binario no imprime nada. No hace falta `#if` ni recompilar, ni hay que quitarlas
después.

## API

| Función                                                | Descripción                      |
| ------------------------------------------------------ | -------------------------------- |
| `int ConDepAbrir ()`                                   | Abre la consola si no la había.  |
| `void ConDepCerrar ()`                                 | La cierra.                       |
| `int ConDepEstaAbierta ()`                             | Estado.                          |
| `void ConDepImprimir ( const char * p_cTexto, … )`     | Escribe sin salto de línea.      |
| `int ConDepEscribir ( const char * p_cTexto, … )`      | Idem, con resultado.             |
| `int ConDepEscribirLinea ( const char * p_cTexto, … )` | Escribe y añade el salto.        |
| `void ConDepEsperar ()`                                | Espera a que se pulse una tecla. |

Las tres de escritura son variádicas, con formato tipo `printf`.

`ConDepAbrir` se apoya en
[AplicacionConsola](../../gjs-c-common-support/doc/AplicacionConsola.md): si ya
hay consola abierta la reutiliza, y si no llama a `AplicConAbrir`. Lleva la
cuenta de si fue él quien la abrió, para no cerrar la que se encontró.

## Las dos macros

```c
#define DEP_INIFUN  ConDepEscribirLinea ( "<Mod: %s; Fun: %s> - INICIO", __FILE__, __FUNCTION__ )
#define DEP_FINFUN  ConDepEscribirLinea ( "<Mod: %s; Fun: %s> - FIN",    __FILE__, __FUNCTION__ )
```

Se ponen al principio y al final de una función y dejan la traza de entrada y
salida sin escribir el nombre a mano:

```c
int MiFuncion ( int iParam )
{
    DEP_INIFUN;
    …
    DEP_FINFUN;
    return ( iRes );
}
```

`__FUNCTION__` no es del C estándar —lo es `__func__`—, pero lo aceptan tanto
GCC como Visual C, que son los dos compiladores del stack.

## Dependencias

[AplicacionConsola](../../gjs-c-common-support/doc/AplicacionConsola.md) para
abrir la consola y medir su ancho, `FrmCadena` de
[FormatoCadena](../../gjs-c-common-base/doc/FormatoCadena.md) para el formateo, y
`EntEstaEnModoTest` de [Entorno](Entorno.md).

## Test

`ConsolaDepuracionTest.c` → `TestConsolaDepuracion()`.

## Observaciones

> **`printf ( p_cValor )` con el texto ya compuesto como formato.** Las tres
> funciones de escritura formatean el mensaje en `p_cValor` y después lo
> imprimen así:
>
> ```c
> printf ( p_cValor );
> ```
>
> Si el texto resultante contiene un `%` —una ruta de Windows con `%TEMP%`, un
> porcentaje en un mensaje, un dato de entrada cualquiera— `printf` lo
> interpreta como especificador de formato y lee argumentos que no existen. El
> resultado va de imprimir basura a caer.
>
> Es la forma clásica del problema de cadena de formato, y el arreglo es de una
> línea: `printf ( "%s", p_cValor )`.

- **La traza se trunca al ancho de la consola.** El búfer se reserva con
  `CadCrear ( AplicConAncho () )` —80 columnas si no hay terminal—, así que una
  línea de depuración más larga se corta. Justo en depuración, que es cuando se
  quiere el mensaje entero.
- **El módulo declara `extern int EntEstaEnModoTest ()` a mano** en lugar de
  incluir `CEntorno.h`. No es un descuido: `CEntorno.h` incluye `CCommon.h`, que
  incluye `ConsolaDepuracion.h`, de modo que hacerlo bien daría una inclusión
  circular. Es el precio de que la cabecera de arranque esté fuera de la
  fachada.
- **Fuera del modo test todo devuelve 1**, incluido `ConDepAbrir`. Un programa
  no puede distinguir "la consola está lista" de "no estoy en modo test", y
  `ConDepEstaAbierta` seguirá diciendo que no.
- **`ConDepImprimir` devuelve `void` y `ConDepEscribir` devuelve `int`**, sin
  que la cabecera aclare en qué se diferencian por lo demás. Las dos escriben
  sin salto de línea.
- **`ConDepEsperar` bloquea el proceso** esperando una tecla. En una suite
  automática eso es un cuelgue, y es precisamente en modo test cuando la función
  hace algo. El componente `support` tiene
  [SimularEntradaConsola](../../gjs-c-common-support/doc/Pruebas.md) para
  desbloquear estos casos.
- El estado son dos variables estáticas, `g_iConsolaDepuracionDisponible` y
  `g_iConsolaDepuracionAbierta`, sin protección entre hilos.
