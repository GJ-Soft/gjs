# gjs-c-common-database

Librería de **entidades** en C del stack GJS: las clases base de los objetos
que se identifican y llevan un contenido colgando, como un cliente, un artículo
o una cuenta. Es la contrapartida en C de
[`gjs-cpp-common-database`](../gjs-cpp-common-database/README.md), y el sitio
donde irá creciendo el soporte de datos del stack.

5 módulos en 4.292 líneas.

---

## Coordenadas Maven

| Dato         | Valor                            |
| ------------ | -------------------------------- |
| `groupId`    | `org.gjsoft.c.common`            |
| `artifactId` | `gjs-c-common-database`          |
| `version`    | `1.0.0`                     |
| `packaging`  | `nar` (biblioteca **shared**)    |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`  |
| Depende de   | `gjs-c-common-types`             |

Las entidades estaban antes en
[`gjs-c-common-types`](../gjs-c-common-types/README.md). Se separaron sin
cambiar su API: un programa que las use sólo tiene que añadir la dependencia e
incluir `TiposBaseDatos.h`.

---

## Uso

La cabecera fachada es `TiposBaseDatos.h`:

```c
#include <Base.h>
#include <TiposBaseDatos.h>

SEntidadNom * p_entnObj = SEntNomCrearLit ( 42, "cliente_a" );

if ( SEntNomEsValida ( p_entnObj ) == 1 )
{
    printf ( "%lu %s\n", SEntNomValorId ( p_entnObj ),
             SEntNomValorNombreLit ( p_entnObj ) );
}
SEntNomDestruir ( &p_entnObj );
```

---

## La idea central: la identidad es el identificador

Hay dos raíces, según cómo se identifique la entidad: `SEntidad`, con un
identificador numérico (la clave técnica), y `SEntidadCod`, con un código de
texto (la clave de negocio). Las demás añaden un nombre o un código a una de las
dos.

En todas, **la identidad es el identificador y nada más**: igualdad, orden y hash
miran sólo el id, y `EsValida` también. Los detalles, y las excepciones, en
[Entidades](doc/Entidades.md).

---

## Convenios

Los del resto del stack. Sufijo `Ext` para la variante que recibe también el
contenido (`SEntCrearExt`, `SEntNomEncapsularExt`…), y `Encapsular` para los
constructores que se quedan con las piezas que reciben.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
los seis módulos anteriores del stack instalados.

---

## Tests

**5 suites**, una por módulo. Sin test sólo la cabecera fachada
(`TiposBaseDatos.h`).

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **De momento sólo trae las entidades.** El equivalente en C++ ya tiene tabla y
  ocurrencia en memoria; aquí están por venir.
- **El desempate de `Comparar` es provisional.** Cuando dos entidades empatan en
  el id, `Comparar` desempata por el nombre o el código, y `EsIgual` no. Ver
  [Entidades](doc/Entidades.md#identidad).
- **`TiposBaseDatosConfig.h` vive en el árbol de fuentes** y no se publica en el
  NAR `noarch`. Hoy sólo incluye las fachadas de los módulos de los que depende.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
