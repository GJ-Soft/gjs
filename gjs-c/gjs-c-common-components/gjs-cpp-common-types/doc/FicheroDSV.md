# FicheroDSV

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

Un [FicheroFormateado](FicheroFormateado.md) partido por **punto y coma**.

```cpp
class FicheroDSV : public FicheroFormateado
{
public:
    FicheroDSV () : FicheroFormateado ( { ";" } ) {};
};
```

Es el «CSV europeo»: en las configuraciones regionales donde la coma es el
separador decimal, las hojas de cálculo exportan con punto y coma para no
chocar con los números.

## Dependencias

[FicheroFormateado](FicheroFormateado.md).

## Test

Cubierto por `FicheroFormateadoTest.cpp`, sin suite propia.

## Observaciones

- **El nombre no corresponde con lo que hace.** DSV es
  *delimiter-separated values*, la familia genérica a la que pertenecen CSV y
  TSV: un DSV es cualquiera de ellos, con el delimitador que sea. Esta clase, en
  cambio, fija el punto y coma.

  Quien la vea esperará poder decirle el delimitador —que es justo lo que hace
  la base, [FicheroFormateado](FicheroFormateado.md), y con varios a la vez—.
  `FicheroPuntoYComa` diría lo que es, y el hueco de «delimitador a elegir» ya
  lo cubre la base.
- **Es el separador que menos aparece dentro de un campo** de los tres, junto con
  el tabulador, así que la falta de comillas y escapes molesta menos aquí que en
  [FicheroCSV](FicheroCSV.md).
- Hereda el resto de limitaciones de la base: carga entera en memoria, sin
  escritura y sin contrato para índices fuera de rango.
