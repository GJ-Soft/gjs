# Módulos de gjs-c-common-calculation

Índice y orquestación: **14 fuentes** y **21 cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 3. Análisis real                                                      │
  │    SFuncionReal · Dominios (sin implementar)                          │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. Objetos de cálculo                                                 │
  │    SIntervalo · SFormaLineal · contenedores de reales dobles          │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Operaciones y unidades                                             │
  │    CalculoOperaciones · Angulos / Radianes / Gradianes · Epsilon      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. Constantes y macros                                                │
  │    ConstantesMatematicas · CalculoDefs · FuncionesMatematicasBasicas  │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice

### Operaciones y unidades

| Módulo               | Prefijo   | Funciones | Fachada | Test | Documento                                   |
| -------------------- | --------- | --------- | ------- | ---- | ------------------------------------------- |
| `CalculoOperaciones` | `Mat`     | 68        | ✔       | ✔    | [CalculoOperaciones](CalculoOperaciones.md) |
| `Epsilon`            | `Epsilon` | 1         | ✔       | ✔    | [Epsilon](Epsilon.md)                       |
| `Angulos`            | `Ang`     | 13        | ✔       | ✔    | [Angulos](Angulos.md)                       |
| `Radianes`           | `Rad`     | 11        | ✔       | ✔    | [Angulos](Angulos.md)                       |
| `Gradianes`          | `Grad`    | 12        | ✔       | ✔    | [Angulos](Angulos.md)                       |

### Objetos de cálculo

| Módulo         | Prefijo   | Struct         | Funciones | Fachada | Test | Documento                       |
| -------------- | --------- | -------------- | --------- | ------- | ---- | ------------------------------- |
| `SIntervalo`   | `SIntv`   | `SIntervalo`   | 26        | ✔       | ✔    | [SIntervalo](SIntervalo.md)     |
| `SFormaLineal` | `SFrmLin` | `SFormaLineal` | 19        | ✔       | ✔    | [SFormaLineal](SFormaLineal.md) |

### Contenedores de reales dobles

| Módulo                   | Prefijo     | Se apoya en  | Funciones | Fachada | Test | Documento                       |
| ------------------------ | ----------- | ------------ | --------- | ------- | ---- | ------------------------------- |
| `SListaRealesDobles`     | `SLisReald` | `SLista`     | 28        | ✔       | ✔    | [RealesDobles](RealesDobles.md) |
| `SVectorRealesDobles`    | `SVecReald` | `SVector`    | 8         | ✔       | ✔    | [RealesDobles](RealesDobles.md) |
| `SSecuenciaRealesDobles` | `SSecReald` | `SSecuencia` | 10        | ✔       | ✔    | [RealesDobles](RealesDobles.md) |
| `STablaRealesDobles`     | `STabReald` | `STabla`     | 10        | ✔       | ✔    | [RealesDobles](RealesDobles.md) |
| `SPilaRealesDobles`      | `SPilReald` | `SPila`      | 10        | ✔       | ✔    | [RealesDobles](RealesDobles.md) |

### Análisis real

| Módulo                | Prefijo    | Struct                | Funciones | Fachada | Test  | Documento                       |
| --------------------- | ---------- | --------------------- | --------- | ------- | ----- | ------------------------------- |
| `SFuncionReal`        | `SFunR`    | `SFuncionReal`        | 12        | —       | ✔     | [SFuncionReal](SFuncionReal.md) |
| `SExtremoDominioReal` | `SExdR`    | `SExtremoDominioReal` | 10        | —       | ✔     | [Dominios](Dominios.md)         |
| `SDominioSimpleReal`  | `SDomSimR` | `SDominioSimpleReal`  | 22        | —       | **—** | [Dominios](Dominios.md)         |
| `SDominioReal`        | `SDomR`    | `SDominioReal`        | 14        | —       | **—** | [Dominios](Dominios.md)         |

Los dos últimos **no tienen fuente**: ver [Dominios](Dominios.md).

---

## Cabeceras sin fuente

### `Calculo.h`

Cabecera fachada. Incluye `ConstantesMatematicas.h`, `Epsilon.h`,
`CalculoOperaciones.h`, `ExpresionesMatematicas.h`,
`FuncionesMatematicasBasicas.h`, `Radianes.h`, `Angulos.h`, `Gradianes.h`,
`SIntervalo.h`, `SFormaLineal.h` y los cinco contenedores de reales dobles.

Deja fuera `CalculoDefs.h`, `SFuncionReal.h` y las tres cabeceras de dominios.

### `ConstantesMatematicas.h`

| Constante | Valor                                        |
| --------- | -------------------------------------------- |
| `PI_16`   | 3,141592653589793238                         |
| `PI_32`   | 3,141592653589793238462643383279502884197169 |
| `PI`      | `PI_32`                                      |
| `D_PI`    | 2π                                           |
| `C_PI`    | 4π                                           |
| `PI_M`    | π/2                                          |
| `RAIZ_PI` | 1,7724538509055160272981674833411            |
| `E`       | 2,718281828459045235                         |
| `RAIZ_2`  | 1,414213562373095048                         |
| `PHI`     | 1,618033988749894848                         |

> Empieza con `#undef PI` y `#undef E`, así que **redefine sin aviso** cualquier
> `PI` o `E` anterior, incluidos los de `<math.h>` en implementaciones que los
> ofrezcan.

### `CalculoDefs.h`

Macros generales y tipos de función:

| Elemento                        | Qué es                                    |
| ------------------------------- | ----------------------------------------- |
| `MAT_PRECISION_DEFECTO`         | `0.0000005`                               |
| `ABS( a )` / `SGN( a )`         | Valor absoluto y signo                    |
| `DEG2RAD( x )` / `RAD2DEG( x )` | Conversión grados ↔ radianes              |
| `MIN` / `MAX`                   | Sólo si no vienen ya definidos            |
| `PFUNREAL`                      | Alias de `PFUNDBLD`: `double (*)(double)` |
| `PFUNCOMPOSICION`               | `double (*)(PFUNREAL, PFUNREAL, double)`  |

**No está en la fachada**, pese a que [SFuncionReal](SFuncionReal.md) necesita
`PFUNREAL` para declarar sus funciones.

### `CalculoConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica). Incluye
`Base.h`, `<math.h>`, `<float.h>`, `CalculoDefs.h`, `ConstantesMatematicas.h` y
`Epsilon.h`.

> Tras incluir `CalculoDefs.h`, **vuelve a definir** `MAT_PRECISION_DEFECTO`,
> `MIN`, `MAX`, `ABS`, `SGN`, `DEG2RAD` y `RAD2DEG` con los mismos valores. La
> redefinición idéntica es legal en C, pero son dos sitios que mantener a la vez.

### `FuncionesMatematicasBasicas.h`

Identificadores de función elemental, para clasificar sin punteros:

| Constante          | Valor |
| ------------------ | ----- |
| `FMAT_ID`          | 0     |
| `FMAT_EXPONENCIAL` | 1     |
| `FMAT_LOGARITNO`   | 2     |
| `FMAT_SENO`        | 3     |
| `FMAT_COSENO`      | 4     |
| `FMAT_TANGENTE`    | 5     |

> `FMAT_LOGARITNO` es una errata de `FMAT_LOGARITMO`. Al ser una constante
> pública, corregirla rompería a quien ya la use.

No hay ninguna función que consuma estos identificadores: son seis constantes
sin uso dentro de la librería.

### `ExpresionesMatematicas.h`

> **No contiene nada matemático.** Sus 29 líneas declaran una única función:
>
> ```c
> int FrmCadena ( char * p_cCadena, const char * p_cFormato, va_list valArgumentos, int iMaxTam );
> ```
>
> Es exactamente el prototipo de
> [FormatoCadena](../../gjs-c-common-base/doc/FormatoCadena.md), el formateador
> de cadenas de la librería base. Compila porque la redeclaración es idéntica,
> pero el fichero está en la fachada prometiendo un soporte de expresiones
> matemáticas que no existe.
