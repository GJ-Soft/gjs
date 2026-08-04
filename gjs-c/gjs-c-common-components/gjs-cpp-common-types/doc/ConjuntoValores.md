# ConjuntoValores

| Dato      | Valor                                            |
| --------- | ------------------------------------------------ |
| Cabecera  | `src/main/include/ConjuntoValores.h` (77 líneas) |
| Fuente    | `ConjuntoValores.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                          |
| Deriva de | `IToString`                                      |
| Derivadas | `Ocurrencia` en `gjs-cpp-common-database`        |
| Test      | `ConjuntoValoresTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Los valores de una fila **por nombre de atributo**. Es la pareja de
[Entidad](Entidad.md): allí la forma, aquí los datos.

```cpp
class ConjuntoValores : public IToString
{
private:
    std::map<std::string, Valor *> mapValores;
    bool                           bPermiteInsercion = true;
    …
};
```

```cpp
ConjuntoValores cjtFila ( { "id", "nombre", "saldo" }, false );

cjtFila.InsertarValor ( "id",     42 );
cjtFila.InsertarValor ( "nombre", "Ana" );

if ( cjtFila.ExisteValor ( "saldo" ) )
{
    double dSaldo = cjtFila.getValor ( "saldo" )->getValorReal ();
}
```

## La API

### Construcción

| Constructor                           | Qué hace                        |
| ------------------------------------- | ------------------------------- |
| `ConjuntoValores ()`                  | Vacío, admite inserciones.      |
| `( initializer_list<string>, bool )`  | Con los atributos entre llaves. |
| `( list<string>, bool )`              | Con la lista ya formada.        |
| `( const std::string & sRuta, bool )` | **Desde un fichero.**           |

El último es el que llama la atención: un conjunto de valores se puede construir
leyendo un fichero, y `Cargar ( sRuta )` hace lo mismo sobre un objeto ya
creado.

### Valores

`NumValores`, `getValor ( sAtributo )`, `ExisteValor`, `EliminarValor`,
`LimpiarValores`, y **diecinueve sobrecargas de `InsertarValor`**, todas con el
nombre del atributo como primer parámetro y el dato en bruto como segundo.

## Dependencias

[Valor](Valor.md) e `IToString`.

## Test

`ConjuntoValoresTest.cpp` → `TestConjuntoValores()`.

## Observaciones

> **Declara `getHash()` protegido sin derivar de
> [IComparable](../../gjs-cpp-common-base/doc/IComparable.md)**, igual que
> [ListaValores](ListaValores.md): un virtual nuevo que no redefine nada y que
> nadie llama. Ver el detalle allí.

- **El constructor desde fichero y `Cargar` no documentan el formato.** Ni qué
  separador, ni si la primera línea son los nombres de atributo, ni qué pasa con
  una línea mal formada. El componente tiene
  [FicheroFormateado](FicheroFormateado.md) con sus derivadas CSV, TSV y DSV
  justo para leer ficheros por columnas; si es lo que usa por dentro, conviene
  decirlo, y si no, explicar por qué hay dos caminos.
- **`Cargar` devuelve `bool` y el constructor no devuelve nada**, de modo que un
  fichero ilegible pasado al constructor deja el objeto vacío sin aviso. Es el
  mismo caso que `SPropCrear` en el stack C.
- **No hay validación contra una [Entidad](Entidad.md).** Las dos clases son las
  dos mitades del mismo modelo —forma y datos— y no hay un
  `EsCompatible ( Entidad & )` que compruebe que los atributos del conjunto son
  los que la entidad declara, ni que los tipos cuadran. `Atributo::EsCompatible ( Valor & )`
  existe y valida de uno en uno; el cruce completo hay que escribirlo a mano.
- **El conjunto posee los `Valor *`**, con la misma ambigüedad que en
  `ListaValores` para la sobrecarga que recibe el puntero.
- **`getValor` sobre un atributo ausente** no tiene contrato: presumiblemente
  `NULL`, con lo que el ejemplo de arriba necesita el `ExisteValor` previo —dos
  búsquedas en el mapa—.
- **`EsValido()` es `const` aquí y `EsValida()` no lo es en
  [ListaValores](ListaValores.md).** Dos clases hermanas, dos géneros y dos
  firmas para el mismo concepto.
- **`bPermiteInsercion` repite la contradicción** entre el valor por defecto del
  campo (`true`) y el del parámetro (`false`).
