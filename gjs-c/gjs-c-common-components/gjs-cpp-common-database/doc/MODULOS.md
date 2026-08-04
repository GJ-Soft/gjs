# Clases de gjs-cpp-common-database

[README](../README.md)

3 cabeceras y 2 fuentes en 450 líneas: **2 clases**.

---

## Índice

| Clase        | Cabecera       | Hereda de                     | Fuente                 | Test                 | Documento                   |
| ------------ | -------------- | ----------------------------- | ---------------------- | -------------------- | --------------------------- |
| `Ocurrencia` | `Ocurrencia.h` | `ListaValores`, `IComparable` | `Ocurrencia.cpp` (196) | `OcurrenciaTest.cpp` | [Ocurrencia](Ocurrencia.md) |
| `Tabla`      | `Tabla.h`      | `Entidad`                     | `Tabla.cpp` (106)      | `TablaTest.cpp`      | [Tabla](Tabla.md)           |

---

## De dónde sale todo

Las dos clases son la punta de una jerarquía que está en
[gjs-cpp-common-types](../../gjs-cpp-common-types/README.md):

```
  IComparable ──┬── Entidad ────────── Tabla          ( esta aqui )
                │      │
                │      └── tiene N ── Atributo
                │
                └── Ocurrencia         ( esta aqui )
                       │
   ListaValores ───────┘
        │
        └── tiene N ── Valor ── es de un ── Tipo
```

| Pieza            | Dónde                                                   | Qué es                      |
| ---------------- | ------------------------------------------------------- | --------------------------- |
| `Atributo`       | [types](../../gjs-cpp-common-types/doc/Atributo.md)     | Una columna: nombre y tipo  |
| `Entidad`        | [types](../../gjs-cpp-common-types/doc/Entidad.md)      | El conjunto de atributos    |
| `Valor`          | [types](../../gjs-cpp-common-types/doc/Valor.md)        | Un dato con su tipo         |
| `ListaValores`   | [types](../../gjs-cpp-common-types/doc/ListaValores.md) | Una lista de valores        |
| **`Ocurrencia`** | aquí                                                    | Una fila: valores + entidad |
| **`Tabla`**      | aquí                                                    | Filas de la misma entidad   |

Lo que este componente añade es **la relación entre las dos mitades**: los
valores sueltos de `ListaValores` pasan a estar descritos por los atributos de
una `Entidad`, y un montón de filas pasa a ser una tabla.

---

## Las dos herencias

| Clase        | Cómo hereda                                          | Por qué                                      |
| ------------ | ---------------------------------------------------- | -------------------------------------------- |
| `Ocurrencia` | `public ListaValores, public IComparable` (múltiple) | Es una lista de valores, y se puede comparar |
| `Tabla`      | `public Entidad`                                     | Una tabla **es** una entidad: la suya        |

La de `Tabla` es la decisión de diseño del componente: en vez de *tener* una
entidad, la tabla *es* la entidad. Así `tabla.NumAtributos()` funciona
directamente y `Tabla::Nueva()` puede pasarse a sí misma como estructura de la
fila nueva:

```cpp
ocurrencia = new Ocurrencia ( (Entidad *) this );
```

Es coherente y tiene un efecto de fondo: **la estructura de la tabla se puede
cambiar mientras tiene filas dentro**, porque los métodos de `Entidad` siguen
siendo públicos. Añadir un atributo a una tabla llena deja las ocurrencias con
menos valores de los que la entidad declara, y `Ocurrencia::EsValida()` empieza a
devolver falso para todas.

---

## Propiedad de la memoria

Es lo que hay que tener claro para usar el componente:

| Quién       | Posee                                                        | Lo libera                                   |
| ----------- | ------------------------------------------------------------ | ------------------------------------------- |
| `Tabla`     | Las `Ocurrencia *` insertadas                                | `Eliminar`, `Vaciar` y el destructor        |
| El llamante | Lo que devuelve `Nueva()` **hasta que `Insertar` lo acepte** | nadie: hay que insertarlo o borrarlo a mano |
| El llamante | Lo que devuelve `Clonar()`                                   | él mismo, siempre                           |
| Nadie       | El `Entidad *` de una `Ocurrencia`                           | es prestado: la ocurrencia no lo borra      |

El punto delicado es la segunda fila, y está descrito en
[Tabla](Tabla.md#observaciones).

---

## La fachada `CppCommonDatabase.h`

Catorce líneas, dos `#include` vivos y dos comentados:

```cpp
#include <Ocurrencia.h>
#include <Tabla.h>
//#include <Esquema.h>
//#include <BDD.h>
```

No deja fuera ninguna cabecera existente. `CommonDatabaseConfig.h` —dieciocho
líneas— es la configuración interna y no se publica, que es lo correcto.
