# Contenedores de reales dobles

| Dato          | Valor                                                                                                                      |
| ------------- | -------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 5                                                                                                                          |
| Cabeceras     | `SListaRealesDobles.h`, `SVectorRealesDobles.h`, `SSecuenciaRealesDobles.h`, `STablaRealesDobles.h`, `SPilaRealesDobles.h` |
| Prefijos      | `SLisReald`, `SVecReald`, `SSecReald`, `STabReald`, `SPilReald`                                                            |
| Funciones     | 28 + 8 + 10 + 10 + 10                                                                                                      |
| Incluidos por | `Calculo.h`                                                                                                                |
| Tests         | Uno por módulo                                                                                                             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Especializaciones en `double` de los contenedores de
[gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md). Cada
uno envuelve su contenedor genérico y expone una API que trabaja con reales
dobles por valor, sin que el llamante vea `SElemento` ni `SContenido`.

| Módulo                   | Envuelve       | Equivalente genérico                                          |
| ------------------------ | -------------- | ------------------------------------------------------------- |
| `SListaRealesDobles`     | `SLista *`     | [Listas](../../gjs-c-common-base-types/doc/Listas.md)         |
| `SVectorRealesDobles`    | `SVector *`    | [Vectores](../../gjs-c-common-base-types/doc/Vectores.md)     |
| `SSecuenciaRealesDobles` | `SSecuencia *` | [Secuencias](../../gjs-c-common-base-types/doc/Secuencias.md) |
| `STablaRealesDobles`     | `STabla *`     | [Tablas](../../gjs-c-common-base-types/doc/Tablas.md)         |
| `SPilaRealesDobles`      | `SPila *`      | [Pilas](../../gjs-c-common-base-types/doc/Pilas.md)           |

Son a `double` lo que `SListaEnteros` y compañía son a `int`, pero viven en este
módulo en lugar de en `base-types`.

## Las cinco APIs

### `SListaRealesDobles` (28 funciones)

La más completa: replica la [lista genérica](../../gjs-c-common-base-types/doc/Listas.md)
con cursor.

| Grupo         | Funciones                                                                                                                           |
| ------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| Ciclo de vida | `Crear`, `Destruir`, `EsValida`, `Vaciar`                                                                                           |
| Consulta      | `NumElementos`, `EstaVacia`, `Elemento`, `Existe`, `Buscar`                                                                         |
| Por índice    | `InsertarElem`, `InsertarAlInicio`, `InsertarAlFinal`, `EliminarElem`                                                               |
| Cursor        | `Posicion`, `Actual`, `Inicio`, `Final`, `Siguiente`, `Anterior`, `MoverA`, `Deposicionar`, `EsNulo`, `EstaEnInicio`, `EstaEnFinal` |
| Por cursor    | `Insertar`, `InsertarDelante`, `InsertarDetras`, `Eliminar`                                                                         |

### `SVectorRealesDobles` (8 funciones)

`Crear`, `Destruir`, `EsValido`, `NumElementos`, `Elemento`, `Asignar`,
`Inicializar`, `Existe`.

### `SSecuenciaRealesDobles` (10 funciones)

`Crear`, `Destruir`, `EsValida`, `NumElementos`, `Elemento`, `Insertar`,
`Modificar`, `Eliminar`, `Vaciar`, `Existe`.

### `STablaRealesDobles` (10 funciones)

`Crear`, `Destruir`, `EsValida`, `NumFilas`, `NumColumnas`, `NumElementos`,
`Elemento`, `Asignar`, `Inicializar`, `Existe`.

### `SPilaRealesDobles` (10 funciones)

`Crear`, `Destruir`, `EsValida`, `NumElementos`, `EstaVacia`, `Apilar`,
`Desapilar`, `Primero`, `EliminarPrimero`, `Vaciar`.

```c
SListaRealesDobles * p_lisObj = SLisRealdCrear ();

SLisRealdInsertarAlFinal ( p_lisObj, 3.14159 );
SLisRealdInsertarAlFinal ( p_lisObj, 2.71828 );

if ( SLisRealdExiste ( p_lisObj, 3.14159 ) == 1 )
{
    double dVal = SLisRealdElemento ( p_lisObj, 0 );
}
SLisRealdDestruir ( &p_lisObj );
```

## Dependencias

- Los contenedores genéricos de
  [gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md).
- [CalculoOperaciones](CalculoOperaciones.md) para la comparación de reales.

## Tests

`SListaRealesDoblesTest.c`, `SVectorRealesDoblesTest.c`,
`SSecuenciaRealesDoblesTest.c`, `STablaRealesDoblesTest.c`,
`SPilaRealesDoblesTest.c`.

## Observaciones

- **Deberían estar en `gjs-c-common-base-types`**, junto a las especializaciones
  de `int` y de cadenas. Están aquí porque el módulo de cálculo es quien las
  necesita, pero eso significa que un consumidor que quiera una lista de
  `double` tiene que depender de toda la librería de cálculo.
- **`Existe` compara reales.** La cabecera no dice si usa `==` o la tolerancia de
  [CalculoOperaciones](CalculoOperaciones.md); es la diferencia entre que
  funcione o no con valores calculados. Conviene comprobarlo en la
  implementación antes de confiar en `Existe` o `Buscar`.
- **No hay variante `Ptr` ni de `float`**, sólo `double` por valor.
- `SVectorRealesDobles` y `STablaRealesDobles` tienen `Inicializar` en lugar de
  `Limpiar`, igual que sus equivalentes de enteros, mientras que la lista, la
  secuencia y la pila usan `Vaciar`. Es la misma asimetría que arrastran los
  contenedores genéricos.
- La lista es la única con búsqueda posicional (`Buscar`); las demás sólo tienen
  `Existe`, que responde sí o no.
