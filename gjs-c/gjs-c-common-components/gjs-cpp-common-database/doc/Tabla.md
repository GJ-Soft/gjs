# Tabla

| Dato      | Valor                                  |
| --------- | -------------------------------------- |
| Cabecera  | `src/main/include/Tabla.h` (50 líneas) |
| Fuente    | `Tabla.cpp` (106 líneas)               |
| Espacio   | `org::gjs::cpp::common`                |
| Hereda de | `Entidad`                              |
| Métodos   | 9                                      |
| Test      | `TablaTest.cpp` (174 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

**Un conjunto de filas con la misma estructura.** La tabla *es* la estructura
—hereda de [`Entidad`](../../gjs-cpp-common-types/doc/Entidad.md)— y guarda
dentro las [`Ocurrencia`](Ocurrencia.md) que la cumplen.

```cpp
Tabla tabla ( entCliente );

Ocurrencia * pFila = tabla.Nueva ();       // creada, aun no dentro
pFila->getValor ( "nombre" )->Establecer ( "Vladimiro" );
tabla.Insertar ( pFila );                  // ahora si

tabla.NumOcurrencias ();                   // 1
tabla.getOcurrencia ( 0 );
tabla.Eliminar ( 0 );                      // la borra de verdad
```

## La API

| Grupo    | Métodos                           |
| -------- | --------------------------------- |
| Consulta | `NumOcurrencias`, `getOcurrencia` |
| Alta     | `Nueva`, `Insertar`               |
| Baja     | `Eliminar`, `Vaciar`              |
| Salida   | `toString`                        |

Más todo lo de `Entidad`, que llega por herencia pública: `NumAtributos`,
`getAtributo`, `EsValida`, `EsCompatible`…

## El ciclo de una fila

```
   tabla.Nueva ()  ──>  Ocurrencia *      el llamante es el dueno
        │
        │  ( rellenar los valores )
        ▼
   tabla.Insertar ( p )
        │
        ├── aceptada  ──>  la tabla pasa a ser la duena
        │
        └── rechazada ──>  nadie es el dueno  <- ver observaciones
```

`Insertar` acepta si la tabla es válida, el puntero no es nulo, la entidad de la
ocurrencia es compatible con la de la tabla, y **ese mismo puntero no estaba ya
dentro**.

`Eliminar` y `Vaciar` **borran** las ocurrencias, y el destructor llama a
`Vaciar`.

---

## Test

`TablaTest.cpp` cubre el ciclo entero: crear, insertar, contar, recuperar por
índice, eliminar y vaciar.

---

## Observaciones

### La regla de tres sin cumplir

`Tabla` posee memoria con punteros desnudos —`std::vector<Ocurrencia *>`— y su
destructor la libera:

```cpp
Tabla::~Tabla () { Vaciar (); }

void Tabla::Vaciar ()
{
    for ( Ocurrencia * ocurrencia : vecContenido ) { delete ocurrencia; }
    vecContenido.clear ();
}
```

pero **no declara constructor de copia ni operador de asignación**. El compilador
los genera copiando el vector *puntero a puntero*, de modo que dos tablas acaban
apuntando a las mismas ocurrencias y **las borran las dos**:

```cpp
Tabla t2 = t1;      // compila
                    // al morir las dos: doble liberacion
```

Es la regla de tres clásica. Las salidas eran dos: declarar la copia —profunda,
clonando cada ocurrencia con `Clonar()`— o prohibirla con `= delete`. Desde el
2026-10-11 está prohibida: `Tabla t2 = t1;` ya no compila. Ningún código del
repositorio copiaba una tabla.

Con `std::vector<std::unique_ptr<Ocurrencia>>` no habría ni destructor que
escribir, y la copia quedaría prohibida sola.

### La fila que se pierde

`Insertar` devuelve `void` y descarta en silencio lo que no encaja:

```cpp
void Tabla::Insertar ( Ocurrencia * ocurrencia )
{
    if ( Entidad::EsValida () && ( ocurrencia != NULL ) )
    {
        if ( Entidad::EsCompatible ( ocurrencia->getEntidad () ) )
        {
            ...  push_back
        }
    }
    // y si no: ni la mete ni la borra ni lo dice
}
```

El objeto viene de `Nueva()`, que lo reservó con `new`. Si `Insertar` lo rechaza
—entidad incompatible, tabla inválida, o el mismo puntero ya dentro— **nadie se
queda con él**: la tabla no lo guarda y el llamante cree que sí. Es una fuga de
memoria por diseño, y el patrón de uso normal la provoca:

```cpp
Ocurrencia * p = tabla.Nueva ();
tabla.Insertar ( p );      // ¿entro? no hay forma de saberlo
```

Devolver `bool` lo resuelve. Que `Insertar` borre lo que rechaza también, y
además cierra el contrato: «me lo das y me ocupo yo, entre o no».

### Otras

- **`Nueva()` no inserta.** El nombre sugiere «dame una fila nueva en la tabla» y
  lo que hace es «dame una fila suelta con la estructura de la tabla». Los dos
  pasos separados son defendibles —permiten rellenar antes de insertar— y el
  nombre no lo dice.
- **`Nueva()` devuelve `NULL` si la tabla no es válida**, y el llamante que no lo
  compruebe se lleva un nulo al `getValor` siguiente.
- **La deduplicación es por identidad de puntero, no por contenido.** `Insertar`
  recorre el vector comparando direcciones con un molde a `void *`. Insertar dos
  veces el mismo objeto no cuela; insertar dos objetos con los mismos valores,
  sí. `Ocurrencia` tiene `operator==` y `getHash`, así que la comparación por
  contenido está disponible y no se usa.
- **Y ese recorrido es lineal**, de modo que llenar una tabla de N filas cuesta
  N². Para una tabla en memoria de tamaño moderado da igual; conviene saberlo
  antes de meterle miles.
- **`getOcurrencia` devuelve un puntero a lo que la tabla posee.** El llamante
  puede borrarlo, y entonces el destructor de la tabla lo borra otra vez. No hay
  nada en la firma que lo desaconseje; devolver una referencia lo haría.
- **`NumOcurrencias()` es `const` y `getOcurrencia` no**, aunque tampoco modifica
  nada. Recorrer una tabla constante no se puede.
- **`getOcurrencia` y `Eliminar` exigen `Entidad::EsValida()`** además del índice.
  Una tabla que deje de ser válida —porque le cambien los atributos por debajo,
  cosa que la herencia pública permite— **deja de dar acceso a las filas que ya
  tiene dentro**, y `Vaciar` sigue funcionando. Es una combinación rara: se
  pueden borrar todas pero no leer ninguna.
- **`toString` no incluye las filas**, sólo la entidad y el número de
  ocurrencias. Es una decisión sensata para una tabla grande, y significa que
  imprimir una tabla no imprime su contenido.
