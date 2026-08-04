# Valor

| Dato      | Valor                                  |
| --------- | -------------------------------------- |
| Cabecera  | `src/main/include/Valor.h` (97 líneas) |
| Fuente    | `Valor.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                |
| Deriva de | `IComparable`                          |
| Test      | `ValorTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un dato de cualquier tipo primitivo, **guardado como texto**, que se puede leer
como número, como real o como booleano.

```cpp
class Valor : public IComparable
{
private:
    std::string sDato;
    bool        bNulo;
    …
};
```

Es la contraparte de [SValor](../../gjs-c-common-types/doc/SValor.md) del stack
C, y comparte con ella la decisión de almacenar todo como cadena. Lo que cambia
es la interfaz: allí 88 funciones con el tipo en el nombre; aquí **17
constructores y 16 `setValor` sobrecargados**, todos con el mismo nombre.

```cpp
Valor valEdad ( 42 );
Valor valNombre ( "Ana" );

long lEdad = valEdad.getValorEntero ();

if ( valNombre.EsNulo () ) { … }
valNombre.Anular ();
```

## La API

### Construcción

Diecisiete constructores: uno por defecto, uno por cada tipo primitivo —los
cuatro enteros con y sin signo, los tres reales, `char`, `unsigned char`,
`bool`—, dos para texto y dos de copia. Todos **`explicit`** menos el de copia,
de modo que no hay conversiones implícitas por sorpresa.

### Lectura

| Método                   | Devuelve           |
| ------------------------ | ------------------ |
| `getValor ()`            | El texto guardado. |
| `getValorBool ()`        | `bool`             |
| `getValorEntero ()`      | `long`             |
| `getValorEnteroLargo ()` | `long long`        |
| `getValorReal ()`        | `double`           |
| `getValorRealLargo ()`   | `long double`      |

### Nulo

`EsNulo ()` y `Anular ()`. El nulo es un estado aparte del contenido, lo que
permite distinguir «cero» de «sin valor» —cosa que el
[SValor](../../gjs-c-common-types/doc/SValor.md) de C no hace—.

### El resto

`setValor` en dieciséis sobrecargas, `Asignar`, `Clonar`, `EsValido`,
`getHash`, `toString`, y los operadores `=`, `==` y `!=`.

## Dependencias

`IComparable` de [gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).

## Test

`ValorTest.cpp` → `TestValor()`.

## Observaciones

> **El constructor de copia recibe una referencia no constante:**
> `Valor ( Valor & obj );`
>
> Con esa firma no se puede copiar de un `const Valor &` ni de un temporal, de
> modo que `Valor v2 ( f () );` no compila si `f` devuelve por valor, y una
> función que reciba `const Valor &` no puede quedarse con una copia. Lo mismo
> ocurre con `operator=`, `operator==` y `operator!=`, ninguno `const`.
>
> Es el mismo descuido que arrastran las interfaces de
> [gjs-cpp-common-base](../../gjs-cpp-common-base/doc/IComparable.md), y aquí
> pesa más porque `Valor` es un tipo de dato que se pasa y se copia
> constantemente.

- **Ninguna lectura dice si la conversión ha funcionado.** `getValorEntero()`
  sobre `"hola"` devuelve algo, y no hay `ConversionValida()` como en el
  [Conversor](../../gjs-cpp-common-base/doc/Conversor.md) del componente raíz,
  ni excepción documentada. Un `EsValido()` existe, pero comprueba el objeto, no
  la convertibilidad al tipo que se pide.
- **`getValorEntero()` devuelve `long`**, con el mismo desajuste de nombre que
  `ToInt` en base. No hay lectura como `int` ni como los tipos sin signo, pese a
  que sí se puede construir con ellos: **se puede escribir un
  `unsigned long long` y no leerlo de vuelta sin pasar por `long long`**.
- **No hay tipo.** El objeto guarda el texto y el nulo, y nada más: no recuerda
  con qué tipo se construyó. Para eso está [Tipo](Tipo.md), pero como clase
  aparte, de modo que un `Valor` suelto no sabe lo que es. `Atributo::EsCompatible ( Valor & )`
  es quien cruza las dos cosas.
- **`Clonar()` devuelve `Valor *` desnudo**, no virtual, con la misma cuestión de
  propiedad que [Objeto::clonar](../../gjs-cpp-common-base/doc/Objeto.md).
- **`EsValido` es `virtual` y no lleva `override`**: no redefine nada, porque ni
  `IComparable` ni `IToString` lo declaran. Es un método nuevo con nombre de
  redefinición, y las clases hermanas lo escriben cada una a su manera —`EsValida`
  en [Entidad](Entidad.md) y en [ListaValores](ListaValores.md), `EsValido` en
  [ConjuntoValores](ConjuntoValores.md)—.
- **`getHash()` es público aquí y protegido en [Tipo](Tipo.md)**, siendo privado
  en la interfaz de la que los dos derivan. Tres niveles de acceso para el mismo
  método en la misma jerarquía.
