# Módulos de gjs-c-common-time

Índice y orquestación: **16 fuentes** y **18 cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 3. Objetos                                                            │
  │    SFecha · SHora · SFechaHora · SPeriodo · SReloj · SCronometro      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. Aritmética y husos                                                 │
  │    Fechas · Horas · TiempoNumerico                                    │
  │    HusosHorarios · ZonasHorarias · SistemasHorarios · UTC             │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Calendario y sistema                                               │
  │    Calendario · TiempoSistema · TiposPeriodicidad                     │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. gjs-c-common-text + gjs-c-common-calculation                       │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice

### Calendario y sistema

| Módulo              | Prefijo     | Funciones | Test | Documento                                 |
| ------------------- | ----------- | --------- | ---- | ----------------------------------------- |
| `Calendario`        | `Calend`    | 36        | ✔    | [Calendario](Calendario.md)               |
| `TiempoSistema`     | `Tiempo`    | 7         | ✔    | [TiempoSistema](TiempoSistema.md)         |
| `TiposPeriodicidad` | `TipPeriod` | 6         | ✔    | [TiposPeriodicidad](TiposPeriodicidad.md) |

### Aritmética de fecha y hora

| Módulo           | Prefijo         | Funciones | Test | Documento                           |
| ---------------- | --------------- | --------- | ---- | ----------------------------------- |
| `Fechas`         | `Fec`           | 44        | ✔    | [Fechas](Fechas.md)                 |
| `Horas`          | `Hor`           | 20        | ✔    | [Horas](Horas.md)                   |
| `TiempoNumerico` | `Tmp`, `Tiempo` | 32        | ✔    | [TiempoNumerico](TiempoNumerico.md) |

### Husos, zonas y sistemas horarios

| Módulo             | Prefijo  | Funciones | Test | Documento                         |
| ------------------ | -------- | --------- | ---- | --------------------------------- |
| `HusosHorarios`    | `Hus`    | 7         | ✔    | [ZonasHorarias](ZonasHorarias.md) |
| `ZonasHorarias`    | `Znh`    | 11        | ✔    | [ZonasHorarias](ZonasHorarias.md) |
| `SistemasHorarios` | `SisHor` | 13        | ✔    | [ZonasHorarias](ZonasHorarias.md) |
| `UTC`              | `UTC`    | 2         | ✔    | [ZonasHorarias](ZonasHorarias.md) |

### Objetos

| Módulo        | Prefijo   | Struct        | Funciones | Test | Documento                   |
| ------------- | --------- | ------------- | --------- | ---- | --------------------------- |
| `SFecha`      | `SFec`    | `SFecha`      | 31        | ✔    | [SFecha](SFecha.md)         |
| `SHora`       | `SHor`    | `SHora`       | 31        | ✔    | [SHora](SHora.md)           |
| `SFechaHora`  | `SFecHor` | `SFechaHora`  | 48        | ✔    | [SFechaHora](SFechaHora.md) |
| `SPeriodo`    | `SPerd`   | `SPeriodo`    | 18        | ✔    | [SPeriodo](SPeriodo.md)     |
| `SReloj`      | `SRlj`    | `SReloj`      | 12        | ✔    | [Relojes](Relojes.md)       |
| `SCronometro` | `SCron`   | `SCronometro` | 5         | ✔    | [Relojes](Relojes.md)       |

---

## Cabeceras sin fuente

### `Tiempo.h`

Cabecera fachada. Incluye los 16 módulos más `TiempoDefs.h`. No deja nada
fuera.

### `TiempoDefs.h`

Dieciséis líneas con dos constantes:

| Constante              | Valor | Significado                            |
| ---------------------- | ----- | -------------------------------------- |
| `FEC_FORMATO_NORMAL`   | 0     | Formato con separadores (`01/08/2026`) |
| `FEC_FORMATO_NUMERICO` | 1     | Formato compacto (`20260801`)          |

### `TiempoConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica en el NAR).
Incluye `Base.h`, `Texto.h`, `Calculo.h` y `<unistd.h>` fuera de Windows, y
define:

- Los siete días de la semana (`DIA_LUNES` = 0 … `DIA_DOMINGO` = 6).
- Las fechas históricas del calendario, ver el
  [README](../README.md#un-calendario-con-historia).
- Los seis patrones de formato y sus tamaños.

> Que esté en el árbol de fuentes tiene una consecuencia práctica: un consumidor
> que quiera formatear una fecha con `FEC_FORMATO_FECHA_DEF` **no tiene acceso a
> la constante**, aunque sí a las funciones que la usan.
