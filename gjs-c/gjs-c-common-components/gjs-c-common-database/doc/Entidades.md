# Entidades

| Dato          | Valor                                                                                                     |
| ------------- | --------------------------------------------------------------------------------------------------------- |
| Módulos       | 5                                                                                                         |
| Cabeceras     | `SEntidad.h`, `SEntidadNom.h`, `SEntidadCod.h`, `SEntidadCodNom.h`, `SEntidadIdCod.h`                     |
| Prefijos      | `SEnt`, `SEntNom`, `SEntCod`, `SEntCodNom`, `SEntIdCod`                                                   |
| Funciones     | 36 + 51 + 42 + 55 + 51                                                                                    |
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
    void *  p_vContenido;
} SEntidad;

typedef struct
{
    SCodigo * p_codEntidad;
    void *    p_vContenido;
} SEntidadCod;
```

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

`EsValida` comprueba **sólo el identificador**, en las cinco clases. El contenido
nunca entra, y el nombre tampoco.

- Una entidad recién creada con `SEntCrearDef ()` **no** es válida: su id vale 0,
  que aún no es un identificador asignado.
- Una entidad con id y sin contenido **sí** es válida.
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

Sin identificador válido, las cinco devuelven `NULL`.

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

| Función                                              | Descripción                                    |
| ---------------------------------------------------- | ---------------------------------------------- |
| `SEntCrearDef ()`                                    | Id a 0, sin contenido. No es válida todavía.   |
| `SEntCrear ( unsigned long ulId )`                   | Con identificador, sin contenido.              |
| `SEntCrearExt ( unsigned long ulId, void * )`        | Con identificador y contenido.                 |
| `SEntEncapsular ( SId * )`                           | Toma la propiedad del identificador.           |
| `SEntEncapsularExt ( SId *, void * )`                | Ídem, con contenido.                           |
| `void * SEntDestruir ( SEntidad ** )`                | Destruye, **devuelve el contenido** y anula.   |

### Propiedad de la memoria

Es la parte que más conviene tener clara:

- **`Crear*` construye las piezas por su cuenta.** Si el encapsulado falla, las
  destruye antes de devolver `NULL`: no se pierde nada.
- **`Encapsular*` recibe piezas ya construidas y se queda con ellas.** Si falla,
  **no las toca**: siguen siendo del llamante, que es quien debe destruirlas.
- **`Destruir` devuelve el contenido sin destruirlo.** El contenido nunca ha sido
  suyo. Lo demás —identificador, nombre, código— sí lo destruye.

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

`SEntEstablecerId`, `SEntEstablecerValorId`, `SEntEstablecerContenido`, más los
del campo propio en cada derivada.

**El retorno dice si se guardó, no si la entidad quedó completa.** Para lo
segundo está `EsValida`, que es una pregunta distinta. `SEntEstablecerId` copia
el valor del `SId` que se le pasa: no se queda con el puntero, que sigue siendo
del llamante. `SEntEstablecerContenido` devuelve el contenido anterior.

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
—no forma parte de la identidad, y la entidad ni siquiera sabe qué hay detrás de
ese `void *`— y el segundo campo tampoco, por mutable. Hubo un parámetro
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
- [SCodigo](../../gjs-c-common-text/doc/SCodigo.md) y
  [SNombre](../../gjs-c-common-text/doc/SNombre.md) — los campos de texto.
- [Hash](../../gjs-c-common-base/doc/Hash.md) — indirecta: es donde acaban
  `SIdHash` y `SCodHash`, en los que delega toda la familia.

## Tests

`SEntidadTest.c`, `SEntidadNomTest.c`, `SEntidadCodTest.c`,
`SEntidadCodNomTest.c`, `SEntidadIdCodTest.c`.

## Observaciones

- **Ninguna de las cinco tiene `Duplicar`**, pese a que casi todos los objetos
  del stack lo ofrecen. Copiar una entidad hay que hacerlo a mano, y hay que
  decidir qué se hace con el contenido, que es un `void *` sin dueño conocido.
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
