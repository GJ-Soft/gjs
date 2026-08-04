# Tablas

| Dato          | Valor                                                             |
| ------------- | ----------------------------------------------------------------- |
| Módulos       | 4                                                                 |
| Cabeceras     | `STabla.h`, `STablaPtr.h`, `STablaEnteros.h`, `STablaLiterales.h` |
| Prefijos      | `STab`, `STabp`, `STabEnt`, `STabLit`                             |
| Incluidos por | `Tipos.h`                                                         |
| Tests         | Uno por módulo                                                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

[Vectores](Vectores.md) de dos dimensiones: una rejilla de filas por columnas,
de tamaño fijo, con acceso directo por coordenadas.

La implementación es literalmente un vector con las dimensiones guardadas al
lado; la tabla se encarga de traducir (fila, columna) en índice lineal.

## Modelo de datos

```c
typedef struct
{
    SVector * p_vecElementos;
    int       iNumFilas;
    int       iNumColumnas;
} STabla;
```

## API de `STabla`

| Función                                                               | Descripción                         |
| --------------------------------------------------------------------- | ----------------------------------- |
| `STabla * STabCrear ( int iNumFilas, int iNumColumnas )`              | Tabla del tamaño dado.              |
| `void STabDestruir ( STabla ** )`                                     | Destruye la tabla y su contenido.   |
| `int STabEsValida ( STabla * )`                                       | 1 si es utilizable.                 |
| `int STabNumFilas ( STabla * )`                                       | Número de filas.                    |
| `int STabNumColumnas ( STabla * )`                                    | Número de columnas.                 |
| `int STabNumElementos ( STabla * )`                                   | Total de celdas (filas × columnas). |
| `SContenido * STabElemento ( STabla *, int iFila, int iColumna )`     | Contenido de la celda.              |
| `int STabAsignar ( STabla *, int iFila, int iColumna, SContenido * )` | Coloca un contenido.                |
| `int STabLimpiarElemento ( STabla *, int iFila, int iColumna )`       | Vacía una celda.                    |
| `int STabLimpiar ( STabla * )`                                        | Vacía todas.                        |
| `SVector * STabVector ( STabla * )`                                   | **Expone el vector interno.**       |

## Las variantes

| Módulo            | Se apoya en            | Almacena                    | Dueño del dato | Añade                   |
| ----------------- | ---------------------- | --------------------------- | -------------- | ----------------------- |
| `STabla`          | [SVector](Vectores.md) | [SContenido](SContenido.md) | La tabla       | `STabVector`            |
| `STablaPtr`       | `SVectorPtr`           | `byte *`                    | Configurable   | Control de liberación   |
| `STablaEnteros`   | `STabla`               | `int` por valor             | La tabla       | `Inicializar`, `Existe` |
| `STablaLiterales` | `STablaPtr`            | `char *`                    | Configurable   | `AsignarDup`, `Existe`  |

La correspondencia con [Vectores](Vectores.md) es exacta: cada variante de tabla
envuelve la variante equivalente de vector, y hereda de ella la política de
memoria.

### `STablaEnteros`

```c
STablaEnteros * p_tabObj = STabEntCrear ( 3, 4 );

STabEntInicializar ( p_tabObj );
STabEntAsignar ( p_tabObj, 1, 2, 42 );
int iVal = STabEntElemento ( p_tabObj, 1, 2 );
STabEntDestruir ( &p_tabObj );
```

Como en `SVectorEnteros`, no tiene `LimpiarElemento` ni `Limpiar`: se reinicia
entera con `STabEntInicializar`.

### `STablaLiterales`

Misma doble forma de asignación que el resto de variantes de literales:

| Función             | Parámetro      | Qué hace con la cadena                          |
| ------------------- | -------------- | ----------------------------------------------- |
| `STabLitAsignar`    | `char *`       | Guarda el puntero; la tabla se hace responsable |
| `STabLitAsignarDup` | `const char *` | **Duplica** la cadena                           |

Más `STabLitExiste ( …, const char * )` y las tres funciones de liberación.

## Comportamiento

El tamaño es fijo desde la creación: no hay forma de redimensionar una tabla.

`STabNumElementos` devuelve el total de celdas, no las ocupadas.

`STabVector` y `STabpVector` exponen el vector subyacente, con el mismo aviso
que en [Secuencias](Secuencias.md): permiten dejar la tabla en un estado que su
propia API no produciría.

## Dependencias

- [Vectores](Vectores.md) — todo el almacenamiento.
- [SContenido](SContenido.md) — el contenido de la variante base.

## Tests

`STablaTest.c`, `STablaPtrTest.c`, `STablaEnterosTest.c`,
`STablaLiteralesTest.c`.

## Observaciones

- Ni la cabecera ni los nombres aclaran **si los índices empiezan en 0 o en 1**.
  Por coherencia con [Vectores](Vectores.md) lo esperable es 0, pero conviene
  confirmarlo en el test antes de escribir código nuevo.
- Como en los vectores, `STabElemento` devuelve `NULL` tanto para celda vacía
  como para coordenadas fuera de rango, sin forma de distinguirlos.
- No hay variante `EnterosLargos` ni acceso por filas o columnas completas: para
  recorrer una fila hay que iterar celda a celda.
