# FechaHora

| Dato     | Valor                                       |
| -------- | ------------------------------------------- |
| Cabecera | `src/main/include/FechaHora.h` (155 líneas) |
| Fuente   | `FechaHora.cpp`                             |
| Espacio  | `org::gjs::cpp::common`                     |
| Envuelve | `std::chrono::system_clock::time_point`     |
| Test     | `FechaHoraTest.cpp`                         |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **instante**: fecha y hora juntas, sobre el reloj del sistema.

```cpp
class FechaHora
{
private:
    std::chrono::system_clock::time_point tpFechaHora;
    …
};
```

Es la clase con más formas de construirse del componente: **nueve
constructores**, porque a los cinco de [Fecha](Fecha.md) y [Hora](Hora.md) se
suman las combinaciones de las dos.

| Forma                           | Ejemplo                                |
| ------------------------------- | -------------------------------------- |
| `long long` con fecha y hora    | `FechaHora ( 20260803143052LL )`       |
| Texto                           | `FechaHora ( "2026-08-03 14:30:52" )`  |
| Dos `long`, fecha y hora        | `FechaHora ( 20260803L, 143052L )`     |
| Los seis enteros                | `FechaHora ( 2026, 8, 3, 14, 30, 52 )` |
| `time_point`                    | `FechaHora ( tp )`                     |
| Un `Fecha` y un `Hora`          | `FechaHora ( fec, hor )`               |
| `year_month_day` y `hh_mm_ss`   | `FechaHora ( ymd, hms )`               |
| Los seis tipos de `std::chrono` | `FechaHora ( y, m, d, hh, mi, ss )`    |

## La API

| Grupo       | Métodos                                                      |
| ----------- | ------------------------------------------------------------ |
| Consulta    | `AAAA`, `MM`, `DD`, `HH`, `MI`, `SS`, `EsValida`             |
| Valor       | `Valor ()` → `long long`, `ValorFecha ()`, `ValorHora ()`    |
| Partes      | `Fecha ()` y `Hora ()`, que devuelven punteros               |
| Texto       | `ValorCadena ()`, `Cadena ( formato )`                       |
| Ahora       | `EstablecerValorDeAhora ()`                                  |
| Comparación | Las cuatro nombradas y los seis operadores, por cada formato |
| Diferencia  | `Diferencia ( … )` y `operator -`, en `long long`            |

`ValorFecha()` y `ValorHora()` devuelven los `long` de la capa numérica, con lo
que el instante se puede descomponer sin construir objetos.

`Diferencia` resta los dos `Valor ()` y devuelve `long long`: un año de
diferencia ya son 10.000.000.000, que no cabe en el `long` de 32 bits de
Windows. Con un puntero nulo devuelve `LLONG_MAX`.

## Dependencias

[Fecha](Fecha.md), [Hora](Hora.md), `<chrono>`.

## Test

`FechaHoraTest.cpp` → `TestFechaHora()`.

## Observaciones

> **Los métodos `Fecha ()` y `Hora ()` se llaman igual que las clases que
> devuelven:**
>
> ```cpp
> Fecha * Fecha ();
> Hora  * Hora  ();
> ```
>
> Es legal, y tiene una consecuencia concreta: a partir de esa línea, dentro del
> ámbito de la clase **`Fecha` nombra a la función, no al tipo**. Los
> constructores que reciben `Fecha &` están declarados antes y por eso compilan;
> cualquier declaración posterior que quiera usar el tipo necesitaría calificarlo
> con el espacio de nombres completo.
>
> Es una trampa colocada para el próximo que edite la cabecera. `getFecha()` y
> `getHora()` —o `ToFecha()`, en la línea de `Fecha::ToYMD()`— la quitan sin
> coste.

- **`Fecha ()` y `Hora ()` devuelven punteros** sin decir quién los libera ni si
  son objetos nuevos o partes internas —no pueden ser lo segundo, porque la
  clase sólo guarda un `time_point`—. Devolver por valor sería lo natural, ya que
  se construyen al vuelo.
- **Ningún método es `const`**, como en [Hora](Hora.md) y a diferencia de
  [Fecha](Fecha.md). Ver el detalle allí.
- **Nueve constructores y ninguno documenta qué pasa con una entrada inválida.**
  `Establecer` devuelve `void` en las ocho formas.
- **`system_clock::time_point` es tiempo UTC**, y la clase no dice en qué zona
  interpreta los enteros que recibe ni los que devuelve. Con
  [SistemasHorarios](SistemasHorarios.md) en el mismo componente y
  `TiempoHoraSolarEsp` en [TiempoNumerico](TiempoNumerico.md), la cuestión no es
  teórica: construir con `( 2026, 8, 3, 14, 30, 52 )` y leer `HH()` puede no
  devolver 14 si media una conversión de zona.
- **No hay aritmética de instantes**: se pueden restar dos y no sumar una
  duración, que es lo que `std::chrono` hace fácil por debajo.
