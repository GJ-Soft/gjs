# Identificadores

| Dato          | Valor                             |
| ------------- | --------------------------------- |
| Módulos       | 2                                 |
| Cabeceras     | `SId.h`, `SGeneradorId.h`         |
| Prefijos      | `SId`, `SGenId`                   |
| Structs       | `SId`, `SGeneradorId`             |
| Incluidos por | `Tipos.h`                         |
| Tests         | `SIdTest.c`, `SGeneradorIdTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Identificadores numéricos únicos y quien los reparte. `SId` da identidad a un
objeto; `SGeneradorId` produce identificadores nuevos dentro de un rango sin
repetirlos.

## `SId`

```c
typedef struct
{
    unsigned long ulValor;
} SId;
```

Un `unsigned long` envuelto. Lo que aporta el módulo es una **batería completa
de comparaciones**: 20 funciones para lo que en el fondo es comparar dos
enteros.

### Ciclo de vida

| Función                                      | Descripción                  |
| -------------------------------------------- | ---------------------------- |
| `SId * SIdCrear ()`                          | Crea un identificador.       |
| `void SIdDestruir ( SId ** )`                | Destruye y anula el puntero. |
| `int SIdEsValido ( SId * )`                  | 1 si es utilizable.          |
| `unsigned long SIdValor ( SId * )`           | Valor numérico.              |
| `int SIdEstablecer ( SId *, unsigned long )` | Fija el valor.               |
| `unsigned int SIdHash ( SId * )`             | Hash del identificador.      |

### Comparación

Cada operación viene en dos formas: contra otro `SId *` y contra un
`unsigned long` suelto (sufijo `Ent`).

| Operación                    | Contra `SId *`     | Contra `unsigned long` |
| ---------------------------- | ------------------ | ---------------------- |
| Igual                        | `SIdEsIgual`       | `SIdEsIgualEnt`        |
| Menor                        | `SIdEsMenor`       | `SIdEsMenorEnt`        |
| Mayor                        | `SIdEsMayor`       | `SIdEsMayorEnt`        |
| Menor o igual                | `SIdEsMenorIg`     | `SIdEsMenorIgEnt`      |
| Mayor o igual                | `SIdEsMayorIg`     | `SIdEsMayorIgEnt`      |
| En rango                     | `SIdEstaEnRango`   | `SIdEstaEnRangoEnt`    |
| En rango, extremos incluidos | `SIdEstaEnRangoIg` | `SIdEstaEnRangoIgEnt`  |

La distinción entre `EstaEnRango` y `EstaEnRangoIg` es la de intervalo abierto
frente a cerrado.

## `SGeneradorId`

```c
typedef struct
{
    unsigned long ulIdInicial;
    unsigned long ulIdFinal;
    unsigned long ulUltimoId;
}  SGeneradorId;
```

| Función                                                                                                       | Descripción                                 |
| ------------------------------------------------------------------------------------------------------------- | ------------------------------------------- |
| `SGeneradorId * SGenIdCrear ( unsigned long ulIdInicial, unsigned long ulUltimoId, unsigned long ulIdFinal )` | Generador acotado, con el último entregado. |
| `SGeneradorId * SGenIdCrearDef ()`                                                                            | Generador con los límites por defecto.      |
| `void SGenIdDestruir ( SGeneradorId ** )`                                                                     | Destruye y anula el puntero.                |
| `int SGenIdEsValido ( SGeneradorId * )`                                                                       | 1 si es utilizable.                         |
| `unsigned long SGenIdInicial ( SGeneradorId * )`                                                              | Primer identificador del rango.             |
| `unsigned long SGenIdFinal ( SGeneradorId * )`                                                                | Último identificador del rango.             |
| `unsigned long SGenIdUltimo ( SGeneradorId * )`                                                               | Último entregado.                           |
| `unsigned long SGenIdSig ( SGeneradorId * )`                                                                  | **Consulta** el siguiente, sin gastarlo.    |
| `unsigned long SGenIdAsignarSig ( SGeneradorId * )`                                                           | **Entrega** el siguiente y avanza.          |
| `int SGenIdIniciar ( SGeneradorId * )`                                                                        | Reinicia la cuenta.                         |
| `int SGenIdEsIgual ( SGeneradorId *, SGeneradorId * )`                                                        | Compara dos generadores.                    |
| `SGeneradorId * SGenIdDuplicar ( SGeneradorId * )`                                                            | Copia del generador.                        |

La pareja `SGenIdSig` / `SGenIdAsignarSig` es la distinción que importa: la
primera es una consulta sin efectos, la segunda consume el identificador.

El estado que se guarda es **el último entregado**, así que un generador se
puede persistir y reconstruir con `SGenIdCrear` pasándole ese valor, que es para
lo que sirve el tercer parámetro del constructor.

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Tests

`SIdTest.c` → `TestSId()`, `SGeneradorIdTest.c` → `TestSGeneradorId()`.

## Observaciones

- **El orden de los parámetros de `SGenIdCrear` es confuso**:
  `( ulIdInicial, ulUltimoId, ulIdFinal )`. El "último entregado" va en medio,
  entre los dos extremos del rango, cuando lo natural sería
  `( inicial, final, ultimo )`. Es fácil pasarlos cambiados, y como los tres son
  `unsigned long` el compilador no avisa.
- **`SId` no tiene `Duplicar`** aunque `SGeneradorId` sí, y aunque casi todos los
  objetos de la librería lo ofrecen.
- `SIdCrear` no recibe valor inicial: hay que crear y después `SIdEstablecer`.
  No hay constructor que haga las dos cosas.
- Ni `SGenIdSig` ni `SGenIdAsignarSig` indican en su tipo de retorno qué ocurre
  cuando **se agota el rango**. Al devolver `unsigned long`, cualquier valor
  centinela sería un identificador legítimo. Conviene comparar el resultado con
  `SGenIdFinal` antes de darlo por bueno.
