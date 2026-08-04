# NoEncontradoExcepcion

| Dato      | Valor                                                       |
| --------- | ----------------------------------------------------------- |
| Cabecera  | `src/main/include/NoEncontradoExcepcion.h`                  |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/NoEncontradoExcepcion.cpp` |
| Espacio   | `org::gjs::cpp::common`                                     |
| Deriva de | [`Excepcion`](Excepcion.md)                                 |
| Test      | **Ninguno**                                                 |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La búsqueda que no encuentra nada. Es la excepción que lanzan los contenedores y
los gestores del stack cuando se les pide algo que no tienen.

```cpp
class NoEncontradoExcepcion : public Excepcion
{
public:
    NoEncontradoExcepcion ( const std::string & sModulo, const std::string & sRutina,
                            const std::string & sTipo,   const std::string & sObjeto );
};
```

Los dos parámetros propios son **qué se buscaba y cómo se llamaba**:

```cpp
throw NoEncontradoExcepcion ( "GestorUsuarios", "Buscar", "usuario", sLogin );
```

```
[GestorUsuarios::Buscar] No se ha encontrado el/la usuario [pepe]
```

Separar el tipo del identificador es lo que permite que el mensaje salga
compuesto sin que cada llamante escriba su propia frase.

## Dependencias

[Excepcion](Excepcion.md) y `Concatenar`.

## Test

**Ninguno.**

## Observaciones

- **`el/la` sale siempre así.** El texto se compone con la barra en el mensaje
  final —*"No se ha encontrado el/la usuario"*— porque la clase no sabe el
  género del sustantivo que le pasan. Es el precio de componer frases en
  castellano a partir de piezas; la alternativa sería pedir el artículo o
  redactar el mensaje sin él (*"No se ha encontrado: usuario [pepe]"*).
- **No guarda ni el tipo ni el objeto.** Como sus dos hermanas, los funde en el
  mensaje y los pierde como datos, de modo que un `catch` no puede reaccionar
  según qué faltaba sin analizar el texto.
- **Sin test.**
- Es la más útil de las tres derivadas y la que más se usa en el stack, sobre
  todo en [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md) con sus
  gestores de sesiones y usuarios.
