# TiempoNumerico

| Dato      | Valor                                            |
| --------- | ------------------------------------------------ |
| Cabecera  | `src/main/include/TiempoNumerico.h` (109 líneas) |
| Fuente    | `TiempoNumerico.cpp`                             |
| Espacio   | `org::gjs::cpp::common`                          |
| Prefijos  | `Tmp`, `Tiempo`                                  |
| Funciones | 26                                               |
| Test      | `TiempoNumericoTest.cpp`                         |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El **instante como número**, juntando fecha y hora. Es la capa numérica que
corresponde a [FechaHora](FechaHora.md), y ofrece dos representaciones:

| Tipo        | Cómo                                      | Sufijo |
| ----------- | ----------------------------------------- | ------ |
| `double`    | Fecha con la hora como parte fraccionaria | —      |
| `long long` | Fecha y hora concatenadas                 | `…LL`  |

```cpp
double dCuando   = TmpFormConstruir ( 20260803L, 143052L );
long long llOtro = TmpFormConstruirLL ( 20260803L, 143052L );
```

Cada operación existe en las dos versiones, la segunda con `LL` al final.

## La API

| Grupo          | `double`                                                       | `long long`                 |
| -------------- | -------------------------------------------------------------- | --------------------------- |
| Construcción   | `TmpFormConstruir`, `TmpFormConstruirExt`                      | `…LL`, `…ExtLL`             |
| Descomposición | `TmpFormDescomponer`, `TmpFormDescomponerExt`                  | `…LL`, `…ExtLL`             |
| Validación     | `TmpFormEsValido`                                              | `TmpFormEsValidoLL`         |
| Partes         | `TmpFormFecha`, `TmpFormHora`                                  | `TmpFormFechaLL`, `…HoraLL` |
| Detalle        | `TmpFormAnos`, `Meses`, `Dias`, `Horas`, `Minutos`, `Segundos` | —                           |
| Valor          | `TmpFormObtenerValor`, `TmpFormEstablecerValor`                | `…ValorLL`                  |

Las variantes `Ext` reciben los seis enteros sueltos en lugar de los dos `long`.

## Las dos sueltas

| Función                                 | Qué hace                                              |
| --------------------------------------- | ----------------------------------------------------- |
| `TiempoNumSegundos ( iD, iH, iMi, iS )` | Convierte días, horas, minutos y segundos a segundos. |
| `TiempoHoraSolarEsp ( lFecha, lHora )`  | La **hora solar en España** para ese instante.        |

## Dependencias

[Fechas](Fechas.md), [Horas](Horas.md) y [Calendario](Calendario.md).

## Test

`TiempoNumericoTest.cpp` → `TestTiempoNumerico()`.

## Observaciones

> **`TiempoHoraSolarEsp` es una regla local en una librería general.** Aplica el
> desfase entre la hora oficial española y la solar —España está en el huso de
> Europa Central desde 1940, con el meridiano de Greenwich pasándole por encima—
> y lo hace sin que nada en el componente lo acote a ese territorio.
>
> Es información útil y bien puesta en un módulo de tiempo; lo que falta es
> decirlo en la cabecera y, si el stack se pretende general, tener la operación
> con el huso como parámetro. Va de la mano de los cambios de hora de
> [Calendario](Calendario.md), que también son de la Unión Europea sin
> declararlo.

- **El instante como `double` pierde precisión.** Un `double` tiene 53 bits de
  mantisa: con la fecha ocupando la parte entera —del orden de 2·10⁷ para
  `AAAAMMDD`— quedan unos 10⁻⁹ de resolución en la fracción, lo que da de sobra
  para segundos. Pero **las comparaciones de igualdad entre instantes no se
  pueden hacer con `==`**, y no hay en el módulo una función que las haga con
  tolerancia, teniendo el stack tres implementaciones de comparación de reales
  —en `base`, en `types` y en `calculation`—.

  La versión `long long` no tiene ese problema y es la que conviene para
  comparar y ordenar.
- **Las dos representaciones no son intercambiables** y el módulo no ofrece
  conversión directa entre ellas: para pasar de `double` a `long long` hay que
  descomponer y volver a construir.
- **`TmpFormEstablecerValor` y `TmpFormObtenerValor` tienen nombres poco
  informativos** —¿qué valor, frente a qué instante?— y en las dos versiones.
- **`TmpFormDescomponer` usa punteros de salida**, coherente con el resto de la
  capa numérica y no con el estilo del componente C++.
- **`TiempoNumSegundos` desentona.** Es la única función del módulo que no habla
  de instantes sino de duraciones, con el prefijo `Tiempo` en vez de `Tmp`, y
  encajaría mejor en [Horas](Horas.md), junto a `HorNumSegundos`.
- **La descomposición no dice qué hace con un valor inválido**, teniendo
  `TmpFormEsValido` al lado para comprobarlo antes.
