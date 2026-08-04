# Relojes: SReloj y SCronometro

| Dato          | Valor                               |
| ------------- | ----------------------------------- |
| Módulos       | 2                                   |
| Cabeceras     | `SReloj.h`, `SCronometro.h`         |
| Prefijos      | `SRlj`, `SCron`                     |
| Funciones     | 12 + 5                              |
| Incluidos por | `Tiempo.h`                          |
| Tests         | `SRelojTest.c`, `SCronometroTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Las dos formas de medir el paso del tiempo:

| Módulo        | Qué mide             | Cómo                                            |
| ------------- | -------------------- | ----------------------------------------------- |
| `SReloj`      | **Qué hora es**      | Un desplazamiento respecto al reloj del sistema |
| `SCronometro` | **Cuánto ha pasado** | Un instante de inicio                           |

## `SReloj`

```c
typedef struct
{
    double dDesplazamiento;
} SReloj;
```

Lo interesante es que **no guarda una hora, sino un desfase**. El reloj dice la
hora del sistema más su desplazamiento, lo que permite tener varios relojes
—de otras zonas, adelantados, atrasados— sin duplicar la fuente de tiempo.

### API

| Función                                                                     | Descripción                                    |
| --------------------------------------------------------------------------- | ---------------------------------------------- |
| `SReloj * SRljCrearDef ()`                                                  | Reloj sincronizado con el sistema (desfase 0). |
| `SReloj * SRljCrear ( long lHora )`                                         | Reloj puesto a una hora.                       |
| `SReloj * SRljCrearHHMMSS ( int iHH, int iMI, int iSS )`                    | Ídem desde componentes.                        |
| `void SRljDestruir ( SReloj ** )`                                           | Destruye y anula el puntero.                   |
| `long SRljHora ( SReloj * )`                                                | Hora actual del reloj, en formato `HHMMSS`.    |
| `long SRljHH ( SReloj * )`                                                  | Hora.                                          |
| `long SRljMI ( SReloj * )`                                                  | Minutos.                                       |
| `long SRljSS ( SReloj * )`                                                  | Segundos.                                      |
| `void SRljEstablecer ( SReloj *, long lHora )`                              | Pone el reloj en hora.                         |
| `void SRljEstablecerHHMMSS ( SReloj *, int, int, int )`                     | Ídem desde componentes.                        |
| `void SRljSincronizarConSistema ( SReloj * )`                               | Vuelve al desfase cero.                        |
| `void SRljSincronizarConSistemaExt ( SReloj *, long lHoraSis, long lHora )` | Sincroniza indicando ambas horas.              |

```c
SReloj * p_rljObj = SRljCrearDef ();

long lAhora = SRljHora ( p_rljObj );        /* la del sistema */
SRljEstablecerHHMMSS ( p_rljObj, 12, 0, 0 ); /* adelanta o atrasa */

SRljDestruir ( &p_rljObj );
```

## `SCronometro`

```c
typedef struct
{
    double dTiempoIni;
} SCronometro;
```

Cinco funciones, la API más pequeña del módulo:

| Función                                 | Descripción                            |
| --------------------------------------- | -------------------------------------- |
| `SCronometro * SCronCrear ()`           | Crea el cronómetro.                    |
| `void SCronDestruir ( SCronometro ** )` | Destruye y anula el puntero.           |
| `void SCronIniciar ( SCronometro * )`   | Pone el cronómetro en marcha.          |
| `double SCronParar ( SCronometro * )`   | Lo detiene y devuelve lo transcurrido. |
| `double SCronComputo ( SCronometro * )` | Lo transcurrido **sin detenerlo**.     |

```c
SCronometro * p_cronObj = SCronCrear ();

SCronIniciar ( p_cronObj );
/* … trabajo … */
double dParcial = SCronComputo ( p_cronObj );
double dTotal   = SCronParar ( p_cronObj );

SCronDestruir ( &p_cronObj );
```

## Dependencias

- [TiempoSistema](TiempoSistema.md) — la fuente de tiempo de ambos.
- [Horas](Horas.md) — el formato `HHMMSS` de `SReloj`.

## Tests

`SRelojTest.c` → `TestSReloj()`, `SCronometroTest.c` → `TestSCronometro()`.

## Observaciones

- **`SReloj` sólo maneja la hora, no la fecha.** Un reloj adelantado que cruce la
  medianoche no puede reflejar el cambio de día, porque el estado es un
  desplazamiento sobre `HHMMSS`. Para instantes completos hay que usar
  [SFechaHora](SFechaHora.md).
- **`SRljHH`, `SRljMI` y `SRljSS` devuelven `long`** para valores que caben de
  sobra en un `int`, y que en [SHora](SHora.md) —donde se llaman igual— son
  `int`. Las dos APIs no son intercambiables pese a compartir nombres.
- **La resolución del cronómetro no está documentada.** Devuelve `double`, pero
  si la fuente es `TiempoHoyAhora` de
  [TiempoSistema](TiempoSistema.md), que trabaja en segundos enteros, medir
  operaciones cortas dará cero. Conviene comprobar la implementación antes de
  usarlo para perfilado fino.
- `SCronParar` devuelve lo transcurrido, pero la cabecera no dice si un
  `SCronComputo` posterior sigue contando o se queda en el valor final. Tampoco
  hay `SCronEstaEnMarcha`.
- Ninguno de los dos tiene `EsValido`, presente en casi todos los objetos del
  stack.
