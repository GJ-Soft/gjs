# FicheroCSV

| Dato      | Valor                                       |
| --------- | ------------------------------------------- |
| Cabecera  | `src/main/include/FicheroFormateado.h`      |
| Fuente    | En línea, en la propia cabecera             |
| Espacio   | `org::gjs::cpp::common`                     |
| Deriva de | [`FicheroFormateado`](FicheroFormateado.md) |
| Test      | `FicheroFormateadoTest.cpp`                 |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un [FicheroFormateado](FicheroFormateado.md) partido por **comas**.

```cpp
class FicheroCSV : public FicheroFormateado
{
public:
    FicheroCSV () : FicheroFormateado ( { "," } ) {};
};
```

Toda la clase es esa línea: fija el delimitador y hereda la API entera. El
nombre viene de *comma-separated values*.

```cpp
FicheroCSV fic;

if ( fic.Cargar ( "clientes.csv" ) )
{
    std::string sPrimerCampo = fic.Campo ( 0, 0 );
}
```

## Dependencias

[FicheroFormateado](FicheroFormateado.md).

## Test

Cubierto por `FicheroFormateadoTest.cpp`, sin suite propia.

## Observaciones

- **No es un lector de CSV, es un partidor por comas.** El formato CSV real
  —RFC 4180— admite campos entre comillas con comas y saltos de línea dentro, y
  comillas dobladas para escapar. Nada de eso se contempla: una línea como

  ```
  1,"Perez, Ana",1250.75
  ```

  se parte en cuatro campos y el segundo queda como `"Perez`. Para ficheros
  generados por el propio stack es suficiente; para un CSV exportado de una hoja
  de cálculo, no, y es justo de donde vienen los CSV.

  El nombre invita a confiar en que sí, y ahí está el riesgo.
- **Hereda todo lo demás** de la base: la carga entera en memoria, la falta de
  escritura y la ausencia de contrato para índices fuera de rango. Ver
  [FicheroFormateado](FicheroFormateado.md).
- **Las tres derivadas son idénticas salvo el separador**, y por eso comparten
  cabecera, fuente y test. Con un parámetro por defecto en el constructor de la
  base —`FicheroFormateado ( { "," } )`— o con un alias, harían falta menos
  clases; tenerlas nombradas hace el código más legible en el sitio de uso.
