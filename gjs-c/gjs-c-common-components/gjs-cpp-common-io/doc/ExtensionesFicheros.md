# ExtensionesFicheros

| Dato       | Valor                                                   |
| ---------- | ------------------------------------------------------- |
| Cabecera   | `src/main/include/ExtensionesFicheros.h` (3.459 líneas) |
| Fuente     | — (sólo macros)                                         |
| Contenido  | **31 macros vivas** y 2.667 comentadas                  |
| La incluye | `CppCommonIo.h` y `CommonIoConfig.h`                    |
| La usa     | `SistemaFicheros.cpp`                                   |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un catálogo de extensiones de fichero como constantes, para que
[SistemaFicheros](SistemaFicheros.md) pueda preguntar por el tipo de un fichero
sin literales sueltos:

```cpp
bool SisEsFicheroCabeceraC ( const string & sRuta )
{
    string sExt = SisFicheroExtension ( sRuta );
    return ( sExt == EXT_FIC_CABECERA_C );      // "h"
}
```

Es el fichero más largo del componente y el que menos aporta.

---

## Las 31 macros vivas

| Grupo         | Macros                                                                                                                          |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| Genéricas     | `EXT_FIC_TEXTO`, `EXT_FIC_BINARIO`                                                                                              |
| Código C/C++  | `EXT_FIC_CABECERA_C`, `EXT_FIC_CODIGO_C`, `…_C_2`, `…_C_3`, `…_C_4`                                                             |
| Otros códigos | `EXT_FIC_VISUAL_BASIC`, `EXT_FIC_CSHARP`, `EXT_FIC_INTERFAZ`                                                                    |
| Marcado       | `EXT_FIC_XML`, `EXT_FIC_HTML`, `EXT_FIC_HTML_2`                                                                                 |
| Fuentes       | `EXT_FIC_FUENTE_TRUE_TYPE`, `EXT_FIC_FUENTE_BITMAP`                                                                             |
| Gráficos      | `EXT_FIC_GRAFICO_BITMAP`, `…_BITMAP_2`, `EXT_FIC_RASTER_SUN`, `EXT_FIC_GEORREF_RASTER_SUN`                                      |
| Cartografía   | `EXT_FIC_SHAPE`, `EXT_FIC_INDICE_SHAPE`, `EXT_FIC_LOCALIZACION_SHAPE`, `EXT_FIC_INFO_SHAPE`, `EXT_FIC_ARCVIEW`, `EXT_FIC_DBASE` |
| Datos         | `EXT_FIC_INFO_TABLA`, `EXT_FIC_GENERADOR_ID`                                                                                    |
| Servicio      | `EXT_FIC_COPIA_SEG`, `EXT_FIC_LOG`, `EXT_FIC_ERROR`, `EXT_FIC_GZIP`                                                             |

Llama la atención el peso de la cartografía —seis de las treinta y una son de
*shapefiles* de ESRI—, herencia de la librería de la que se extrajo el módulo.

De las 31, [SistemaFicheros](SistemaFicheros.md) usa **diez**, en las siete
funciones `SisEsFichero*`. Las otras veintiuna están publicadas y no las consume
nadie dentro del componente.

---

## El bloque comentado

Y aquí está lo que hay que saber del fichero:

```
  linea    1 ─┐
              │  cabecera de comentario y guarda de inclusion
  linea   26 ─┤
              │  31 #define utiles                     <- lo unico vivo
  linea   73 ─┤
  linea   74 ─┤  /*                                    <- se abre el comentario
              │
              │  2.667 lineas de la forma
              │      #define EXT_FIC_    "af2" // Flowchart (ABC FlowCharter 2.0)
              │      #define EXT_FIC_    "aff" // AnyForm Form file
              │      ...
              │
  linea 3454 ─┤  */                                    <- se cierra
  linea 3456 ─┤  #define FORM_FIC( ext )  "%s.ext"
  linea 3459 ─┘  #endif
```

**De las 3.459 líneas, 3.381 están dentro de un único bloque `/* … */`**: el
98 % del fichero no llega al compilador. Comprobado con el preprocesador: `g++ -E
-dM` sobre la cabecera devuelve 31 macros, y `EXT_FIC_` sin sufijo **no queda
definida**.

Está comentado por una razón que se ve al mirar el contenido: **todas esas
definiciones se llaman igual**. El nombre es `EXT_FIC_` a secas, sin sufijo que
las distinga, así que si el bloque se descomentara serían 2.667 redefiniciones
consecutivas de la misma macro —2.666 avisos de compilación en cada unidad que
incluya la fachada— y sólo sobreviviría la última, `"~mn"`. El catálogo no se
puede aprovechar tal cual: hay que darle nombre a cada entrada, o convertirlo en
una tabla de datos en vez de en macros.

Hay además restos de un volcado mal cortado. Una entrada dice:

```cpp
#define EXT_FIC_    "egistration .ais" // Array of Intensity Samples graphics (Xerox)
```

donde la línea anterior es `"air" // Automatic Image` — la descripción
«Automatic Image Registration» se partió en dos y la `R` se quedó en el corte.

---

## Observaciones

- **El coste real es cero y el coste aparente no.** Al estar comentado, el bloque
  no define nada ni ralentiza de forma apreciable la compilación, pero **son
  3.459 líneas que el `nar-maven-plugin` copia al `nar` publicado** y que
  cualquiera que abra la cabecera tiene que atravesar para encontrar las 31
  líneas útiles.
- **`FORM_FIC` no funciona.** La última línea viva del fichero es:

  ```cpp
  #define FORM_FIC( ext )     "%s.ext"
  ```

  El parámetro `ext` no se usa: `.ext` es texto literal dentro de la cadena, no
  una sustitución. `FORM_FIC( "pdf" )` da `"%s.ext"`, no `"%s.pdf"`. Para
  concatenar el parámetro haría falta el operador de cadena (`"%s." #ext`). No la
  usa nadie en el componente, así que el fallo no se ha notado.
- **No es una cabecera de entrada y salida.** Como
  [SistemaFicheros](SistemaFicheros.md), está en este componente por afinidad
  temática. La versión C la tiene en `gjs-c-common-system`.
- **Las tres decisiones posibles**, por si se retoma:
  1. **Borrar el bloque** y quedarse con las 31 macros: el fichero pasa de 3.459
     líneas a 78 y no cambia nada de lo que compila hoy.
  2. **Recuperarlo con nombres**, que son 2.667 nombres que inventar.
  3. **Convertirlo en datos** —un `map` de extensión a descripción, o un fichero
     de recursos— que es lo que el contenido pide: es un catálogo, no un juego de
     constantes de compilación.

  La primera es la única que no cuesta trabajo, y deja el repositorio igual de
  capaz que ahora.
