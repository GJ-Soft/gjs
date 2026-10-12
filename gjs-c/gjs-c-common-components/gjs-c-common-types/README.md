# gjs-c-common-types

Librería de **tipos de aplicación** en C del stack GJS. Donde
[`gjs-c-common-base-types`](../gjs-c-common-base-types/README.md) aporta
estructuras de datos genéricas, este módulo aporta los conceptos con los que se
escribe una aplicación: valores tipados, mensajes, errores, parámetros,
acciones y localizadores. Las entidades identificadas están en
[`gjs-c-common-database`](../gjs-c-common-database/README.md).

30 módulos en 13.752 líneas.

---

## Coordenadas Maven

| Dato         | Valor                                                               |
| ------------ | ------------------------------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                                                  |
| `artifactId` | `gjs-c-common-types`                                                |
| `version`    | `1.0.0`                                                        |
| `packaging`  | `nar` (biblioteca **shared**)                                       |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`                                        |
| Depende de   | `gjs-c-common-base-types`, `gjs-c-common-text`, `gjs-c-common-time` |

Es el primer módulo del stack que depende de los tres pilares a la vez:
estructuras, texto y tiempo.

---

## Uso

La cabecera fachada es `TiposDatos.h`:

```c
#include <Base.h>
#include <TiposDatos.h>

SValor * p_valObj = SValCrearEntero ( 42 );

if ( SValEsEntero ( p_valObj ) == 1 )
{
    printf ( "%d\n", SValValorEntero ( p_valObj ) );
}
SValDestruir ( &p_valObj );
```

Quedan **fuera de la fachada**: `SEntrada.h`, `SEntradaExt.h` y
`TiposDatosErrores.h`.

---

## La idea central: el valor tipado

`SValor` es el módulo que da sentido al resto. Combina un **código de tipo** con
el valor guardado como texto convertible:

```c
typedef struct
{
    int           iTipo;        /* catálogo TIP_* de la librería base */
    SCadenaConv * p_cadValor;   /* el valor, con conversión incorporada */
} SValor;
```

Los códigos de tipo son los de
[Tipos](../gjs-c-common-base/doc/Tipos.md) de `gjs-c-common-base`
(`TIP_NUMERO`, `TIP_CADENA`, `TIP_FECHA`…), y la conversión la resuelve
[SCadenaConv](../gjs-c-common-text/doc/SCadenaConv.md) de `gjs-c-common-text`.

De ahí salen las 88 funciones del módulo: **un constructor, un predicado, un
asignador y un lector por cada tipo del catálogo**.

`STipo` envuelve el mismo catálogo como objeto, y `SParametro` empareja un
`SValor` con un nombre.

---

## Convenios

Los del resto del stack. Sufijo `Ext` para la variante con parámetros
adicionales, presente en `SEntrada`/`SEntradaExt`,
`SLocalizador`/`SLocalizadorExt`, `SAccCrear`/`SAccCrearExt` y
`SCnctDestruir`/`SCnctDestruirExt`.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
los cinco módulos anteriores del stack instalados.

**Verificado** el 2026-08-02 en el modo normal (Cygwin POSIX,
`mvn clean install`): `BUILD SUCCESS`, 31 suites, 0 KO.

---

## Tests

**30 suites**, una por módulo. Sin test sólo las dos cabeceras sin fuente
(`TiposDatos.h`, `TiposDatosErrores.h`).

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`SEntrada` y `SEntradaExt` no están en la fachada, pero sus listas sí.**
  Quien incluya `TiposDatos.h` obtiene `SListaEntradas` sin disponer del tipo de
  sus elementos: hay que incluir `SEntrada.h` a mano. Ver
  [Entradas](doc/Entradas.md).
- **`TiposDatosConfig.h` arrastra un bloque de parametrización de árboles B con
  varias macros rotas** —`ARB_B_CLAVE COMP(...)` con un espacio donde debería ir
  un guion bajo, `ARB_B_CLAVE_INIC` que usa una variable inexistente,
  `ARB_B_ORDENACION_VALIDA` que compara contra constantes que no existen. Ninguna
  se usa: [SHoja](doc/Localizacion.md) sólo emplea las dos sanas. Ver
  [MODULOS.md](doc/MODULOS.md#tiposdatosconfigh).
- **`TiposDatosConfig.h` hace `#include <Tipos.h>`**, el nombre que colisiona
  entre `gjs-c-common-base` y `gjs-c-common-base-types`. Cuál se resuelve depende
  del orden de los `-I`. Ver
  [gjs-c-common-base-types](../gjs-c-common-base-types/doc/MODULOS.md#tiposh).
- `TiposDatosConfig.h` vive en el árbol de **fuentes**, así que sus constantes no
  se publican en el NAR `noarch`.
- `TiposDatosErrores.h` define un único código de error (`ERR_LIS_ELEMENTO_NULO`,
  300) y **no está en la fachada**, de modo que un consumidor que reciba ese
  código no tiene la constante para compararlo.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
