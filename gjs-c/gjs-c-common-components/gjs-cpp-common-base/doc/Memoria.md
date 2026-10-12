# Memoria e InfoMemoria

| Dato      | Valor                                          |
| --------- | ---------------------------------------------- |
| Cabeceras | `Memoria.h` (108 líneas), `InfoMemoria.h` (67) |
| Fuentes   | `Memoria.cpp`, `InfoMemoria.cpp`               |
| Espacio   | `org::gjs::cpp::common`                        |
| Funciones | 3 + 5, más macros                              |
| Test      | `MemoriaTest.cpp`                              |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Reserva de memoria y comprobación de punteros, heredadas del stack C. Es la
parte del componente que menos se parece a C++: aquí no hay contenedores ni
punteros inteligentes, sino `MemReservar` y macros.

## `Memoria`

```cpp
void * MemReservar ( int iNumBytes );
int    MemLiberar  ( void ** p_p_vBloque );
void   MemLimpiar  ( void * p_vBloque, int iNumBytes );
```

`MemLiberar` recibe **puntero a puntero** y anula el original, que es el
convenio de todo el stack C: después de liberar, la variable del llamante queda
a `NULL` y no puede quedarse colgando.

Por debajo son `new unsigned char [ n ] ()` y `delete []`, iguales en los tres
modos; el bloque sale a cero. Hasta el 2026-10-12 eran `malloc` / `free` en
POSIX y `HeapAlloc` / `HeapFree` en WIN. Un bloque de `MemReservar` sólo lo
libera `MemLiberar`: ni `free` ni `delete` sin `[]`.

### Los macros de comprobación

`ES_VALIDO` y `ES_NULO` son la pareja que usa todo el stack para comprobar un
puntero antes de tocarlo. Y aquí está lo interesante: **su definición cambia con
el compilador**.

| Modo                | `ES_VALIDO ( p )` comprueba                                   |
| ------------------- | ------------------------------------------------------------- |
| Visual C en Windows | Que no sea nulo **ni ninguno de los cinco valores centinela** |
| Cualquier otro      | Que no sea nulo                                               |

Los centinelas son los que el depurador de Visual C escribe en la memoria para
que salten a la vista:

| Constante                   | Valor        | Significa                  |
| --------------------------- | ------------ | -------------------------- |
| `MEM_DIN_NO_INICIALIZADA`   | `0xCDCDCDCD` | Reservada, sin inicializar |
| `MEM_DIN_NO_INICIALIZADA_2` | `0xBAADF00D` | Idem                       |
| `MEM_DIN_LIBERADA`          | `0xDDDDDDDD` | Ya liberada                |
| `MEM_DIN_LIBERADA_2`        | `0xFEEEFEEE` | Idem                       |
| `MEM_PIL_NO_INICIALIZADA`   | `0xCCCCCCCC` | Pila sin inicializar       |
| `MEM_DIN_MARCA_FIN`         | `0xFDFDFDFD` | Guarda de fin de bloque    |

Más `ES_MANEJADOR` y `ES_PUNTERO`, que distinguen un puntero de un manejador de
Windows por el bit 2.

## `InfoMemoria`

**Toda la cabecera está dentro de `#if ( defined ( MODO_DEPURACION ) )`.** Fuera
de ese modo no declara nada.

| Función                      | Qué da                           |
| ---------------------------- | -------------------------------- |
| `MemReservada ()`            | Bytes reservados y no liberados. |
| `MemNumBloquesReservados ()` | Cuántos se han pedido.           |
| `MemNumBloquesLiberados ()`  | Cuántos se han soltado.          |
| `MemNumBloquesActuales ()`   | Los vivos.                       |
| `MemImprimirInforme ( … )`   | Vuelca el estado.                |

Va de la mano de [Depurador](Depurador.md), que lleva la cuenta por objeto.

## Dependencias

`BaseConfig.h`.

## Test

`MemoriaTest.cpp` → `TestMemoria()`.

## Observaciones

- **`ES_VALIDO` sólo comprueba de verdad con Visual C.** Con GCC —los tres modos
  de compilación reales del stack— se reduce a `p != NULL`, de modo que el
  código escrito confiando en que detecta punteros liberados no lo hace en
  ninguna de las compilaciones que se usan a diario. No es incorrecto: es que la
  protección es de un compilador que aquí no se emplea.
- **Los centinelas son de 32 bits.** `0xCDCDCDCD` comparado contra un puntero de
  64 bits sólo coincide si la mitad alta es cero, y la comparación se hace
  moldeando a `unsigned long`, que en Windows de 64 bits mide 4 bytes y en
  Cygwin 8. El macro, tal cual, no está pensado para 64 bits.
- **`MemReservar` toma un `int`**, no `size_t`: no se puede pedir más de 2 GB, y
  un tamaño calculado que se pase de rango llega negativo.
- **En un componente C++ con `std::string`, `std::vector` y `<format>`, la
  gestión de memoria sigue siendo la de C.** No hay `std::unique_ptr` ni
  `std::make_unique` en toda la cabecera, y el propio componente los necesitaría
  en [Objeto::clonar](Objeto.md), que devuelve un puntero desnudo sin dueño.
- **`MemLimpiar` no dice con qué rellena.** Presumiblemente ceros, pero un
  módulo que ofrece constantes de patrón de memoria podría dejarlo escrito.
- **En `MODO_DEPURACION` ya no se descuentan los bytes liberados**, sólo los
  bloques: de un bloque de `new []` no se puede preguntar el tamaño, que antes
  se sacaba de `malloc_usable_size` o de `HeapSize`. `MODO_DEPURACION` está
  pendiente de revisar entero.
- **`InfoMemoria` desaparece fuera de `MODO_DEPURACION`**, así que el código que
  la use necesita el mismo `#if` alrededor. Es la misma situación de
  [Depurador](Depurador.md).
