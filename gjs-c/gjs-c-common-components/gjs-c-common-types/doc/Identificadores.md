# Identificadores adaptables

| Dato          | Valor                                                          |
| ------------- | -------------------------------------------------------------- |
| Módulos       | 3                                                              |
| Cabeceras     | `SIdAdap.h`, `SGeneradorIdAdap.h`, `SSecuenciaGeneradoresId.h` |
| Prefijos      | `SIdAdp`, `SGenIdAdp`, `SSecGenId`                             |
| Funciones     | 25 + 12 + 9                                                    |
| Incluidos por | `TiposDatos.h`                                                 |
| Tests         | Uno por módulo                                                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Identificadores **con formato**, frente a los puramente numéricos de
[SId](../../gjs-c-common-base-types/doc/Identificadores.md) en `base-types`.

Un `SIdAdap` no es un número: es un valor que sigue un **patrón** —de los de
[Patrones](../../gjs-c-common-text/doc/Patrones.md)— y que sabe incrementarse
respetándolo. Eso permite generar referencias del tipo `FRA-2026-0001` o
matrículas, no sólo contadores.

```c
typedef struct
{
    char * p_cPatron;
    char * p_cValor;
    int    iTam;
} SIdAdap;
```

## `SIdAdap`

| Grupo          | Funciones                                                                                         |
| -------------- | ------------------------------------------------------------------------------------------------- |
| Ciclo de vida  | `SIdAdpCrear`, `SIdAdpCrearExt`, `SIdAdpDestruir`, `SIdAdpDuplicar`, `SIdAdpEsValido`             |
| Acceso         | `SIdAdpPatron`, `SIdAdpValor`, `SIdAdpTam`                                                        |
| Asignación     | `SIdAdpEstablecer`, `SIdAdpAsignar`, `SIdAdpEstablecerValorInicial`, `SIdAdpEstablecerValorFinal` |
| Recorrido      | `SIdAdpIncrementar`, `SIdAdpDecrementar`, `SIdAdpIncrementarDesde`, `SIdAdpDecrementarDesde`      |
| Comparación    | `SIdAdpEsIgual`, `SIdAdpEsMenor`, `SIdAdpEsMayor`, `SIdAdpEsMenorIg`, `SIdAdpEsMayorIg`           |
| Rango          | `SIdAdpEstaEnRango`, `SIdAdpEstaEnRangoIg`                                                        |
| Compatibilidad | `SIdAdpEsCompatible`, `SIdAdpEsCompatibleValor`                                                   |

`SIdAdpEsCompatible` comprueba que dos identificadores compartan patrón, y
`SIdAdpEsCompatibleValor` que un texto encaje en el patrón de uno.

El incremento delega en `PatIncrementarValor` de
[Patrones](../../gjs-c-common-text/doc/Patrones.md), con la misma mecánica de
acarreo posición a posición.

## `SGeneradorIdAdap`

El que reparte identificadores dentro de un rango:

| Función                                                   | Descripción                             |
| --------------------------------------------------------- | --------------------------------------- |
| `SGeneradorIdAdap * SGenIdAdpCrear ( … )`                 | Generador con patrón.                   |
| `SGeneradorIdAdap * SGenIdAdpCrearExt ( … )`              | Ídem con límites.                       |
| `void SGenIdAdpDestruir ( … )`                            | Destruye y anula el puntero.            |
| `int SGenIdAdpEsValido ( … )`                             | 1 si es utilizable.                     |
| `SGenIdAdpPatron`                                         | Patrón del generador.                   |
| `SGenIdAdpInicial` / `SGenIdAdpFinal` / `SGenIdAdpUltimo` | Extremos y último entregado.            |
| `SGenIdAdpAsignarSig`                                     | **Entrega** el siguiente identificador. |
| `SGenIdAdpEstablecerUltimo`                               | Fija el último entregado.               |
| `SGenIdAdpIniciar`                                        | Reinicia la cuenta.                     |
| `SGenIdAdpEsCompatibleValor`                              | 1 si un valor encaja en el patrón.      |

Es el equivalente de
[SGeneradorId](../../gjs-c-common-base-types/doc/Identificadores.md) para
identificadores con formato. `SGenIdAdpEstablecerUltimo` permite reconstruir el
estado tras persistirlo.

## `SSecuenciaGeneradoresId`

Nueve funciones para guardar varios generadores a la vez: una aplicación que
numere facturas, albaranes y pedidos por separado necesita un generador por
serie, y esta secuencia los agrupa.

## Dependencias

- [Patrones](../../gjs-c-common-text/doc/Patrones.md) — el formato y el
  incremento.
- [Secuencias](../../gjs-c-common-base-types/doc/Secuencias.md) — el
  almacenamiento de `SSecuenciaGeneradoresId`.

## Tests

`SIdAdapTest.c`, `SGeneradorIdAdapTest.c`, `SSecuenciaGeneradoresIdTest.c`.

## Observaciones

- **`SGeneradorIdAdap` no tiene el `Sig` de sólo consulta.** Su hermano
  [SGeneradorId](../../gjs-c-common-base-types/doc/Identificadores.md) ofrece
  `SGenIdSig` (mira sin gastar) y `SGenIdAsignarSig` (entrega); aquí sólo está el
  segundo, así que no se puede saber cuál sería el siguiente sin consumirlo.
- **Tampoco tiene `Duplicar`**, que `SIdAdap` sí ofrece y que
  `SGeneradorId` también.
- El patrón se guarda como `char *` y la cabecera no dice si el objeto lo copia o
  se queda con el puntero. Dado que `SIdAdpPatron` lo devuelve, conviene no
  liberar el patrón original mientras el identificador viva.
- `SGenIdAdpAsignarSig` no indica en su tipo de retorno qué pasa **al agotar el
  rango**, el mismo problema que su equivalente numérico. Conviene comparar
  contra `SGenIdAdpFinal`.
- Ninguno de los tres módulos hereda del `SIdAdap` la validación de que el valor
  inicial y el final compartan patrón; `SIdAdpEsCompatible` existe pero hay que
  llamarlo a mano.
