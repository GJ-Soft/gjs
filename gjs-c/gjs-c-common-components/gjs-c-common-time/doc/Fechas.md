# Fechas

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/Fechas.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/Fechas.c` (804 líneas) |
| Prefijo      | `Fec`                                               |
| Funciones    | 44                                                  |
| Incluido por | `Tiempo.h`                                          |
| Test         | `FechasTest.c` → `TestFechas()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Aritmética y comparación de fechas sobre valores sueltos, sin objetos. Es la
capa que usa [SFecha](SFecha.md) por dentro, y la que conviene usar
directamente cuando no hace falta un objeto.

## Las tres representaciones

Cada operación aparece dos veces: sobre **componentes** y sobre el **formato
empaquetado** `AAAAMMDD`, que se distingue por el infijo `Form`.

```c
int  FecEsValida     ( int iA, int iM, int iD );
int  FecFormEsValida ( long lFecha );
```

Más la conversión al **valor** continuo (`double`), que es la representación que
usa [TiempoNumerico](TiempoNumerico.md).

## API

### Construcción y descomposición

| Función                                                                       | Descripción            |
| ----------------------------------------------------------------------------- | ---------------------- |
| `long FecFormConstruir ( int iA, int iM, int iD )`                            | Componentes → formato. |
| `void FecFormDescomponer ( long lFecha, int * p_iA, int * p_iM, int * p_iD )` | Formato → componentes. |
| `int FecFormAnos ( long lFecha )`                                             | Año del formato.       |
| `int FecFormMeses ( long lFecha )`                                            | Mes.                   |
| `int FecFormDias ( long lFecha )`                                             | Día.                   |
| `int FecEsValida ( int, int, int )` / `int FecFormEsValida ( long )`          | Validez.               |

### Días del año

| Función                                                 | Descripción             |
| ------------------------------------------------------- | ----------------------- |
| `int FecNumDiasAnualesHasta ( int iA, int iM, int iD )` | Día del año (1-366).    |
| `int FecNumDiasAnualesDesde ( … )`                      | Días que quedan de año. |
| `int FecFormNumDiasAnualesHasta ( long )`               | Ídem sobre formato.     |
| `int FecFormNumDiasAnualesDesde ( long )`               | Ídem.                   |

### Diferencia

`FecDiferencia ( iA1, iM1, iD1, iA2, iM2, iD2 )` y
`FecFormDiferencia ( lFecha1, lFecha2 )`.

### Aritmética

Cinco operaciones por dos representaciones, veinte funciones:

| Operación             | Componentes (por puntero) | Formato (devuelve)   |
| --------------------- | ------------------------- | -------------------- |
| Sumar fecha completa  | `FecSumar`                | `FecFormSumar`       |
| Restar fecha completa | `FecRestar`               | `FecFormRestar`      |
| Sumar días            | `FecSumarDias`            | `FecFormSumarDias`   |
| Restar días           | `FecRestarDias`           | `FecFormRestarDias`  |
| Sumar meses           | `FecSumarMeses`           | `FecFormSumarMeses`  |
| Restar meses          | `FecRestarMeses`          | `FecFormRestarMeses` |
| Sumar años            | `FecSumarAnos`            | `FecFormSumarAnos`   |
| Restar años           | `FecRestarAnos`           | `FecFormRestarAnos`  |

Las de componentes **modifican por puntero** y devuelven `int`; las de formato
devuelven el `long` resultante:

```c
int iA = 2026, iM = 8, iD = 1;
FecSumarMeses ( &iA, &iM, &iD, 7 );              /* 2027-03-01 */

long lFecha = FecFormSumarMeses ( 20260801, 7 ); /* 20270301   */
```

### Comparación

Cinco predicados por dos representaciones:

| Predicado     | Componentes       | Formato               |
| ------------- | ----------------- | --------------------- |
| Igual         | `FecEsIgual`      | `FecFormEsIgual`      |
| Menor         | `FecEsMenor`      | `FecFormEsMenor`      |
| Mayor         | `FecEsMayor`      | `FecFormEsMayor`      |
| Menor o igual | `FecEsMenorIgual` | `FecFormEsMenorIgual` |
| Mayor o igual | `FecEsMayorIgual` | `FecFormEsMayorIgual` |

Sobre el formato empaquetado la comparación coincide con la numérica, que es
justamente la ventaja de esa representación.

### Valor continuo

| Función                                                  | Descripción          |
| -------------------------------------------------------- | -------------------- |
| `int FecValEsValido ( double dValor )`                   | Validez del valor.   |
| `double FecObtenerValor ( int iA, int iM, int iD )`      | Componentes → valor. |
| `double FecFormObtenerValor ( long lFecha )`             | Formato → valor.     |
| `int FecEstablecerValor ( double, int *, int *, int * )` | Valor → componentes. |
| `long FecFormEstablecerValor ( double dValor )`          | Valor → formato.     |

## Dependencias

- [Calendario](Calendario.md) — validez, bisiestos y días por mes.
- `TiempoConfig.h`.

## Test

`FechasTest.c` → `TestFechas()`.

## Observaciones

- **La asimetría entre las dos familias es fácil de tropezar**: `FecSumarDias`
  modifica sus argumentos por puntero y devuelve un código, mientras que
  `FecFormSumarDias` devuelve la fecha nueva y no toca nada. Confundirlas compila
  sin problema porque los tipos difieren, pero el patrón mental es distinto.
- `FecSumar` y `FecRestar` reciben **una fecha como incremento**
  (`int iA, int iM, int iD`), no una cantidad: sumar "1 año, 2 meses y 3 días".
  El nombre no lo aclara y la firma es idéntica a la de una fecha absoluta.
- **`FecDiferencia` devuelve `int`** mientras que
  `CalendDiasTranscurridos` devuelve `long` para lo que parece el mismo cálculo.
  La cabecera no dice en qué unidad expresa la diferencia.
- No hay comparación `EsDiferente`, aunque
  [SFecha](SFecha.md) sí la ofrece.
- El módulo no valida que el formato empaquetado sea coherente antes de operar:
  `FecFormSumarDias ( 20261301, 1 )` opera sobre un mes 13 sin quejarse. Conviene
  pasar antes por `FecFormEsValida`.
