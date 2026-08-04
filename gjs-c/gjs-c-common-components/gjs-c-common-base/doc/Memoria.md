# Memoria

| Dato         | Valor                                   |
| ------------ | --------------------------------------- |
| Cabecera     | `src/main/include/Memoria.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Memoria.c` |
| Prefijo      | `Mem`, `ES_`                            |
| Incluido por | `Base.h`                                |
| Test         | `MemoriaTest.c` → `TestMemoria()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Capa única de reserva y liberación de memoria dinámica de toda la librería.
Ningún otro módulo llama directamente a `malloc`/`free`: todo pasa por aquí, lo
que permite (a) abstraer la diferencia entre el *heap* del proceso de Windows y
`malloc` en POSIX, (b) devolver siempre memoria puesta a cero, (c) anular el
puntero del llamante al liberar y (d) contabilizar los bloques en modo depuración
([InfoMemoria](InfoMemoria.md)).

También define los macros `ES_VALIDO` / `ES_NULO`, que son el idioma de
validación de punteros usado en todo el proyecto.

## API

### Macros de validación

| Macro                | Descripción                            |
| -------------------- | -------------------------------------- |
| `ES_VALIDO( p_Obj )` | Cierto si el puntero es utilizable.    |
| `ES_NULO( p_Obj )`   | Cierto si el puntero no es utilizable. |

Con `GNU` (el caso normal) equivalen a `p_Obj != NULL` y `p_Obj == NULL`. Con
`VC` sobre `WIN` comprueban además los patrones de memoria basura del *debug
heap* de Visual C++ (`BAD_PTR`, `DELETED_PTR`, `BAD_STACK_PTR`,
`MEM_DIN_LIBERADA`, `MEM_DIN_LIBERADA_2`), que la cabecera define como
constantes documentadas (`0xCDCDCDCD`, `0xBAADF00D`, `0xDDDDDDDD`, `0xCCCCCCCC`,
`0xFEEEFEEE`, `0xFDFDFDFD`).

### Reserva y liberación

| Función                                                                          | Descripción                                  |
| -------------------------------------------------------------------------------- | -------------------------------------------- |
| `void * MemReservar ( int iNumBytes )`                                           | Reserva un bloque puesto a cero.             |
| `void * MemReservarVector ( int iNumElems, int iNumBytesElem )`                  | Reserva `iNumElems × iNumBytesElem`.         |
| `void * MemReservarTabla ( int iNumFilas, int iNumColumnas, int iNumBytesElem )` | Reserva `filas × columnas × tamaño`.         |
| `int MemRedimensionar ( void ** p_p_vBloque, int iNumBytes )`                    | Redimensiona el bloque. Devuelve 1/0.        |
| `int MemLiberar ( void ** p_p_vBloque )`                                         | Libera el bloque y pone el puntero a `NULL`. |
| `int MemLiberarCadena ( char ** p_p_cCadena )`                                   | Variante tipada para `char *`.               |
| `int MemLiberarUnicode ( unichar ** p_p_uniCadena )`                             | Variante para cadenas `unichar`.             |

### Manipulación y consulta

| Función                                                                  | Descripción                             |
| ------------------------------------------------------------------------ | --------------------------------------- |
| `void MemLimpiar ( void * p_vBloque, int iNumBytes )`                    | Pone el bloque a cero.                  |
| `void MemLlenar ( void * p_vBloque, byte byValor, int iNumBytes )`       | Rellena el bloque con un valor.         |
| `void MemCopiar ( void * p_vDest, void * p_vOrig, int iNumBytes )`       | Copia entre bloques.                    |
| `int MemEsValida ( void * p_vDireccion )`                                | Comprueba si la dirección es plausible. |
| `int MemEsIgual ( void * p_vBloque1, void * p_vBloque2, int iNumBytes )` | Compara byte a byte.                    |

## Comportamiento

### `MemReservar`

- En `WIN`: `HeapAlloc` sobre `GetProcessHeap()` con `HEAP_ZERO_MEMORY`.
- En el resto: `malloc` seguido de `memset` a cero.

Siempre devuelve memoria inicializada a cero, y por tanto una cadena reservada
con `MemReservar` ya está terminada.

Errores anotados (ver [Errores](Errores.md)):

| Situación                              | Código                                       |
| -------------------------------------- | -------------------------------------------- |
| `iNumBytes <= 0`                       | `ERR_PARAMETROS`                             |
| No se pudo obtener el *heap*           | `ERR_MEMORIA_INVALIDA`                       |
| Reserva fallida con *heap* íntegro     | `ERR_MEMORIA_INSUFICIENTE`                   |
| Reserva fallida y `HeapValidate` falla | `ERR_MEMORIA_INVALIDA` + **fin del proceso** |

Ese último caso es el único de toda la librería que aborta: llama a
`FinalizarEjecucion` ([Finalizacion](Finalizacion.md)) con el mensaje
`"Error grave de memoria: se ha corrompido el 'heap' del proceso."`. Sólo puede
darse en `WIN`.

`MemReservarVector` y `MemReservarTabla` son envoltorios sobre `MemReservar` que
multiplican los factores; **no comprueban desbordamiento** de la multiplicación.

### `MemLiberar`

Toma un **puntero a puntero** y deja el puntero del llamante a `NULL`, lo que
evita el uso posterior por descuido:

```c
char * p_cCad = CadDuplicar ( "algo" );
MemLiberar ( (void **) &p_cCad );   /* p_cCad queda a NULL */
```

Si el bloque ya era nulo o no supera `MemEsValida`, devuelve `1` (éxito) y anula
el puntero igualmente: liberar dos veces es inocuo. Sólo devuelve `0` si el
puntero a puntero es nulo, o si en Windows no se pudo obtener el *heap*.

`MemLiberarUnicode` en `WIN` hace algo particular: antes de liberar recorre el
bloque sobrescribiendo con `0x20` el byte alto de cada carácter mientras el bajo
no sea nulo, y sólo entonces libera con `HeapFree`. Fuera de Windows delega
directamente en `MemLiberar`.

### `MemEsValida`

No consulta al sistema: comprueba que la dirección caiga en un rango fijo
codificado en el `.c` (`MEM_LIM_INF` = `0x10000`, `MEM_LIM_SUP` = `0x7FFFFFFF` en
32 bits, `0x00007FFFFFFFFFFF` en 64). Con `VC` añade `IsBadReadPtr`. Es una
heurística de plausibilidad, no una garantía: descarta punteros claramente
absurdos, no punteros colgantes.

### `MemLimpiar`, `MemLlenar`, `MemCopiar`

Validan tamaño y punteros; si algo no cuadra anotan `ERR_PARAMETROS` y no hacen
nada. En Windows usan `ZeroMemory`, `FillMemory` y `CopyMemory`; en el resto,
`memset` y `memcpy`. `MemCopiar` valida el destino con `MemEsValida` pero el
origen sólo con `ES_VALIDO`, y no comprueba solapamiento (es un `memcpy`, no un
`memmove`).

### `MemEsIgual`

Comparación byte a byte con salida temprana. Con `iNumBytes == 0` devuelve `1`
(dos bloques de longitud cero son iguales). Con punteros nulos devuelve `0` sin
anotar error.

## Dependencias

- [Errores](Errores.md) — `ERROR_ESTABLECER`.
- [Finalizacion](Finalizacion.md) — `FinalizarEjecucion` en el caso de *heap*
  corrupto.
- [InfoMemoria](InfoMemoria.md) — bajo `MODO_DEPURACION`, notifica cada reserva y
  liberación con `_MemBloqueReservado` / `_MemBloqueLiberado`, declaradas aquí
  como `extern`.

Hay una dependencia circular funcional con `Errores`, que a su vez reserva
memoria para sus mensajes. No da problemas porque ninguno de los dos módulos
necesita inicialización.

## Test

`MemoriaTest.c` → `TestMemoria()`.

## Observaciones

- `MemValorByte` ya no se declara: su implementación sigue comentada en
  `Memoria.c` porque la firma original (`unsigned long` como dirección) trunca
  punteros en Windows de 64 bits (LLP64). Si se quisiera recuperar, debería
  tomar `uintptr_t`.
- Bajo `MODO_DEPURACION` fuera de Windows se llama a `malloc_usable_size`, que
  requiere `<malloc.h>`; esa cabecera no se incluye en ningún punto de la
  compilación, así que ese modo no está probado en POSIX.
- El comentario `// TODO: MemValida HEAP` de la cabecera y el `PENDIENTE` sobre
  `HeapWalk` del fuente apuntan a la misma carencia: no hay recorrido del *heap*
  para liberar bloques pendientes.
