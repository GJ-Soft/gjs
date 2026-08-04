# FicheroTSV

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

Un [FicheroFormateado](FicheroFormateado.md) partido por **tabuladores**.

```cpp
class FicheroTSV : public FicheroFormateado
{
public:
    FicheroTSV () : FicheroFormateado ( { "\t" } ) {};
};
```

*Tab-separated values*: el formato que sale de copiar una selección de una hoja
de cálculo, y el que exportan muchas herramientas cuando los datos llevan comas.

## Dependencias

[FicheroFormateado](FicheroFormateado.md).

## Test

Cubierto por `FicheroFormateadoTest.cpp`, sin suite propia.

## Observaciones

- **Es la más segura de las tres derivadas.** El tabulador no aparece dentro de
  un campo casi nunca, así que la partición a secas —sin comillas ni escapes—
  acierta donde [FicheroCSV](FicheroCSV.md) falla. El formato TSV clásico
  resuelve el problema prohibiendo el tabulador en el contenido, en lugar de
  escaparlo.
- **Un campo vacío entre dos tabuladores** es el caso que conviene comprobar: si
  la partición colapsa los delimitadores consecutivos, una fila con una columna
  vacía en medio saldría con un campo de menos y todo lo demás desplazado. La
  cabecera no lo dice y el comportamiento depende de la función de partición de
  [Cadenas](../../gjs-cpp-common-base/doc/Cadenas.md).
- Hereda el resto de limitaciones de la base: carga entera en memoria, sin
  escritura y sin contrato para índices fuera de rango.
