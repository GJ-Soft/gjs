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
de comparaciones**: 24 funciones para lo que en el fondo es comparar dos
enteros.

### Ciclo de vida

| Función                                      | Descripción                                       |
| -------------------------------------------- | ------------------------------------------------- |
| `SId * SIdCrearDef ()`                       | Crea un identificador con valor 0.                |
| `SId * SIdCrear ( unsigned long )`           | Crea un identificador con el valor dado.          |
| `void SIdDestruir ( SId ** )`                | Destruye y anula el puntero.                      |
| `int SIdEsValido ( SId * )`                  | 1 si el puntero es utilizable **y** su valor > 0. |
| `unsigned long SIdValor ( SId * )`           | Valor numérico.                                   |
| `int SIdEstablecer ( SId *, unsigned long )` | Fija el valor.                                    |
| `int SIdAsignar ( SId *, SId * )`            | Copia el valor de otro identificador.             |
| `unsigned int SIdHash ( SId * )`             | Hash del identificador.                           |

`SIdCrear` es el constructor con valor; `SIdCrearDef` el de por defecto, que deja
el identificador a 0. Ojo con la asimetría que eso crea: un identificador recién
creado con `SIdCrearDef` **no** pasa `SIdEsValido`, porque esa función no
comprueba el puntero sino que el identificador esté *asignado*, es decir que su
valor sea mayor que 0.

### Comparación

Cada operación viene en dos formas: contra otro `SId *` y contra un
`unsigned long` suelto (sufijo `Num`).

| Operación                    | Contra `SId *`     | Contra `unsigned long` |
| ---------------------------- | ------------------ | ---------------------- |
| Igual                        | `SIdEsIgual`       | `SIdEsIgualNum`        |
| Menor                        | `SIdEsMenor`       | `SIdEsMenorNum`        |
| Mayor                        | `SIdEsMayor`       | `SIdEsMayorNum`        |
| Menor o igual                | `SIdEsMenorIg`     | `SIdEsMenorIgNum`      |
| Mayor o igual                | `SIdEsMayorIg`     | `SIdEsMayorIgNum`      |
| En rango                     | `SIdEstaEnRango`   | `SIdEstaEnRangoNum`    |
| En rango, extremos incluidos | `SIdEstaEnRangoIg` | `SIdEstaEnRangoIgNum`  |
| Comparación de tres vías     | `SIdComparar`      | `SIdCompararNum`       |

Las siete primeras devuelven 1 o 0. La distinción entre `EstaEnRango` y
`EstaEnRangoIg` es la de intervalo abierto frente a cerrado.

`SIdComparar` y `SIdCompararNum` son distintas: devuelven una de las constantes
`COMP_*` de `ConstantesBase.h`, así que sirven para ordenar y no sólo para
preguntar. Cuando un puntero no supera `ES_VALIDO`, ese operando ordena antes:

| Caso                                | `SIdComparar` | `SIdCompararNum` |
| ----------------------------------- | ------------- | ---------------- |
| Los dos punteros válidos            | según valor   | según valor      |
| Sólo el del objeto es válido        | `COMP_MAYOR`  | —                |
| Sólo el del otro operando es válido | `COMP_MENOR`  | —                |
| El del objeto no es válido          | —             | `COMP_MENOR`     |
| Ninguno de los dos es válido        | `COMP_IGUAL`  | —                |

Todas las comparaciones, sin excepción, validan sus operandos con `ES_VALIDO` y
no con `SIdEsValido`: sólo miran el valor del puntero, así que un identificador
a 0 se compara como cualquier otro.

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
- **`SIdEsValido` ya no se usa dentro del módulo**: desde que las comparaciones
  pasaron a `ES_VALIDO`, la función se declara y se define pero no la llama
  ninguna otra de `SId.c`. Sigue siendo útil para el llamante —es la única forma
  de preguntar si un identificador está *asignado*—, pero conviene tenerlo
  presente: «válido» significa cosas distintas dentro y fuera del módulo.
- **La API añadida no tiene tests**: `SIdTest.c` cubre `SIdCrearDef`,
  `SIdEstablecer`, las comparaciones y el hash, pero no `SIdCrear ( ulValor )`,
  `SIdAsignar`, `SIdComparar` ni `SIdCompararNum`.
- **`SId` no tiene `Duplicar`** aunque `SGeneradorId` sí, y aunque casi todos los
  objetos de la librería lo ofrecen. `SIdAsignar` cubre el caso parecido de
  copiar el valor sobre un identificador que ya existe, pero no crea uno nuevo.
- Ni `SGenIdSig` ni `SGenIdAsignarSig` indican en su tipo de retorno qué ocurre
  cuando **se agota el rango**. Al devolver `unsigned long`, cualquier valor
  centinela sería un identificador legítimo. Conviene comparar el resultado con
  `SGenIdFinal` antes de darlo por bueno.
