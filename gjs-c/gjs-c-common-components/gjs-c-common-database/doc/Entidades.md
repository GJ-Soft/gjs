# Entidades

| Dato          | Valor                                                                                                     |
| ------------- | --------------------------------------------------------------------------------------------------------- |
| Módulos       | 5                                                                                                         |
| Cabeceras     | `SEntidad.h`, `SEntidadNom.h`, `SEntidadCod.h`, `SEntidadCodNom.h`, `SEntidadIdCod.h`                     |
| Prefijos      | `SEnt`, `SEntNom`, `SEntCod`, `SEntCodNom`, `SEntIdCod`                                                   |
| Funciones     | 40 + 55 + 46 + 59 + 55                                                                                    |
| Incluidos por | `TiposBaseDatos.h`                                                                                        |
| Tests         | Uno por módulo                                                                                            |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **entidad** es algo que se identifica y lleva un contenido colgando: un
cliente, un artículo, una cuenta. Son las clases base sobre las que se montan
las colecciones ordenadas y las tablas asociativas del resto del stack.

Hay **dos raíces**, según cómo se identifique la entidad, y cada una tiene sus
derivadas:

```
  SEntidad  ( identificador numerico )
     ├── SEntidadNom      ( + nombre )
     └── SEntidadIdCod    ( + codigo )

  SEntidadCod  ( identificador de texto )
     └── SEntidadCodNom   ( + nombre )
```

`SEntidadCod` **no** deriva de `SEntidad`: son dos jerarquías independientes. La
distinción es la clásica de una base de datos, la clave técnica frente a la
clave de negocio.

[SMensaje](../../gjs-c-common-types/doc/SMensaje.md), de `gjs-c-common-types`,
sigue el mismo contrato pero no es una entidad: guarda el `SId` directamente.

```c
typedef struct
{
    SId  *  p_idEntidad;
    SPtr *  p_ptrContenido;
} SEntidad;

typedef struct
{
    SCodigo * p_codEntidad;
    SPtr *    p_ptrContenido;
} SEntidadCod;
```

El contenido es un [SPtr](../../gjs-c-common-base-types/doc/SPtr.md): el objeto
junto con la función que sabe destruirlo. La entidad es **dueña** de ese `SPtr`
y lo destruye con ella. Siempre hay uno, aunque esté vacío: una entidad sin
contenido lleva un `SPtrCrearDef ( NULL )`.

Las derivadas guardan un puntero a su base más el campo que añaden. El contenido
vive siempre en la base:

```c
typedef struct
{
    SEntidad *  p_entInfo;
    SNombre  *  p_nomEntidad;
} SEntidadNom;

typedef struct
{
    SEntidad *  p_entInfo;
    SCodigo  *  p_codEntidad;
} SEntidadIdCod;

typedef struct
{
    SEntidadCod * p_entcInfo;
    SNombre     * p_nomEntidad;
} SEntidadCodNom;
```

## Identidad

**La identidad de una entidad es su identificador, y nada más**: el `SId` en la
rama de `SEntidad`, el `SCodigo` en la de `SEntidadCod`. Ni el nombre, ni el
código secundario, ni el contenido entran en ella. El motivo es que no se
permiten identificadores repetidos, así que el identificador ya distingue.

De ahí salen tres reglas que conviene tener presentes:

- `EsIgual`, `EsMenor`, `EsMayor`, `EsMenorIg` y `EsMayorIg` miran sólo el
  identificador.
- `Hash` mira sólo el identificador, y lo hace **delegando en la clase base**.
  Una entidad derivada reparte exactamente igual que su base, así que las dos
  pueden convivir en la misma tabla a través de `*Base`. Meter el nombre o el
  código secundario en el hash rompería la tabla, porque son campos mutables: al
  cambiar uno, la entidad quedaría fuera de la cubeta donde se guardó.
- `Comparar` mira el identificador **y, sólo cuando empata, desempata por el
  segundo campo**.

Ese desempate es deliberado y **provisional**. Sirve para las situaciones de
carga: listas cuyos elementos aún no tienen identificador asignado, unificar dos
listas, o reasignar identificadores ordenando por nombre o por código. Como
consecuencia, dos entidades con el mismo id y distinto nombre son iguales para
`EsIgual` y distintas para `Comparar`. No es un descuido; es el andamio, y se
retirará cuando el desarrollo esté más avanzado.

## Validez

`EsValida` comprueba **el identificador** y que haya `SPtr` de contenido, en las
cinco clases. Que el `SPtr` lleve algo no entra, y el nombre tampoco. Como los
constructores siempre ponen un `SPtr`, en la práctica sólo decide el
identificador.

- Una entidad recién creada con `SEntCrearDef ()` **no** es válida: su id vale 0,
  que aún no es un identificador asignado.
- Una entidad con id y sin contenido **sí** es válida. Para saber si lleva
  contenido está `TieneContenido` en las cinco clases (`SEntTieneContenido`,
  `SEntNomTieneContenido`…): 1 si el `SPtr` no está vacío, 0 si lo está o si la
  entidad es nula. Las compuestas preguntan a su entidad interna.
- Para saber si el nombre o el código secundario sirven hay que preguntarles
  aparte, con `SNomEsValido` o `SCodEsValido`.

### Qué exige cada constructor

Lo que `EsValida` no mira, los constructores sí pueden exigirlo. No es uniforme,
y conviene tenerlo delante:

| Clase            | Identificador | Segundo campo                                    |
| ---------------- | ------------- | ------------------------------------------------ |
| `SEntidad`       | Obligatorio   | —                                                |
| `SEntidadCod`    | Obligatorio   | —                                                |
| `SEntidadNom`    | Obligatorio   | Opcional: si falta, un `SNombre` vacío           |
| `SEntidadCodNom` | Obligatorio   | Opcional: si falta, un `SNombre` vacío           |
| `SEntidadIdCod`  | Obligatorio   | **Obligatorio**: sin código no se crea la entidad |

Sin identificador válido, las cinco devuelven `NULL`. Las variantes `…Ext`, que
reciben el contenido, devuelven `NULL` también si el `SPtr` es nulo: para crear
sin contenido están las que no llevan `Ext`, o un `SPtrCrearDef ( NULL )`.

En `SEntidadNom` y `SEntidadCodNom`, un nombre que no supere la validación de
`SNombre` **no impide crear la entidad**: `EncapsularExt` pone en su lugar un
`SNomCrearDef ()`. Por eso `SEntNomNombre` nunca devuelve `NULL` sobre una
entidad construida, y `SEntNomValorNombreLit` devuelve la cadena vacía, no
`NULL`. Es lo que permite asignarle un nombre después con
`SEntNomEstablecerValorNombre`: el objeto interno ya existe.

`SEntidadIdCod` es la excepción: el código es su segundo identificador, no un
adorno, así que `SEntIdCodEncapsularExt` exige que sea válido y devuelve `NULL`
si no lo es. Un `SEntIdCodCrearLit ( 5, "COD-001", 10 )` con un código que no
pasa la validación no da una entidad sin código: no da entidad.

## API

Las cinco siguen el mismo esquema. Se indican las de `SEntidad`; las demás
cambian el prefijo y añaden lo suyo.

### Ciclo de vida

| Función                                              | Descripción                                         |
| ---------------------------------------------------- | --------------------------------------------------- |
| `SEntCrearDef ()`                                    | Id a 0, sin contenido. No es válida todavía.        |
| `SEntCrear ( unsigned long ulId )`                   | Con identificador, sin contenido.                   |
| `SEntCrearExt ( unsigned long ulId, SPtr * )`        | Con identificador y contenido.                      |
| `SEntEncapsular ( SId * )`                           | Toma la propiedad del identificador.                |
| `SEntEncapsularExt ( SId *, SPtr * )`                | Ídem, con contenido.                                |
| `void SEntDestruir ( SEntidad ** )`                  | Destruye, **contenido incluido**, y anula.          |
| `SPtr * SEntPtr ( SEntidad * )`                      | La envuelve en un `SPtr` con `SEntDestruir`.        |

### Propiedad de la memoria

Es la parte que más conviene tener clara:

- **`Crear*` construye las piezas por su cuenta.** Si el encapsulado falla, las
  destruye antes de devolver `NULL`: no se pierde nada. Las que no llevan `Ext`
  crean también el `SPtr` vacío, y lo destruyen igual si fallan.
- **`Encapsular*` recibe piezas ya construidas y se queda con ellas.** Si falla,
  **no las toca**: siguen siendo del llamante, que es quien debe destruirlas.
- **El `SPtr` de contenido que recibe un `…Ext` pasa a ser de la entidad** si se
  crea, y sigue siendo del llamante si no.
- **`Destruir` lo destruye todo**: identificador, nombre o código, y el
  contenido, con el destructor de su `SPtr`. Hasta el 2026-10-18 devolvía el
  contenido sin destruirlo; ahora quien quiera conservarlo no debe dárselo a la
  entidad.
- **`SEntPtr`** (y `SEntNomPtr`, `SEntCodPtr`…) pasa la propiedad de la entidad a
  un `SPtr`: después se libera con `SPtrDestruir`, que llama a `SEntDestruir`, y
  no por separado. Con entidad nula devuelve un `SPtr` vacío; si falla la reserva
  del `SPtr`, devuelve `NULL` y la entidad sigue siendo del llamante.

### Acceso

`SEntId` (el `SId` interno), `SEntValorId` (el número), `SEntContenido`,
`SEntEsValida`. Las derivadas añaden el suyo (`SEntNomNombre`,
`SEntNomValorNombre`, `SEntNomValorNombreLit`…) y un accesor a la base.

> **`SEntNomBase`, `SEntIdCodBase` y `SEntCodNomBase` devuelven el objeto
> interno, no una copia.** Están para meter la entidad en colecciones que
> trabajen con la clase base. No hay que destruirlos, ni usarlos después de
> destruir la entidad que los contiene. De momento no son `const`, a propósito;
> está pendiente de revisar.

### Asignación

`SEntEstablecerId`, `SEntEstablecerValorId`, `SEntEstablecerContenido`,
`SEntEstablecerContenidoExt`, `SEntAsignarContenido`, más los del campo propio
en cada derivada.

**El retorno dice si se guardó, no si la entidad quedó completa.** Para lo
segundo está `EsValida`, que es una pregunta distinta. `SEntEstablecerId` copia
el valor del `SId` que se le pasa: no se queda con el puntero, que sigue siendo
del llamante.

El contenido se cambia de tres maneras:

| Función                                                                         | Qué cambia                                                                     |
| ------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| `int SEntEstablecerContenido ( SEntidad *, void * )`                            | El objeto dentro del `SPtr`, con `SPtrEstablecer`: destruye el anterior.       |
| `int SEntEstablecerContenidoExt ( SEntidad *, void *, PRC_DESTRUCTOR )`         | Objeto y destructor: crea un `SPtr` nuevo y lo asigna.                         |
| `int SEntAsignarContenido ( SEntidad *, SPtr * )`                               | El `SPtr` entero: destruye el anterior y se queda con el nuevo.                |

Las tres devuelven 1, o 0 si la entidad es nula. Además:

- `AsignarContenido` falla con un `SPtr` nulo, y entonces no cambia nada.
  Asignar el mismo `SPtr` que ya tiene no lo destruye.
- `EstablecerContenidoExt` falla sin destructor, o si no puede reservar el
  `SPtr`: la entidad conserva su contenido y el objeto sigue siendo del
  llamante. Con **el mismo objeto** que ya tiene sólo cambia el destructor;
  crear otro `SPtr` destruiría el objeto al sustituir al anterior. Así se le
  puede dar a un contenido ya establecido el destructor que le faltaba.

> **El destructor lo fija quien pone el contenido, y es su responsabilidad.**
> `EstablecerContenido ( void * )` usa el destructor del `SPtr` que ya hay, y en
> una entidad creada sin contenido ése es `MemLiberar`, que sólo vale para un
> bloque de `MemReservar`. La entidad no sabe qué estructura tiene su
> contenido, así que no puede corregirlo. Si se guarda así un objeto del stack
> —una `SCadena`, un `SValor`—, al destruirlo o sustituirlo **fallará**. El
> destructor correcto hay que darlo de una de tres formas:
>
> - al crear la entidad, con un `SPtr` ya hecho (`SPtrCrear`, `SPtrPreparar`,
>   `SCadPtr`…) en el `…Ext`;
> - con `AsignarContenido ( p_ent, SCadPtr ( p_cad ) )`;
> - con `EstablecerContenidoExt ( p_ent, p_cad, (PRC_DESTRUCTOR) SCadDestruir )`.
>
> Después, `EstablecerContenido` sirve para cambiar el objeto por otro del mismo
> tipo.

### Comparación

Cuatro familias por cada clase, según con qué se compare:

| Clase            | Contra sí misma | Contra la base | Contra el identificador | Contra el valor suelto |
| ---------------- | --------------- | -------------- | ----------------------- | ---------------------- |
| `SEntidad`       | `SEntEs…`       | —              | `SEntEs…Id`             | `SEntEs…Num`           |
| `SEntidadNom`    | `SEntNomEs…`    | `SEntNomEs…Ent`| `SEntNomEs…Id`          | `SEntNomEs…Num`        |
| `SEntidadIdCod`  | `SEntIdCodEs…`  | `SEntIdCodEs…Ent` | `SEntIdCodEs…Id`     | `SEntIdCodEs…Num`      |
| `SEntidadCod`    | `SEntCodEs…`    | —              | `SEntCodEs…Codigo`      | `SEntCodEs…Cad` / `…Lit` |
| `SEntidadCodNom` | `SEntCodNomEs…` | `SEntCodNomEs…Ent` | `SEntCodNomEs…Codigo` | `SEntCodNomEs…Cad` / `…Lit` |

Las de tres estados llevan `Comparar` en lugar de `Es…` y devuelven `COMP_MENOR`,
`COMP_IGUAL` o `COMP_MAYOR`. Ante punteros nulos, el nulo ordena antes: una
entidad frente a `NULL` da `COMP_MAYOR`, `NULL` frente a una entidad da
`COMP_MENOR`, y dos nulos dan `COMP_IGUAL`.

Las ramas con identificador numérico añaden además `EstaEnRango…` y
`EstaEnRangoIg…`, intervalo abierto y cerrado.

### Hash

`unsigned int SEntHash ( SEntidad * )`, y una por clase. Todas tienen la misma
firma: **sólo el objeto**, sin parámetros añadidos.

Es una consecuencia directa de la regla de identidad: el hash tiene que ir de la
mano de `EsIgual`, así que mira lo mismo que él y nada más. El contenido no entra
—no forma parte de la identidad, y la entidad ni siquiera sabe qué hay dentro de
su `SPtr`— y el segundo campo tampoco, por mutable. Hubo un parámetro
opcional para pasar una función de hash del contenido; se quitó precisamente
porque usarlo rompía el contrato con `EsIgual`.

Cada clase delega hacia abajo hasta llegar al identificador:

| Clase            | Delega en                                     |
| ---------------- | --------------------------------------------- |
| `SEntidad`       | `SIdHash` sobre el `SId`                      |
| `SEntidadCod`    | `SCodHash` sobre el `SCodigo`                 |
| `SEntidadNom`    | `SEntHash` sobre su `SEntidad` base           |
| `SEntidadIdCod`  | `SEntHash` sobre su `SEntidad` base           |
| `SEntidadCodNom` | `SEntCodHash` sobre su `SEntidadCod` base     |

Sobre un puntero nulo el resultado es **0**. Ojo, `EsValida` no interviene: una
entidad recién creada con `SEntCrearDef ()`, que no es válida todavía, sí tiene
hash —el de su id a 0—, y no es 0. Como en el resto del stack, 0 es a la vez el
hash de una entrada inválida y un hash legítimo posible.

## Dependencias

- [Identificadores](../../gjs-c-common-base-types/doc/Identificadores.md) — `SId`.
- [SPtr](../../gjs-c-common-base-types/doc/SPtr.md) — el contenido, y los
  `…Ptr` de cada clase.
- [SCodigo](../../gjs-c-common-text/doc/SCodigo.md) y
  [SNombre](../../gjs-c-common-text/doc/SNombre.md) — los campos de texto.
- [Hash](../../gjs-c-common-base/doc/Hash.md) — indirecta: es donde acaban
  `SIdHash` y `SCodHash`, en los que delega toda la familia.

## Tests

`SEntidadTest.c`, `SEntidadNomTest.c`, `SEntidadCodTest.c`,
`SEntidadCodNomTest.c`, `SEntidadIdCodTest.c`. En las cinco: creación con y sin
contenido, y con `SPtr` nulo; `AsignarContenido` con otro `SPtr`, con el mismo y
con nulo; `EstablecerContenidoExt` con destructor propio, con el mismo objeto,
sin destructor y sobre una entidad nula, comprobando que después
`EstablecerContenido` y `Destruir` usan ese destructor; y el `…Ptr`, con entidad
y con `NULL`. Con `MODO_DEPURACION`
comprueban además que destruir la entidad libera el contenido y que no queda
memoria reservada.

## Observaciones

- **Ninguna de las cinco tiene `Duplicar`**, pese a que casi todos los objetos
  del stack lo ofrecen. Copiar una entidad hay que hacerlo a mano, y hay que
  decidir qué se hace con el contenido: el `SPtr` sabe destruirlo, pero no
  copiarlo.
- **Los `Establecer…` del segundo campo asignan sobre el objeto interno, no lo
  sustituyen.** En `SEntidadNom` y `SEntidadCodNom` eso no da problema porque el
  `SNombre` siempre existe. Y
  `SEntIdCodEstablecerCodigo` usa `SCodAsignar` sobre el `SCodigo` interno, que
  ahí siempre existe también por ser obligatorio, así que hoy ninguna de las
  cinco tiene el problema; conviene no perderlo de vista si alguna vez se
  relaja la obligatoriedad del código.
- El identificador numérico es `unsigned long`, que son 32 bits con MinGW-w64 y
  64 en Cygwin y Linux. Una entidad persistida con ids altos no es portable entre
  los dos modos de compilación.
- `SEntidadCod` y `SEntidadNom` no se combinan: no hay una entidad con id, código
  y nombre a la vez. La que más se le acerca es `SEntidadCodNom`, que renuncia al
  id.
