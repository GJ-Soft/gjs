# ASCII

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/ASCII.h` (+ tabla en `ASCIIOEM850.h`) |
| Fuente       | `src/main/c/org/gjs/c/common/ASCII.c` (2.110 líneas)    |
| Prefijo      | `ASCII`                                                 |
| Funciones    | 80                                                      |
| Incluido por | `Texto.h`                                               |
| Test         | `ASCIITest.c` → `TestASCII()`                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Clasificación de caracteres del **juego extendido**, más allá del rango 0-127
que cubre
[ASCIIEstandar](../../gjs-c-common-base/doc/ASCIIEstandar.md) en la librería
base. Aquí están las letras acentuadas, las de otros alfabetos europeos y los
signos, con la página de códigos **OEM 850** como referencia.

Es lo que permite a [Cadenas](Cadenas.md) saber si una cadena es un
identificador válido o contiene caracteres no estándar.

## La API por familias

| Familia              | Nº  | Ejemplos                                                                                                     |
| -------------------- | --- | ------------------------------------------------------------------------------------------------------------ |
| Juego de caracteres  | 2   | `ASCIIPerteneceAlJuegoPrincipal`, `…Secundario`                                                              |
| Letras               | 9   | `ASCIIEsLetra`, `…Min`, `…May`, `EsVocal`, `EsConsonante` y sus variantes                                    |
| Letras con signo     | 6   | `ASCIIEsLetraConSigno`, `…Acentuada`, con `Min`/`May`                                                        |
| Por tipo de signo    | 24  | Acento abierto, cerrado, circunflejo, diéresis, tilde, cedilla, anillo, barrada — cada uno con `Min` y `May` |
| Alfabetos nacionales | 6   | `ASCIIPerteneceAlAlfabetoEsp`, `Ing`, `Fra`, `Ale`, `Cat`, `Por`                                             |
| Griegas y especiales | 6   | `ASCIIEsLetraGriega`, `…Nordica`, `…Especial`, con `Min`/`May`                                               |
| Conversión           | 3   | `ASCIILetraMinAMay`, `ASCIILetraMayAMin`, `ASCIILetraSinSigno`                                               |
| Signos               | 9   | `ASCIIEsSigno`, `…Punt`, `…Arit`, `…Cont`, `…Comp`, `…Esp`, `…Modif`, `…Moneda`                              |
| Caracteres concretos | 8   | `ASCIIEsDigito`, `EsEspacio`, `EsGuion`, `EsGuionBajo`, `EsPunto`, `EsComa`, `EsPuntoComa`, `EsDosPuntos`    |
| Validación           | 5   | `ASCIIEsImprimible`, `EsAlfanumerico`, `EsValidoToken`, `EsValidoInicioToken`, `EsValidoIdentificador`       |

Todas reciben un carácter y devuelven `1` o `0`.

`ASCIILetraSinSigno` es la más útil del grupo de conversión: quita el acento,
la diéresis o la cedilla y devuelve la letra base, que es lo que hace falta para
normalizar texto antes de compararlo u ordenarlo.

## Comportamiento

La clasificación se apoya en la tabla de `ASCIIOEM850.h`, que describe la página
de códigos 850 (Latin-1 de MS-DOS). Eso significa que **la interpretación de los
caracteres por encima de 127 depende de que el texto esté realmente en OEM 850**;
con UTF-8 o Windows-1252 los resultados no son los esperados.

Las funciones de alfabeto nacional (`ASCIIPerteneceAlAlfabetoEsp` y compañía)
responden si el carácter forma parte del alfabeto de ese idioma, incluidos sus
caracteres propios: la `ñ` para el español, la `ç` para el catalán y el
portugués, las vocales con diéresis para el alemán.

## Dependencias

- [ASCIIEstandar](../../gjs-c-common-base/doc/ASCIIEstandar.md) y
  `ASCIICodigos.h` de la librería base.
- `ASCIIOEM850.h` — la tabla de la página de códigos.

## Test

`ASCIITest.c` → `TestASCII()`.

## Observaciones

> **El condicional de página de códigos no hace nada.** `ASCII.h`, líneas 24-28:
>
> ```c
> #ifdef OEM850
> #	include <ASCIIOEM850.h>
> #else
> #	include <ASCIIOEM850.h>
> #endif
> ```
>
> Las dos ramas incluyen **el mismo fichero**, así que el `#define OEM850` de
> `TextoConfig.h` es irrelevante y el módulo está cableado a OEM 850. La
> estructura sugiere que se pensó para elegir entre varias tablas —existe un
> `PaginasCodigos.h`— pero esa alternativa nunca se escribió.

- La clasificación es **específica de una página de códigos de MS-DOS**, algo a
  tener en cuenta hoy: el repositorio está en UTF-8 (salvo dos ficheros), así
  que las cadenas literales del propio código no se clasifican bien con estas
  rutinas.
- `ASCIIOEM850.h` no está en la fachada `Texto.h`, de modo que un consumidor que
  quiera consultar la tabla directamente tiene que incluirla a mano.
- Con `char` con signo, los caracteres por encima de 127 llegan como valores
  negativos. La cabecera no indica si las rutinas lo contemplan; conviene
  convertir a `unsigned char` antes de llamar.
