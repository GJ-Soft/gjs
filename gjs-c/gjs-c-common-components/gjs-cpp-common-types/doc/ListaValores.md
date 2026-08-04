# ListaValores

| Dato      | Valor                                         |
| --------- | --------------------------------------------- |
| Cabecera  | `src/main/include/ListaValores.h` (69 líneas) |
| Fuente    | `ListaValores.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                       |
| Deriva de | `IToString`                                   |
| Test      | `ListaValoresTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un vector de [Valor](Valor.md) accesible **por posición**. Es la fila de datos
cuando lo que importa es el orden de las columnas y no su nombre —para eso está
[ConjuntoValores](ConjuntoValores.md)—.

```cpp
class ListaValores : public IToString
{
private:
    std::vector<Valor *> vecValores;
    bool                 bPermiteInsercion = true;
    …
};
```

```cpp
ListaValores lisFila ( 3, false );      // tres huecos, sin admitir mas

lisFila.InsertarValor ( 42 );
lisFila.InsertarValor ( "Ana" );
lisFila.InsertarValor ( 1250.75 );

Valor * p_valNombre = lisFila.getValor ( 1 );
```

## La API

| Método                        | Qué hace                                                             |
| ----------------------------- | -------------------------------------------------------------------- |
| `ListaValores ()`             | Vacía, admite inserciones.                                           |
| `ListaValores ( iTam, bool )` | Con tamaño y política de inserción.                                  |
| `NumValores ()`               | Cuántos hay.                                                         |
| `getValor ( int )`            | Por posición.                                                        |
| `InsertarValor ( … )`         | **Diecisiete sobrecargas**: un `Valor *` o cualquier tipo primitivo. |
| `EliminarValor ( int )`       | Por posición.                                                        |
| `LimpiarValores ()`           | Los quita todos.                                                     |
| `EsValida ()`                 | Estado.                                                              |
| `toString ()`                 | Volcado.                                                             |

Las diecisiete sobrecargas de `InsertarValor` son lo que hace cómoda la clase:
se le pasa el dato en bruto y ella construye el `Valor`.

`bPermiteInsercion` es la parte interesante: una lista creada con tamaño fijo
—el segundo parámetro a `false`— rechaza inserciones nuevas, de modo que sirve
como fila de una tabla con un número de columnas ya decidido.

## Dependencias

[Valor](Valor.md) e `IToString`.

## Test

`ListaValoresTest.cpp` → `TestListaValores()`.

## Observaciones

> **Declara `getHash()` sin heredarlo de nadie.**
>
> ```cpp
> class ListaValores : public IToString
> {
> protected:
>     virtual long getHash() const;
> ```
>
> `getHash()` es el método puro de
> [IComparable](../../gjs-cpp-common-base/doc/IComparable.md), no de
> `IToString`. Al derivar sólo de la segunda, esta declaración **no redefine
> nada**: es un virtual nuevo, protegido, que nadie llama y que no habilita
> ninguna comparación.
>
> O la clase quería ser `IComparable` —y entonces le falta cambiar la base, con
> lo que ganaría los seis operadores— o el método sobra. Lo mismo ocurre en
> [ConjuntoValores](ConjuntoValores.md).

- **El valor por defecto de `bPermiteInsercion` se contradice.** El campo se
  inicializa a `true` y el parámetro del constructor con tamaño tiene por
  defecto `false`:

  ```cpp
  bool bPermiteInsercion = true;
  ListaValores ( int _iTam, bool _bPermiteInsercion = false );
  ```

  De modo que `ListaValores ()` admite inserciones y `ListaValores ( 3 )` no.
  Es defendible —quien fija un tamaño quiere ese tamaño— pero conviene saberlo,
  porque los dos constructores se leen igual.
- **La lista posee los `Valor *`** y no lo dice. `InsertarValor ( Valor * )`
  acepta un puntero de fuera; las otras dieciséis construyen dentro. Quien pase
  un puntero propio no sabe si puede seguir usándolo ni si debe liberarlo.
- **`getValor` devuelve el puntero interno**, modificable, sin `const`.
- **No hay `setValor ( int, … )`.** Se puede insertar y eliminar por posición,
  pero no sustituir: hay que borrar y volver a insertar, cambiando el orden.
- **`EsValida()` no es `const`**, a diferencia del `EsValido()` de
  [ConjuntoValores](ConjuntoValores.md), que sí lo es. Dos clases hermanas y dos
  firmas.
- **Con la inserción cerrada no hay forma de saberlo desde fuera**: no hay
  `PermiteInsercion()`, así que un `InsertarValor` sobre una lista cerrada falla
  sin que el llamante pueda preguntarlo antes —ni enterarse después, porque el
  método devuelve `void`—.
