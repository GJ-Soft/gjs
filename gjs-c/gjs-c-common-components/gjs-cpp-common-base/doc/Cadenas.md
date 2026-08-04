# Cadenas

| Dato      | Valor                                         |
| --------- | --------------------------------------------- |
| Cabecera  | `src/main/include/Cadenas.h` (101 líneas)     |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Cadenas.cpp` |
| Espacio   | `org::gjs::cpp::common`                       |
| Funciones | 52                                            |
| Test      | `CadenasTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Todo lo que `std::string` no trae: recortar, reemplazar, partir, y decir si un
texto es un entero, una URL o un nombre de fichero.

Son **funciones libres que reciben y devuelven `std::string` por valor**, sin
tocar el original. Es la diferencia grande con
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md) del stack C, donde se modifica
un búfer en su sitio y hay que llevar la cuenta del tamaño.

## La API

### Recorte y limpieza

| Función                                                                | Qué hace                                  |
| ---------------------------------------------------------------------- | ----------------------------------------- |
| `Trim` / `LTrim` / `RTrim`                                             | Quita blancos de los dos lados, o de uno. |
| `Limpiar`                                                              | Recorte más normalización.                |
| `FormatearBlancos`                                                     | Deja un solo espacio entre palabras.      |
| `EliminarBlancos` / `EliminarTabuladores`                              | Quita **todas** las apariciones.          |
| `EliminarCaracteresNoAlfanumericos` / `…NoImprimibles` / `…NoEstandar` | Filtros por familia.                      |
| `EliminarUltimoSaltoLinea`                                             | El terminador final.                      |

> `Trim` recorta los extremos; `EliminarBlancos` los quita todos, incluidos los
> interiores. Los dos existen y hacen cosas distintas, y confundirlos es el
> defecto que apareció dos veces en el stack C —en
> [SMensajes](../../gjs-c-common/doc/SMensajes.md) y en
> [SArgumentos](../../gjs-c-common/doc/SArgumentos.md)—. Aquí los nombres lo
> dicen mejor.

### Búsqueda y partición

| Función                                       | Qué hace                                     |
| --------------------------------------------- | -------------------------------------------- |
| `Separar ( sCadena, delimitadores )`          | Parte en un `std::vector<std::string>`.      |
| `BuscarPrimero ( sCadena, delimitadores, … )` | La primera aparición de cualquiera de ellos. |
| `BuscarDesdeAtrasCaracter`                    | Búsqueda hacia atrás.                        |
| `SubcadenaHasta` / `SubcadenaDesde`           | Corta por un carácter.                       |
| `NumPalabras` / `ExtraerPalabra`              | Por delimitador.                             |

`Separar` acepta los delimitadores como `initializer_list`, de modo que se
escribe `Separar ( sLinea, { ",", ";" } )`, y por defecto parte por espacios.

### Transformación

`ToLowerCase`, `ToUpperCase`, `ReemplazarTodos` —por carácter y por
subcadena—, `EliminarTodos`, `EliminarCaracter`, `EliminarCaracteres`,
`EliminarPrimerosCaracteres`, `EliminarUltimosCaracteres`,
`EliminarApariciones`.

### Predicados

| Grupo      | Funciones                                                                                                                                           |
| ---------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Contenido  | `ContieneCaracter`, `ContieneBlancos`, `ContieneTabuladores`, `ContieneCaracteresNoImprimibles`, `…NoAlfanumericos`, `…NoEstandar`, `TieneEspacios` |
| Extremos   | `EmpiezaPor`, `TerminaPor`, `TerminaEnSaltoLinea`                                                                                                   |
| Igualdad   | `SonIgualesIn` — sin distinguir mayúsculas                                                                                                          |
| Forma      | `EsPalabra`, `EsToken`, `EsNombreFichero`                                                                                                           |
| Número     | `EsNatural`, `EsEntero`, `EsReal`, `EsBooleano`                                                                                                     |
| Web        | `EsURL`, `EsURN`, `EsURI`                                                                                                                           |
| Equilibrio | `CoherenciaParentesis`, `CoherenciaLlaves`, `CoherenciaCorchetes`, `CoherenciaParejaSignos`                                                         |

Las tres de equilibrio son la parte menos habitual del módulo: comprueban que
los signos de apertura y cierre cuadren, con `CoherenciaParejaSignos` como
versión general para cualquier pareja.

`EsURL`, `EsURN` y `EsURI` se apoyan en
[ExpresionesRegulares](ExpresionesRegulares.md).

## Dependencias

`<string>`, `<list>`, `<vector>`, `<initializer_list>` y
[ExpresionesRegulares](ExpresionesRegulares.md).

## Test

`CadenasTest.cpp` → `TestCadenas()`.

## Observaciones

- **`ContieneCaracteresNoImprimibles` está declarada dos veces**, con la misma
  firma, separadas por `ContieneCaracteresNoAlfanumericos`. Es legal y no rompe
  nada, pero delata una edición a mano de la lista.
- **Todo se devuelve por valor.** Es lo correcto para una interfaz limpia, y
  significa que encadenar —`Trim ( ToLowerCase ( ReemplazarTodos ( … ) ) )`—
  construye una cadena nueva en cada paso. Para bucles con mucho texto conviene
  saberlo.
- **`BuscarPrimero` devuelve `size_t` y comunica el fallo con
  `std::string::npos`**, mientras que `Separar` devuelve un vector vacío y los
  predicados devuelven `bool`. Tres convenios de fallo en el mismo módulo, aunque
  cada uno sea el natural de su tipo.
- **`tamDelim` es un parámetro de salida por puntero** con valor por defecto
  `NULL`, en un módulo que por lo demás no usa parámetros de salida. Devolver un
  `std::pair` o una pequeña estructura encajaría mejor con el estilo del resto.
- **No hay conversión a `std::wstring` aquí**; eso está en
  [Codificacion](Codificacion.md), de modo que el trabajo con texto ancho está
  repartido entre dos cabeceras.
- **Las 52 funciones están en un solo espacio de nombres sin prefijo.** `Trim`,
  `Limpiar` o `Separar` son nombres muy generales para funciones libres
  exportadas por una librería; el `using namespace` que casi todo el mundo pone
  las trae al ámbito global.
