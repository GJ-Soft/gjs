# Objeto

| Dato      | Valor                                        |
| --------- | -------------------------------------------- |
| Cabecera  | `src/main/include/Objeto.h`                  |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Objeto.cpp` |
| Espacio   | `org::gjs::cpp::common`                      |
| Deriva de | —                                            |
| Derivadas | `Depurador`                                  |
| Test      | `ObjetoTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **clase base universal al estilo de Java**: identidad, igualdad, copia y
representación textual para cualquier objeto que quiera heredarla.

```cpp
class Objeto
{
public:
    Objeto ();
    virtual ~Objeto ();

    std::string getTipo () const;
    virtual int  hash () const;
    virtual bool esValido () const;
    size_t       getTam () const;
    Objeto *     clonar ();
    virtual bool equals ( Objeto & objeto ) const;
    virtual bool equals ( Objeto * objeto ) const;
    virtual std::string toString ();

protected:
    virtual void assignar ( Objeto & objeto );

public:
    Objeto & operator=  ( Objeto & objeto );
    bool     operator== ( Objeto & objeto );
    bool     operator!= ( Objeto & objeto );
};
```

## La API

| Método        | Qué da                                           |
| ------------- | ------------------------------------------------ |
| `getTipo ()`  | El nombre del tipo real, por RTTI.               |
| `getTam ()`   | El tamaño en bytes del objeto real.              |
| `hash ()`     | Un entero para tablas de dispersión.             |
| `esValido ()` | Si el objeto está en un estado utilizable.       |
| `clonar ()`   | Una copia en memoria dinámica.                   |
| `equals ()`   | Igualdad, en versión referencia y puntero.       |
| `toString ()` | Representación textual.                          |
| `assignar ()` | El gancho protegido en que se apoya `operator=`. |

`getTipo` es lo mejor de la clase: resuelve `typeid ( *this )` y **desmangla el
nombre** con `abi::__cxa_demangle`, de modo que devuelve `Depurador` y no
`9Depurador`. No hace falta que las derivadas declaren nada.

`assignar` protegido con `operator=` público encima es el patrón que permite a
las derivadas extender la asignación sin reescribir el operador.

## Lo que hace la implementación base

Casi todos los métodos son ganchos vacíos a la espera de que alguien los
redefina:

| Método        | En `Objeto`                            |
| ------------- | -------------------------------------- |
| `hash ()`     | Devuelve **0**, siempre.               |
| `esValido ()` | Devuelve **`true`**, siempre.          |
| `assignar ()` | Cuerpo **vacío**.                      |
| `equals ()`   | Compara `getTipo()` y luego `hash()`.  |
| `toString ()` | `[Objeto={Tipo=…}]`                    |
| `clonar ()`   | `new Objeto()` y le aplica `assignar`. |

## Dependencias

`<string>` y nada más. Es la clase más independiente del componente.

## Test

`ObjetoTest.cpp` → `TestObjeto()`.

## Observaciones

> **`Objeto` y las interfaces del componente son dos diseños incompatibles para
> el mismo problema**, y conviven sin tocarse:
>
> | Concepto     | En `Objeto`             | En las interfaces                 |
> |--------------|-------------------------|-----------------------------------|
> | Texto        | `virtual std::string toString ()` | `IToString::toString () = 0` |
> | Dispersión   | `virtual int hash () const`       | `IComparable::getHash () const = 0`, **`long`** |
> | Igualdad     | `equals ()`, `operator==`         | `esIgual ()`, `operator==`   |
>
> `Objeto` **no deriva de `IToString`** pese a tener el mismo método, así que un
> `Objeto` no se puede pasar a `ToString ( IToString & )` ni meter en las
> colecciones que el stack construye sobre esa interfaz.
>
> En la práctica ha ganado la vía de las interfaces: los contenedores de
> [gjs-cpp-common-types](../../gjs-cpp-common-types/README.md) derivan de
> `IToString`, y de `Objeto` sólo cuelga [Depurador](Depurador.md). Lo coherente
> sería que `Objeto` implementara `IComparable`, o retirar una de las dos.

> **`equals()` da `true` para dos objetos distintos del mismo tipo.** Compara el
> tipo y después el `hash()`, que en la base **devuelve 0 siempre**:
>
> ```cpp
> int Objeto::hash () const { return ( 0 ); }
>
> bool Objeto::equals ( Objeto & objeto ) const
> {
>     if ( getTipo ().compare ( objeto.getTipo () ) == 0 )
>     {
>         bRes = ( hash () == objeto.hash () );   // 0 == 0
>     }
> }
> ```
>
> Una derivada que no redefina `hash()` hereda una igualdad que sólo mira el
> tipo: dos instancias con contenidos distintos salen iguales, y `operator==`
> con ellas también. Como `hash()` es virtual y sin cuerpo útil, lo natural sería
> declararlo **puro** —`virtual int hash () const = 0;`— y obligar a las
> derivadas a definirlo, en lugar de darles un valor por defecto que miente.

- **`getTam()` devuelve siempre el tamaño de `Objeto`.** Está implementado como
  `sizeof ( *this )`, y `sizeof` **no es polimórfico**: `*this` es de tipo
  estático `Objeto`, así que una derivada de 200 bytes también informa del
  tamaño de la base. A diferencia de `getTipo()`, que sí acierta porque `typeid`
  sobre un tipo polimórfico consulta en ejecución.
- **`clonar()` no es virtual y siempre construye un `Objeto`.** El cuerpo es
  `new Objeto ()` seguido de `assignar`, de modo que clonar una derivada
  devuelve la parte base: el *slicing* clásico. Lo esperable sería
  `virtual Objeto * clonar () const` redefinido en cada derivada.
- **`assignar()` tiene el cuerpo vacío**, así que `operator=` no copia nada.
  Es coherente con que sea un gancho, pero significa que asignar dos `Objeto`
  es una operación nula que aparenta no serlo.
- **`getTipo()` depende de GCC.** Usa `<cxxabi.h>` y `abi::__cxa_demangle`, que
  no existen en Visual C. El resto del stack mantiene ramas `#if defined ( VC )`;
  ésta no, de modo que el componente no compilaría con ese compilador.
- **`hash()` devuelve `int` y `getHash()` de [IComparable](IComparable.md)
  devuelve `long`.** Dos tipos para el mismo concepto en el mismo componente.
- **`clonar()` devuelve `Objeto *` sin decir quién lo libera.** No hay
  `std::unique_ptr` ni indicación en la cabecera; el llamante tiene que saberlo
  por convenio.
- **`equals` es `const` pero `operator==` no lo es.** Comparar dos objetos
  constantes no compila por el operador, sólo por el método. Igual con
  `toString()`, que tampoco es `const`.
