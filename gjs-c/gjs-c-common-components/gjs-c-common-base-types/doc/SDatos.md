# SDatos

| Dato         | Valor                                  |
| ------------ | -------------------------------------- |
| Cabecera     | `src/main/include/SDatos.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SDatos.c` |
| Prefijo      | `SDat`                                 |
| Struct       | `SDatos`                               |
| Funciones    | 30                                     |
| Incluido por | `Tipos.h`                              |
| Test         | `SDatosTest.c` → `TestSDatos()`        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Envoltorio de alto nivel sobre [SBuffer](SBuffer.md) para manejar contenido
binario: asignar, extraer trozos, volcar a hexadecimal e imprimir. Es la
estructura que usan las capas superiores cuando manejan "un dato" de tamaño
variable sin querer saber cómo está reservado.

## Modelo de datos

```c
typedef struct
{
    SBuffer * p_bufDatos;
} SDatos;
```

Una única indirección: `SDatos` delega todo el almacenamiento en su `SBuffer`.

## API

### Ciclo de vida

| Función                                                            | Descripción                                     |
| ------------------------------------------------------------------ | ----------------------------------------------- |
| `SDatos * SDatCrear ( int iTam )`                                  | Crea el dato con el tamaño indicado.            |
| `void SDatDestruir ( SDatos ** )`                                  | Destruye el dato y anula el puntero.            |
| `int SDatEsValido ( SDatos * )`                                    | 1 si es utilizable.                             |
| `int SDatInicializar ( SDatos *, int iTam )`                       | Reinicia al tamaño dado.                        |
| `int SDatRedimensionar ( SDatos *, int iTam, int iConservarCont )` | Cambia el tamaño.                               |
| `void SDatLimpiar ( SDatos * )`                                    | Pone el contenido a cero.                       |
| `void SDatLiberar ( SDatos * )`                                    | Libera el contenido sin destruir la estructura. |
| `SDatos * SDatDuplicar ( SDatos * )`                               | Copia independiente.                            |

### Acceso

| Función                                                              | Descripción                       |
| -------------------------------------------------------------------- | --------------------------------- |
| `byte SDatByte ( SDatos *, int iPos )`                               | Lee un byte.                      |
| `int SDatEstablecerByte ( SDatos *, int iPos, byte )`                | Escribe un byte.                  |
| `byte * SDatContenido ( SDatos * )`                                  | Puntero interno (no liberar).     |
| `byte * SDatContenidoEnPos ( SDatos *, int iPos, int iTam )`         | Puntero interno desplazado.       |
| `byte * SDatDuplicarContenido ( SDatos * )`                          | Copia del contenido. **Reserva.** |
| `byte * SDatDuplicarContenidoEnPos ( SDatos *, int iPos, int iTam )` | Copia de un tramo. **Reserva.**   |
| `int SDatTam ( SDatos * )`                                           | Tamaño actual.                    |
| `int SDatPosicionPrimerNulo ( SDatos * )`                            | Posición del primer byte a cero.  |

### Asignación y copia

| Función                                                                  | Descripción                    |
| ------------------------------------------------------------------------ | ------------------------------ |
| `int SDatAsignarContenido ( SDatos *, byte *, int iTam )`                | Copia memoria externa al dato. |
| `int SDatAsignarContenidoEnPos ( SDatos *, int iPos, byte *, int iTam )` | Ídem en una posición.          |
| `int SDatAsignar ( SDatos *, SDatos * )`                                 | Asigna desde otro dato.        |
| `int SDatCopiar ( SDatos *, SDatos * )`                                  | Copia desde otro dato.         |
| `int SDatCopiarEnPos ( SDatos *, int iPos, SDatos * )`                   | Ídem en una posición.          |

### Extracción

| Función                                                          | Descripción                            |
| ---------------------------------------------------------------- | -------------------------------------- |
| `SDatos * SDatExtraer ( SDatos *, int iTam )`                    | Primeros `iTam` bytes como dato nuevo. |
| `SDatos * SDatExtraerEnPos ( SDatos *, int iPos, int iTam )`     | Tramo como dato nuevo.                 |
| `char * SDatExtraerCadena ( SDatos *, int iTam )`                | Tramo como cadena. **Reserva.**        |
| `char * SDatExtraerCadenaEnPos ( SDatos *, int iPos, int iTam )` | Ídem desde una posición.               |
| `SDatos * SDatExtraerHastaNulo ( SDatos *, int iIncluirNulo )`   | Hasta el primer byte a cero.           |

### Hexadecimal y diagnóstico

| Función                                                      | Descripción                            |
| ------------------------------------------------------------ | -------------------------------------- |
| `char * SDatCadenaHex ( SDatos * )`                          | Contenido en hexadecimal. **Reserva.** |
| `int SDatAsignarCadenaHex ( SDatos *, const char * p_cHex )` | Asigna desde hexadecimal.              |
| `void SDatImprimir ( SDatos * )`                             | Vuelca el contenido por consola.       |
| `unsigned int SDatHash ( SDatos * )`                         | Hash del contenido.                    |

## Comportamiento

Toda función que devuelve `SDatos *` o `char *` **reserva memoria** que pertenece
al llamante. Las que devuelven `byte *` sin "Duplicar" en el nombre
(`SDatContenido`, `SDatContenidoEnPos`) devuelven punteros internos que no hay
que liberar y que caducan al redimensionar.

La pareja `SDatCadenaHex` / `SDatAsignarCadenaHex` permite serializar el
contenido a texto y recuperarlo, lo que hace este módulo cómodo para volcar
datos binarios en trazas o ficheros de configuración.

`SDatExtraerHastaNulo` con `iIncluirNulo` a 1 incluye el terminador en el
resultado; con 0 lo deja fuera.

Los tamaños por defecto están en `TiposBasicosConstantes.h`:
`DAT_TAM_INICIAL_DEF` y `DAT_TAM_BLOQUE_DEF`, ambos 256.

## Dependencias

- [SBuffer](SBuffer.md) — todo el almacenamiento.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`SDatosTest.c` → `TestSDatos()`.

## Observaciones

- `SDatos` dimensiona con `int` mientras que el `SBuffer` que tiene debajo lo
  hace con `unsigned long`. La conversión es implícita en cada llamada, así que
  un dato no puede pasar de `INT_MAX` aunque el búfer sí podría.
- `SDatLiberar` deja la estructura viva con el contenido liberado. Conviene
  llamar a `SDatInicializar` antes de volver a usarla; el módulo no impide leer
  de un dato liberado.
- La distinción entre `SDatAsignar` y `SDatCopiar` no se aprecia en la cabecera:
  ambas toman otro `SDatos`. Al usarlas conviene mirar la implementación para
  saber cuál redimensiona el destino y cuál exige que ya tenga tamaño.
