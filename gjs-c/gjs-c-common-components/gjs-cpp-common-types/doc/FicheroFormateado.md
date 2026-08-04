# FicheroFormateado

| Dato      | Valor                                                                                 |
| --------- | ------------------------------------------------------------------------------------- |
| Cabecera  | `src/main/include/FicheroFormateado.h` (76 líneas)                                    |
| Fuente    | `FicheroFormateado.cpp`                                                               |
| Espacio   | `org::gjs::cpp::common`                                                               |
| Deriva de | —                                                                                     |
| Derivadas | [FicheroCSV](FicheroCSV.md), [FicheroTSV](FicheroTSV.md), [FicheroDSV](FicheroDSV.md) |
| Test      | `FicheroFormateadoTest.cpp`                                                           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un fichero de texto **partido en filas y columnas** por uno o varios
delimitadores. Es la base de las tres clases con nombre —CSV, TSV y DSV— que
sólo fijan el separador.

```cpp
class FicheroFormateado
{
private:
    std::list<std::string>                lisSeparadores;
    std::string                           sFichero;
    bool                                  bCargado = false;
    std::vector<std::vector<std::string>> vecContenido;

public:
    explicit FicheroFormateado ( const std::initializer_list<std::string> & delimitadores );
    virtual ~FicheroFormateado ();

    bool        Cargar ( const std::string & sRuta );
    std::string getRuta () const;
    int         NumLineas () const;
    std::vector<std::string> & Linea ( int iLinea );
    int         NumCamposLinea ( int iLinea ) const;
    std::string Campo ( int iLinea, int iCampo );

private:
    void Vaciar ();
};
```

```cpp
FicheroCSV fic;

if ( fic.Cargar ( "clientes.csv" ) )
{
    for ( int iL = 0; iL < fic.NumLineas (); iL = iL + 1 )
    {
        std::string sNombre = fic.Campo ( iL, 1 );
    }
}
```

**Acepta varios delimitadores a la vez**, no uno solo: el constructor recibe una
lista, de modo que una clase derivada podría partir por coma y por punto y coma
en la misma pasada. Las tres que existen usan uno cada una.

El contenido se carga entero en memoria, en un vector de vectores.

## Dependencias

`<list>`, `<vector>`, `<string>` y las utilidades de partición de
[Cadenas](../../gjs-cpp-common-base/doc/Cadenas.md).

## Test

`FicheroFormateadoTest.cpp` → `TestFicheroFormateado()`.

## Observaciones

- **El constructor es `explicit` y sin versión por defecto**, de modo que la
  clase base no se puede instanciar sin decir los delimitadores. Es coherente:
  se usa a través de sus tres derivadas.
- **`bCargado` no se puede consultar.** El campo existe y no hay `EstaCargado()`,
  así que preguntar si ya se cargó algo obliga a mirar `NumLineas() > 0`, que no
  es lo mismo —un fichero vacío se carga bien y da cero líneas—.
- **`Linea` devuelve una referencia no constante al vector interno**, con lo que
  el llamante puede modificar el contenido cargado. Y `NumLineas` y
  `NumCamposLinea` sí son `const`, pero `Linea` y `Campo` no, así que un
  `const FicheroFormateado &` sólo sirve para contar.
- **Nada dice qué pasa con un índice fuera de rango.** Ni `Linea`, ni `Campo`, ni
  `NumCamposLinea`: sin excepción documentada ni valor de retorno convenido, y
  con `std::vector` debajo el acceso directo sería comportamiento indefinido.
- **No hay escritura.** Se puede leer un CSV y no generarlo, a diferencia de
  [Propiedades](Propiedades.md), que sí tiene `Guardar`.
- **Ni comillas ni escapes.** Un CSV de verdad admite campos entrecomillados con
  comas dentro; partir por el delimitador a secas rompe esa línea en dos campos.
  Para ficheros propios es suficiente; para un CSV de fuera, no.
- **Carga el fichero entero**, como `LeerFichero` de
  [Ficheros](../../gjs-cpp-common-base/doc/Ficheros.md), sin opción de recorrer
  por líneas.
