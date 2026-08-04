# Tipo

| Dato      | Valor                                 |
| --------- | ------------------------------------- |
| Cabecera  | `src/main/include/Tipo.h` (68 líneas) |
| Fuente    | `Tipo.cpp`                            |
| Espacio   | `org::gjs::cpp::common`               |
| Deriva de | `IComparable`                         |
| Derivadas | `Atributo`                            |
| Test      | `TipoTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El enumerado [TipoDatos](TipoDatos.md) convertido en objeto: comparable,
volcable y con predicados.

```cpp
class Tipo : public IComparable
{
private:
    TipoDatos tipo;
    …
};
```

## La API

| Método                                         | Qué hace                         |
| ---------------------------------------------- | -------------------------------- |
| `getTipo ()` / `setTipo ( TipoDatos )`         | El enumerado.                    |
| `isEntero ()`                                  | ¿`TipoDatos::ENTERO`?            |
| `isReal ()`                                    | ¿`TipoDatos::REAL`?              |
| `isCadena ()`                                  | ¿`TipoDatos::CADENA`?            |
| `isBooleano ()`                                | ¿`TipoDatos::BOOLEANO`?          |
| `EsCompatible ( Tipo & )`                      | Si dos tipos se pueden mezclar.  |
| `EsCompatible ( const std::string & )`         | Si un texto encaja en este tipo. |
| `Asignar` / `Clonar` / `EsValido` / `toString` | El guion común del componente.   |

`EsCompatible ( const std::string & )` es el método útil: dice si una cadena
—que es como [Valor](Valor.md) guarda todo— se puede interpretar como este
tipo. Es la validación que usa [Atributo](Atributo.md) antes de aceptar un
valor.

## Dependencias

[TipoDatos](TipoDatos.md) e `IComparable`.

## Test

`TipoTest.cpp` → `TestTipo()`.

## Observaciones

- **Los predicados están en inglés y el resto en castellano.** `isEntero`,
  `isReal`, `isCadena`, `isBooleano` conviven con `EsCompatible`, `EsValido` y
  `Asignar` en la misma clase. La forma `Es…` es la del resto del componente.
- **No hay predicado para `INDEFINIDO`.** Los cuatro `is…` cubren los cuatro
  tipos reales, y para saber si el tipo está sin fijar hay que comparar con
  `TipoDatos::INDEFINIDO` a mano —o llamar a `EsValido()`, que es lo que
  presumiblemente hace, aunque la cabecera no lo diga—.
- **`getHash()` es `protected`**, mientras que en [Valor](Valor.md),
  [Atributo](Atributo.md) y [Entidad](Entidad.md) es público y en la interfaz
  `IComparable` es privado. La derivada `Atributo` lo vuelve a subir a público.
- **El constructor de copia toma `Tipo &` no constante**, como en toda la
  familia: no se puede copiar de un `const Tipo &`.
- **`EsCompatible` no es simétrica en su documentación.** La cabecera no dice si
  `ENTERO` es compatible con `REAL`, ni en qué dirección, que es justo la
  pregunta que se hace al validar. Con cuatro tipos, una tabla de compatibilidad
  en la cabecera valdría más que las tres sobrecargas.
