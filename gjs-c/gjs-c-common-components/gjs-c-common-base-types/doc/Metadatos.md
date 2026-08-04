# Metadatos

| Dato          | Valor                                          |
| ------------- | ---------------------------------------------- |
| Módulos       | 3                                              |
| Cabeceras     | `SDefDato.h`, `SDefPrimitiva.h`, `SInterfaz.h` |
| Prefijos      | `SDefDat`, `SDefPrim`, `SIntrfz`               |
| Structs       | `SDefDato`, `SDefPrimitiva`, `SInterfaz`       |
| Incluidos por | `Tipos.h`                                      |
| Tests         | Uno por módulo                                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Describir **la forma de los datos y de las operaciones**, no los datos en sí.
Es la parte reflexiva de la librería: con estos tres módulos se puede declarar
que existe una interfaz con ciertas primitivas, cada una con sus parámetros y
su valor de retorno, y consultarlo en tiempo de ejecución.

Se apilan en tres niveles:

```
SInterfaz        un conjunto de primitivas con nombre
  └── SDefPrimitiva    una función o procedimiento
        ├── SDefDato       el valor de retorno
        └── SDefDato …     los parámetros
```

## `SDefDato` — la descripción de un dato

```c
typedef struct
{
    int            iTipo;
    unsigned long  ulId;
    char *         p_cNombre;
    int            iReferencia;
    int            iTam;
    int            iDecimales;
    char *         p_cValorDef;
} SDefDato;
```

| Función                                                                                                                                                  | Descripción                      |
| -------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------- |
| `SDefDato * SDefDatCrear ( unsigned long ulId, const char * p_cNombre, int iTipo, int iReferencia, int iTam, int iDecimales, const char * p_cValorDef )` | Crea la definición.              |
| `void SDefDatDestruir ( SDefDato ** )`                                                                                                                   | Destruye y anula el puntero.     |
| `int SDefDatEsValido ( SDefDato * )`                                                                                                                     | 1 si es utilizable.              |
| `unsigned long SDefDatId ( SDefDato * )`                                                                                                                 | Identificador.                   |
| `int SDefDatTipo ( SDefDato * )`                                                                                                                         | Código de tipo.                  |
| `const char * SDefDatNombre ( SDefDato * )`                                                                                                              | Nombre.                          |
| `int SDefDatEsValor ( SDefDato * )`                                                                                                                      | 1 si se pasa por valor.          |
| `int SDefDatEsReferencia ( SDefDato * )`                                                                                                                 | 1 si se pasa por referencia.     |
| `int SDefDatTam ( SDefDato * )`                                                                                                                          | Tamaño declarado.                |
| `int SDefDatDecimales ( SDefDato * )`                                                                                                                    | Decimales, para tipos numéricos. |
| `const char * SDefDatValorDefecto ( SDefDato * )`                                                                                                        | Valor por defecto, como texto.   |

`iTipo` usa el catálogo `TIP_*` de
[Tipos](../../gjs-c-common-base/doc/Tipos.md) de la librería base.

Los límites de nombre y valor están en `TiposBasicosConstantes.h`:
`TIP_MAX_TAM_VARIABLE` y `TIP_MAX_TAM_VALOR`, ambos 255.

## `SDefPrimitiva` — la descripción de una operación

```c
typedef struct
{
    int             iTipo;
    unsigned long   ulId;
    char *          p_cNombre;
    SDefDato *      p_ddatRetorno;
    SSecuenciaPtr * p_secParametros;
} SDefPrimitiva;
```

`iTipo` toma los valores de `TiposPrimitiva.h`: `TIP_PRIM_NULO`,
`TIP_PRIM_PROCEDIMIENTO` o `TIP_PRIM_FUNCION`.

| Función                                                                                                                                                  | Descripción                  |
| -------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------- |
| `SDefPrimitiva * SDefPrimCrear ( unsigned long ulId, const char * p_cNombre, int iTipo )`                                                                | Crea la primitiva.           |
| `void SDefPrimDestruir ( SDefPrimitiva ** )`                                                                                                             | Destruye y anula el puntero. |
| `int SDefPrimEsValida ( SDefPrimitiva * )`                                                                                                               | 1 si es utilizable.          |
| `unsigned long SDefPrimId ( SDefPrimitiva * )`                                                                                                           | Identificador.               |
| `int SDefPrimTipo ( SDefPrimitiva * )`                                                                                                                   | Código de tipo.              |
| `int SDefPrimEsFuncion ( SDefPrimitiva * )`                                                                                                              | 1 si devuelve valor.         |
| `int SDefPrimEsProcedimiento ( SDefPrimitiva * )`                                                                                                        | 1 si no devuelve valor.      |
| `const char * SDefPrimNombre ( SDefPrimitiva * )`                                                                                                        | Nombre.                      |
| `int SDefPrimDefinirValorRetorno ( SDefPrimitiva *, int iTipo, int iReferencia, int iTam, int iDecimales )`                                              | Declara el retorno.          |
| `SDefDato * SDefPrimValorRetorno ( SDefPrimitiva * )`                                                                                                    | Definición del retorno.      |
| `int SDefPrimCrearParametro ( SDefPrimitiva *, const char * p_cNombre, int iTipo, int iReferencia, int iTam, int iDecimales, const char * p_cValorDef )` | Añade un parámetro.          |
| `int SDefPrimNumParametros ( SDefPrimitiva * )`                                                                                                          | Número de parámetros.        |
| `SDefDato * SDefPrimParametro ( SDefPrimitiva *, int iParametro )`                                                                                       | Parámetro por posición.      |

Obsérvese que los parámetros y el retorno **no se pasan ya construidos**: la
primitiva los fabrica internamente a partir de los datos sueltos
(`SDefPrimCrearParametro`, `SDefPrimDefinirValorRetorno`), y es ella quien los
posee.

## `SInterfaz` — el conjunto de operaciones

```c
typedef struct
{
    unsigned long   ulId;
    char *          p_cNombre;
    SSecuenciaPtr * p_secPrimitivas;
} SInterfaz;
```

| Función                                                                        | Descripción                  |
| ------------------------------------------------------------------------------ | ---------------------------- |
| `SInterfaz * SIntrfzCrear ( unsigned long ulId, const char * p_cNombre )`      | Crea la interfaz.            |
| `void SIntrfzDestruir ( SInterfaz ** )`                                        | Destruye y anula el puntero. |
| `int SIntrfzEsValido ( SInterfaz * )`                                          | 1 si es utilizable.          |
| `unsigned long SIntrfzId ( SInterfaz * )`                                      | Identificador.               |
| `const char * SIntrfzNombre ( SInterfaz * )`                                   | Nombre.                      |
| `int SIntrfzCrearPrimitiva ( SInterfaz *, const char * p_cNombre, int iTipo )` | Añade una primitiva.         |
| `int SIntrfzNumPrimitivas ( SInterfaz * )`                                     | Número de primitivas.        |
| `SDefPrimitiva * SIntrfzPrimitiva ( SInterfaz *, int iPrimitiva )`             | Primitiva por posición.      |

Ocho funciones: es el módulo con la API más pequeña de la librería.

## Dependencias

- [Secuencias](Secuencias.md) — `SSecuenciaPtr` guarda parámetros y primitivas.
- `TiposPrimitiva.h` — la clasificación función/procedimiento.
- El catálogo `TIP_*` de la librería base.

## Tests

`SDefDatoTest.c`, `SDefPrimitivaTest.c`, `SInterfazTest.c`.

## Observaciones

- **No hay búsqueda por nombre en ningún nivel.** `SIntrfzPrimitiva` y
  `SDefPrimParametro` acceden sólo por posición, así que localizar una primitiva
  por su nombre obliga a recorrer y comparar a mano. Para una estructura pensada
  para consultarse en tiempo de ejecución, es la carencia más notable.
- **`SDefPrimCrearParametro` devuelve `int`, no el `SDefDato *` creado.** Para
  usar el parámetro recién añadido hay que pedirlo después con
  `SDefPrimParametro ( …, SDefPrimNumParametros ( … ) - 1 )`. Lo mismo con
  `SIntrfzCrearPrimitiva`.
- `SDefDato` tiene los siete campos del constructor en un orden
  (`ulId, nombre, tipo, referencia, tam, decimales, valorDef`) que **no coincide**
  con el de `SDefPrimDefinirValorRetorno` (`tipo, referencia, tam, decimales`)
  ni con el de `SDefPrimCrearParametro` (`nombre, tipo, referencia, …`). Cinco de
  los siete parámetros son `int`, así que confundirlos compila sin aviso.
- Ninguno de los tres módulos ofrece `Duplicar`, a diferencia de la mayoría de
  objetos de la librería.
