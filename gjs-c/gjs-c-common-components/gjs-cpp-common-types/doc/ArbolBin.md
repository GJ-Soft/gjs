# ArbolBin

| Dato      | Valor                                     |
| --------- | ----------------------------------------- |
| Cabecera  | `src/main/include/ArbolBin.h` (57 líneas) |
| Fuente    | `ArbolBin.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                   |
| Deriva de | `IToString`                               |
| Test      | `ArbolBinTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un árbol binario sobre datos sin tipo. Junto con [NodoBin](NodoBin.md) forma una
pareja donde **el árbol es el que tiene raíz** y el nodo el que tiene hijos:

```cpp
class ArbolBin : public IToString
{
private:
    NodoBin * nodoRaiz;
    …
};
```

Un `ArbolBin` es un nodo raíz, y cada `NodoBin` tiene dos `ArbolBin *` como
hijos. La recursión se reparte entre las dos clases en lugar de que el nodo
apunte directamente a otros nodos.

## La API

| Método                                   | Qué hace                              |
| ---------------------------------------- | ------------------------------------- |
| `ArbolBin ()`                            | Vacío.                                |
| `ArbolBin ( NodoBin * )` / `( void * )`  | Con raíz, o con los datos de la raíz. |
| `TieneRaiz ()`                           | Si hay algo.                          |
| `Tam ()`                                 | Número de nodos.                      |
| `Profundidad ()`                         | Altura.                               |
| `getRaiz ()` / `setRaiz ( … )`           | La raíz, por nodo o por datos.        |
| `EmpadrarPorDer ( … )` / `…PorIzq ( … )` | **Mete un padre nuevo por encima.**   |
| `Vaciar ()`                              | Lo deja vacío.                        |
| `PrimeroPreorden ()`                     | El primero en preorden.               |
| `PrimeroPostorden ()`                    | En postorden.                         |
| `PrimeroInorden ()`                      | En inorden.                           |
| `toString ()`                            | Volcado.                              |

`EmpadrarPorDer` y `EmpadrarPorIzq` son la operación característica: en lugar de
colgar un hijo, **cuelgan un padre** —el árbol actual pasa a ser el hijo derecho
o izquierdo del nodo nuevo—. Es lo que hace falta para construir un árbol de
expresión de abajo arriba, según van llegando los operadores.

## Los recorridos

Los tres `Primero…` devuelven el primer nodo de cada orden, y a partir de ahí se
avanza con los `Sig…` de [NodoBin](NodoBin.md):

```cpp
NodoBin * p_nodo = arbol.PrimeroInorden ();

while ( p_nodo != NULL )
{
    /* … */
    p_nodo = p_nodo->SigInorden ();
}
```

Es un iterador repartido entre las dos clases, sin objeto iterador de por medio.

## Dependencias

[NodoBin](NodoBin.md) e `IToString`.

## Test

`ArbolBinTest.cpp` → `TestArbolBin()`.

## Observaciones

- **Los datos son `void *`.** Todo el árbol es genérico por la vía de C, no por
  plantillas, en un componente que sí tiene [Ptr\<T\>](Ptr.md) y
  [MapaVector\<T\>](MapaVector.md). Un `template<typename T> class ArbolBin`
  daría seguridad de tipos y ahorraría los moldes en cada acceso. La razón
  probable es que se tradujo del `SArbolBin` del stack C, donde no había
  alternativa.
- **Sin árbol de búsqueda.** No hay `Insertar` ordenado, ni `Buscar`, ni
  comparador: es una estructura de árbol, no un contenedor asociativo. Para
  ordenar hay que hacerlo desde fuera con los `Empadrar…`.
- **`Tam()` y `Profundidad()` se recalculan en cada llamada**, presumiblemente
  recorriendo el árbol entero, sin caché. En un bucle que consulte el tamaño en
  cada vuelta eso es cuadrático.
- **No hay iterador ni `begin`/`end`**, de modo que el árbol no se puede recorrer
  con un `for` de rango ni pasar a los algoritmos de la estándar.
- **`setRaiz` no dice qué hace con la raíz anterior**, ni si la libera. Con
  `Vaciar()` al lado, lo esperable es que no, y entonces sustituir la raíz pierde
  el árbol viejo.
- **La copia y la asignación están borradas** (`= delete`, desde 2026-10-11),
  como en [Ptr](Ptr.md): con la implícita, copiar un `ArbolBin` copiaba el
  puntero y las dos copias borraban el mismo árbol. Lo mismo se hizo en
  `ListaValores` y `ConjuntoValores`. No hay movimiento.
