# Memoria

| Dato         | Valor                                   |
| ------------ | --------------------------------------- |
| Cabecera     | `src/main/include/Memoria.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Memoria.c` |
| Prefijo      | `Mem`, `MEM_`, `ES_`                    |
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
validación de punteros usado en todo el proyecto, y `ES_MANEJADOR_VALIDO` /
`ES_MANEJADOR_NULO`, su equivalente para los manejadores del sistema en Windows.

## API

### Macros de validación

| Macro                         | Descripción                                                              |
| ----------------------------- | ------------------------------------------------------------------------ |
| `MEM_EN_RANGO( p_Obj )`       | Cierto si el valor cae en el espacio de direcciones de la aplicación.    |
| `ES_VALIDO( p_Obj )`          | Cierto si el puntero es utilizable. Hoy es exactamente `MEM_EN_RANGO`.   |
| `ES_NULO( p_Obj )`            | El contrario de `ES_VALIDO`.                                             |
| `ES_MANEJADOR_VALIDO( hObj )` | Manejador distinto de `NULL` y de `INVALID_HANDLE_VALUE`. Sólo con `WIN`. |
| `ES_MANEJADOR_NULO( hObj )`   | El contrario. Sólo con `WIN`.                                            |

`ES_VALIDO` **ya no es `p_Obj != NULL`**. Comprueba que el *valor* del puntero
caiga entre `MEM_LIM_INF` y `MEM_LIM_SUP`, los límites del espacio de
direcciones utilizable por la aplicación:

| Arquitectura | `MEM_LIM_INF` | `MEM_LIM_SUP`        |
| ------------ | ------------- | -------------------- |
| `A64`        | `0x10000`     | `0x00007FFFFFFFFFFF` |
| resto        | `0x10000`     | `0x7FFFFFFF`         |

Por debajo del inferior está la primera página, que ni Windows ni Linux
(`mmap_min_addr` = `0x10000`) mapean nunca; por encima del superior están las
direcciones no canónicas y el espacio del núcleo. No se consulta la memoria
apuntada: son dos comparaciones, sin llamada ni *syscall*.

A cambio se cazan tres cosas que el `!= NULL` anterior dejaba pasar:

- El desplazamiento desde un nulo (`&p->campo` con `p` nulo), que quedaba como un
  puntero pequeño pero distinto de `NULL`.
- El puntero automático sin inicializar, **siempre que se compile con el perfil
  `debug`**: es el que añade `-ftrivial-auto-var-init=pattern` (ver
  `gjs-c-nar-parent`), que rellena toda variable automática sin inicializar con
  `0xFEFEFEFEFEFEFEFE`, fuera de rango. Es el sustituto GNU de los rellenos
  `0xCC` / `0xCD` del CRT de depuración de MSVC que miraba la versión anterior
  de la macro. Sin ese perfil, un puntero sin inicializar puede caer dentro del
  rango por casualidad y pasar el filtro.
- La dirección no canónica y la del espacio de núcleo.

Lo que sigue **sin** detectar es el puntero colgante: una dirección ya liberada
está en rango, y `ES_VALIDO` la da por buena.

> **No aplicar `ES_VALIDO` a manejadores del sistema** (`HANDLE`, `HKEY`,
> `HINSTANCE`): el núcleo de Windows los reparte como valores pequeños (`0x4`,
> `0x8`, `0x1C`…), por debajo de `MEM_LIM_INF`, así que los rechazaría todos.
> Para ésos están `ES_MANEJADOR_VALIDO` / `ES_MANEJADOR_NULO`, que sólo existen
> bajo `WIN` porque dependen de `INVALID_HANDLE_VALUE`. El propio `Memoria.c` no
> los usa: comprueba su manejador de *heap* con un `hMem != NULL` directo.

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

### `MemRedimensionar`

Toma un **puntero a puntero**. Si el bloque de entrada es `ES_NULO`, delega en
`MemReservar`. Si no, `HeapReAlloc` con `HEAP_ZERO_MEMORY` en `WIN` y `realloc`
en el resto.

Ante un fallo de la reasignación, las dos ramas dejan `*p_p_vBloque` **intacto**:
el bloque original sigue siendo válido y no se pierde la referencia. El resultado
de `HeapReAlloc` o de `realloc` se recoge primero en una variable local, y sólo
se escribe sobre el puntero del llamante cuando es utilizable.

Comparte con `MemReservar` la terminación del proceso si `HeapValidate` dice que
el *heap* está corrupto.

Bajo `MODO_DEPURACION` la reasignación se contabiliza como lo que es —una
liberación más una reserva—, así que notifica a [InfoMemoria](InfoMemoria.md)
`_MemBloqueLiberado` del bloque viejo y `_MemBloqueReservado` del nuevo. El
tamaño del viejo se consulta **antes** de reasignar, con `HeapSize` o
`malloc_usable_size`, porque después ya no existe.

### `MemLiberar`

Toma un **puntero a puntero** y deja el puntero del llamante a `NULL`, lo que
evita el uso posterior por descuido:

```c
char * p_cCad = CadDuplicar ( "algo" );
MemLiberar ( (void **) &p_cCad );   /* p_cCad queda a NULL */
```

Si el bloque no supera `MemEsValida` —lo que ahora incluye cualquier valor fuera
de rango, no sólo el nulo—, devuelve `1` (éxito) y anula el puntero igualmente:
liberar dos veces es inocuo. Sólo devuelve `0` si el puntero a puntero no es
válido, o si en Windows no se pudo obtener el *heap*.

`MemLiberarUnicode` en `WIN` hace algo particular: si el segundo byte del bloque
es `0x00` lo toma por Unicode, y antes de liberar lo recorre sobrescribiendo con
`0x20` el byte alto de cada carácter mientras el bajo no sea nulo; sólo entonces
libera con `HeapFree`. Si ese segundo byte no es nulo delega en `MemLiberar`, y
fuera de Windows delega siempre.

### `MemEsValida`

Desde que el control de rango vive en `ES_VALIDO`, esta función se ha quedado en
un envoltorio de la macro: devuelve `1` si `ES_VALIDO ( p_vDireccion )` y `0` si
no. Los `MEM_LIM_*` ya no están duplicados en el `.c` —estaban repetidos con los
mismos valores en las ramas `WIN` y no-`WIN` de cada arquitectura— y la rama
`IsBadReadPtr`, que sólo existía con `VC`, ha desaparecido. Sigue siendo una
heurística de plausibilidad, no una garantía: descarta punteros claramente
absurdos, no punteros colgantes.

### `MemLimpiar`, `MemLlenar`, `MemCopiar`

Validan tamaño y punteros; si algo no cuadra anotan `ERR_PARAMETROS` y no hacen
nada. En Windows usan `ZeroMemory`, `FillMemory` y `CopyMemory`; en el resto,
`memset` y `memcpy`. `MemCopiar` valida el destino con `ES_VALIDO` **y** con
`MemEsValida` —que hoy son la misma comprobación— y el origen sólo con
`ES_VALIDO`; no comprueba solapamiento (es un `memcpy`, no un `memmove`).

### `MemEsIgual`

Comparación byte a byte con salida temprana. Con `iNumBytes == 0` devuelve `1`
(dos bloques de longitud cero son iguales). Si alguno de los punteros no supera
`ES_VALIDO` devuelve `0` sin anotar error.

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

- `MemEsValida` y `ES_VALIDO` son ahora la misma comprobación, así que las
  validaciones dobles que quedan en el fuente (`ES_VALIDO ( p_vDest ) && …
  MemEsValida ( p_vDest ) == 1` en `MemCopiar`) son redundantes.
- **La contabilidad de tamaños de [InfoMemoria](InfoMemoria.md) no cuadra del
  todo, y no es cosa de un módulo.** Al reservar se suma el tamaño **pedido**
  (`_MemBloqueReservado` recibe `iNumBytes`), pero al liberar se resta el tamaño
  **utilizable** que devuelven `HeapSize` o `malloc_usable_size`, que es mayor o
  igual. Cada pareja reserva-liberación deja el total un poco más bajo de lo que
  toca; `_MemBloqueLiberado` lo corta en 0 para que no dé la vuelta. El recuento
  de bloques sí es exacto: sólo se desvía el de bytes.
- `MemLiberarUnicode`, cuando el puntero no supera `MemEsValida`, anota
  `ERR_MEMORIA_INVALIDA` y aun así devuelve `1` (éxito). `MemLiberar`, en el
  mismo caso, devuelve `1` sin anotar nada: los dos no se comportan igual.
- `MemValorByte` ya no se declara: su implementación sigue comentada en
  `Memoria.c` porque la firma original (`unsigned long` como dirección) trunca
  punteros en Windows de 64 bits (LLP64). Si se quisiera recuperar, debería
  tomar `uintptr_t` — y además llama a `MemValida`, un nombre que no existe.
- Bajo `MODO_DEPURACION` fuera de Windows se llama a `malloc_usable_size`, que
  se declara en `<malloc.h>`. Hasta el 2026-10-01 esa cabecera no se incluía
  y `Memoria.c` no compilaba en ese modo en Cygwin (declaración implícita, que
  en C23 es error). Ahora se incluye bajo `MODO_DEPURACION` y `!WIN`.
  Comprobado en Cygwin y en Windows puro; en Linux no se ha podido probar.
  El perfil `-Pdebug` **no** define `MODO_DEPURACION`: hay que pasarlo a
  mano.
- El comentario `// TODO: MemValida HEAP` de la cabecera y el `PENDIENTE` sobre
  `HeapWalk` del fuente apuntan a la misma carencia: no hay recorrido del *heap*
  para liberar bloques pendientes.
