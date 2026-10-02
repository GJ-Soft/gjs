# Calendario

| Dato      | Valor                                        |
| --------- | -------------------------------------------- |
| Cabecera  | `src/main/include/Calendario.h` (100 líneas) |
| Fuente    | `Calendario.cpp` (924 líneas)                |
| Espacio   | `org::gjs::cpp::common`                      |
| Prefijo   | `Calend`                                     |
| Funciones | 26                                           |
| Test      | `CalendarioTest.cpp` (408 líneas)            |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Las reglas del calendario gregoriano: bisiestos, días de cada mes, día de la
semana y **los cambios de hora estacionales**.

Todas las funciones reciben la fecha como año, mes y día sueltos.

## La API

### Validación y comparación

`CalendEsValido`, `CalendEsMenor`, `CalendEsIgual`, `CalendEsMayor`.

### Estructura del año

| Función                             | Qué da                           |
| ----------------------------------- | -------------------------------- |
| `CalendEsBisiesto ( iA )`           | Si el año tiene 366 días.        |
| `CalendDiasAno ( iA )`              | 365 o 366.                       |
| `CalendDiasMes ( iA, iM )`          | Los días de ese mes.             |
| `CalendDiasHastaElAno ( iA )`       | Días acumulados desde el origen. |
| `CalendDiasAnualesHastaElMes ( … )` | Días del año antes de ese mes.   |
| `CalendDiasAnualesDesdeElMes ( … )` | Los que quedan.                  |
| `CalendDiasTranscurridos ( … )`     | Entre dos fechas.                |

### Día de la semana

`CalendDiaSemana ( iA, iM, iD )` más un predicado por día:
`CalendDiaEsLunes` … `CalendDiaEsDomingo`.

### Cambios de hora

| Función                                            | Qué da                                           |
| -------------------------------------------------- | ------------------------------------------------ |
| `CalendDiaCambioAHorarioInvierno ( iA )`           | El día del cambio de ese año.                    |
| `CalendMesCambioAHorarioInvierno ( iA )`           | El mes.                                          |
| `CalendDiaCambioAHorarioVerano ( iA )`             | Idem para el de verano.                          |
| `CalendMesCambioAHorarioVerano ( iA )`             | Idem.                                            |
| `CalendEsDiaCambioAHorarioInvierno ( iA, iM, iD )` | Si esa fecha es el día del cambio.               |
| `CalendEsDiaCambioAHorarioVerano ( … )`            | Idem.                                            |
| `CalendAplicarUnaHoraMas ( iA, iM, iD )`           | Si a esa fecha le corresponde la hora de verano. |

Es la parte que no trae `std::chrono` y la razón de ser del módulo: la regla del
cambio de hora es una decisión política, no una fórmula de calendario.

## Dependencias

Ninguna del stack.

## Test

`CalendarioTest.cpp` → `TestCalendario()`.

Desde el 2026-09-20 hay tres casos que comparan contra **valores absolutos**, no
contra la propia librería: `TestCalendDiaSemana02` (doce días de la semana
históricos, de 1583 a 2100), `TestCalendCambioHorario02` (día y mes de cambio,
**un año por cada una de las cinco épocas**) y `TestCalendAplicarUnaHoraMas01`
(los **dos días de cada frontera** en las cinco épocas, más controles en 1917,
1940 y 1960).

Eso es lo que faltaba. Los casos que había —`TestCalendDiaSemana01` y
`TestCalendBisiestoDias01`— comprueban cosas **consistentes consigo mismas**:
que el resultado esté en `[0,6]`, que exactamente uno de los siete predicados de
día sea cierto, que dos días seguidos den valores seguidos, y que el día del
cambio horario «sea domingo» **según el propio `CalendDiaEsDomingo`**. Las cuatro
las pasa igual de bien una función desplazada un número fijo de días, que es
justo lo que pasaba. El copia-pega del punto 7 lo cazó el test nuevo en su
primera ejecución.

## Observaciones

### Diez defectos arreglados el 2026-09-20

Se repasó el módulo contrastándolo **día a día contra los datos de IANA**
(`zdump -v Europe/Madrid`, que Cygwin trae instalado) y salieron ocho defectos
encadenados. Conviene saber que estuvieron ahí, porque explican por qué las
fechas de este módulo no se parecen a las de ninguna versión anterior:

1. **`CalendDiaSemana` devolvía mal el día de la semana en *todas* las fechas.**
   En el stack C, porque tomaba como época el 15 de octubre de 1582 y
   `CalendDiasTranscurridos` descuenta ahí los diez días de la reforma aunque el
   intervalo esté entero después de ella: tres días de desfase. Ahora la época es
   el **1 de enero de 1583, que fue sábado** (`CAL_EPOCA_DIA_SEMANA_*`).
2. En el stack C++ la causa era **otra**: su `CalendDiasTranscurridos` es una
   implementación distinta que sumaba «lo que queda del mes» y «lo que queda del
   año» *además* de la diferencia de años. Para dos fechas **iguales** devolvía
   **365**. Reescrita como diferencia de dos números de día absolutos, igual que
   el stack C.
3. **`CalendAplicarUnaHoraMas` contestaba al revés** de 1996 en adelante:
   invierno donde la cabecera promete verano. Por ahí `HorFormSolarEsp` daba la
   hora solar con una hora de error todo el año.
4. Las ramas de `== 1996` y `> 1996` eran **la misma regla escrita dos veces**, y
   la de 1996 no miraba marzo: daba invierno de enero a septiembre. Fundidas.
5. **De 1974 a 1995 contestaba que no había cambio horario**, y sí lo hubo. Las
   tablas de 1974-1980 y las reglas de 1981-1995 existían y las usaban las otras
   cuatro funciones, pero ésta no las consultaba.
6. **`CalendMesCambioAHorario*` sacaba el mes con `% 100`**, que da el día: para
   1944 devolvía 1 en vez de 10.
7. **`CalendMesCambioAHorarioVerano` devolvía el mes de invierno** —copia-pega de
   la función de al lado—: 9 en vez de 3 para 1981-1995.
8. **`CalendDiaCambioAHorarioVerano` devolvía la fecha entera** (`19750413`) en
   vez del día para 1974-1980. Su gemela de invierno sí llevaba el `% 100`.
9. **`CalendEsBisiesto` aplicaba la regla gregoriana a los años julianos**, con
   lo que el día de la semana de cualquier fecha anterior a 1582 salía mal. Ver
   más abajo.
10. **Octubre de 1582 decía tener 20 días** en vez de 21.

Y las cuatro tablas de fechas mezclaban «el día del cambio» con «la víspera»,
porque los decretos dicen *«a las veintitrés horas del día X»* y el reloj salta a
las 00:00 del X+1. **Ahora todas guardan el día en que el reloj cambia**, y por
eso la comparación de la ventana de verano es `>= inicio` y `< fin`: el día del
cambio cuenta como lo que empieza.

### Qué sigue sin cuadrar, a propósito

Del barrido de 1918 a 2030 **cuadran 109 de 113 años**. Los cuatro que no:

- **1931** no aparece en los datos de IANA. Se conserva porque estaba, pero es la
  única fila de las tablas sin contrastar contra ninguna fuente.
- **1937, 1938 y 1939** usan las fechas de la **zona nacional**, que durante la
  guerra llevó horas distintas de la republicana. IANA sigue a la otra zona, así
  que no cuadran con `zdump` **y no es un error**.

Y **1940 está a `-1` en las tablas** aunque el 17 de marzo de 1940 el reloj se
adelantó una hora: aquello no fue un cambio estacional sino el paso definitivo a
UTC+1, y de eso se encarga `SIS_HOR_FEC_INI_UTC` en `SistemasHorarios.h`.
Ponerlo también en la tabla lo contaría dos veces.

### Antes de 1582 el calendario es otro, y el módulo lo sabe

Las fechas anteriores al 15 de octubre de 1582 son **julianas**, y desde el
2026-09-20 se tratan como tales. Lo que faltaba era la regla de bisiestos:

> **En el juliano había bisiestos, y más que ahora**: uno cada cuatro años **sin
> excepción**. Las reglas del 100 y del 400 las trajo la reforma precisamente
> porque sobraban bisiestos y el calendario se había adelantado diez días
> respecto al sol; por eso hubo que saltarse del 4 al 15 de octubre. Así que
> `CalendEsBisiesto ( 1500 )` responde **que sí**, aunque la regla gregoriana
> diga que no.

`CalendEsBisiesto` es ahora la única función que conoce las dos reglas, y de ella
cuelgan `CalendDiasAno`, `CalendDiasMes`, `CalendDiasHastaElAno` y, a través de
ellas, el día de la semana. El año 1582 cae del lado gregoriano y da igual: no es
múltiplo de 4, no es bisiesto por ninguna de las dos reglas.

Dos avisos:

- **Estas fechas no coinciden con las de una librería moderna.** Casi todas
  —`std::chrono`, `datetime` de Python, `java.time`— usan el **gregoriano
  proléptico**, o sea aplican las reglas de hoy hacia atrás indefinidamente. Aquí
  no: aquí el 12 de octubre de 1492 es una fecha juliana, que es la que escribió
  Colón. Comprobado contra dos hechos históricos, la batalla de Hastings (14 de
  octubre de 1066, sábado) y la llegada de Colón (viernes).
- **Para años antes de Cristo se aplica la misma regla de cada cuatro**, el
  juliano proléptico. No es exacto del todo: en los primeros decenios tras Julio
  César los bisiestos se pusieron mal —cada tres años— hasta que Augusto lo
  corrigió. Eso no está contemplado.

Y de paso se arregló que **octubre de 1582 decía tener 20 días** cuando tuvo
**21** (del 1 al 4 y del 15 al 31). Con el 20, la suma de los doce meses de 1582
daba 354 mientras `CalendDiasAno` decía 355.

### Lo demás

- **Las reglas de cambio de hora son de la Unión Europea**, a juzgar por su
  presencia junto a `TiempoHoraSolarEsp` de
  [TiempoNumerico](TiempoNumerico.md), y la cabecera no lo dice. En la UE el
  cambio es el último domingo de marzo y el último de octubre; en Estados Unidos
  son otras fechas, y en buena parte del mundo no hay cambio. Una función que
  responde `CalendDiaCambioAHorarioVerano ( 2026 )` sin decir para qué territorio
  invita a usarla donde no vale.

  Y el cambio estacional está en revisión en la propia UE desde hace años: si se
  suprime, estas seis funciones dejan de ser ciertas a partir de un año concreto,
  sin que nada en la interfaz permita expresarlo.
- **`CalendDiaSemana` sí dice qué numeración usa, aquí.** Las constantes
  `DIA_LUNES` (0) … `DIA_DOMINGO` (6) están en la cabecera pública de este stack.
  En el stack C viven en `TiempoConfig.h`, que es privada, así que allí el entero
  suelto sí se presta a error y hasta el propio test tiene que escribir los
  números a mano.
- **`CalendDiasHastaElAno` devuelve `long` desde un origen no documentado.**
  Sirve para restar dos fechas, que es lo que hace
  `CalendDiasTranscurridos`, pero el valor absoluto no significa nada sin saber
  el año cero.
- **Sí hay tratamiento de la reforma gregoriana**, al contrario de lo que decía
  aquí hasta el 2026-09-20: `CalendEsValido` rechaza los diez días que se
  saltaron (del 5 al 14 de octubre de 1582, comprobado) y `CalendDiaSemana` tiene
  una rama aparte para las fechas anteriores, que desde el 2026-09-20 además
  acierta. La reforma está codificada con la fecha
  de adopción de **España, Italia y Portugal**; Gran Bretaña la adoptó en 1752 y
  Rusia en 1918, así que para fechas anteriores a esos años en esos países el
  cálculo no coincide.
- **Se solapa parcialmente con `std::chrono`**, que desde C++20 sabe de años
  bisiestos y días del mes: `std::chrono::year::is_leap()` y
  `year_month_day_last`. Lo que no trae —el día de la semana en castellano y los
  cambios de hora— es lo que justifica el módulo.
- **Todo son enteros sueltos.** Con [Fecha](Fecha.md) en el mismo componente, una
  sobrecarga que aceptara la clase evitaría descomponerla en cada llamada.
