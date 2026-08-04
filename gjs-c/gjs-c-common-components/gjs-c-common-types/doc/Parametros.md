# Parámetros y listas de valores

| Dato          | Valor                                                   |
| ------------- | ------------------------------------------------------- |
| Módulos       | 3                                                       |
| Cabeceras     | `SParametro.h`, `SListaParametros.h`, `SListaValores.h` |
| Prefijos      | `SPar`, `SLisPar`, `SLisVal`                            |
| Funciones     | 15 + 30 + 30                                            |
| Incluidos por | `TiposDatos.h`                                          |
| Tests         | Uno por módulo                                          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **parámetro** es un [SValor](SValor.md) con nombre. Las dos listas son los
contenedores para transportar conjuntos de ellos: la de parámetros con nombre y
la de valores sueltos.

Es el mecanismo con el que se pasan argumentos entre capas sin firmas fijas:
configuración, invocación de primitivas, resultados de consulta.

## `SParametro`

```c
typedef struct
{
    SValor *  p_valContenido;
    SCadena * p_cadNombre;
} SParametro;
```

| Función                                              | Descripción                  |
| ---------------------------------------------------- | ---------------------------- |
| `SParametro * SParCrearDef ()`                       | Parámetro vacío.             |
| `SParametro * SParCrear ( … )`                       | Con nombre y valor.          |
| `SParametro * SParCrearExt ( … )`                    | Variante con más argumentos. |
| `SParametro * SParCrearExtLit ( … )`                 | Ídem con nombre literal.     |
| `SParametro * SParDuplicar ( SParametro * )`         | Copia independiente.         |
| `void SParDestruir ( SParametro ** )`                | Destruye y anula el puntero. |
| `int SParEsValido ( SParametro * )`                  | 1 si es utilizable.          |
| `SCadena * SParNombre ( SParametro * )`              | Nombre.                      |
| `SValor * SParValor ( SParametro * )`                | Valor.                       |
| `int SParTipo ( SParametro * )`                      | Tipo del valor.              |
| `int SParEstablecerNombre ( … )` / `…Lit`            | Cambia el nombre.            |
| `int SParEstablecerValor ( … )` / `…Ext` / `…ExtLit` | Cambia el valor.             |

El sufijo `Lit` indica que el nombre se pasa como `const char *` en lugar de
como [SCadena](../../gjs-c-common-text/doc/SCadena.md).

## `SListaParametros` y `SListaValores`

Treinta funciones cada una, con la API habitual de
[lista con cursor](../../gjs-c-common-base-types/doc/Listas.md): ciclo de vida,
acceso por índice, cursor, inserción y búsqueda.

La diferencia es el elemento:

| Módulo             | Guarda         | Búsqueda por |
| ------------------ | -------------- | ------------ |
| `SListaParametros` | `SParametro *` | Nombre       |
| `SListaValores`    | `SValor *`     | Posición     |

```c
SListaParametros * p_lisObj = SLisParCrear ();
SParametro * p_parObj = SParCrear ( … );

SLisParInsertar ( p_lisObj, p_parObj );
SLisParDestruir ( &p_lisObj );
```

## Dependencias

- [SValor](SValor.md) — el contenido.
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — el nombre.
- [Listas](../../gjs-c-common-base-types/doc/Listas.md) — el almacenamiento.

## Tests

`SParametroTest.c`, `SListaParametrosTest.c`, `SListaValoresTest.c`.

## Observaciones

- **`SParCrearExt` y `SParEstablecerValorExt` no dicen en la cabecera qué añade
  el `Ext`.** En el resto del stack ese sufijo significa "con parámetros
  adicionales", pero aquí conviven `Crear`, `CrearExt` y `CrearExtLit` sin que se
  aprecie la diferencia entre las tres.
- `SParNombre` devuelve `SCadena *`, es decir, la cadena **interna
  modificable**: se puede cambiar el nombre del parámetro sin pasar por
  `SParEstablecerNombre`. Lo mismo con `SParValor`.
- Las dos listas tienen exactamente **30 funciones**, lo que sugiere que son la
  misma plantilla con el tipo cambiado. Sin embargo `SListaParametros` puede
  buscar por nombre y `SListaValores` no, así que no son intercambiables.
- No hay conversión entre ambas: para pasar de una lista de parámetros a la de
  sus valores hay que recorrer y extraer a mano.
