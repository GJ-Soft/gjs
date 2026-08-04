# SistemasHorarios

| Dato      | Valor                                             |
| --------- | ------------------------------------------------- |
| Cabecera  | `src/main/include/SistemasHorarios.h` (86 líneas) |
| Fuente    | `SistemasHorarios.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                           |
| Prefijo   | `SisHor`                                          |
| Funciones | 13                                                |
| Test      | `SistemasHorariosTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo de **escalas de tiempo**: UTC, GMT y MMT, con la fecha y la hora en
que cada una entró en vigor.

```cpp
const std::string & SisHorNombre ( int iId );
int  SisHorId      ( const std::string & sNombre );

bool SisHorEsValido ( int iId );
bool SisHorEsNulo   ( int iId );
bool SisHorEsUTC    ( int iId );
bool SisHorEsGMT    ( int iId );
bool SisHorEsMMT    ( int iId );

long SisHorFechaInicio ( int iId );
long SisHorHoraInicio  ( int iId );

long SisHorFechaInicioUTC ();
long SisHorHoraInicioUTC ();
long SisHorFechaInicioGMT ();
long SisHorHoraInicioGMT ();
```

## Las tres escalas

| Escala | Qué es                                                               |
| ------ | -------------------------------------------------------------------- |
| MMT    | *Mean Mean Time* de Greenwich, la escala anterior a la normalización |
| GMT    | *Greenwich Mean Time*, el tiempo medio del meridiano de Greenwich    |
| UTC    | *Coordinated Universal Time*, el actual, basado en relojes atómicos  |

Guardar **desde cuándo rige cada una** es lo que da sentido al módulo: un
instante anterior a 1972 no está en UTC aunque se exprese como si lo estuviera,
y para cálculos históricos la diferencia existe.

Sigue el patrón de catálogo del stack: la pareja `SisHorNombre` / `SisHorId`
para ir del identificador al texto y al revés, más un predicado por valor. Es el
mismo de [TiposSistema](../../gjs-c-common-system/doc/Catalogos.md) en C.

## Dependencias

`<string>`.

## Test

`SistemasHorariosTest.cpp` → `TestSistemasHorarios()`.

## Observaciones

- **No son husos horarios, son escalas de tiempo**, y el nombre del módulo se
  presta a confusión. Lo que hace falta para trabajar con fechas de varios
  países —`Europe/Madrid`, `America/New_York`, con sus reglas de cambio de hora—
  no está aquí ni en ninguna parte del componente. C++20 lo trae con
  `std::chrono::time_zone` y la base de datos IANA.

  Lo que sí hay son las reglas de cambio de hora europeas en
  [Calendario](Calendario.md) y el desfase español en
  [TiempoNumerico](TiempoNumerico.md), cada uno por su lado.
- **Ningún módulo del componente usa estas escalas.** Ni [Fecha](Fecha.md), ni
  [FechaHora](FechaHora.md), ni [TiempoSistema](TiempoSistema.md) reciben o
  devuelven un identificador de escala, así que la información está disponible y
  desconectada: saber que UTC empieza en una fecha no sirve de nada si ninguna
  conversión lo consulta.
- **`SisHorNombre` devuelve `const std::string &`**, una referencia a algo que
  presumiblemente es estático. Es eficiente y correcto si así es; la cabecera no
  lo dice, y devolver una referencia a un temporal sería un error grave. El resto
  del stack devuelve `std::string` por valor en funciones equivalentes.
- **Un identificador inválido no tiene contrato** en `SisHorNombre` ni en las
  cuatro de fecha y hora de inicio. `SisHorEsValido` está para preguntarlo antes.
- **`SisHorEsNulo` frente a `SisHorEsValido`**: dos predicados que parecen
  complementarios y probablemente no lo son —el nulo será un valor concreto del
  catálogo, y el inválido cualquier otra cosa—. La cabecera no los distingue.
- **Hay atajos para UTC y GMT y no para MMT.** `SisHorFechaInicioUTC()` y
  `…GMT()` existen; el tercero hay que pedirlo por identificador.
