# SistemaFicheros y EntradaSalida

| Dato          | Valor                                                 |
| ------------- | ----------------------------------------------------- |
| Módulos       | 2                                                     |
| Cabeceras     | `SistemaFicheros.h`, `EntradaSalida.h`                |
| Fuentes       | `SistemaFicheros.c` (2.710 líneas), `EntradaSalida.c` |
| Prefijo       | `Sis` — **compartido, ver Observaciones**             |
| Funciones     | 75 + 8                                                |
| Incluidos por | `Ficheros.h`                                          |
| Tests         | `SistemaFicherosTest.c`, `EntradaSalidaTest.c`        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La frontera con el sistema operativo. `SistemaFicheros` es el fuente más grande
del stack C (2.710 líneas) y es donde vive toda la diferencia entre Windows y
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
`SisFicheroConOptimizacionEspacial` y otros. Diez en total, y **ya no son cosa
sólo de Windows**: lo eran hasta el 2026-09-18, cuando se comprobó que la
premisa era falsa. **Desde un binario POSIX de Cygwin la API de Windows contesta
perfectamente**, basta traducir la ruta con `cygwin_create_path`; eso lo hace
`SistemaFicherosWin32.c`, la única unidad del módulo que incluye `windows.h`
—y por eso está aparte: `windows.h` y `BaseConfig.h` no caben en la misma unidad
de traducción cuando `WIN` no está definido—.

| Función                             | Cygwin                      | Linux    |
| ----------------------------------- | --------------------------- | -------- |
| `SisRutaOculta`                      | el punto inicial del nombre | igual    |
| `SisRutaDeSoloLectura`               | `access ( W_OK )`           | igual    |
| `SisRutaDesactivarModoSoloLectura`   | permiso de escritura        | igual    |
| `SisFicheroEsAccesible`              | `access ( R_OK )`           | igual    |
| `SisRutaComprimida`                  | `FILE_ATTRIBUTE_COMPRESSED` | contesta *no* |
| `SisRutaEncriptada`                  | `FILE_ATTRIBUTE_ENCRYPTED`  | contesta *no* |
| `SisRutaDelSistema`                  | `FILE_ATTRIBUTE_SYSTEM`     | contesta *no* |
| `SisFicheroEsTemporal`               | `FILE_ATTRIBUTE_TEMPORARY`  | contesta *no* |
| `SisFicheroAsociadoAAplicacion`      | atributo de Windows         | contesta *no* |
| `SisFicheroConOptimizacionEspacial`  | atributo de Windows         | contesta *no* |

Las cuatro primeras **no son atributos de NTFS**: tienen respuesta POSIX de toda
la vida y por eso valen igual en Linux. Y en Cygwin van por la rama POSIX **a
propósito**, porque ahí es mejor: medido, `access ( W_OK )` ve tanto el atributo
de sólo lectura de NTFS —que Cygwin refleja en el modo— como un `chmod 0444` que
no llega a tocar NTFS; el bit de NTFS por sí solo se pierde el segundo caso.

Las otras seis sí son de NTFS. Sobre Linux **contestan que no, y eso es una
limitación conocida, no un descuido** (decidido así el 2026-09-19). No es falta
de código: haría falta preguntarle al montaje en tiempo de ejecución (`ntfs-3g`
los expone como el atributo extendido `system.ntfs_attrib`) y sólo valdría sobre
montajes NTFS. Se deja así a propósito porque **el modo Linux todavía no existe
en el build**; cuando exista se revisa entero, y con él la cuestión de fondo: que
ese 0 no distingue "no lo tiene" de "aquí no se puede saber".

Un aviso sobre `SisRutaOculta`: en Cygwin conviven **dos** nociones de oculto que
**no se solapan** —el punto inicial y el atributo de NTFS—, y se elige el punto.

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

### `SisExisteFichero` pregunta «existe y no es un directorio»

No «existe y es un fichero regular», que es más estricto y es lo que se contestó
por error hasta el 2026-09-20. La diferencia se nota en FIFOs, sockets y
dispositivos: `S_ISREG` / `is_regular_file` dice que no a todos ellos, cuando en
Windows —donde `GetFileAttributes` sólo mira `FILE_ATTRIBUTE_DIRECTORY`— cuentan
como fichero. Ahora las dos ramas y los dos stacks preguntan lo mismo.


- **Los dos módulos comparten el prefijo `Sis`.** Al leer `SisAsincEscribir` no
  hay forma de saber que viene de `EntradaSalida` y no de `SistemaFicheros`. Es
  el mismo problema que `Tiempo` en
  [gjs-c-common-time](../../gjs-c-common-time/doc/TiempoNumerico.md), pero aquí
  con 83 funciones repartidas.
- **`SistemaFicheros.c` concentra 2.710 líneas**, la sexta parte del módulo, y
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
