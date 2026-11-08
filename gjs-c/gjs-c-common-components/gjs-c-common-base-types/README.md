# gjs-c-common-base-types

Librería de **estructuras de datos** en C del stack GJS. Se apoya en
[`gjs-c-common-base`](../gjs-c-common-base/README.md) y aporta el catálogo de
contenedores sobre el que se construyen las capas superiores: bloques de
memoria, listas, secuencias, vectores, tablas, pilas, colas, conjuntos, árboles
y grafos.

Es el módulo más grande del stack C: **73 módulos** en 4.664 líneas de cabeceras
y algo más de 34.000 de implementación.

---

## Coordenadas Maven

| Dato         | Valor                                |
| ------------ | ------------------------------------ |
| `groupId`    | `org.gjsoft.c.common`                   |
| `artifactId` | `gjs-c-common-base-types`            |
| `version`    | `1.1.0-SNAPSHOT`                |
| `packaging`  | `nar` (biblioteca **shared**)        |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`         |
| Depende de   | `org.gjsoft.c.common:gjs-c-common-base` |

---

## Uso

La cabecera fachada es `TiposBasicos.h`:

```c
#include <TiposBasicos.h>
```

Arrastra las 74 cabeceras de módulo, **excepto `SArbolB.h` y `SListaVec.h`**,
que hay que incluir a mano.

Ejemplo con una lista de enteros:

```c
#include <Base.h>
#include <TiposBasicos.h>

int main ( void )
{
    SListaEnteros * p_lisObj = SLisIntCrear ();

    if ( SLisIntEsValida ( p_lisObj ) == 1 )
    {
        SLisIntInsertarAlFinal ( p_lisObj, 42 );
        SLisIntInsertarAlFinal ( p_lisObj, 7 );
        printf ( "%d elementos\n", SLisIntNumElementos ( p_lisObj ) );
    }
    SLisIntDestruir ( &p_lisObj );
    return ( 0 );
}
```

---

## Convenios de la librería

### El patrón de objeto

Todos los módulos siguen el mismo esquema de "objeto en C": una `struct` con
nombre `S<Concepto>` y un juego de funciones con un prefijo corto propio.

| Elemento    | Forma                               | Ejemplo                         |
| ----------- | ----------------------------------- | ------------------------------- |
| Tipo        | `S<Concepto>`                       | `SLista`                        |
| Constructor | `S<Pfx>Crear…`                      | `SLisCrear ()`                  |
| Destructor  | `S<Pfx>Destruir ( S<Concepto> ** )` | `SLisDestruir ( &p_lisObj )`    |
| Validación  | `S<Pfx>EsValido` / `EsValida`       | `SLisEsValida ( p_lisObj )`     |
| Consulta    | `S<Pfx><Sustantivo>`                | `SLisNumElementos ( p_lisObj )` |
| Acción      | `S<Pfx><Verbo>`                     | `SLisInsertarAlFinal ( … )`     |

El destructor toma **puntero a puntero** y anula el puntero del llamante, igual
que `MemLiberar` en [gjs-c-common-base](../gjs-c-common-base/doc/Memoria.md).

### Las variantes

La mayor parte del catálogo son variantes del mismo contenedor sobre distinto
tipo de elemento. El sufijo del nombre y del prefijo indican cuál es:

| Sufijo          | Qué almacena                             | Ejemplo               | Prefijo    |
| --------------- | ---------------------------------------- | --------------------- | ---------- |
| *(ninguno)*     | `SElemento` (bloque de bytes genérico)   | `SLista`              | `SLis`     |
| `Ptr`           | punteros `void *` sin copia ni propiedad | `SListaPtr`           | `SLisp`    |
| `Enteros`       | `int` por valor                          | `SListaEnteros`       | `SLisInt`  |
| `EnterosLargos` | `long` por valor                         | `SListaEnterosLargos` | `SLisIntl` |
| `Literales`     | cadenas `char *`                         | `SListaLiterales`     | `SLisLit`  |
| `Flags`         | bits                                     | `SVectorFlags`        | `SVecFlg`  |

Las variantes de enteros se llaman `…Enteros`, pero su prefijo es `Int`, no
`Ent` (`SLisInt`, `SLisIntl`, `SLisIntLss`, `SSecInt`, `SArbInt`…): `Ent` lo usan
las entidades de `gjs-c-common-database` (`SLisEnt` para `SListaEntidades`,
`SCnjEnt` para `SConjuntoEntidades`).

La diferencia práctica está en **quién es dueño de la memoria**: las variantes
base y las de valor copian el dato dentro de la estructura; las `Ptr` guardan el
puntero tal cual y no lo liberan al destruir el contenedor.

### Memoria y errores

Se heredan los convenios de `gjs-c-common-base`: toda la reserva pasa por
`MemReservar` / `MemLiberar`, los predicados devuelven `1`/`0`, y los fallos se
anotan en el estado global de errores (`ERROR_ESTABLECER`), no en el valor de
retorno.

---

## Compilación

Igual que el resto del repositorio, con Maven y en los mismos tres modos
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)):

| Modo                    | Consola          | Comando             | Estado                                          |
| ----------------------- | ---------------- | ------------------- | ----------------------------------------------- |
| Cygwin (**el normal**)  | mintty (Cygwin)  | `mvn clean install` | **Verificado**: `BUILD SUCCESS`, 70/70 tests OK |
| Windows puro            | PowerShell / cmd | `mvn clean install` | **Verificado** (2026-09)                        |
| Linux                   | consola Linux    | `mvn clean install` | Sin verificar: no hay máquina                   |

Requiere tener instalado antes `gjs-c-common-base`.

---

## Tests

Mismo arnés que el resto del stack C: un ejecutable propio cuyo `main` está en
`src/test/c/.../Test.c` y que registra **72 suites**.

```
Test.exe               # todas
Test.exe SListaTest    # una sola
mvn test               # vía Maven
```

Sin test asociado: `SArbolB`, `TiposBasicos`, `TiposBasicosConstantes`,
`TiposBasicosErrores`, `TiposPrimitiva` y `TiposResultado`.

---

## Documentación de los módulos

Los 73 módulos son en su mayoría variantes de un mismo contenedor, así que la
documentación se organiza **por familias**: cada documento cubre el contenedor
base y tabula en qué se diferencian sus especializaciones.

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **La fachada se llamaba `Tipos.h`**, igual que el catálogo de super-tipos
  `TIP_*` de `gjs-c-common-base`. Los dos se publicaban en su NAR `noarch`, así
  que `#include <Tipos.h>` resolvía según el orden de los `-I`: dentro de este
  módulo, el `#include <Tipos.h>` de `BaseConfig.h` traía la fachada en lugar del
  catálogo. Ahora se llama `TiposBasicos.h` y `<Tipos.h>` es siempre el de base.
- **`SArbolB` está sin portar.** Todo el contenido de la cabecera está dentro de
  un bloque de comentario, con includes de una base de código anterior
  (`mt_rc_libs_*`). No está en la fachada y no tiene test.
  Ver [Arboles](doc/Arboles.md).
- **`TiposBasicos.h:96` incluye `<SSecuenciaEnteroslargosSinSigno.h>`** con `l`
  minúscula; el fichero real lleva `L` mayúscula. Funciona sólo porque Windows y
  Cygwin no distinguen mayúsculas en los nombres de fichero: **fallará en el modo
  Linux nativo** pendiente.
- `TiposBasicosConfig.h` vive en el árbol de **fuentes**, no en `src/main/include`,
  así que no se publica en el NAR `noarch` y no está disponible para los módulos
  consumidores.
- Cada documento de familia tiene una sección *Observaciones* con los detalles
  detectados en su código.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
