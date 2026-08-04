# Atributo

| Dato      | Valor                                     |
| --------- | ----------------------------------------- |
| Cabecera  | `src/main/include/Atributo.h` (72 líneas) |
| Fuente    | `Atributo.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                   |
| Deriva de | [`Tipo`](Tipo.md)                         |
| Test      | `AtributoTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un [Tipo](Tipo.md) con nombre y con la marca de si admite nulos. Es la columna
de una tabla: la pieza con la que [Entidad](Entidad.md) describe su forma.

```cpp
class Atributo : public Tipo
{
private:
    TipoDatos   tipo;          // <- ojo con éste
    std::string sNombre;
    bool        bAnulable;
    …
};
```

```cpp
Atributo atrNombre ( TipoDatos::CADENA, "nombre", false );

if ( atrNombre.EsCompatible ( valEntrada ) ) { … }
```

## La API

| Método                                         | Qué hace                   |
| ---------------------------------------------- | -------------------------- |
| `getNombre ()` / `setNombre ( … )`             | El nombre de la columna.   |
| `isAnulable ()` / `setAnulable ( bool )`       | Si admite nulo.            |
| `EsCompatible ( Atributo & )`                  | Si dos atributos encajan.  |
| `EsCompatible ( Valor & )`                     | **Si un valor cabe aquí.** |
| `Asignar` / `Clonar` / `EsValido` / `toString` | El guion común.            |

`EsCompatible ( Valor & )` es la razón de ser de la clase: cruza el tipo
heredado con el contenido de un [Valor](Valor.md) y, con `bAnulable`, decide si
el dato es admisible. Es la validación de una celda contra su columna.

El constructor acepta el tipo de dos formas —`TipoDatos` o `Tipo &`— y
`bAnulable` por defecto a `true`.

## Dependencias

[Tipo](Tipo.md) y [Valor](Valor.md).

## Test

`AtributoTest.cpp` → `TestAtributo()`.

## Observaciones

> **`Atributo` vuelve a declarar el campo `tipo` que ya tiene su base.**
>
> ```cpp
> class Tipo : public IComparable
> {
> private:
>     TipoDatos tipo;      // el de la base
> …
> class Atributo : public Tipo
> {
> private:
>     TipoDatos tipo;      // otro, que tapa al anterior
> ```
>
> El objeto acaba con **dos campos `TipoDatos`**. Los métodos de `Atributo` ven
> el suyo; los heredados de `Tipo` —`getTipo()`, `setTipo()`, `isEntero()`,
> `isReal()`, `EsCompatible ( const std::string & )` y el `getHash()` de la
> base— siguen leyendo y escribiendo el de `Tipo`.
>
> La consecuencia práctica depende de por dónde se entre: si el constructor
> rellena los dos, todo cuadra hasta que alguien llame a `setTipo()`, que sólo
> cambia el de la base y deja el del `Atributo` con el valor viejo. A partir de
> ahí `getTipo()` y `EsCompatible ( Valor & )` responden cosas distintas sobre
> el mismo objeto.
>
> El arreglo es quitar la línea: el campo de la base ya está, y `Tipo` ofrece
> `getTipo()` y `setTipo()` para llegar a él.

- **`getHash()` vuelve a ser público aquí**, siendo `protected` en
  [Tipo](Tipo.md) y privado en `IComparable`. La cadena de tres clases usa tres
  niveles de acceso para el mismo método.
- **`EsValido()` sí lleva `override`**, a diferencia del de
  [Valor](Valor.md), porque aquí sí hay uno en la base. Es el único de la familia
  que lo marca.
- **`isAnulable` en inglés, `EsCompatible` en castellano**, dentro de la misma
  clase. Hereda la mezcla de [Tipo](Tipo.md).
- **La herencia es discutible.** Un atributo *tiene* un tipo más que *es* un
  tipo: con `Atributo : public Tipo`, un `Atributo` se puede pasar a cualquier
  función que espere `Tipo &`, perdiendo el nombre y la anulabilidad. La
  composición —un campo `Tipo` con `getTipo()` delegado— evitaría además el
  problema del campo duplicado.
