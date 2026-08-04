# Simbolos

| Dato      | Valor                                     |
| --------- | ----------------------------------------- |
| Cabecera  | `src/main/include/Simbolos.h` (47 líneas) |
| Fuente    | `Simbolos.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                   |
| Deriva de | —                                         |
| Test      | `SimbolosTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una lista de cadenas con acceso por índice y volcado a flujo. Sirve para
transportar un juego de símbolos —delimitadores, operadores, palabras
reservadas— como un objeto en lugar de como un contenedor suelto.

```cpp
class Simbolos
{
private:
    std::vector<std::string> vecContenido;

public:
    Simbolos ();
    explicit Simbolos ( const std::initializer_list<std::string> & args );
    explicit Simbolos ( const std::list<std::string> & args );
    explicit Simbolos ( const std::vector<std::string> & args );

    int         Tam ();
    std::string Simbolo ( int i );
    void        Insertar ( const std::string & simbolo );

    std::string & operator[] ( int i );

    friend std::ostream & operator<< ( std::ostream & strm, const Simbolos & simbolos );
};
```

Los tres constructores cubren las tres formas de tener ya las cadenas: entre
llaves, en una lista o en un vector.

```cpp
Simbolos simOperadores ( { "+", "-", "*", "/" } );

std::cout << simOperadores << std::endl;
```

## Dependencias

`<string>`, `<vector>`, `<list>`, `<ostream>`.

## Test

`SimbolosTest.cpp` → `TestSimbolos()`.

## Observaciones

- **`operator[]` devuelve `std::string &` y `Simbolo ( int )` devuelve por
  valor.** Dos accesos al mismo dato con semánticas distintas: por el primero se
  puede modificar el contenido, por el segundo no. La cabecera no dice cuál usar.
- **No hay versión constante de `operator[]`**, de modo que un
  `const Simbolos &` no se puede indexar —justo el tipo que recibe el
  `operator<<` amigo—.
- **`Tam()` no es `const`**, así que tampoco se puede contar sobre un objeto
  constante.
- **Ni `Eliminar`, ni `Limpiar`, ni `Contiene`.** Se puede construir, insertar y
  leer; no quitar ni buscar, que es lo que se querría de un juego de símbolos
  —comprobar si una cadena está entre ellos—.
- **No deriva de `IToString`** pese a tener volcado propio con `operator<<`. Si
  lo hiciera, ganaría el `toString()` del stack y entraría en sus colecciones
  volcables; tal como está, tiene el volcado a flujo y no el de texto.
- **Se solapa con `ToVector` y `ToList` de
  [Colecciones](../../gjs-cpp-common-base/doc/Colecciones.md)**, que construyen
  lo mismo desde una `initializer_list` sin envolverlo en una clase. Y con
  `std::vector<std::string>` a secas, que es lo que la clase guarda dentro.
- **El índice no se valida.** Ni `operator[]` ni `Simbolo` dicen qué ocurre
  fuera de rango.
