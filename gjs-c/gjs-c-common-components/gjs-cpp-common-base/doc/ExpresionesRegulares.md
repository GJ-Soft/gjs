# ExpresionesRegulares

| Dato      | Valor                                                      |
| --------- | ---------------------------------------------------------- |
| Cabecera  | `src/main/include/ExpresionesRegulares.h` (47 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/ExpresionesRegulares.cpp` |
| Espacio   | `org::gjs::cpp::common`                                    |
| Funciones | 1                                                          |
| Test      | `ExpresionesRegularesTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una función y seis patrones. La función es trivial; lo que aporta el módulo es
el **catálogo de expresiones ya escritas** para lo que el stack necesita
reconocer.

```cpp
bool CumpleExpresionRegular ( const std::string & cadena, const std::string & patron );
```

## Los seis patrones

| Constante               | Reconoce                                              |
| ----------------------- | ----------------------------------------------------- |
| `REGEX_NUM_ENTERO`      | `-?[0-9]+`                                            |
| `REGEX_NUM_REAL`        | Entero con parte decimal opcional                     |
| `REGEX_NUM_HEXADECIMAL` | Pares de dígitos hexadecimales separados por espacios |
| `REGEX_URL`             | Esquema, `localhost` / IP / dominio, puerto           |
| `REGEX_URN`             | Ruta, extensión y cadena de consulta                  |
| `REGEX_URI`             | La URL y la URN juntas                                |

De ellos salen `EsEntero`, `EsReal`, `EsURL`, `EsURN` y `EsURI` de
[Cadenas](Cadenas.md), que es como se usan en la práctica: casi nadie llama
directamente a `CumpleExpresionRegular`.

`REGEX_URI` es la composición literal de las otras dos, lo que hace que un URI
completo se valide de una pasada.

## Dependencias

`<string>` y `<regex>` de la estándar.

## Test

`ExpresionesRegularesTest.cpp` → `TestExpresionesRegulares()`.

## Observaciones

- **`REGEX_NUM_HEXADECIMAL` acepta la `G`.** El juego de caracteres es
  `[0-9ABCDEFGabcdefg]`, con una `g` de más en los dos casos: en hexadecimal los
  dígitos llegan hasta la `F`. Un `"GG"` pasa la validación.
- **Y exige pares con espacios.** El patrón es `([0-9A-Fa-f]{2} ?)+`, de modo que
  reconoce `FF 0A 1B` —un volcado de bytes— pero no `0xFF` ni `FFF`. Es
  coherente con el `CadenaHex()` de [Conversor](Conversor.md) si éste separa los
  bytes, y no sirve para validar un literal hexadecimal de código.
- **`REGEX_NUM_REAL` no admite exponente.** `1.5e-3` no pasa, aunque
  `ToDouble` sí lo convierta, así que `EsReal ( s )` puede decir que no y la
  conversión funcionar. Tampoco admite el `+` inicial.
- **La función compila el patrón en cada llamada.** `std::regex` es caro de
  construir, y al recibir el patrón como `std::string` no hay forma de reutilizar
  el autómata: validar mil líneas compila la expresión mil veces. Un
  `std::regex` estático por patrón —o una sobrecarga que acepte uno ya
  construido— resolvería el coste allí donde importa.
- **Los patrones son `#define`, no constantes.** En un componente C++ que usa
  `constexpr` en [Real](Real.md) y `const std::string` en
  [TerminalANSI](Configuracion.md), estos seis van por macro, sin tipo ni
  espacio de nombres.
- **No hay extracción**, sólo comprobación: no se puede obtener el esquema, el
  puerto o la ruta de una URI reconocida. Para eso el stack tiene la clase `URI`,
  pero en [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md).
