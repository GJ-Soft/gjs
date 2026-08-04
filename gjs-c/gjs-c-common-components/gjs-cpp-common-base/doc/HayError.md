# HayError

| Dato      | Valor                                          |
| --------- | ---------------------------------------------- |
| Cabecera  | `src/main/include/HayError.h` (36 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/HayError.cpp` |
| Espacio   | `org::gjs::cpp::common`                        |
| Deriva de | —                                              |
| Test      | **Ninguno**                                    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una bandera de error para heredar. La clase entera es un `bool` con sus dos
accesos:

```cpp
class HayError
{
private:
    bool bError = false;

public:
    HayError ();
    virtual ~HayError ();

    bool isError ();
    void setError ( bool bValor );
};
```

La idea es que una clase que pueda quedar en estado de error herede de ésta y se
ahorre declarar la bandera. Es el patrón de estado de error que en el stack C
llevan los objetos con su `SXxxEsValido`.

## Dependencias

Ninguna.

## Test

**Ninguno.**

## Observaciones

- **Es una alternativa a las excepciones dentro del mismo componente.** El
  stack C++ señala los fallos lanzando [Excepcion](Excepcion.md); esta clase
  ofrece el camino contrario, el de consultar una bandera después de operar.
  Tener las dos vías disponibles obliga al usuario a saber cuál sigue cada
  clase, y en este componente **nadie hereda de `HayError`**.
- **Se solapa con `Objeto::esValido()`.** Dos formas de preguntar por el estado
  del objeto, en dos jerarquías que no se tocan. Ver [Objeto](Objeto.md).
- **`isError()` no es `const`**, de modo que no se puede consultar el error de un
  objeto constante. Es el mismo descuido que en
  [IToString](IToString.md) e [IComparable](IComparable.md).
- **El nombre es una frase, no un sustantivo.** `HayError` se lee como pregunta;
  las clases del resto del stack se llaman `Objeto`, `Conversor`, `Excepcion`.
  Algo como `EstadoError` encajaría mejor con una clase base.
- **`setError` acepta `true` y `false` pero no dice qué error.** Sin código ni
  mensaje, quien consulte sabe que algo falló y nada más; para eso ya está el
  `bool` de retorno de la propia función que falló.
- **Sin test**, siendo de las pocas clases del componente lo bastante pequeñas
  para probarla entera en diez líneas.
