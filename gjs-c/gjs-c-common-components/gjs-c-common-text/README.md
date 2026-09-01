# gjs-c-common-text

Librería de **cadenas y texto** en C del stack GJS. Se apoya en
[`gjs-c-common-base`](../gjs-c-common-base/README.md) y
[`gjs-c-common-base-types`](../gjs-c-common-base-types/README.md), y aporta desde
las rutinas sueltas sobre `char *` hasta objetos de texto con cursor, tokens,
patrones y expresiones regulares.

18 módulos en 20.967 líneas, de las cuales sólo 2.522 son cabeceras: el grueso
está en tres implementaciones muy densas (`Cadenas.c`, `SCadena.c`,
`SCadenaConv.c`).

---

## Coordenadas Maven

| Dato         | Valor                                          |
| ------------ | ---------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                             |
| `artifactId` | `gjs-c-common-text`                            |
| `version`    | `1.0.0-RC.2`                                   |
| `packaging`  | `nar` (biblioteca **shared**)                  |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`                   |
| Depende de   | `gjs-c-common-base`, `gjs-c-common-base-types` |

---

## Uso

La cabecera fachada es `Texto.h`:

```c
#include <Base.h>
#include <Texto.h>
```

Arrastra 19 cabeceras. Quedan fuera y hay que incluirlas a mano:
`ASCIIOEM850.h`, `PaginasCodigos.h` y `TiposCaracter.h`.

```c
SCadena * p_cadObj = SCadGenerar ( "Hola mundo" );

if ( SCadNumPalabras ( p_cadObj ) == 2 )
{
    SCadConvertirAMayusculas ( p_cadObj );
    printf ( "%s\n", SCadValorConstante ( p_cadObj ) );
}
SCadDestruir ( &p_cadObj );
```

---

## Las dos formas de trabajar

El módulo ofrece la misma funcionalidad por dos vías, y conviene elegir una:

| Vía                        | Qué es                                                                    | Módulo                    |
| -------------------------- | ------------------------------------------------------------------------- | ------------------------- |
| **Rutinas sobre `char *`** | Funciones sueltas que reciben y devuelven cadenas de C                    | [Cadenas](doc/Cadenas.md) |
| **Objeto cadena**          | Una `struct` con tamaño máximo, sensibilidad a mayúsculas y ciclo de vida | [SCadena](doc/SCadena.md) |

La primera no reserva estado; la segunda evita tener que ir pasando longitudes.
`SCadena` está implementada sobre `Cadenas`, así que el comportamiento coincide.

### El sufijo `Ext`

En [Cadenas](doc/Cadenas.md), casi todas las rutinas vienen por duplicado:

```c
int CadCopiar    ( char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadCopiarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
```

La variante `Ext` recibe **las longitudes máximas** de las cadenas implicadas.
La forma corta usa el tope global `CAD_MAX_TAM`. En código nuevo conviene usar
siempre `Ext`: es la única que acota de verdad.

En los objetos `S*` el sufijo tiene otro significado —suele ser un parámetro
extra de la operación— y el que indica el tipo del argumento es otro:
`…Cad` para `SCadena *` y `…Lit` o `…Literal` para `const char *`.

---

## Los campos con regla de contenido

Sobre `SCadena` hay una segunda familia: una cadena acotada **con una función de
validación asociada**.

```
  SCampo ( SCadena + PFUNINTPCAD )
     │
     ├── SCodigo       SCadEsCodigoValido       alfanumérico, empieza por letra
     ├── SNombre       SCadEsNombreValido       sin blancos, ASCII imprimible
     └── SDescripcion  SCadEsDescripcionValida  sólo imprimible; puede ser vacía
```

Las tres reglas están escritas en un único sitio,
[ValidacionCadenas](doc/ValidacionCadenas.md), y [SCampo](doc/SCampo.md) admite
cualquier otra `int f ( SCadena * )`.

```c
SCodigo * p_codObj = SCodCrearValorLit ( "IMP_TOTAL" );   /* válido   */
SCodigo * p_codMal = SCodCrearValorLit ( "1IMPORTE" );    /* NULL     */

SCodDestruir ( &p_codObj );
```

Los tres módulos derivados son idénticos entre sí salvo por la validación, el
tope por defecto y el prefijo. Quien no necesite el etiquetado puede usar
`SCampo` directamente.

### Establecer no es validar

`SCampEstablecer` **establece siempre lo que le quepa**, y su retorno responde a
"¿es válido lo que hay ahora dentro?":

| Retorno | Situación                                            |
| ------- | ---------------------------------------------------- |
| `1`     | El valor entra y es válido.                          |
| `0`     | El valor entra pero **no** es válido.                |
| `0`     | El valor **no** entra: excede el tope. Queda el anterior. |

Así un campo puede sostener a propósito un dato a medio corregir, y
`SCampEsValido` —o `SCodEsValido`, `SNomEsValido`, `SDescEsValida`— responde por
él en cualquier momento. Para rechazar de entrada, la validación está suelta en
[ValidacionCadenas](doc/ValidacionCadenas.md) y se puede llamar antes.

---

## Convenios

Se heredan los de las librerías de las que depende: patrón de objeto
`SXxxCrear` / `SXxxDestruir ( S** )` / `SXxxEsValido`, predicados que devuelven
`1`/`0`, memoria vía `MemReservar` / `MemLiberar` y errores en el estado global
(`ERROR_ESTABLECER`).

Constantes propias en `TextoConstantes.h`:

| Constante                                 | Valor                         | Qué acota                           |
| ----------------------------------------- | ----------------------------- | ----------------------------------- |
| `CAD_TAM_DEFECTO`                         | `CAD_BASE_TAM_DEFECTO` (1023) | Tamaño por defecto                  |
| `CAD_MAX_TAM`                             | `CAD_BASE_MAX_TAM` (8191)     | Tope absoluto                       |
| `CAD_NUM_TAM_DEFECTO`                     | 3                             | Cadena numérica                     |
| `COD_MAX_TAM_DEF`                         | 10                            | [SCodigo](doc/SCodigo.md)           |
| `NOM_MAX_TAM_DEF`                         | 35                            | [SNombre](doc/SNombre.md), [SCampo](doc/SCampo.md) |
| `DESC_MAX_TAM_DEF`                        | 255                           | [SDescripcion](doc/SDescripcion.md) |
| `TXT_ALIN_IZQUIERDA` / `TXT_ALIN_DERECHA` | 0 / 1                         | Alineación                          |

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
tener instalados antes `gjs-c-common-base` y `gjs-c-common-base-types`.

**Verificado** en el modo normal (Cygwin POSIX, `mvn clean install`):
`BUILD SUCCESS`, 15 suites, 0 KO, `Resultado global: OK`. Las tres suites
añadidas después (`ValidacionCadenas`, `SCampo`, `SCodigo`) están **pendientes de
pasar por `mvn`**: se han verificado con un `gcc` directo sobre las 18 suites.

---

## Tests

Mismo arnés que el resto del stack: **18 suites** registradas en
`src/test/c/.../Test.c`.

```
mvn test
Test.exe SCadenaTest
```

Sin test asociado: las cabeceras sin fuente (`ASCIIOEM850`, `JuegosCaracteres`,
`PaginasCodigos`, `Texto`, `TextoConstantes`).

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`JuegosCaracteres.h` está duplicado con `gjs-c-common-base`.** Los dos
  ficheros comparten el mismo guard `_ORG_GJS_C_CC_JUEGOSCARACTERES_H` y su
  contenido es equivalente, así que el segundo en incluirse se expande a nada.
  Hoy es inocuo, pero son dos copias que pueden divergir.
- **`TextoConfig.h` hace `#include <Tipos.h>`**, y hay **dos `Tipos.h`** en el
  stack (el catálogo de tipos de `gjs-c-common-base` y la fachada de
  `gjs-c-common-base-types`). Cuál se coge depende del orden de los `-I`. Ver
  [gjs-c-common-base-types](../gjs-c-common-base-types/doc/MODULOS.md#tiposh).
- `TextoConfig.h` vive en el árbol de **fuentes**, no en `src/main/include`, así
  que no se publica en el NAR `noarch`.
- **El condicional de página de códigos de `ASCII.h` es inerte**: las dos ramas
  del `#ifdef OEM850` incluyen el mismo fichero. Ver [ASCII](doc/ASCII.md).
- **`SLinea` y `STexto` mezclan dos prefijos** (`SLin`/`Lin` y `STxt`/`Txt`),
  con dos convenios de nombres de parámetro distintos dentro del mismo fichero.
- **`SCadVaciar` no vacía: libera.** Deja `p_cValor` a `NULL` y `iMaxTam` a 0, y
  quien la llame pierde el tope. Es lo que le pasa a
  [SToken](doc/SToken.md) en `STokEstablecer…`, que redimensiona el token al
  último valor asignado. `SCadLimpiar` es la que conserva la capacidad.
- **La comparación con nulo no es uniforme.** Los predicados `…Es…` devuelven
  `0` ante un nulo, sin distinguir; las funciones `…Comparar…` lo tratan como un
  valor (válido > nulo, nulo == nulo).
- **`ExpRegSeCumple` con el patrón `*` a secas devuelve `0`** en lugar de casar
  con cualquier cadena. El caso 1 de `ExpRegSeCumple 03` falla por eso. Es
  anterior a la familia de campos y sigue abierto.
- `STexto` incluye funciones de **lectura y escritura de ficheros**
  (`TxtCargarFichero`, `TxtSalvarFichero`) pese a que el módulo no depende de
  `gjs-c-common-io`. Ver [STexto](doc/STexto.md).
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
