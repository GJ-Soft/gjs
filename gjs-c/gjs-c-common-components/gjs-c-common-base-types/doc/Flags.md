# Flags

| Dato          | Valor                                      |
| ------------- | ------------------------------------------ |
| Módulos       | 2                                          |
| Cabeceras     | `SVectorFlags.h`, `SMatrizFlags.h`         |
| Prefijos      | `SVecFlg`, `SMatFlg`                       |
| Structs       | `SVectorFlags`, `SMatrizFlags`             |
| Incluidos por | `Tipos.h`                                  |
| Tests         | `SVectorFlagsTest.c`, `SMatrizFlagsTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Conjuntos de **bits** direccionables individualmente, en una o dos dimensiones.
Sirven para llevar marcas —visitado, ocupado, modificado— sobre colecciones
grandes sin gastar un byte o un entero por marca.

Aunque el nombre `SVectorFlags` sugiere parentesco con
[SVector](Vectores.md), no comparten nada: aquí no hay array de punteros, sino un
[SBuffer](SBuffer.md) tratado como mapa de bits.

## Modelo de datos

```c
typedef struct
{
    SBuffer * p_bufContenido;
} SVectorFlags;

typedef struct
{
    SBuffer *      p_bufContenido;
    unsigned long  ulNumFilas;
    unsigned long  ulNumColumnas;
} SMatrizFlags;
```

La matriz es el mismo búfer con las dos dimensiones guardadas para poder
convertir (fila, columna) en posición de bit.

## API de `SVectorFlags`

| Función                                                             | Descripción                              |
| ------------------------------------------------------------------- | ---------------------------------------- |
| `SVectorFlags * SVecFlgCrear ( unsigned long ulNumFlags )`          | Vector con el número de marcas indicado. |
| `SVectorFlags * SVecFlgEncapsular ( SBuffer * )`                    | Envuelve un búfer ya existente.          |
| `void SVecFlgDestruir ( SVectorFlags ** )`                          | Destruye y anula el puntero.             |
| `int SVecFlgEsValido ( SVectorFlags * )`                            | 1 si es utilizable.                      |
| `unsigned long SVecFlgNumFlags ( SVectorFlags * )`                  | Número de marcas.                        |
| `int SVecFlgFlag ( SVectorFlags *, unsigned long ulPos )`           | Valor de la marca.                       |
| `int SVecFlgFlagEstaActivo ( SVectorFlags *, unsigned long ulPos )` | 1 si está activa.                        |
| `int SVecFlgActivarFlag ( SVectorFlags *, unsigned long ulPos )`    | Pone la marca a 1.                       |
| `int SVecFlgDesactivarFlag ( SVectorFlags *, unsigned long ulPos )` | Pone la marca a 0.                       |
| `int SVecFlgLimpiar ( SVectorFlags * )`                             | Desactiva todas.                         |

## API de `SMatrizFlags`

La misma, con coordenadas de dos dimensiones:

| Función                                                                                  | Descripción                  |
| ---------------------------------------------------------------------------------------- | ---------------------------- |
| `SMatrizFlags * SMatFlgCrear ( unsigned long ulNumFilas, unsigned long ulNumColumnas )`  | Matriz de marcas.            |
| `void SMatFlgDestruir ( SMatrizFlags ** )`                                               | Destruye y anula el puntero. |
| `int SMatFlgEsValida ( SMatrizFlags * )`                                                 | 1 si es utilizable.          |
| `unsigned long SMatFlgNumFilas ( SMatrizFlags * )`                                       | Número de filas.             |
| `unsigned long SMatFlgNumColumnas ( SMatrizFlags * )`                                    | Número de columnas.          |
| `int SMatFlgFlag ( SMatrizFlags *, unsigned long ulFil, unsigned long ulCol )`           | Valor de la marca.           |
| `int SMatFlgFlagEstaActivo ( SMatrizFlags *, unsigned long ulFil, unsigned long ulCol )` | 1 si está activa.            |
| `int SMatFlgActivarFlag ( SMatrizFlags *, unsigned long ulFil, unsigned long ulCol )`    | Pone la marca a 1.           |
| `int SMatFlgDesactivarFlag ( SMatrizFlags *, unsigned long ulFil, unsigned long ulCol )` | Pone la marca a 0.           |
| `int SMatFlgLimpiar ( SMatrizFlags * )`                                                  | Desactiva todas.             |

## Comportamiento

Ambos dimensionan con `unsigned long`, igual que el [SBuffer](SBuffer.md) que
tienen debajo y a diferencia del resto de la librería, que usa `int`.

`SVecFlgEncapsular` permite montar un vector de marcas sobre un búfer que ya
existe, por ejemplo uno leído de fichero. `SMatrizFlags` no tiene equivalente:
sólo se puede crear desde cero.

Ejemplo:

```c
SVectorFlags * p_vecfObj = SVecFlgCrear ( 1000 );

SVecFlgActivarFlag ( p_vecfObj, 42 );
if ( SVecFlgFlagEstaActivo ( p_vecfObj, 42 ) == 1 )
{
    /* … */
}
SVecFlgDestruir ( &p_vecfObj );
```

## Dependencias

- [SBuffer](SBuffer.md) — el almacenamiento de los bits.

## Tests

`SVectorFlagsTest.c` → `TestSVectorFlags()`,
`SMatrizFlagsTest.c` → `TestSMatrizFlags()`.

## Observaciones

- **`SVecFlgFlag` y `SVecFlgFlagEstaActivo` parecen la misma función.** Ambas
  devuelven `int` y consultan una marca; la cabecera no aclara en qué se
  diferencian. Lo previsible es que `Flag` devuelva el valor del bit y
  `FlagEstaActivo` un booleano normalizado, pero al ser los dos `int` el
  llamante no puede distinguirlo sin mirar la implementación. Lo mismo en
  `SMatrizFlags`.
- Ninguna de las dos indica **cómo señalan un índice fuera de rango**: las
  funciones de consulta devuelven `int`, así que un fuera de rango se confunde
  con una marca desactivada. Conviene validar contra `SVecFlgNumFlags` antes de
  consultar.
- `SMatrizFlags` no tiene `Encapsular`, lo que impide reconstruir una matriz
  desde un búfer persistido, aunque el vector sí lo permite.
- El nombre `SVectorFlags` invita a pensar que pertenece a la familia
  [Vectores](Vectores.md); no comparte ni estructura ni API con ella. En el
  índice están separados por eso.
