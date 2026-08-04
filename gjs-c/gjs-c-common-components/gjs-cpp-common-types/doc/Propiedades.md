# Propiedades

| Dato      | Valor                                        |
| --------- | -------------------------------------------- |
| Cabecera  | `src/main/include/Propiedades.h` (57 líneas) |
| Fuente    | `Propiedades.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                      |
| Deriva de | —                                            |
| Test      | `PropiedadesTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un fichero de configuración `clave=valor`. Es la contraparte de
[SPropiedades](../../gjs-c-common-support/doc/SPropiedades.md) del stack C, y la
comparación entre las dos es instructiva.

```cpp
class Propiedades
{
private:
    std::vector<std::string>           vecClaves;
    std::map<std::string, std::string> mapPropiedades;

public:
    Propiedades ();
    explicit Propiedades ( const std::string & sRuta );
    virtual ~Propiedades ();

    std::string getPropiedad ( const std::string & sClave ) const;
    std::string getPropiedad ( const std::string & sClave, const std::string & sValorDef ) const;
    void        setPropiedad ( const std::string & sClave, const std::string & sValor );

    std::vector<std::string> getPropiedades () const;
    bool ExistePropiedad ( const std::string & sClave ) const;
    int  NumPropiedades () const;
    void EliminarPropiedad ( const std::string & sClave );

    bool Cargar  ( const std::string & sRuta );
    bool Guardar ( const std::string & sRuta );

private:
    bool EsPropiedad ( const std::string & sLinea );
    std::pair<std::string, std::string> ParsearPropiedad ( const std::string & sLinea );
};
```

## Lo que hace mejor que la versión C

| Aspecto            | En C                                                          | Aquí                                   |
| ------------------ | ------------------------------------------------------------- | -------------------------------------- |
| Auxiliares         | `_EsPropiedad` y `_ParsearPropiedad` **globales**, exportadas | **privadas** de la clase               |
| Devolver dos cosas | Dos punteros de salida, con fuga al quitar comillas           | `std::pair<std::string, std::string>`  |
| Memoria            | Tres fugas comprobadas                                        | `std::string` y contenedores por valor |
| Consulta           | Métodos `const`                                               | Cinco de ellos `const`                 |

Los mismos dos auxiliares que en C eran símbolos globales con guion bajo inicial
—nombre reservado por el estándar— aquí están donde deben, y `ParsearPropiedad`
devuelve la pareja en lugar de escribir en dos punteros.

## Dependencias

`<string>`, `<vector>`, `<map>` y las utilidades de cadena de
[gjs-cpp-common-base](../../gjs-cpp-common-base/doc/Cadenas.md).

## Test

`PropiedadesTest.cpp` → `TestPropiedades()`.

## Observaciones

- **Mantiene dos contenedores en paralelo**, `vecClaves` y `mapPropiedades`,
  igual que la versión C, y por la misma razón: conservar el orden de inserción.
  El componente tiene [MapaVector](MapaVector.md), que resuelve exactamente eso
  y está en la misma fachada. Aquí no se usa.
- **`getPropiedad` sin valor por defecto no dice qué devuelve** si la clave no
  está: presumiblemente cadena vacía, que es indistinguible de una propiedad
  cuyo valor sea vacío. La sobrecarga con `sValorDef` evita el problema y es la
  que conviene usar.
- **`Guardar` no es `const`** aunque sólo escriba: las cinco consultas sí lo
  son, de modo que la asimetría llama la atención. Un objeto constante puede
  consultarse y no volcarse.
- **La cabecera no documenta el formato.** Si admite comentarios, si respeta los
  espacios interiores del valor, si entrecomilla los que llevan blancos en los
  extremos —todo lo que en la versión C hubo que averiguar leyendo el código, y
  donde estaban los defectos—. Con `EsPropiedad` y `ParsearPropiedad` privadas,
  aquí sólo se puede saber probando.
- **`Cargar` sobre un objeto con datos** no dice si mezcla o reemplaza.
- La clase **no deriva de `IToString`**, así que no tiene `toString()` ni entra
  en las colecciones volcables del stack, a diferencia de casi todas sus
  hermanas del componente.
