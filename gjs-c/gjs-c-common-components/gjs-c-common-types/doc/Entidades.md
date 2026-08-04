# Entidades

| Dato          | Valor                                              |
| ------------- | -------------------------------------------------- |
| Módulos       | 3                                                  |
| Cabeceras     | `SEntidadId.h`, `SEntidadCod.h`, `SEntidadIdCod.h` |
| Prefijos      | `SEntId`, `SEntCod`, `SEntIdCod`                   |
| Funciones     | 9 + 9 + 13                                         |
| Incluidos por | `TiposDatos.h`                                     |
| Tests         | Uno por módulo                                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **entidad** es algo que se identifica y tiene nombre: un cliente, un
artículo, una cuenta. Los tres módulos cubren las tres formas habituales de
identificarla.

| Módulo          | Identificador   | Struct                        |
| --------------- | --------------- | ----------------------------- |
| `SEntidadId`    | Numérico        | `unsigned long ulId` + nombre |
| `SEntidadCod`   | Código de texto | código + nombre               |
| `SEntidadIdCod` | Ambos           | id + código + nombre          |

```c
typedef struct
{
    unsigned long ulId;
    SCadena *     p_cadNombre;
} SEntidadId;

typedef struct
{
    SCadena * p_cadCodigo;
    SCadena * p_cadNombre;
} SEntidadCod;

typedef struct
{
    unsigned long ulId;
    SCadena *     p_cadCodigo;
    SCadena *     p_cadNombre;
} SEntidadIdCod;
```

La distinción es la clásica de una base de datos: la clave técnica (`ulId`), la
clave de negocio (`p_cadCodigo`), o las dos.

## API

Las tres siguen el mismo esquema:

| Función             | `SEntidadId`             | `SEntidadCod`             | `SEntidadIdCod`             |
| ------------------- | ------------------------ | ------------------------- | --------------------------- |
| Crear               | `SEntIdCrear`            | `SEntCodCrear`            | `SEntIdCodCrear`            |
| Envolver sin copiar | `SEntIdEncapsular`       | `SEntCodEncapsular`       | `SEntIdCodEncapsular`       |
| Destruir            | `SEntIdDestruir`         | `SEntCodDestruir`         | `SEntIdCodDestruir`         |
| Validar             | `SEntIdEsValido`         | `SEntCodEsValido`         | `SEntIdCodEsValido`         |
| Leer id             | `SEntIdId`               | —                         | `SEntIdCodId`               |
| Leer código         | —                        | `SEntCodCodigo`           | `SEntIdCodCodigo`           |
| Leer nombre         | `SEntIdNombre`           | `SEntCodNombre`           | `SEntIdCodNombre`           |
| Fijar id            | `SEntIdEstablecerId`     | —                         | `SEntIdCodEstablecerId`     |
| Fijar código        | —                        | `SEntCodEstablecerCodigo` | `SEntIdCodEstablecerCodigo` |
| Fijar nombre        | `SEntIdEstablecerNombre` | `SEntCodEstablecerNombre` | `SEntIdCodEstablecerNombre` |

Más las variantes `…Lit` de los asignadores, que reciben `const char *` en lugar
de [SCadena](../../gjs-c-common-text/doc/SCadena.md).

`SEntidadIdCod` añade `SEntIdCodTipo`.

### `Crear` frente a `Encapsular`

La pareja se repite en los tres módulos y es la decisión de propiedad:
`Crear` copia lo que se le da, `Encapsular` se queda con los objetos que recibe
y los destruye con la entidad. Es el mismo criterio que
[SContenido](../../gjs-c-common-base-types/doc/SContenido.md) en `base-types`.

## Dependencias

- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — nombre y código.

## Tests

`SEntidadIdTest.c`, `SEntidadCodTest.c`, `SEntidadIdCodTest.c`.

## Observaciones

- **Ninguna de las tres tiene comparación ni `Duplicar`.** No hay
  `SEntIdEsIgual` ni forma de copiar una entidad, pese a que casi todos los
  objetos del stack ofrecen ambas cosas. Para comparar hay que sacar el id o el
  código y compararlos aparte.
- **`SEntidadIdCod` no es una composición de las otras dos**, sino una tercera
  estructura que repite sus campos. Un cambio en el criterio de validación hay
  que hacerlo en tres sitios.
- `SEntIdCodTipo` existe sólo en la variante completa y la cabecera no dice a qué
  tipo se refiere: presumiblemente el catálogo `TIP_*`, pero no hay campo `iTipo`
  en la estructura.
- El identificador numérico es `unsigned long`, que son 32 bits en Windows puro y
  64 en Cygwin y Linux. Una entidad persistida con ids altos no es portable entre
  los dos modos de compilación.
