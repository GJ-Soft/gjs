# Entidad

| Dato      | Valor                                    |
| --------- | ---------------------------------------- |
| Cabecera  | `src/main/include/Entidad.h` (79 líneas) |
| Fuente    | `Entidad.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                  |
| Deriva de | `IComparable`                            |
| Test      | `EntidadTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La **descripción de una estructura de datos**: un nombre y los atributos que la
componen. Es el esquema de una tabla, o la definición de un registro.

```cpp
class Entidad : public IComparable
{
private:
    std::string                       sNombre;
    std::map<std::string, Atributo *> mapDefinicion;
    …
};
```

```cpp
Entidad entCliente ( "Cliente" );

entCliente.InsertarAtributo ( TipoDatos::ENTERO, "id",     false );
entCliente.InsertarAtributo ( TipoDatos::CADENA, "nombre", false );
entCliente.InsertarAtributo ( TipoDatos::REAL,   "saldo"        );

if ( entCliente.TieneAtributo ( "saldo" ) ) { … }
```

## La API

### Atributos

| Método                                     | Qué hace                                      |
| ------------------------------------------ | --------------------------------------------- |
| `NumAtributos ()`                          | Cuántos hay.                                  |
| `TieneAtributo ( sNombre )`                | Si existe.                                    |
| `getAtributo ( sNombre )` / `( int )`      | Por nombre o por índice.                      |
| `getIndiceAtributo ( sNombre )`            | La posición de uno.                           |
| `ListaAtributos ()`                        | Los nombres.                                  |
| `InsertarAtributo ( … )`                   | Tres formas: puntero, `TipoDatos` o `Tipo &`. |
| `EliminarAtributo ( sNombre )` / `( int )` | Lo quita.                                     |
| `LimpiarAtributos ()`                      | Los quita todos.                              |

### Comparación

`EsCompatible ( Entidad & )` dice si dos entidades tienen la misma forma, que es
lo que hace falta antes de copiar datos de una a otra.

## Dependencias

[Atributo](Atributo.md), [Tipo](Tipo.md) e `IComparable`.

## Test

`EntidadTest.cpp` → `TestEntidad()`.

## Observaciones

- **El acceso por índice sobre un `std::map` es engañoso.** `getAtributo ( int )`
  y `getIndiceAtributo` sugieren un orden, pero el contenedor es un mapa
  ordenado **por nombre**: el atributo 0 es el primero alfabéticamente, no el
  primero que se insertó. Insertar `"id"` y luego `"apellido"` deja el segundo
  en la posición 0.

  Y eso importa cuando la entidad describe un fichero por columnas o un
  registro binario, donde el orden de declaración es el orden de los datos. El
  componente tiene [MapaVector](MapaVector.md) justo para esto —un mapa que
  conserva el orden de inserción— y aquí no se usa.
- **`ListaAtributos()` devuelve `std::vector<std::string> *`**, un puntero
  desnudo, sin decir quién lo libera. El resto del componente devuelve por valor
  o referencia; es el único sitio con esta forma.
- **La entidad posee los `Atributo *` de su mapa**, a juzgar por
  `LimpiarAtributos` y el destructor, pero `InsertarAtributo ( Atributo * )`
  acepta un puntero de fuera sin decir que se queda con él. Las otras dos
  sobrecargas construyen el atributo dentro, que es lo seguro.
- **`getAtributo` devuelve el puntero interno**, de modo que quien lo reciba
  puede modificar la definición de la entidad —o quedárselo más allá de un
  `EliminarAtributo`, que presumiblemente lo destruye—.
- **`EsValida()` con `a` final**, mientras que [Valor](Valor.md) y
  [ConjuntoValores](ConjuntoValores.md) tienen `EsValido` y
  [ListaValores](ListaValores.md) `EsValida`. Concordar el género con el nombre
  de la clase es defendible; lo que impide es escribir código genérico que
  pregunte por la validez.
- **No hay clave.** Una entidad describe atributos y no dice cuál identifica al
  registro, que es lo primero que hace falta para lo que viene después:
  [Tabla](../../gjs-cpp-common-database/README.md) de
  `gjs-cpp-common-database`.
