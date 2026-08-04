# SistemaFicheros y EntradaSalida

| Dato          | Valor                                                 |
| ------------- | ----------------------------------------------------- |
| Módulos       | 2                                                     |
| Cabeceras     | `SistemaFicheros.h`, `EntradaSalida.h`                |
| Fuentes       | `SistemaFicheros.c` (2.703 líneas), `EntradaSalida.c` |
| Prefijo       | `Sis` — **compartido, ver Observaciones**             |
| Funciones     | 75 + 8                                                |
| Incluidos por | `Ficheros.h`                                          |
| Tests         | `SistemaFicherosTest.c`, `EntradaSalidaTest.c`        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La frontera con el sistema operativo. `SistemaFicheros` es el fuente más grande
del stack C (2.703 líneas) y es donde vive toda la diferencia entre Windows y
POSIX: crear y borrar ficheros, consultar atributos, recorrer directorios y
componer rutas.

`EntradaSalida` cubre la otra mitad: los descriptores estándar y la escritura
asíncrona a consola.

## `SistemaFicheros`

### Existencia y ciclo de vida

| Familia    | Funciones                                                                                          |
| ---------- | -------------------------------------------------------------------------------------------------- |
| Existencia | `SisExisteFichero`, `SisExisteFicheroExt`, `SisExisteDirectorio`, `SisExisteDirectorioExt`         |
| Creación   | `SisCrearFichero`, `SisCrearFicheroExt`, `SisCrearDirectorio`, `SisCrearDirectorioExt`             |
| Borrado    | `SisEliminarFichero`, `SisEliminarFicheroExt`, `SisEliminarDirectorio`, `SisEliminarDirectorioExt` |

El sufijo `Ext` separa la ruta en directorio y nombre en lugar de recibirla
entera.

### Rutas

Diecisiete funciones `SisRuta…`: `SisRutaDirectorio`, `SisRutaFichero`,
`SisRutaAbsoluta`, `SisRutaComprimida`, `SisRutaDeSoloLectura`,
`SisRutaDelSistema`, `SisRutaDesactivarModoSoloLectura` y demás, más
`SisComponerRuta`, `SisComponerRutaExt` y `SisComponerFichero`.

### Clasificación de ficheros

Quince predicados `SisEs…`, entre ellos `SisEsDirectorioValido`,
`SisEsDirectorioValidoSistema`, `SisEsFicheroC` y `SisEsFicheroCabeceraC`. Estos
dos últimos son llamativos: la librería sabe reconocer un fuente C y una
cabecera C, presumiblemente por extensión.

### Directorios

`SisDirectorioActual`, `SisDirectorioRaiz`, `SisDirectorioRaizExt`,
`SisDirectorioNumSubdirectorios`, más `SisCadenaDirectorioSistema` y
`SisCadenaDirectorioFuentes`.

### Atributos de fichero

`SisFicheroEsAccesible`, `SisFicheroAsociadoAAplicacion`,
`SisFicheroConOptimizacionEspacial` y otros.

## `EntradaSalida`

Ocho funciones sobre descriptores y consola:

| Función                                                            | Descripción                                                          |
| ------------------------------------------------------------------ | -------------------------------------------------------------------- |
| `int SisEstadoDescriptor ( int iDescriptor )`                      | 0 = cerrado, 1 = abierto pero redirigido, 2 = abierto y es terminal. |
| `int SisObtenerDescriptor ( FILE * p_fObj )`                       | Descriptor de un `FILE *`.                                           |
| `int SisAsincEscribir ( int iDescriptor, const char * )`           | Escritura asíncrona a un descriptor.                                 |
| `int SisAsincEscribirConFormato ( int, const char *, … )`          | Ídem con formato.                                                    |
| `int SisAsincEscribirConFormatoExt ( int, const char *, va_list )` | Ídem con `va_list`.                                                  |
| `int SisConAsincEscribir ( const char * )`                         | Escritura asíncrona a consola.                                       |
| `int SisConAsincEscribirConFormato ( const char *, … )`            | Ídem con formato.                                                    |
| `int SisConAsincEscribirConFormatoExt ( const char *, va_list )`   | Ídem con `va_list`.                                                  |

`SisEstadoDescriptor` es la función que permite saber **si la salida es un
terminal o está redirigida**, que es lo que decide si tiene sentido emitir
colores ANSI o barras de progreso.

## Dependencias

- `FicherosConfig.h` — las cabeceras del sistema por entorno.
- [gjs-c-common-text](../../gjs-c-common-text/README.md) — manipulación de
  rutas como texto.

## Tests

`SistemaFicherosTest.c` → `TestSistemaFicheros()`,
`EntradaSalidaTest.c` → `TestEntradaSalida()`.

## Observaciones

- **Los dos módulos comparten el prefijo `Sis`.** Al leer `SisAsincEscribir` no
  hay forma de saber que viene de `EntradaSalida` y no de `SistemaFicheros`. Es
  el mismo problema que `Tiempo` en
  [gjs-c-common-time](../../gjs-c-common-time/doc/TiempoNumerico.md), pero aquí
  con 83 funciones repartidas.
- **`SistemaFicheros.c` concentra 2.703 líneas**, la sexta parte del módulo, y
  es donde se resuelve toda la divergencia Windows/POSIX. Es el punto más
  sensible al modo de compilación de todo el stack.
- `SisEsFicheroC` y `SisEsFicheroCabeceraC` meten conocimiento del lenguaje C en
  una capa de sistema de ficheros. Con `ExtensionesFicheros.h` disponible, la
  clasificación por extensión podría hacerse fuera.
- La escritura "asíncrona" no se explica en la cabecera: no queda claro si
  significa sin búfer, no bloqueante, o simplemente saltándose `stdio`.
- `SisDirectorioActual` está señalada en las notas del proyecto como una de las
  funciones que difieren entre modos: usa `GetCurrentDirectory` en Windows y
  `getcwd` en POSIX.
