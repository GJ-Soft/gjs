# SPeriodo

| Dato         | Valor                                                 |
| ------------ | ----------------------------------------------------- |
| Cabecera     | `src/main/include/SPeriodo.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SPeriodo.c` (529 líneas) |
| Prefijo      | `SPerd`                                               |
| Struct       | `SPeriodo`                                            |
| Funciones    | 18                                                    |
| Incluido por | `Tiempo.h`                                            |
| Test         | `SPeriodoTest.c` → `TestSPeriodo()`                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **evento recurrente**: algo que ocurre cada día, semana, mes, trimestre o
año, y que sabe decir cuándo tocó la última vez, cuándo toca la siguiente y
cuántas veces ha ocurrido.

Es la pieza para vencimientos, cuotas, avisos periódicos y tareas programadas.

```c
typedef struct
{
    int  iPeriodicidad;
    long lFechaOcurrencia;
} SPeriodo;
```

Sólo guarda **la última ocurrencia**, no el historial: el resto se calcula.

## API

### Ciclo de vida

| Función                                                           | Descripción                  |
| ----------------------------------------------------------------- | ---------------------------- |
| `SPeriodo * SPerdCrear ( int iPeriodicidad, long lFechaInicial )` | Crea el periodo.             |
| `void SPerdDestruir ( SPeriodo ** p_perdObj )`                    | Destruye y anula el puntero. |
| `int SPerdEsValido ( SPeriodo * )`                                | 1 si es utilizable.          |
| `void SPerdIniciar ( SPeriodo *, long lFechaInicial )`            | Reinicia desde una fecha.    |

La periodicidad usa las constantes de
[TiposPeriodicidad](TiposPeriodicidad.md).

### Consulta de la periodicidad

| Función                                                                      | Descripción             |
| ---------------------------------------------------------------------------- | ----------------------- |
| `int SPerdPeriodicidad ( SPeriodo * )`                                       | Código de periodicidad. |
| `int SPerdEsDiario` / `EsSemanal` / `EsMensual` / `EsTrimestral` / `EsAnual` | Predicado por tipo.     |

### Ocurrencias

| Función                                                         | Descripción                     |
| --------------------------------------------------------------- | ------------------------------- |
| `int SPerdHaOcurrido ( SPeriodo * )`                            | 1 si ya ha ocurrido alguna vez. |
| `long SPerdFechaOcurrencia ( SPeriodo * )`                      | Fecha de la última ocurrencia.  |
| `long SPerdFechaProximaOcurrencia ( SPeriodo * )`               | Fecha de la siguiente.          |
| `int SPerdVecesQueHaOcurrido ( SPeriodo * )`                    | Veces ocurridas hasta hoy.      |
| `int SPerdOcurreHastaFecha ( SPeriodo *, long lFecha )`         | 1 si ocurre antes de esa fecha. |
| `int SPerdVecesQueOcurreHastaFecha ( SPeriodo *, long lFecha )` | Veces que ocurriría.            |

### Avance

| Función                                                     | Descripción                             |
| ----------------------------------------------------------- | --------------------------------------- |
| `int SPerdActualizarHastaFecha ( SPeriodo *, long lFecha )` | Avanza las ocurrencias hasta esa fecha. |
| `int SPerdActualizarHastaHoy ( SPeriodo * )`                | Avanza hasta hoy.                       |

```c
SPeriodo * p_perdObj = SPerdCrear ( TIP_PERIOD_MENSUAL, 20260101 );

int iVeces = SPerdVecesQueOcurreHastaFecha ( p_perdObj, 20260801 );  /* 7 */
long lProx = SPerdFechaProximaOcurrencia ( p_perdObj );

SPerdActualizarHastaHoy ( p_perdObj );
SPerdDestruir ( &p_perdObj );
```

## Dependencias

- [TiposPeriodicidad](TiposPeriodicidad.md) — el catálogo.
- [Fechas](Fechas.md) — la aritmética de avance.
- [TiempoSistema](TiempoSistema.md) — `SPerdActualizarHastaHoy`.

## Test

`SPeriodoTest.c` → `TestSPeriodo()`.

## Observaciones

- **`SPerdDestruir` declara `SPeriodo ** p_perdObj`**, con el nombre de un
  puntero simple. El convenio del stack es `p_p_perdObj` para el puntero a
  puntero, y todos los demás destructores lo respetan.
- **Hereda el catálogo cerrado de [TiposPeriodicidad](TiposPeriodicidad.md)**: no
  se puede expresar "cada dos meses" ni "cada quince días". Y como los valores de
  anual y trimestral están invertidos, ordenar periodos por frecuencia comparando
  `SPerdPeriodicidad` no funciona.
- **Trabaja con fechas, no con instantes**: la ocurrencia es un `long` en formato
  `AAAAMMDD`, así que no se puede modelar algo que ocurra a una hora concreta.
- `SPerdVecesQueHaOcurrido` y `SPerdActualizarHastaHoy` consultan el reloj del
  sistema, lo que hace que sus resultados dependan del momento de la llamada:
  conviene tenerlo en cuenta al escribir tests sobre código que los use.
- No hay `SPerdDuplicar` ni forma de listar todas las ocurrencias en un rango:
  sólo contarlas.
- La periodicidad **no se puede cambiar** después de crear el periodo, sólo
  consultarla.
