# Conversor

| Dato      | Valor                                           |
| --------- | ----------------------------------------------- |
| Cabecera  | `src/main/include/Conversor.h` (122 líneas)     |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Conversor.cpp` |
| Espacio   | `org::gjs::cpp::common`                         |
| Deriva de | —                                               |
| Test      | `ConversorTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **valor de un tipo cualquiera, leído como cualquier otro**. Se le da un
entero y se le pide una cadena; se le da una cadena y se le pide un real.

Es la contraparte C++ de
[SConversor](../../gjs-c-common-base/doc/SConversor.md) del stack C, con la
diferencia de que aquí la sobrecarga permite que constructor y asignador se
llamen igual para los trece tipos.

```cpp
Conversor conv ( "3.1416" );

if ( conv.EsCadenaNumericaReal () )
{
    double d = conv.RealDoble ();
}

conv.EstablecerValor ( 255 );
std::string sHex = conv.CadenaHex ();      // "FF"
```

## La API

### Construcción y asignación

Trece sobrecargas de cada una, para `int`, `long`, `long long`, sus versiones
sin signo, `float`, `double`, `long double`, `std::string` —por valor y
constante— y `char *` —por valor y constante—.

| Grupo                      | Métodos                                  |
| -------------------------- | ---------------------------------------- |
| Constructores              | `Conversor ()` más las trece sobrecargas |
| `EstablecerValor ( … )`    | Las mismas trece                         |
| `EstablecerValorHex ( … )` | Cuatro, sólo para texto                  |

### Lectura

| Método                        | Devuelve                |
| ----------------------------- | ----------------------- |
| `Entero ()`                   | `int`                   |
| `EnteroLargo ()`              | `long`                  |
| `EnteroDobleLargo ()`         | `long long`             |
| `EnteroSinSigno ()`           | `unsigned int`          |
| `EnteroLargoSinSigno ()`      | `unsigned long`         |
| `EnteroDobleLargoSinSigno ()` | `unsigned long long`    |
| `Real ()`                     | `float`                 |
| `RealDoble ()`                | `double`                |
| `RealDobleLargo ()`           | `long double`           |
| `Cadena ()`                   | `const std::string &`   |
| `CadenaHex ()`                | El valor en hexadecimal |

### Comprobación

| Método                           | Responde a                        |
| -------------------------------- | --------------------------------- |
| `EsCadenaNumerica ()`            | ¿El texto es un número?           |
| `EsCadenaNumericaEntera ()`      | ¿Entero?                          |
| `EsCadenaNumericaReal ()`        | ¿Real?                            |
| `EsCadenaNumericaHexadecimal ()` | ¿Hexadecimal?                     |
| `ConversionValida ()`            | ¿La última conversión salió bien? |

`ConversionValida()` es lo que distingue un cero legítimo de un texto que no se
pudo convertir, y hay que consultarlo después de cada lectura.

## Dependencias

`<string>` y nada más del stack.

## Test

`ConversorTest.cpp` → `TestConversor()`.

## Observaciones

- **Guarda diez campos, uno por tipo, y todos a la vez.** La estructura tiene un
  `int`, un `long`, un `long long`, sus tres versiones sin signo, tres reales y
  un `std::string`: unas 80 bytes por objeto para representar un solo valor.
  Es la traducción literal del `SConversor` de C, donde se hacía con una
  estructura equivalente; en C++ lo natural sería un `std::variant` o
  simplemente guardar el texto y convertir al leer.
- **No hay forma de saber qué tipo tiene dentro.** No existe un `Tipo()` ni un
  `EsEntero()` sobre el valor guardado —los cuatro predicados preguntan por el
  **texto**—, así que el llamante tiene que acordarse de lo que metió.
- **`Cadena()` devuelve una referencia constante al campo interno.** Es eficiente
  y es lo correcto, pero significa que la referencia se invalida en el siguiente
  `EstablecerValor`; el resto de lecturas devuelven por valor.
- **`EstablecerValorHex` sólo acepta texto**, de modo que no hay camino de
  entrada hexadecimal desde un entero; la salida sí existe, con `CadenaHex()`.
- **Las trece sobrecargas de `EstablecerValor` incluyen `std::string &` y
  `const std::string &`**, que en C++ es un par innecesario: la segunda acepta
  todo lo que acepta la primera. Lo mismo con `char *` y `const char *`. Son
  cuatro sobrecargas donde bastan dos, y complican la resolución para el
  compilador.
- **`Inicializar()` es privada y no hay constructor de copia declarado** pese a
  que la clase tiene diez campos de estado. Funciona con los implícitos, pero
  con `std::string` dentro conviene dejarlo escrito.
