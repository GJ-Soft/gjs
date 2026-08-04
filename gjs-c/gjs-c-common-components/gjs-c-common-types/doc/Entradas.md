# Entradas

| Dato          | Valor                                                                    |
| ------------- | ------------------------------------------------------------------------ |
| Módulos       | 4                                                                        |
| Cabeceras     | `SEntrada.h`, `SEntradaExt.h`, `SListaEntradas.h`, `SListaEntradasExt.h` |
| Prefijos      | `SEtr`, `SEtx`, `SLisEtr`, `SLisEtx`                                     |
| Funciones     | 17 + 21 + 15 + 14                                                        |
| Incluidos por | Sólo las dos listas — **ver Observaciones**                              |
| Tests         | Uno por módulo                                                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **entrada** asocia un nombre con su definición: es la pareja de un
diccionario, un glosario o una tabla de símbolos.

```c
typedef struct
{
    char * p_cNombre;
    char * p_cDefinicion;
} SEntrada;
```

La variante `Ext` admite **varias definiciones** para el mismo nombre, con una
marcada como principal — igual que
[SLocalizadorExt](Localizacion.md) hace con las posiciones.

## `SEntrada`

| Grupo               | Funciones                                                                                   |
| ------------------- | ------------------------------------------------------------------------------------------- |
| Ciclo de vida       | `SEtrCrearDef`, `SEtrCrear`, `SEtrCrearExt`, `SEtrDestruir`, `SEtrDuplicar`, `SEtrEsValido` |
| Acceso              | `SEtrNombre`, `SEtrDefinicion`                                                              |
| Asignación          | `SEtrEstablecer`, `SEtrEstablecerNombre`, `SEtrEstablecerDefinicion`                        |
| Comparación         | `SEtrEsIgual`, `SEtrEsMenor`, `SEtrEsMayor`                                                 |
| Comparación literal | `SEtrEsIgualLit`, `SEtrEsMenorLit`, `SEtrEsMayorLit`                                        |

La comparación es **por nombre**, lo que permite mantener listas ordenadas y
buscar por clave.

## `SEntradaExt`

Añade sobre la anterior:

| Función                                     | Descripción                 |
| ------------------------------------------- | --------------------------- |
| `int SEtxNumDefiniciones ( SEntradaExt * )` | Cuántas definiciones tiene. |
| `SEtxDefinicion ( …, int )`                 | Definición por índice.      |
| `SEtxDefinicionPrinc ( … )`                 | La definición principal.    |
| `SEtxEstablecerDefinicionPrinc ( … )`       | Fija la principal.          |
| `SEtxInsertarDefinicion ( … )`              | Añade otra definición.      |

## Las listas

`SListaEntradas` (15 funciones) y `SListaEntradasExt` (14) siguen el patrón de
lista con búsqueda por clave:

| Grupo         | Funciones                                 |
| ------------- | ----------------------------------------- |
| Ciclo de vida | `Crear`, `Destruir`, `EsValida`, `Vaciar` |
| Consulta      | `NumElementos`, `EstaVacia`, `Elemento`   |
| Atajos        | `NombreElemento`, `DefinicionElemento`    |
| Inserción     | `Insertar`, `InsertarExt`                 |
| Eliminación   | `Eliminar`, `EliminarElem`                |
| Búsqueda      | `Buscar`, `Existe`                        |

`SLisEtrNombreElemento` y `SLisEtrDefinicionElemento` evitan tener que sacar la
`SEntrada` para leer sus dos campos, igual que hace
[SListaErrores](Errores.md).

## Dependencias

- [Cadenas](../../gjs-c-common-text/doc/Cadenas.md) — nombres y definiciones.
- [Listas](../../gjs-c-common-base-types/doc/Listas.md) — el almacenamiento.

## Tests

`SEntradaTest.c`, `SEntradaExtTest.c`, `SListaEntradasTest.c`,
`SListaEntradasExtTest.c`.

## Observaciones

> **La fachada expone las listas pero no su tipo de elemento.**
> `TiposDatos.h` incluye `SListaEntradas.h` y `SListaEntradasExt.h`, pero **no**
> `SEntrada.h` ni `SEntradaExt.h`. Un consumidor que sólo incluya la fachada
> puede crear la lista y contar sus elementos, pero no declarar una variable
> `SEntrada *` para recoger lo que devuelve `SLisEtrElemento`.
>
> Basta con incluir `SEntrada.h` a mano, pero la omisión no parece intencionada:
> son los dos únicos módulos del componente que quedan fuera, y sus listas sí
> están dentro.

- **La entrada guarda `char *`, no [SCadena](../../gjs-c-common-text/doc/SCadena.md)**,
  a diferencia de [Entidades](Entidades.md), que sí usa el objeto cadena. Las dos
  representaciones de texto conviven en el mismo componente.
- No hay variantes `Lit` en los asignadores (`SEtrEstablecerNombre` recibe un
  único tipo), pero sí en las comparaciones (`SEtrEsIgualLit`). La asimetría
  obliga a mirar cada firma.
- `SEntradaExt` no ofrece forma de **eliminar** una definición concreta: se
  pueden insertar y leer, pero sólo se limpian todas destruyendo la entrada.
- Las listas no tienen cursor, a diferencia de
  [SListaParametros](Parametros.md), que sí lo tiene con sus 30 funciones.
