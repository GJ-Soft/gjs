# SBuffer

| Dato         | Valor                                   |
| ------------ | --------------------------------------- |
| Cabecera     | `src/main/include/SBuffer.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SBuffer.c` |
| Prefijo      | `SBuf`                                  |
| Struct       | `SBuffer`                               |
| Funciones    | 17                                      |
| Incluido por | `Tipos.h`                               |
| Test         | `SBufferTest.c` → `TestSBuffer()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Búfer de bytes **redimensionable**. Donde [SBloque](SBloque.md) es un bloque de
tamaño fijo pensado para envolver un valor, `SBuffer` está pensado para
acumular: puede crecer y encoger conservando el contenido.

Es la base de [SDatos](SDatos.md), que le añade una API orientada a contenido.

## Modelo de datos

```c
typedef struct
{
    byte *          p_byContenido;
    unsigned long   ulTam;
} SBuffer;
```

A diferencia de `SBloque`, **no lleva bandera de propiedad**: el búfer siempre es
dueño de su contenido.

Los tamaños se manejan como `unsigned long`, no como `int`.

## API

| Función                                                                                                    | Descripción                                      |
| ---------------------------------------------------------------------------------------------------------- | ------------------------------------------------ |
| `SBuffer * SBufCrear ( unsigned long ulTam )`                                                              | Crea el búfer con el tamaño dado.                |
| `void SBufDestruir ( SBuffer ** )`                                                                         | Destruye el búfer y anula el puntero.            |
| `int SBufEsValido ( SBuffer * )`                                                                           | 1 si es utilizable.                              |
| `unsigned long SBufTam ( SBuffer * )`                                                                      | Tamaño actual.                                   |
| `byte * SBufDireccion ( SBuffer * )`                                                                       | Puntero interno al contenido (no liberar).       |
| `byte SBufLeer ( SBuffer *, unsigned long ulPos )`                                                         | Lee un byte.                                     |
| `int SBufLeerBuffer ( SBuffer *, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )`     | Lee un tramo.                                    |
| `int SBufEscribir ( SBuffer *, unsigned long ulPos, byte byValor )`                                        | Escribe un byte.                                 |
| `int SBufEscribirBuffer ( SBuffer *, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )` | Escribe un tramo.                                |
| `byte * SBufDuplicarValor ( SBuffer * )`                                                                   | Copia del contenido completo. **Reserva.**       |
| `byte * SBufDuplicarContenido ( SBuffer *, unsigned long ulPos, unsigned long ulTam )`                     | Copia de un tramo. **Reserva.**                  |
| `char * SBufDuplicarCadena ( SBuffer * )`                                                                  | Copia del contenido como cadena. **Reserva.**    |
| `int SBufLimpiar ( SBuffer * )`                                                                            | Pone el contenido a cero.                        |
| `unsigned long SBufPosicionPrimerNulo ( SBuffer * )`                                                       | Posición del primer byte a cero.                 |
| `int SBufInicializar ( SBuffer *, unsigned long ulTam )`                                                   | Reinicia el búfer al tamaño dado.                |
| `int SBufRedimensionar ( SBuffer *, unsigned long ulTam, int iConservarCont )`                             | Cambia el tamaño, conservando o no el contenido. |
| `unsigned int SBufHash ( SBuffer * )`                                                                      | Hash del contenido.                              |

## Comportamiento

`SBufRedimensionar` toma `iConservarCont` como bandera: con 1 mantiene los bytes
que quepan en el nuevo tamaño; con 0 el contenido queda indefinido o a cero.

`SBufPosicionPrimerNulo` es lo que permite tratar el búfer como cadena sin
recorrerlo a mano; lo usa `SBufDuplicarCadena`.

Los límites de tamaño están en `TiposBasicosConstantes.h`:
`BUF_TAM_DEFECTO` (256) y `BUF_MAX_TAM` (268.435.456, o sea 256 MB).

`SBufDireccion` devuelve el puntero **interno**: deja de ser válido tras un
`SBufRedimensionar`, que puede mover el bloque.

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`SBufferTest.c` → `TestSBuffer()`.

## Observaciones

- Es el único módulo de la librería que dimensiona con `unsigned long` en lugar
  de `int`. Eso lo hace sensible al modelo de datos: en Cygwin y Linux
  (LP64) `unsigned long` son 64 bits, pero en Windows puro (LLP64) son 32. Un
  búfer no puede superar los 4 GB en Windows aunque `BUF_MAX_TAM` sea mucho
  menor, así que en la práctica no se nota.
- No hay bandera de propiedad: no se puede envolver memoria ajena como sí permite
  `SBlqAsignar`. Si hace falta eso, el módulo adecuado es [SBloque](SBloque.md).
- Tras `SBufRedimensionar` hay que volver a pedir `SBufDireccion`: cualquier
  puntero anterior queda colgando.
