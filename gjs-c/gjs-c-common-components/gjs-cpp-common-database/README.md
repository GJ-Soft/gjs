# gjs-cpp-common-database

**Datos en forma de tabla**: una fila —la *ocurrencia*— y el conjunto de filas
que comparten estructura —la *tabla*—.

3 cabeceras y 2 fuentes en **450 líneas**, con **2 clases**. Es el componente más
pequeño del stack C++, y el único que está declaradamente a medias: su fachada
deja apuntados dos módulos que aún no existen.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjsoft.c.common`             |
| `artifactId` | `gjs-cpp-common-database`      |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent` |
| Depende de   | `gjs-cpp-common-support`       |

Depende de `support` y, a través de él, de todo el stack. En realidad lo que usa
está en [gjs-cpp-common-types](../gjs-cpp-common-types/README.md) —`Entidad`,
`ListaValores`, `Valor`, `Atributo`—, cuatro capas más abajo.

---

## Uso

La cabecera fachada es `CppCommonDatabase.h`:

```cpp
#include <CppCommonDatabase.h>

using namespace org::gjs::cpp::common;

// La estructura viene de gjs-cpp-common-types
Entidad entCliente ( "Cliente" );
entCliente.addAtributo ( ... );

Tabla tabla ( entCliente );

Ocurrencia * pFila = tabla.Nueva ();
pFila->getValor ( "nombre" )->Establecer ( "Vladimiro" );
tabla.Insertar ( pFila );          // a partir de aqui la tabla es la duena

for ( int i = 0; i < tabla.NumOcurrencias (); i++ )
{
    std::cout << tabla.getOcurrencia ( i )->toString () << std::endl;
}
```

---

## El modelo

Tres piezas, y sólo dos escritas:

```
   Entidad          la estructura: que atributos tiene una fila
   ( types )        y de que tipo son
      │
      ├── Ocurrencia    una fila concreta: los valores
      │
      └── Tabla         un conjunto de filas de la misma entidad
```

`Entidad` no está aquí: vive en
[gjs-cpp-common-types](../gjs-cpp-common-types/doc/Entidad.md), junto a
`Atributo`, `Valor` y `ListaValores`. Este componente pone encima las dos piezas
que faltan para que eso sea una tabla.

| Clase        | Es un…                                           | Documento                       |
| ------------ | ------------------------------------------------ | ------------------------------- |
| `Ocurrencia` | `ListaValores` + `IComparable`, con su `Entidad` | [Ocurrencia](doc/Ocurrencia.md) |
| `Tabla`      | `Entidad`, con un vector de ocurrencias          | [Tabla](doc/Tabla.md)           |

---

## Lo que falta

La fachada lo dice con dos líneas comentadas:

```cpp
#include <Ocurrencia.h>
#include <Tabla.h>
//#include <Esquema.h>
//#include <BDD.h>
```

`Esquema` sería el conjunto de tablas relacionadas y `BDD` la base de datos
—conexión, consultas, persistencia—. **Ninguno de los dos ficheros existe**, ni
como cabecera ni como fuente.

O sea: el componente se llama *database* y **no tiene nada que hablar con una
base de datos**. Lo que hay es un modelo de tabla en memoria, sin lectura, sin
escritura, sin consultas y sin índices. Es un punto de partida honesto —las dos
piezas de abajo están escritas y probadas— y conviene no confundirlo con lo que
el nombre promete.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-support` instalado.

**No hay `output.txt` en la raíz**, al contrario que en `io`, `log`, `system` y
`support`: este módulo no arrastra ningún log de compilación viejo.

---

## Tests

**2 suites** en 423 líneas, casi tanto como el código que prueban (450). Es la
mejor proporción del stack C++.

| Suite                | Líneas |
| -------------------- | ------ |
| `OcurrenciaTest.cpp` | 193    |
| `TablaTest.cpp`      | 174    |

---

## Documentación de las clases

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`Tabla` posee sus ocurrencias con punteros desnudos y no declara constructor
  de copia ni asignación.** Su destructor las borra, de modo que copiar una
  `Tabla` —cosa que el compilador permite en silencio— acaba en **doble
  liberación**. Es la regla de tres sin cumplir. Ver [Tabla](doc/Tabla.md).
- **`Tabla::Insertar` puede rechazar la ocurrencia sin decirlo.** Devuelve `void`
  y descarta lo que no encaja, así que el objeto que el llamante acaba de crear
  con `Nueva()` **se pierde**: nadie lo borra y nadie sabe que no entró.
- **`Ocurrencia::Asignar` falla en silencio por el mismo motivo**, y `operator=`
  delega en ella: `a = b` puede no asignar nada.
- **El `try/catch (...)` de `Ocurrencia::toString` no protege de lo que parece.**
  Dentro llama a `getEntidad()->toString()` sin comprobar el nulo, y
  desreferenciar un nulo no lanza una excepción: es comportamiento indefinido, y
  el `catch` no lo ve.
- **Las dos clases pierden la corrección constante de sus bases.** `Entidad`
  declara `EsValida()` y `EsCompatible()` **`const`**; `Ocurrencia` las
  redeclara sin `const`, y con ellas `toString`, `getValor` y los tres
  operadores. Una `const Ocurrencia` no se puede ni comparar ni imprimir.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
