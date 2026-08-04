# Fechas

| Dato      | Valor                                   |
| --------- | --------------------------------------- |
| Cabecera  | `src/main/include/Fechas.h` (58 líneas) |
| Fuente    | `Fechas.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                 |
| Prefijo   | `Fec`                                   |
| Funciones | 20                                      |
| Test      | `FechasTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La fecha como **número**, sin objetos: un `long` con forma `AAAAMMDD`.

```cpp
long lFecha = FecFormConstruir ( 2026, 8, 3 );     // 20260803

if ( FecFormEsValida ( lFecha ) )
{
    int iAno = FecFormAnos ( lFecha );
}
```

Es la traducción del módulo homónimo del stack C, y sigue siendo útil por dos
razones: una fecha en ese formato **se lee de un vistazo**, y se ordena
comparando el entero.

## Los dos prefijos

| Prefijo    | Recibe                          | Ejemplo                        |
| ---------- | ------------------------------- | ------------------------------ |
| `Fec…`     | Año, mes y día sueltos          | `FecEsValida ( 2026, 8, 3 )`   |
| `FecForm…` | El `long` en formato `AAAAMMDD` | `FecFormEsValida ( 20260803 )` |

Casi todas las funciones existen en las dos versiones.

## La API

| Grupo        | Funciones                                                                                |
| ------------ | ---------------------------------------------------------------------------------------- |
| Construcción | `FecFormConstruir`, `FecFormDescomponer`                                                 |
| Validación   | `FecEsValida`, `FecFormEsValida`, `FecValEsValido`                                       |
| Partes       | `FecFormAnos`, `FecFormMeses`, `FecFormDias`                                             |
| Día del año  | `FecNumDiasAnualesHasta` / `…Desde`, y sus versiones `FecForm…`                          |
| Aritmética   | `FecSumar`, `FecRestar`, `FecFormSumar`, `FecFormRestar`                                 |
| Valor real   | `FecObtenerValor`, `FecFormObtenerValor`, `FecEstablecerValor`, `FecFormEstablecerValor` |

`FecSumar` y `FecRestar` son la aritmética que a [Fecha](Fecha.md) le falta:
suman un año, un mes y un día a otra fecha, con acarreo.

El grupo de «valor real» convierte la fecha a `double` y de vuelta, que es la
base sobre la que [TiempoNumerico](TiempoNumerico.md) monta el instante
completo.

## Dependencias

[Calendario](Calendario.md) para las reglas de bisiesto y días del mes.

## Test

`FechasTest.cpp` → `TestFechas()`.

## Observaciones

- **`FecSumar` y `FecRestar` usan punteros de entrada y salida a la vez.**

  ```cpp
  int FecSumar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD );
  ```

  Los tres primeros son la fecha de partida **y** el resultado; los tres últimos,
  lo que se suma. Es el estilo del stack C, y en C++ tiene alternativas —devolver
  una `Fecha`, o una estructura— que además dejarían claro cuál es cuál. Tal como
  está, invertir los argumentos compila igual y da otro resultado.
- **`FecFormSumar ( lFecha1, lFecha2 )` suma dos fechas.** Sumar dos `AAAAMMDD`
  no es una operación con sentido salvo que el segundo se interprete como
  intervalo —«sumar 0 años, 1 mes y 15 días» sería `115`—, cosa que la cabecera
  no dice. Sin esa aclaración, el nombre invita a llamarlo con dos fechas de
  verdad.
- **El `long` en formato `AAAAMMDD` cabe hasta el año 214 748**, así que no hay
  problema de rango; lo que sí hay es que **no admite fechas anteriores al año
  0** ni negativas, y no se dice.
- **`FecValEsValido ( double )` valida el valor real** y `FecFormEsValida ( long )`
  el formato entero. Dos nombres muy parecidos para dos cosas distintas, con
  `Val` y `Form` como única pista.
- **No hay conversión directa a [Fecha](Fecha.md).** La clase acepta el `long` en
  su constructor, así que el puente existe en un sentido; para el otro está
  `Fecha::Valor()`. No hace falta más, pero conviene saber que ése es el camino
  entre las dos capas.
- **`FecNumDiasAnualesHasta` y `…Desde` no dicen si el día en cuestión cuenta.**
  Es la clase de detalle que decide un resultado por uno.
