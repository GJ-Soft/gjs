# Codificacion

| Dato      | Valor                                              |
| --------- | -------------------------------------------------- |
| Cabecera  | `src/main/include/Codificacion.h` (34 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Codificacion.cpp` |
| Espacio   | `org::gjs::cpp::common`                            |
| Funciones | 4                                                  |
| Test      | `CodificacionTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El puente entre `std::wstring` y `std::string`: pasar de texto ancho a UTF‑8 o
UTF‑16 y volver.

```cpp
std::string  UnicodeAUtf8  ( const std::wstring & valor );
std::string  UnicodeAUtf16 ( const std::wstring & valor );
std::wstring Utf8AUnicode  ( const std::string & valor );
std::wstring Utf16AUnicode ( const std::string & valor );
```

Cuatro funciones, dos de ida y dos de vuelta. Hacen falta en el borde con el
sistema: la API ancha de Windows devuelve `wchar_t *`, y el resto del stack
—como el repositorio— trabaja en UTF‑8.

Es el equivalente C++ de
[UniChar](../../gjs-c-common-base/doc/UniChar.md) del stack C, con la ventaja de
que aquí no hay que reservar búferes ni llevar longitudes.

## Dependencias

`<string>`.

## Test

`CodificacionTest.cpp`. En la salida de la suite aparece rotulado como
`[Test Cadenas]`, igual que `CadenasTest.cpp`, de modo que los dos son
indistinguibles en el registro de la compilación.

## Observaciones

- **`wchar_t` no mide lo mismo en todas partes.** Son 2 bytes en Windows y en
  Cygwin, y 4 en Linux y macOS. Es decir: `UnicodeAUtf16` sobre un `wchar_t` de
  2 bytes es casi una copia, y sobre uno de 4 es una conversión de verdad con
  pares suplentes. Las funciones existen para tapar esa diferencia, y conviene
  saber que el `wchar_t` de un lado no es el del otro —es la misma cuestión que
  quedó anotada en [UniChar](../../gjs-c-common-base/doc/UniChar.md) del stack
  C—.
- **Ninguna dice qué hace con una entrada mal formada.** Una secuencia UTF‑8
  inválida en `Utf8AUnicode` no tiene contrato: ni excepción documentada, ni
  carácter de reemplazo, ni forma de saber que se ha perdido algo. Y en este
  módulo el caso no es raro: convertir un fichero en otra codificación es
  precisamente lo que se hace con estas funciones.
- **No hay conversión de o a las páginas de códigos heredadas**, en particular
  la 850, que sí aparece en el stack —`gjs-c-common-support` dibuja sus marcos
  con ella y `gjs-c-common-io` tiene `CF_OEMTEXT`—. El puente con esa parte del
  mundo hay que hacerlo fuera.
- **Los parámetros se llaman `valor`, sin notación húngara**, a diferencia del
  resto del componente. Detalle menor, pero es el único sitio donde el convenio
  se rompe en las cuatro funciones a la vez.
