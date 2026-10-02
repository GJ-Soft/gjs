# Intercambios

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/Intercambios.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Intercambios.c` |
| Prefijo      | `Intercambiar`                               |
| Incluido por | `Base.h`                                     |
| Test         | `IntercambiosTest.c` → `TestIntercambios()`  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Intercambiar el contenido de dos variables del mismo tipo. Es el clásico *swap*
con variable auxiliar, ofrecido como función tipada para los siete tipos
escalares que usa la librería, de modo que el llamante no tenga que escribirlo
(ni castear a `void *`) cada vez.

## API

| Función                                                                                             | Tipo intercambiado |
| --------------------------------------------------------------------------------------------------- | ------------------ |
| `void IntercambiarCaracteres ( char * p_cValorA, char * p_cValorB )`                                | `char`             |
| `void IntercambiarEnteros ( int * p_iValorA, int * p_iValorB )`                                     | `int`              |
| `void IntercambiarEnterosLargos ( long * p_lValorA, long * p_lValorB )`                             | `long`             |
| `void IntercambiarEnterosSinSigno ( unsigned int * p_uiValorA, unsigned int * p_uiValorB )`         | `unsigned int`     |
| `void IntercambiarEnterosLargosSinSigno ( unsigned long * p_ulValorA, unsigned long * p_ulValorB )` | `unsigned long`    |
| `void IntercambiarReales ( float * p_fValorA, float * p_fValorB )`                                  | `float`            |
| `void IntercambiarRealesDobles ( double * p_dValorA, double * p_dValorB )`                          | `double`           |

## Comportamiento

Todas siguen exactamente el mismo esquema: si **ambos** punteros son válidos
(`ES_VALIDO`), intercambian los valores usando una variable auxiliar local; si
alguno no lo es, no hacen nada.

No devuelven nada y **no anotan error** en el subsistema de
[Errores](Errores.md): un intercambio sobre un puntero nulo es silenciosamente un
no-op. Si el llamante necesita saber si se hizo, debe validar antes.

Pasar dos veces el mismo puntero es inocuo: el valor queda como estaba.

## Dependencias

- [Memoria](Memoria.md) — únicamente por el macro `ES_VALIDO`.

La cabecera no incluye nada; el `.c` incluye `Intercambios.h` y `Memoria.h`.

## Test

`IntercambiosTest.c` cubre las siete funciones.

## Observaciones

- La cabecera `Intercambios.h` no incluye `BaseConfig.h` ni ninguna otra. No hace
  falta porque sólo declara tipos nativos de C, pero rompe el patrón del resto de
  módulos, en los que la cabecera es autosuficiente.
- No hay variantes para `long long`/`unsigned long long`, `byte`, `word` ni
  `dword`, aunque la librería trabaja con esos tipos.
- Silenciar el caso de puntero nulo es coherente con la ausencia de valor de
  retorno, pero significa que un error de programación pasa inadvertido.
