# Errores

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabecera     | `src/main/include/Errores.h` (+ códigos en `BaseErrores.h`) |
| Fuente       | `src/main/c/org/gjs/c/common/Errores.c`                     |
| Prefijo      | `Err`, `ERROR_`, `ERR_`                                     |
| Incluido por | `Base.h`                                                    |
| Test         | `ErroresTest.c` → `TestErrores()`                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Subsistema global de errores. La librería no propaga códigos de error por el
valor de retorno: cuando una rutina falla, anota el error en un estado global
(código + descripción + módulo + línea) y devuelve un valor neutro. El llamante
decide cuándo consultarlo.

## API

### Macros de anotación

| Macro                                                   | Descripción                                                     |
| ------------------------------------------------------- | --------------------------------------------------------------- |
| `ERROR_ESTABLECER( iCodigo )`                           | Anota un error predefinido, capturando `__FILE__` y `__LINE__`. |
| `ERROR_ESTABLECER_FORM( iCodigo, p_cDescripcion, ... )` | Anota un error con descripción formateada.                      |

### Funciones

| Función                                                                                                              | Descripción                                       |
| -------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------- |
| `void ErrEstablecer ( const char * p_cModulo, int iLinea, int iCodigo )`                                             | Anota un error. Normalmente se llama vía macro.   |
| `void ErrEstablecerConFormato ( const char * p_cModulo, int iLinea, int iCodigo, const char * p_cDescripcion, ... )` | Ídem con descripción formateada.                  |
| `int ErrHayError ()`                                                                                                 | 1 si el código actual no es `ERR_OK`.             |
| `int ErrCodigo ()`                                                                                                   | Código del último error.                          |
| `const char * ErrDescripcion ()`                                                                                     | Descripción del último error.                     |
| `const char * ErrModulo ()`                                                                                          | Fichero donde se produjo.                         |
| `unsigned int ErrLinea ()`                                                                                           | Línea donde se produjo.                           |
| `const char * ErrMensaje ()`                                                                                         | Mensaje completo formateado. **Reserva memoria.** |
| `void ErrImprimir ()`                                                                                                | Imprime el mensaje completo por consola.          |
| `void ErrLimpiar ()`                                                                                                 | Reinicia el estado a `ERR_OK`.                    |

### Códigos

Definidos en `BaseErrores.h`: `ERR_OK` (0), `ERR_MEMORIA_INVALIDA` (1),
`ERR_MEMORIA_INSUFICIENTE` (2), `ERR_MEMORIA_PROCESO` (3), `ERR_PARAMETROS` (4),
`ERR_POSICION_INVALIDA` (5), `ERR_ESTRUCTURA_INVALIDA` (6),
`ERR_IMPOSIBLE_ABRIR_FICHERO` (100).

## Comportamiento

### Estado

Cuatro variables estáticas de módulo:

```c
static int           g_iGError            = ERR_OK;
static const char *  g_p_cGErrDescripcion = NULL;
static const char *  g_p_cGErrModulo      = NULL;
static unsigned int  g_uiGErrLinea        = 0;
```

Es un estado **global y único**, no por hilo. Cada nueva anotación pisa la
anterior: no hay pila ni encadenado de errores. Y como la librería anota errores
en rutinas muy usadas (por ejemplo `CadLongitud` con puntero nulo), conviene
llamar a `ErrLimpiar()` antes del bloque de código que se quiere vigilar.

### Códigos predefinidos vs. libres

`_ErrPredefinido` distingue dos familias:

- **Predefinidos** (`ERR_OK`, `ERR_MEMORIA_INVALIDA`, `ERR_MEMORIA_INSUFICIENTE`,
  `ERR_MEMORIA_PROCESO`, `ERR_PARAMETROS`): la descripción la genera la propia
  librería con `_ErrDescripcion`, y se ignora cualquier texto que se pase.
- **Cualquier otro código**: se guarda la descripción que aporte el llamante. Si
  se usa `ERROR_ESTABLECER` (que no pasa texto), la descripción queda a `NULL`.

Obsérvese que `ERR_POSICION_INVALIDA`, `ERR_ESTRUCTURA_INVALIDA` y
`ERR_IMPOSIBLE_ABRIR_FICHERO` **no** tienen descripción predefinida pese a estar
declarados: con ellos hay que usar `ErrEstablecerConFormato`.

### Memoria

La descripción y el módulo se guardan como copias hechas con `CadDuplicar`, y se
liberan con `MemLiberar` en cada nueva anotación y en `ErrLimpiar`. Es decir:
`ErrDescripcion()` y `ErrModulo()` devuelven punteros a memoria **propiedad del
módulo**, que quedan colgando en cuanto se anote el siguiente error. Si el valor
debe sobrevivir, hay que duplicarlo.

`ErrMensaje()` es la excepción: **reserva** una cadena de 255 caracteres con el
formato `"Error %d - %s (%s:%u)"` y la devuelve; el llamante debe liberarla.
`ErrImprimir()` la usa y la libera por su cuenta.

### Flujo típico

```c
ErrLimpiar ();
p_cResultado = HacerAlgo ();
if ( ErrHayError () == 1 )
{
    ErrImprimir ();          /* "Error 4 - Uno o mas parametros ... (Fichero.c:123)" */
    ErrLimpiar ();
}
```

## Dependencias

- [Memoria](Memoria.md) — reserva y liberación de las cadenas del estado.
- [CadenasBase](CadenasBase.md) — `CadCrear`, `CadDuplicar`.
- [FormatoCadena](FormatoCadena.md) — `FrmCadena` para la variante con formato.

Dependencia circular funcional con `Memoria`, que a su vez anota sus fallos aquí.
No hay problema porque ninguno de los dos requiere inicialización.

## Test

`ErroresTest.c` → `TestErrores()`.

## Observaciones

- `ERROR_ESTABLECER_FORM` usa `##__VA_ARGS__`, que es una extensión de GNU (el
  equivalente estándar en C23 es `__VA_OPT__`). No es problema con el `gcc` que
  usa el proyecto, pero sí lo sería al portar a otro compilador.
- `ErrMensaje()` devuelve `NULL` cuando no hay error; `ErrImprimir()` lo
  comprueba antes de imprimir, así que en ese caso no escribe nada.
- `g_p_cGErrDescripcion` y `g_p_cGErrModulo` son `const char *` y se pasan a
  `MemLiberar` con un *cast* que descarta el `const`. Funciona, pero es una señal
  de que el tipo debería ser `char *`.
- Todo el bloque `InfErr*` (lista dinámica de errores dados de alta en tiempo de
  ejecución, con descripción y nivel de gravedad) está escrito pero **comentado**
  tanto en la cabecera como en el fuente. La implementación actual es la versión
  simplificada con cinco descripciones fijas.
- El macro `ALM_ERRORES` que menciona `Precompilacion.h` no se usa en este módulo.
