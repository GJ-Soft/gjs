# SIntervalo

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/SIntervalo.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SIntervalo.c` (572 líneas) |
| Prefijo      | `SIntv`                                                 |
| Struct       | `SIntervalo`                                            |
| Funciones    | 26                                                      |
| Incluido por | `Calculo.h`                                             |
| Test         | `SIntervaloTest.c` → `TestSIntervalo()`                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un intervalo real `[min, max]` que además sabe **dividirse en subintervalos**.
Es la estructura que hace falta para discretizar un rango: mallas de
integración numérica, ejes de gráficas, tramos de una tabla.

```c
typedef struct
{
    double   dMin;
    double   dMax;
    int      iNumDivisiones;
    double * p_dDivisiones;
} SIntervalo;
```

Las divisiones se guardan como un vector de puntos de corte, así que los
subintervalos **no tienen por qué ser iguales**.

## API

### Construcción

Siete constructores, uno por caso de uso habitual:

| Función                                         | Intervalo resultante |
| ----------------------------------------------- | -------------------- |
| `SIntvCrear ( double dMin, double dMax )`       | `[dMin, dMax]`       |
| `SIntvCrearExt ( dMin, dMax, int iValores, … )` | Creado ya dividido   |
| `SIntvCrearSimetrico ( double dMax )`           | `[−dMax, dMax]`      |
| `SIntvCrearDesdeCero ( double dMax )`           | `[0, dMax]`          |
| `SIntvCrearUnidad ()`                           | `[0, 1]`             |
| `SIntvCrearCentena ()`                          | `[0, 100]`           |
| `SIntvCrearPunto ( double dValor )`             | `[dValor, dValor]`   |

Más `void SIntvDestruir ( SIntervalo ** )` y `int SIntvEsValido ( SIntervalo * )`.

### Extremos y medida

| Función                                 | Descripción            |
| --------------------------------------- | ---------------------- |
| `double SIntvMin ( SIntervalo * )`      | Extremo inferior.      |
| `double SIntvMax ( SIntervalo * )`      | Extremo superior.      |
| `int SIntvEstablecerMin ( …, double )`  | Cambia el mínimo.      |
| `int SIntvEstablecerMax ( …, double )`  | Cambia el máximo.      |
| `double SIntvLongitud ( SIntervalo * )` | Anchura del intervalo. |

### División

| Función                                                                     | Descripción                               |
| --------------------------------------------------------------------------- | ----------------------------------------- |
| `int SIntvDividir ( SIntervalo *, int iValores, … )`                        | Divide por los puntos de corte indicados. |
| `int SIntvDividirEquidistantemente ( SIntervalo *, int iNumSubintervalos )` | Divide en partes iguales.                 |
| `void SIntvLimpiarDivisiones ( SIntervalo * )`                              | Elimina las divisiones.                   |
| `int SIntvNumDivisiones ( SIntervalo * )`                                   | Número de puntos de corte.                |
| `int SIntvNumSubintervalos ( SIntervalo * )`                                | Número de tramos.                         |

`NumDivisiones` y `NumSubintervalos` son distintos: N puntos de corte producen
N+1 tramos.

### Subintervalos

| Función                                                   | Descripción                    |
| --------------------------------------------------------- | ------------------------------ |
| `SIntervalo * SIntvSubintervalo ( …, int iSubintervalo )` | Un tramo como intervalo nuevo. |
| `double SIntvSubintervaloMin ( …, int )`                  | Extremo inferior del tramo.    |
| `double SIntvSubintervaloMax ( …, int )`                  | Extremo superior del tramo.    |
| `double SIntvLongitudSubintervalo ( …, int )`             | Anchura del tramo.             |
| `int SIntvBuscarInervalo ( SIntervalo *, double dValor )` | Tramo que contiene un valor.   |

### Transformaciones

| Función                                             | Descripción          |
| --------------------------------------------------- | -------------------- |
| `SIntervalo * SIntvObtenerReflejo ( SIntervalo * )` | Intervalo reflejado. |
| `SIntervalo * SIntvObtenerInverso ( SIntervalo * )` | Intervalo inverso.   |

```c
SIntervalo * p_intvObj = SIntvCrearUnidad ();

SIntvDividirEquidistantemente ( p_intvObj, 4 );          /* 4 tramos de 0,25 */

for ( int i = 0; i < SIntvNumSubintervalos ( p_intvObj ); i = i + 1 )
{
    printf ( "[%f, %f]\n", SIntvSubintervaloMin ( p_intvObj, i ),
                           SIntvSubintervaloMax ( p_intvObj, i ) );
}
SIntvDestruir ( &p_intvObj );
```

## Dependencias

- [CalculoOperaciones](CalculoOperaciones.md) — comparación con tolerancia.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`SIntervaloTest.c` → `TestSIntervalo()`.

## Observaciones

- **`SIntvBuscarInervalo` lleva una errata en el nombre** —falta la `t` de
  *Intervalo*— y está en la API pública.
- **El intervalo es siempre cerrado.** No hay forma de expresar `(a, b)` ni
  `[a, b)`; para eso está
  [SDominioSimpleReal](Dominios.md), que sí distingue si cada extremo está
  incluido… pero no tiene implementación.
- `SIntvCrearExt` y `SIntvDividir` usan **lista variable de argumentos** con un
  contador previo (`int iValores, …`). Si el contador no casa con los argumentos
  reales, el comportamiento es indefinido y el compilador no puede avisar.
- `SIntvObtenerReflejo` y `SIntvObtenerInverso` no explican en la cabecera qué
  transformación aplican exactamente; hay que mirar la implementación.
- `SIntvEstablecerMin` y `SIntvEstablecerMax` no dicen qué ocurre con las
  divisiones ya calculadas al mover un extremo.
