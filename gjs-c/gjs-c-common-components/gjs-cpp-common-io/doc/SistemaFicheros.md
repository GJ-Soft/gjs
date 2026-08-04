# SistemaFicheros

| Dato      | Valor                                             |
| --------- | ------------------------------------------------- |
| Cabecera  | `src/main/include/SistemaFicheros.h` (137 líneas) |
| Fuente    | `SistemaFicheros.cpp` (1.444 líneas)              |
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

- **Los atributos de fichero sólo existen en Windows.** Hay ocho marcas
  `// PENDIENTE` en el fuente, repartidas en **siete funciones** cuya rama POSIX
  está vacía y **devuelve `false` sin avisar**:

  | Función                             | En Windows                  | En POSIX |
  | ----------------------------------- | --------------------------- | -------- |
  | `SisRutaComprimida`                 | `FILE_ATTRIBUTE_COMPRESSED` | `false`  |
  | `SisRutaEncriptada`                 | `FILE_ATTRIBUTE_ENCRYPTED`  | `false`  |
  | `SisRutaOculta`                     | `FILE_ATTRIBUTE_HIDDEN`     | `false`  |
  | `SisRutaDelSistema`                 | `FILE_ATTRIBUTE_SYSTEM`     | `false`  |
  | `SisFicheroAsociadoAAplicacion`     | atributo de Windows         | `false`  |
  | `SisFicheroConOptimizacionEspacial` | atributo de Windows         | `false`  |
  | `SisCadenaDirectorioSistema`        | implementada                | vacía    |

  De ellas, `SisRutaOculta` es la que más duele: en POSIX un fichero oculto es
  simplemente uno cuyo nombre empieza por punto, así que la rama que falta es una
  línea. **Compilando en modo Cygwin POSIX —el modo por defecto— estas siete
  funciones mienten.** `SisRutaDeSoloLectura`, en cambio, sí está resuelta en los
  dos sistemas.
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
