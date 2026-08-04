# Hora

| Dato     | Valor                                         |
| -------- | --------------------------------------------- |
| Cabecera | `src/main/include/Hora.h` (146 líneas)        |
| Fuente   | `Hora.cpp`                                    |
| Espacio  | `org::gjs::cpp::common`                       |
| Envuelve | `std::chrono::hh_mm_ss<std::chrono::seconds>` |
| Test     | `HoraTest.cpp`                                |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una hora del día, con precisión de segundo. Es la gemela de
[Fecha](Fecha.md): misma estructura, mismos cinco formatos de entrada, misma
batería de comparaciones.

```cpp
class Hora
{
private:
    std::chrono::hh_mm_ss<std::chrono::seconds> hmsHora;
    …
};
```

```cpp
Hora horCierre ( 20, 0, 0 );
Hora horAhora;   horAhora.EstablecerValorDeAhora ();

if ( horAhora < horCierre )
{
    long lSegundos = horCierre - horAhora;
}
```

## Los cinco formatos

| Forma                            | Ejemplo               |
| -------------------------------- | --------------------- |
| Hora, minuto y segundo           | `Hora ( 14, 30, 52 )` |
| `long` en formato `HHMMSS`       | `Hora ( 143052L )`    |
| Texto                            | `Hora ( "14:30:52" )` |
| `std::chrono::hh_mm_ss<seconds>` | `Hora ( hms )`        |
| `hours`, `minutes` y `seconds`   | `Hora ( hh, mi, ss )` |

## La API

| Grupo       | Métodos                                                             |
| ----------- | ------------------------------------------------------------------- |
| Consulta    | `HH ()`, `MI ()`, `SS ()`, `EsValida ()`                            |
| Valor       | `Valor ()` → `long` en `HHMMSS`                                     |
| Texto       | `ValorCadena ()`, `Cadena ( formato )`                              |
| Ahora       | `EstablecerValorDeAhora ()`                                         |
| Comparación | `EsIgual`, `EsMenor`, `EsMayor`, `EsDiferente`, en las cinco formas |
| Diferencia  | `Diferencia ( … )`, en segundos                                     |
| Operadores  | Los seis de comparación por cada formato, y `-`                     |

## Dependencias

`<chrono>`, `<string>`.

## Test

`HoraTest.cpp` → `TestHora()`.

## Observaciones

> **Ningún método es `const`**, mientras que en [Fecha](Fecha.md) lo son todos.
>
> `Valor()`, `HH()`, `EsValida()`, las veinte comparaciones y los treinta
> operadores: ninguno. La consecuencia es que **una `Hora` constante no sirve
> para nada** —no se puede leer, ni comparar, ni volcar—, y que una función que
> reciba `const Hora &` no puede hacer nada con ella.
>
> Es más visible aquí que en el resto del stack porque la clase hermana sí está
> bien: las dos se escribieron con el mismo molde y sólo una recibió la revisión.
> El arreglo es mecánico y no toca los cuerpos, como el que se aplicó a
> [IComparable](../../gjs-cpp-common-base/doc/IComparable.md).
>
> Lo mismo ocurre en [FechaHora](FechaHora.md).

- **Las comparaciones toman `Hora &` no constante**, de modo que ni siquiera se
  puede comparar contra un temporal: `hor == Hora ( 20, 0, 0 )` no compila.
- **`Establecer` devuelve `void`**, a diferencia del de `Fecha`, que devuelve
  `bool`. Una hora inválida no se puede detectar en la asignación; queda
  `EsValida()`.
- **`ValorCadena ()` y `Cadena ( … )` devuelven `std::string *`**, con la misma
  cuestión de propiedad que en `Fecha` — y aquí sin un `Formatear` que devuelva
  por valor, así que no hay alternativa limpia.
- **No hay aritmética**: se pueden restar dos horas y no sumar minutos a una. La
  capa numérica lo tiene con `HorSumar` y `HorFormSumar` de
  [Horas](Horas.md).
- **`hh_mm_ss` admite valores fuera del día.** El tipo de `std::chrono` no acota
  a 24 horas —está pensado para representar una duración descompuesta—, así que
  `EsValida()` es la única barrera contra una hora como `25:00:00`, y su
  criterio no está documentado.
- **Sin submúltiplos de segundo.** `hh_mm_ss<seconds>` fija la precisión; para
  milisegundos habría que cambiar el parámetro de plantilla, que está fijado en
  el campo.
