# gjs-c-common-calculation

Librería de **cálculo** en C del stack GJS: operaciones matemáticas, ángulos en
tres sistemas de unidades, intervalos, formas lineales, funciones reales y
contenedores especializados en `double`.

14 módulos en 5.428 líneas. Es el módulo más pequeño de los grandes del stack, y
también el que más piezas incompletas tiene: dos de sus cabeceras declaran una
API que **no está implementada**.

---

## Coordenadas Maven

| Dato         | Valor                                                                |
| ------------ | -------------------------------------------------------------------- |
| `groupId`    | `org.gjs.c.common`                                                   |
| `artifactId` | `gjs-c-common-calculation`                                           |
| `version`    | `1.0.0-RC.2`                                                         |
| `packaging`  | `nar` (biblioteca **shared**)                                        |
| Pom padre    | `org.gjs.c:gjs-c-lib-parent`                                         |
| Depende de   | `gjs-c-common-base-types` (y a través de él, de `gjs-c-common-base`) |

---

## Uso

La cabecera fachada es `Calculo.h`:

```c
#include <Base.h>
#include <Calculo.h>

double dSeno = MatRaiz ( MatCuadrado ( 3.0 ) + MatCuadrado ( 4.0 ) );   /* 5.0 */

SIntervalo * p_intvObj = SIntvCrear ( 0.0, 1.0 );
SIntvDividirEquidistantemente ( p_intvObj, 10 );
SIntvDestruir ( &p_intvObj );
```

Quedan **fuera de la fachada** y hay que incluirlas a mano: `CalculoDefs.h`,
`SFuncionReal.h`, `SExtremoDominioReal.h`, `SDominioReal.h` y
`SDominioSimpleReal.h`.

---

## Convenios

Los del resto del stack: patrón de objeto `SXxxCrear` / `SXxxDestruir ( S** )` /
`SXxxEsValido`, predicados `1`/`0`, memoria vía `MemReservar`/`MemLiberar`.

Las rutinas sueltas usan el prefijo `Mat` ([CalculoOperaciones](doc/CalculoOperaciones.md)),
y las de ángulos `Ang`, `Rad` y `Grad` según el sistema de unidades.

### Precisión

Toda la comparación de reales pasa por una **precisión configurable**, no por
`==`:

| Elemento                                        | Dónde                                           | Valor                    |
| ----------------------------------------------- | ----------------------------------------------- | ------------------------ |
| `MAT_PRECISION_DEFECTO`                         | `CalculoDefs.h`                                 | `0.0000005`              |
| `MatPresicion ()` / `MatEstablecerPresicion ()` | [CalculoOperaciones](doc/CalculoOperaciones.md) | En tiempo de ejecución   |
| `Epsilon ()`                                    | [Epsilon](doc/Epsilon.md)                       | El épsilon de la máquina |

### Constantes

`ConstantesMatematicas.h` define `PI` (con variantes `PI_16` y `PI_32`),
`D_PI` (2π), `C_PI` (4π), `PI_M` (π/2), `RAIZ_PI`, `E`, `RAIZ_2` y `PHI`.

> Hace `#undef PI` y `#undef E` antes de definirlos, así que **pisa cualquier
> `PI` o `E` que venga de `<math.h>` o del código del proyecto**.

`CalculoDefs.h` añade las macros `ABS`, `SGN`, `DEG2RAD`, `RAD2DEG`, más `MIN` y
`MAX` si no vienen ya de la librería base.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
tener instalados antes `gjs-c-common-base` y `gjs-c-common-base-types`.

**Verificado** en el modo normal (Cygwin POSIX, `mvn clean install`):
`BUILD SUCCESS`, 14 suites, 0 KO.

---

## Tests

**14 suites** registradas en `src/test/c/.../Test.c`.

Sin test: las siete cabeceras sin fuente, incluidas
[SDominioReal y SDominioSimpleReal](doc/Dominios.md), que sí declaran API.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`SDominioReal` y `SDominioSimpleReal` no están implementados.** Declaran 14 y
  22 funciones respectivamente y **no tienen `.c`**. Comprobado enlazando contra
  la biblioteca ya construida: `SExdRCrearInfinito` enlaza y
  `SDomSimRCrearEjeReal` da `undefined reference`. Tampoco tienen test ni están
  en la fachada. Ver [Dominios](doc/Dominios.md).
- **`SFuncionReal` arrastra esas dos cabeceras**, así que su capacidad de acotar
  el dominio de una función queda inservible. Además, el campo `p_funInterior`
  está declarado como `struct SFuncionReal *`, un tipo **incompleto y distinto**
  del `typedef SFuncionReal`; asignarlo da
  `error: incompatible pointer types`, comprobado con el `gcc` del proyecto. Ver
  [SFuncionReal](doc/SFuncionReal.md).
- **`ExpresionesMatematicas.h` no tiene nada matemático**: declara `FrmCadena`,
  la función de formateo de cadenas de
  [FormatoCadena](../gjs-c-common-base/doc/FormatoCadena.md). Está en la fachada
  y no aporta nada.
- `CalculoDefs.h` y `CalculoConfig.h` **duplican las mismas seis macros**
  (`MAT_PRECISION_DEFECTO`, `MIN`, `MAX`, `ABS`, `SGN`, `DEG2RAD`, `RAD2DEG`),
  y la segunda incluye a la primera antes de repetirlas.
- `CalculoConfig.h` vive en el árbol de **fuentes**, así que no se publica en el
  NAR `noarch`. `CalculoDefs.h` sí se publica pero **no está en la fachada**,
  pese a definir `PFUNREAL`, que es el tipo que necesita
  [SFuncionReal](doc/SFuncionReal.md).
- Varios nombres llevan **erratas** que ya forman parte de la API pública:
  `MatPresicion` y `MatEstablecerPresicion` (por *Precision*),
  `MatExponecialNatural` (por *Exponencial*), `SIntvBuscarInervalo` (por
  *Intervalo*) y `FMAT_LOGARITNO` (por *LOGARITMO*).
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
