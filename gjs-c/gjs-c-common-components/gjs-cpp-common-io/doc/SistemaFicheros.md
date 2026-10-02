# SistemaFicheros

| Dato      | Valor                                             |
| --------- | ------------------------------------------------- |
| Cabecera  | `src/main/include/SistemaFicheros.h` (142 líneas) |
| Fuente    | `SistemaFicheros.cpp` (1.538 líneas)              |
| Espacio   | `org::gjs::cpp::common`                           |
| Prefijo   | `Sis`                                             |
| Funciones | 71, libres — ninguna clase                        |
| Test      | `SistemaFicherosTest.cpp` (664 líneas)            |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Manejo de **rutas y ficheros**, sin relación con el resto del componente: aquí no
hay sockets ni protocolos. Está en `gjs-cpp-common-io` porque es entrada y salida,
y porque [ServidorFTP](FTP.md) y [ServidorHTTP](HTTP.md) lo usan para servir
directorios.

Es la traducción del módulo homónimo de
[gjs-c-common-system](../../gjs-c-common-system/README.md), con `std::string` en
lugar de `char *`.

```cpp
SisComponerRuta ( "/datos", "informe.pdf" );      // "/datos/informe.pdf"
SisFicheroExtension ( "informe.pdf" );            // "pdf"
SisRutaEstiloWindows ( "/c/datos" );              // "c:\datos"
SisExisteDirectorio ( "/datos" );
SisCopiarFichero ( "a.txt", "b.txt" );
```

---

## La API por grupos

| Grupo               | Funciones | Ejemplos                                                                  |
| ------------------- | --------- | ------------------------------------------------------------------------- |
| Validación          | 3         | `SisEsSubdirectorioValido`, `SisEsFicheroValido`                          |
| Partes de una ruta  | 9         | `SisRutaDirectorio`, `SisRutaFichero`, `SisFicheroExtension`              |
| Composición         | 3         | `SisComponerRuta`, `SisComponerRutaExt`, `SisComponerFichero`             |
| Estilos             | 9         | `SisRutaEstiloWindows`, `…EstiloUnix`, `…EstiloCygwin`, `…EstiloSistema`  |
| Absoluta o relativa | 3         | `SisEsRutaAbsoluta`, `SisEsRutaRelativa`, `SisResolverDirectorioRelativo` |
| Directorio actual   | 4         | `SisDirectorioActual`, `SisEstDirectorioActual`                           |
| Existencia          | 4         | `SisExisteFichero`, `SisExisteDirectorio` (+ variantes `Ext`)             |
| Crear               | 4         | `SisCrearFichero`, `SisCrearDirectorio` (+ `Ext`)                         |
| Borrar y vaciar     | 6         | `SisEliminarFichero`, `SisEliminarDirectorio`, `SisVaciarDirectorio`      |
| Copiar y mover      | 4         | `SisCopiarFichero`, `SisMoverFichero` (+ `Ext`)                           |
| Atributos           | 10        | `SisRutaOculta`, `SisRutaDeSoloLectura`, `SisRutaComprimida`              |
| Tipo por extensión  | 7         | `SisEsFicheroC`, `SisEsFicheroXML`, `SisEsFicheroHTML`                    |
| Raíz y separador    | 3         | `SisDirectorioRaiz`, `SisSeparadorRutaFicheros`                           |

### El patrón `Ext`

Casi todas las operaciones sobre ficheros existen dos veces: una que toma **la
ruta entera** y otra acabada en `Ext` que toma **directorio y fichero por
separado**.

```cpp
SisExisteFichero    ( "/datos/informe.pdf" );
SisExisteFicheroExt ( "/datos", "informe.pdf" );
```

La segunda no es más que la primera sobre `SisComponerRuta`. Es cómodo cuando el
directorio viene de un sitio y el nombre de otro, y duplica el tamaño de la API.

### Los cuatro estilos de ruta

Lo más útil del módulo, y lo que justifica que exista habiendo `std::filesystem`:

| Función                | Convierte a                         |
| ---------------------- | ----------------------------------- |
| `SisRutaEstiloWindows` | `c:\datos\fichero.txt`              |
| `SisRutaEstiloUnix`    | `/datos/fichero.txt`                |
| `SisRutaEstiloCygwin`  | `/cygdrive/c/datos/fichero.txt`     |
| `SisRutaEstiloSistema` | El del sistema en el que se compiló |

Es exactamente el problema que tiene este repositorio, con sus tres modos de
compilación, y la razón por la que el módulo se mantiene aparte de la biblioteca
estándar.

---

## Test

`SistemaFicherosTest.cpp` cubre composición, descomposición, estilos,
existencia, creación, copia y borrado, creando y limpiando sus propios ficheros
temporales.

---

## Observaciones

### `SisExisteFichero` pregunta «existe y no es un directorio»

No «existe y es un fichero regular», que es más estricto y es lo que se contestó
por error hasta el 2026-09-20. La diferencia se nota en FIFOs, sockets y
dispositivos: `S_ISREG` / `is_regular_file` dice que no a todos ellos, cuando en
Windows —donde `GetFileAttributes` sólo mira `FILE_ATTRIBUTE_DIRECTORY`— cuentan
como fichero. Ahora las dos ramas y los dos stacks preguntan lo mismo.


- **Los atributos de fichero ya no son cosa sólo de Windows.** Lo eran hasta el
  2026-09-18, cuando se comprobó que la premisa era falsa: **desde un binario
  POSIX de Cygwin la API de Windows contesta perfectamente**, basta traducir la
  ruta con `cygwin_create_path`. Estado actual:

  | Función                             | Cygwin                      | Linux    |
  | ----------------------------------- | --------------------------- | -------- |
  | `SisRutaOculta`                      | el punto inicial del nombre | igual    |
  | `SisRutaDeSoloLectura`               | `access ( W_OK )`           | igual    |
  | `SisRutaDesactivarModoSoloLectura`   | permiso de escritura        | igual    |
  | `SisFicheroEsAccesible`              | `access ( R_OK )`           | igual    |
  | `SisRutaComprimida`                  | `FILE_ATTRIBUTE_COMPRESSED` | contesta *no* |
  | `SisRutaEncriptada`                  | `FILE_ATTRIBUTE_ENCRYPTED`  | contesta *no* |
  | `SisRutaDelSistema`                  | `FILE_ATTRIBUTE_SYSTEM`     | contesta *no* |
  | `SisFicheroEsTemporal`               | `FILE_ATTRIBUTE_TEMPORARY`  | ¿cuelga del directorio temporal? |
  | `SisFicheroAsociadoAAplicacion`      | atributo de Windows         | contesta *no* |
  | `SisFicheroConOptimizacionEspacial`  | atributo de Windows         | contesta *no* |
  | `SisCadenaDirectorioSistema`         | **no se declara** ( sólo WIN ) | **no se declara** |

  Las cuatro primeras **no son atributos de NTFS**: tienen respuesta POSIX de
  toda la vida y por eso valen igual en Linux. Y en Cygwin van por la rama POSIX
  **a propósito**, porque ahí es mejor: medido, `access ( W_OK )` ve tanto el
  atributo de solo lectura de NTFS —que Cygwin refleja en el modo— como un
  `chmod 0444` que no llega a tocar NTFS; el bit de NTFS por sí solo se pierde
  el segundo caso.

  Las otras seis sí son de NTFS. En Cygwin se leen con la API de Windows desde
  `SistemaFicherosWin32`, la única unidad del módulo que incluye `windows.h`.
  Sobre Linux **contestan que no, y eso es una limitación conocida, no un
  descuido** (decidido así el 2026-09-19). No es falta de código: haría falta
  preguntarle al montaje en tiempo de ejecución (`ntfs-3g` los expone como el
  atributo extendido `system.ntfs_attrib`) y sólo valdría sobre montajes NTFS.
  Se deja así a propósito porque **el modo Linux todavía no existe en el build**;
  cuando exista se revisa entero, y con él la cuestión de fondo: que ese `false`
  no distingue "no lo tiene" de "aquí no se puede saber".

  `SisFicheroEsTemporal` es el caso aparte de los seis: en Linux no se queda
  callada, contesta **otra pregunta parecida** —si el fichero cuelga del
  directorio temporal—, que no es lo mismo que el atributo `TEMPORARY` de NTFS.
  Está marcado en el código.

  `SisCadenaDirectorioSistema` ha pasado a ser **sólo WIN** (2026-09-19), como
  `SisRedEnviarMensaje` y `SisTituloProceso`: el "directorio del sistema" es
  `C:\Windows\System32`, un concepto sin equivalente en POSIX, y su gemela del
  stack C, `SisDirectorioSistema`, ya estaba declarada sólo bajo `WIN`. Fuera de
  Windows no se declara, para que quien la llame se encuentre un error de
  compilación en vez de una cadena vacía.

  Un aviso sobre `SisRutaOculta`: en Cygwin conviven **dos** nociones de oculto
  que **no se solapan** —el punto y el atributo de NTFS—, y se elige el punto,
  que es la semántica del modo en que se compila. Medido: un fichero con punto
  delante no queda marcado como oculto en NTFS.
- **`INVALID_FILE_ATTRIBUTES` está redefinido a mano** en `CommonIoConfig.h`, y
  hace falta: en Cygwin de 64 bits `DWORD` es `unsigned long` de 64 bits, así que
  el `(DWORD)-1` de las cabeceras vale `0xFFFFFFFFFFFFFFFF` y no coincide con el
  `0x00000000FFFFFFFF` que devuelve `GetFileAttributes` al fallar. Sin ese
  arreglo, **todas** las funciones de atributos darían el fichero por existente.
  Es el mismo problema de anchura de `DWORD` que hubo en `BaseConfig.h` del
  stack C.
- **Ninguna función distingue «no» de «no se pudo comprobar».** Todas devuelven
  `bool` o cadena vacía: un fichero que no existe y uno al que no se tiene acceso
  dan la misma respuesta, y `SisExisteFichero` sobre una ruta mal formada también.
- **`SisSeparadorRutaFicheros` y `SF_DIR_SEPARADOR` conviven.** La primera es una
  función pública que devuelve el separador; la segunda, una macro interna con el
  mismo valor. Dentro del `.cpp` se usan las dos.
- **`SisMascaraBusquedaEnDirectorio` está en el grupo de borrado**, entre
  `SisEliminarFicheroExt` y `SisEliminarDirectorio`, y no borra nada: compone la
  máscara `*.*`. La colocación en la cabecera despista.
- **Doce funciones de composición y descomposición hacen lo mismo que
  `std::filesystem::path`**, que este mismo componente ya usa en
  [ServidorFTP](FTP.md) y [ServidorHTTP](HTTP.md) para guardar el directorio
  raíz. Conviven dos formas de representar una ruta en el mismo componente. Lo
  que `std::filesystem` **no** da es la conversión entre estilos Windows, Unix y
  Cygwin, que es justo lo que aquí hace falta; el resto sí se podría delegar.
- **La cabecera arrastra los caracteres perdidos** (`U+FFFD`) del bloque de
  comentario original, como varios ficheros del stack C.
- **El comentario de cabecera describe otra cosa.** Dice que el módulo «mantiene
  un objeto global privado de clase `CSistemaFicheros` que puede utilizarse para
  moverse por el árbol de directorios». No hay tal clase ni tal objeto: son 71
  funciones sin estado. El texto viene de la librería de 2008 de la que se
  extrajo.
