# SFechaHora

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/SFechaHora.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SFechaHora.c` (769 líneas) |
| Prefijo      | `SFecHor`                                               |
| Struct       | `SFechaHora`                                            |
| Funciones    | 48                                                      |
| Incluido por | `Tiempo.h`                                              |
| Test         | `SFechaHoraTest.c` → `TestSFechaHora()`                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Fecha y hora juntas como un solo objeto. Es el tipo de más alto nivel de la
librería y el que se usa en la práctica cuando hace falta un instante completo.

```c
typedef struct
{
    double dValor;
} SFechaHora;
```

Guarda el valor combinado de [TiempoNumerico](TiempoNumerico.md), no la fecha y
la hora por separado.

## API

### Ciclo de vida

| Función                                    | Descripción                         |
| ------------------------------------------ | ----------------------------------- |
| `SFechaHora * SFecHorCrearDef ()`          | Sin valor.                          |
| `SFechaHora * SFecHorCrear ( … )`          | Desde componentes.                  |
| `SFechaHora * SFecHorCrearLit ( … )`       | Desde texto.                        |
| `SFechaHora * SFecHorCrearFecha ( … )`     | Desde una [SFecha](SFecha.md).      |
| `SFechaHora * SFecHorCrearFechaHora ( … )` | Desde `SFecha` y [SHora](SHora.md). |
| `SFechaHora * SFecHorCrearFecHor ( … )`    | Desde otro `SFechaHora`.            |
| `void SFecHorDestruir ( SFechaHora ** )`   | Destruye y anula el puntero.        |
| `int SFecHorEsValida ( SFechaHora * )`     | 1 si es utilizable.                 |
| `int SFecHorTieneValor ( SFechaHora * )`   | 1 si tiene instante asignado.       |

Seis constructores: es el objeto con más formas de crearse de la librería,
porque puede componerse desde cualquiera de las piezas.

### Acceso a las partes

| Función                                                          | Devuelve                     |
| ---------------------------------------------------------------- | ---------------------------- |
| `int SFecHorAAAA` / `MM` / `DD`                                  | Año, mes y día.              |
| `int SFecHorHH` / `MI` / `SS`                                    | Hora, minuto y segundo.      |
| `long SFecHorFechaForm`                                          | Fecha en formato `AAAAMMDD`. |
| `long SFecHorHoraForm`                                           | Hora en formato `HHMMSS`.    |
| `long SFecHorFechaHoraForm`                                      | Ambas empaquetadas.          |
| `SFecHorFecha` / `SFecHorHora` / `SFecHorFechaHora`              | Las partes como objeto.      |
| `double SFecHorValor` / `SFecHorValorFecha` / `SFecHorValorHora` | Valores continuos.           |
| `double SFecHorValorNumerico`                                    | Valor numérico completo.     |

### Asignación

`SFecHorEstablecer`, `SFecHorEstablecerLit`, `SFecHorEstablecerFecHor`,
`SFecHorEstablecerValorDeAhora`.

### Comparación

Cinco operaciones por **cuatro** tipos de argumento, veinte funciones:

| Operación  | Contra `SFechaHora *` | Contra `SFecha *`     | Contra texto        | Contra valor          |
| ---------- | --------------------- | --------------------- | ------------------- | --------------------- |
| Igual      | `SFecHorEsIgual`      | `SFecHorEsIgualFecha` | `SFecHorEsIgualLit` | `SFecHorEsIgualValor` |
| Diferente  | `SFecHorEsDiferente`  | `…DiferenteFecha`     | `…DiferenteLit`     | `…DiferenteValor`     |
| Menor      | `SFecHorEsMenor`      | `…MenorFecha`         | `…MenorLit`         | `…MenorValor`         |
| Mayor      | `SFecHorEsMayor`      | `…MayorFecha`         | `…MayorLit`         | `…MayorValor`         |
| Diferencia | `SFecHorDiferencia`   | —                     | `…DiferenciaLit`    | `…DiferenciaValor`    |

La columna `Fecha` permite comparar un instante contra una fecha sin hora, que
es la comparación que más se necesita en la práctica ("¿es de hoy?").

```c
SFechaHora * p_fhObj = SFecHorCrearDef ();

SFecHorEstablecerValorDeAhora ( p_fhObj );
printf ( "%04d/%02d/%02d %02d:%02d:%02d\n",
         SFecHorAAAA ( p_fhObj ), SFecHorMM ( p_fhObj ), SFecHorDD ( p_fhObj ),
         SFecHorHH ( p_fhObj ), SFecHorMI ( p_fhObj ), SFecHorSS ( p_fhObj ) );
SFecHorDestruir ( &p_fhObj );
```

## Dependencias

- [TiempoNumerico](TiempoNumerico.md) — la representación combinada.
- [SFecha](SFecha.md) y [SHora](SHora.md) — construcción y comparación.
- [TiempoSistema](TiempoSistema.md) — `SFecHorEstablecerValorDeAhora`.

## Test

`SFechaHoraTest.c` → `TestSFechaHora()`.

## Observaciones

- **Es el único de los tres objetos que llega a `Diferencia` en tres de las
  cuatro columnas**, pero **no tiene `SFecHorDiferenciaFecha`**: se puede
  comparar contra una `SFecha` pero no medir la diferencia contra ella.
- Como [SFecha](SFecha.md) y [SHora](SHora.md), **no tiene aritmética**: no hay
  forma de sumar días u horas a un instante desde el propio objeto.
- **La zona horaria no forma parte del objeto.** Un `SFechaHora` es un instante
  sin referencia: para interpretarlo hay que saber aparte qué zona y qué sistema
  horario rigen, y aplicar
  [ZonasHorarias](ZonasHorarias.md) y [Calendario](Calendario.md) a mano.
- El almacenamiento en `double` limita la precisión a segundos enteros; no hay
  milisegundos en ninguna parte de la API.
- `SFecHorCrearFecha` y `SFecHorCrearFechaHora` no dicen qué hora asignan cuando
  sólo se les da la fecha: presumiblemente las 00:00:00, pero la cabecera no lo
  garantiza.
