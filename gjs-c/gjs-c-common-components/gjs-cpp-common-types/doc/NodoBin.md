# NodoBin

| Dato      | Valor                                    |
| --------- | ---------------------------------------- |
| Cabecera  | `src/main/include/NodoBin.h` (77 líneas) |
| Fuente    | `NodoBin.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                  |
| Deriva de | `IToString`                              |
| Test      | `NodoBinTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El nodo de un [ArbolBin](ArbolBin.md): unos datos, dos subárboles y el padre.

```cpp
class NodoBin : public IToString
{
private:
    void *     datos;
    ArbolBin * arbolDer;
    ArbolBin * arbolIzq;
    NodoBin *  nodoPadre;
    …
};
```

Guarda el **padre** además de los hijos, que es lo que permite recorrer el árbol
sin pila auxiliar: los tres `Sig…` suben y bajan por los enlaces.

## La API

### Estructura

| Método                                                  | Qué responde                                                   |
| ------------------------------------------------------- | -------------------------------------------------------------- |
| `TieneHijoDer ()` / `TieneHijoIzq ()` / `TieneHijos ()` | Si cuelga algo.                                                |
| `TienePadre ()`                                         | Si es raíz o no.                                               |
| `EsHijoDer ()` / `EsHijoIzq ()`                         | De qué lado cuelga.                                            |
| `getHijoDer ()` / `getHijoIzq ()`                       | Los subárboles.                                                |
| `getPadre ()`                                           | El nodo de arriba.                                             |
| `setHijoDer ( … )` / `setHijoIzq ( … )`                 | Por `ArbolBin *` o por `NodoBin *`, con bandera de liberación. |
| `setPadre ( NodoBin *, bool )`                          | Idem.                                                          |

### Recorrido

`SigPreorden ()`, `SigPostorden ()`, `SigInorden ()`, que continúan el recorrido
empezado con los `Primero…` de [ArbolBin](ArbolBin.md).

### Datos

`getDatos ()`, `setDatos ( void * )`, `EsValido ()`, y dos virtuales **privados**
pensados para redefinir:

```cpp
private:
    virtual void        LiberarDatos  ( void * _datos );
    virtual std::string DatosToString ( void * _datos );
```

Ése es el punto de extensión de la clase: una derivada dice cómo se liberan y
cómo se imprimen sus datos, y el nodo se encarga del resto. Es el idioma de la
interfaz no virtual, el mismo de `getHash()` en
[IComparable](../../gjs-cpp-common-base/doc/IComparable.md).

## Dependencias

[ArbolBin](ArbolBin.md) —con declaración adelantada, porque las dos clases se
refieren la una a la otra— e `IToString`.

## Test

`NodoBinTest.cpp` → `TestNodoBin()`.

## Observaciones

- **`LiberarDatos` y `DatosToString` son privadas y virtuales, y eso está bien
  pensado**: la derivada las redefine y nadie de fuera las llama. Merece la pena
  señalarlo porque es el único sitio del componente donde el idioma se usa a
  conciencia.

  Lo que falta es decirlo en la cabecera: sin comentario, un lector que quiera
  extender el nodo no tiene forma de saber que ése es el gancho, y que redefinir
  algo privado es legal en C++.
- **La bandera `bLiberar` de los `setHijo…` y `setPadre` no dice de qué.** ¿Libera
  el hijo que había antes, o marca que este nodo pasa a ser dueño del nuevo? Con
  el valor por defecto a `true` y sin documentación, es la clase de parámetro que
  se acaba pasando por inercia.
- **`setPadre` con bandera de liberación es más raro todavía**: liberar el padre
  desde el hijo invierte la propiedad natural del árbol.
- **`datos` es `void *`**, con lo que ya está dicho en
  [ArbolBin](ArbolBin.md): sin plantilla, sin seguridad de tipos, y con un molde
  en cada uso.
- **`EsValido()` no es `const`**, como en casi todo el componente.
- **La pareja árbol-nodo duplica la información de estructura.** El nodo conoce a
  su padre y el árbol a su raíz; mantener los dos enlaces coherentes en cada
  `setHijo…`, `setPadre` y `Empadrar…` es responsabilidad del código, y no hay
  ninguna comprobación que lo verifique —ni un `EsCoherente()` como el `isValid()`
  de [MapaVector](MapaVector.md), que sí reconoce el problema equivalente—.
