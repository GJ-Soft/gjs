# Horas

| Dato      | Valor                                  |
| --------- | -------------------------------------- |
| Cabecera  | `src/main/include/Horas.h` (62 líneas) |
| Fuente    | `Horas.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                |
| Prefijo   | `Hor`                                  |
| Funciones | 20                                     |
| Test      | `HorasTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La hora como **número**: un `long` con forma `HHMMSS`. Es el módulo simétrico de
[Fechas](Fechas.md), con la misma estructura y los mismos dos prefijos.

```cpp
long lHora = HorFormConstruir ( 14, 30, 52 );      // 143052

int iSegundos = HorFormNumSegundos ( lHora );      // 52252
```

## Los dos prefijos

| Prefijo    | Recibe                        | Ejemplo                      |
| ---------- | ----------------------------- | ---------------------------- |
| `Hor…`     | Hora, minuto y segundo        | `HorEsValida ( 14, 30, 52 )` |
| `HorForm…` | El `long` en formato `HHMMSS` | `HorFormEsValida ( 143052 )` |

## La API

| Grupo        | Funciones                                                                                |
| ------------ | ---------------------------------------------------------------------------------------- |
| Construcción | `HorFormConstruir`, `HorFormDescomponer`                                                 |
| Validación   | `HorEsValida`, `HorFormEsValida`, `HorValEsValido`                                       |
| Partes       | `HorFormHoras`, `HorFormMinutos`, `HorFormSegundos`                                      |
| Totales      | `HorNumMinutos`, `HorNumSegundos`, y sus versiones `HorForm…`                            |
| Aritmética   | `HorSumar`, `HorRestar`, `HorFormSumar`, `HorFormRestar`                                 |
| Valor real   | `HorObtenerValor`, `HorFormObtenerValor`, `HorEstablecerValor`, `HorFormEstablecerValor` |

`HorNumSegundos` es la que más se usa: convierte una hora a los segundos
transcurridos desde medianoche, que es la forma cómoda de restar y comparar.

El grupo de «valor real» convierte la hora a una **fracción de día** —`0.5` es
mediodía—, que es lo que [TiempoNumerico](TiempoNumerico.md) suma a la fecha
para formar un instante.

## Dependencias

Ninguna del stack.

## Test

`HorasTest.cpp` → `TestHoras()`.

## Observaciones

- **`HorSumar` y `HorRestar` repiten el patrón de punteros de entrada y salida**
  de [Fechas](Fechas.md), con la misma cuestión: los tres primeros parámetros son
  la hora de partida y el resultado, los tres últimos lo que se suma.
- **Ninguna dice qué pasa al pasar de las 24 horas.** Sumar `20:00:00` y
  `06:00:00` puede dar `26:00:00`, `02:00:00`, o un error; con el acarreo de día
  perdido en cualquiera de los dos últimos casos. Es la pregunta central de un
  módulo de aritmética horaria y no está contestada, ni aquí ni en el valor de
  retorno de `HorSumar`, que es un `int` sin documentar.
- **`HorFormSumar ( lHora1, lHora2 )` suma dos horas**, con la misma ambigüedad
  que su gemela de fechas: sólo tiene sentido si la segunda se lee como
  intervalo.
- **`HorValEsValido ( double )` valida la fracción de día** y `HorFormEsValida`
  el entero `HHMMSS`. Dos nombres casi iguales para dos dominios distintos.
- **No hay submúltiplos de segundo**, coherente con [Hora](Hora.md), que fija la
  precisión en segundos.
- **`HorNumMinutos` trunca.** Convertir `14:30:52` a minutos da 870 y se pierden
  los 52 segundos, sin que la cabecera diga si redondea o descarta.
