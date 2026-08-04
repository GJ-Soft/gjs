# Fecha

| Dato     | Valor                                   |
| -------- | --------------------------------------- |
| Cabecera | `src/main/include/Fecha.h` (152 líneas) |
| Fuente   | `Fecha.cpp`                             |
| Espacio  | `org::gjs::cpp::common`                 |
| Envuelve | `std::chrono::year_month_day`           |
| Test     | `FechaTest.cpp`                         |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un día del calendario. Es la clase mejor construida del componente: envuelve el
tipo de C++20 y es **const-correcta de principio a fin**.

```cpp
class Fecha
{
private:
    std::chrono::year_month_day fecha;
    …
};
```

```cpp
Fecha fecPlazo ( 2026, 12, 31 );
Fecha fecHoy;   fecHoy.EstablecerValorDeHoy ();

if ( fecHoy < fecPlazo )
{
    long lDias = fecPlazo - fecHoy;
}

std::cout << fecPlazo.Formatear ( "%d/%m/%Y" ) << std::endl;
```

## Los cinco formatos de entrada

La clase acepta una fecha de cinco maneras, y las repite en constructores,
`Establecer`, comparaciones y `Diferencia`:

| Forma                                    | Ejemplo                  |
| ---------------------------------------- | ------------------------ |
| Año, mes y día sueltos                   | `Fecha ( 2026, 12, 31 )` |
| `long` en formato `AAAAMMDD`             | `Fecha ( 20261231L )`    |
| Texto                                    | `Fecha ( "2026-12-31" )` |
| `std::chrono::year_month_day`            | `Fecha ( ymd )`          |
| `year`, `month` y `day` de `std::chrono` | `Fecha ( y, m, d )`      |

Esa simetría es la que hace que la clase encaje con la capa numérica de
[Fechas](Fechas.md) y con `std::chrono` a la vez, sin conversiones a mano.

## La API

| Grupo       | Métodos                                                                  |
| ----------- | ------------------------------------------------------------------------ |
| Consulta    | `AAAA ()`, `MM ()`, `DD ()`, `EsValida ()`                               |
| Valor       | `Valor ()` → `long`, `ValorTiempo ()` → `time_t`, `ToYMD ()`             |
| Texto       | `Formatear ( sFormato )`, `ValorCadena ()`, `Cadena ( sFormato )`        |
| Ahora       | `EstablecerValorDeHoy ()`                                                |
| Comparación | `EsIgual`, `EsMenor`, `EsMayor`, `EsDiferente` — **en las cinco formas** |
| Diferencia  | `Diferencia ( … )` en las cinco formas, en días                          |
| Operadores  | `==`, `!=`, `<`, `<=`, `>`, `>=` en las cinco formas, y `-`              |

Son **30 operadores de comparación** y cinco de resta: seis por cada formato de
entrada. Escribir `fec > "2026-01-01"` o `fec == 20260101L` funciona sin
construir nada.

## Dependencias

`<chrono>`, `<ctime>`, `<string>`.

## Test

`FechaTest.cpp` → `TestFecha()`.

## Observaciones

- **`ValorCadena ()` y `Cadena ( … )` devuelven `std::string *`**, mientras que
  `Formatear ( … )`, en la misma clase y para lo mismo, devuelve
  `std::string` por valor. El puntero obliga a liberar —sin que la cabecera diga
  quién— y en un método `const` que construye la cadena al vuelo no hay razón
  para no devolver por valor. `Formatear` es la que conviene usar.
- **Los operadores con puntero son una trampa.** `operator== ( const Fecha * )`
  compara **el contenido apuntado**, no las direcciones, lo que es lo útil pero
  contradice lo que cualquiera espera de comparar punteros. Y con `nullptr` no
  hay contrato.

  Además hacen ambigua la comparación con `0`: `fec == 0` puede resolverse a la
  sobrecarga de `long` o a la de puntero.
- **`Establecer` devuelve `bool` y los constructores no.** Una fecha inválida
  pasada al constructor —`Fecha ( 2026, 2, 30 )`— no tiene forma de informar;
  queda `EsValida()` para preguntarlo después, y conviene hacerlo siempre que la
  fecha venga de fuera.
- **El texto que aceptan constructor y `Establecer` no está documentado.** Ni el
  formato esperado, ni qué pasa si no encaja.
- **`Diferencia` devuelve `long` en días**, y no hay forma de pedirla en meses o
  años, que es lo que suele hacer falta con fechas. `Calendario` tiene
  `CalendDiasTranscurridos` y tampoco.
- **No hay aritmética de fechas**: ni `SumarDias`, ni `operator+`. Se pueden
  restar dos fechas y no avanzar una. La capa numérica sí lo tiene, con
  `FecSumar` y `FecFormSumar` de [Fechas](Fechas.md).
- **No deriva de `IToString`**, así que no tiene `toString()` ni entra en las
  colecciones volcables del stack —cosa que sí hacen casi todas las clases de
  [gjs-cpp-common-types](../../gjs-cpp-common-types/README.md)—.
