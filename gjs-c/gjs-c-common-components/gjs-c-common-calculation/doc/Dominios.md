# Dominios reales

| Dato          | Valor                                                             |
| ------------- | ----------------------------------------------------------------- |
| Módulos       | 3 (uno implementado, **dos no**)                                  |
| Cabeceras     | `SExtremoDominioReal.h`, `SDominioSimpleReal.h`, `SDominioReal.h` |
| Prefijos      | `SExdR`, `SDomSimR`, `SDomR`                                      |
| Incluidos por | **Nadie** — los tres fuera de la fachada `Calculo.h`              |
| Tests         | Sólo `SExtremoDominioRealTest.c`                                  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Describir **el dominio de una función real**: qué subconjunto de la recta real
acepta. Se construye en tres niveles:

```
SDominioReal              unión de tramos disjuntos          ← sin implementar
  └── SDominioSimpleReal      un tramo [a, b], (a, b]…       ← sin implementar
        └── SExtremoDominioReal   un extremo del tramo       ← implementado
```

Es lo que daría sentido a
[SFuncionReal](SFuncionReal.md): saber dónde está definida una función y, por
tanto, si es invertible.

> **Sólo el nivel más bajo existe.** `SDominioSimpleReal` y `SDominioReal`
> declaran 22 y 14 funciones respectivamente y **no tienen fichero `.c`**:
> cualquier llamada compila pero falla al enlazar. Tampoco tienen test.

## `SExtremoDominioReal` — implementado

Un extremo de intervalo, que puede ser un valor finito (incluido o no) o el
infinito.

```c
typedef struct
{
    int    iIncluido;
    int    iInfinito;
    double dValor;
} SExtremoDominioReal;
```

| Función                                                             | Descripción                         |
| ------------------------------------------------------------------- | ----------------------------------- |
| `SExtremoDominioReal * SExdRCrear ( double dValor, int iIncluido )` | Extremo finito.                     |
| `SExtremoDominioReal * SExdRCrearInfinito ()`                       | +∞.                                 |
| `SExtremoDominioReal * SExdRCrearMenosInfinito ()`                  | −∞.                                 |
| `void SExdRDestruir ( SExtremoDominioReal ** )`                     | Destruye y anula el puntero.        |
| `int SExdREsValido ( SExtremoDominioReal * )`                       | 1 si es utilizable.                 |
| `double SExdRValor ( SExtremoDominioReal * )`                       | Valor numérico.                     |
| `int SExdREstaIncluido ( SExtremoDominioReal * )`                   | 1 si el extremo pertenece al tramo. |
| `int SExdREsInfinito ( SExtremoDominioReal * )`                     | 1 si es +∞.                         |
| `int SExdREsMenosInfinito ( SExtremoDominioReal * )`                | 1 si es −∞.                         |
| `SExtremoDominioReal * SExdRDuplicar ( SExtremoDominioReal * )`     | Copia.                              |

Es lo que distingue este nivel de un simple `double`: sabe si el extremo es
abierto o cerrado, algo que [SIntervalo](SIntervalo.md) no puede expresar.

## `SDominioSimpleReal` — declarado, no implementado

Un tramo delimitado por dos extremos.

```c
typedef struct
{
    SExtremoDominioReal * p_extA;
    SExtremoDominioReal * p_extB;
} SDominioSimpleReal;
```

Declara 22 funciones: seis constructores (`SDomSimRCrear`,
`SDomSimRCrearHastaInfinito`, `SDomSimRCrearDesdeMenosInfinito`,
`SDomSimRCrearEjeReal`, `SDomSimRCrearPuntoSingular`,
`SDomSimRCrearExtremos`), acceso a cada extremo (`SDomSimRA`, `SDomSimRB`,
`SDomSimRValorA`, `SDomSimRValorB`, `SDomSimREstaIncluidoA/B`,
`SDomSimREsMenosInfinitoA`, `SDomSimREsInfinitoB`), pertenencia
(`SDomSimREstaIncluido`, `…Origen`, `…Infinito`, `…MenosInfinito`), más
`SDomSimREsPuntoSingular`, `SDomSimREsValido`, `SDomSimRDestruir` y
`SDomSimRDuplicar`.

## `SDominioReal` — declarado, no implementado

Una unión de tramos, guardada en una
[SListaPtr](../../gjs-c-common-base-types/doc/Listas.md).

```c
typedef struct
{
    SListaPtr * p_lisDominios;
} SDominioReal;
```

Declara 14 funciones: gestión de la lista de tramos (`SDomRCrear`,
`SDomRDestruir`, `SDomREsValido`, `SDomRNumDominiosSimples`,
`SDomRNumDominioSimple`, `SDomRInsertarDominioSimple`,
`SDomREliminarDominioSimple`, `SDomRLimpiar`, `SDomRDuplicar`) y consultas sobre
el conjunto (`SDomREstaIncluido`, `…Origen`, `…Infinito`, `…MenosInfinito`,
`SDomREsConexo`).

## Dependencias

- `SDominioSimpleReal` depende de `SExtremoDominioReal`.
- `SDominioReal` depende de `SDominioSimpleReal` y de
  [SListaPtr](../../gjs-c-common-base-types/doc/Listas.md).
- Los usa (o los usaría) [SFuncionReal](SFuncionReal.md).

## Tests

Sólo `SExtremoDominioRealTest.c` → `TestSExtremoDominioReal()`.

## Observaciones

> **Dos módulos completos sin implementación.** `SDominioSimpleReal.h` y
> `SDominioReal.h` describen 36 funciones entre las dos y no existe ningún
> `SDominioSimpleReal.c` ni `SDominioReal.c`. Compilar contra ellas funciona; al
> enlazar aparecen los símbolos sin resolver.
>
> Es el mismo patrón que
> [SListaHash](../../gjs-c-common-base-types/doc/Listas.md) en `base-types`, con
> una diferencia importante: allí la cabecera era una copia inerte que no
> declaraba nada nuevo, y aquí las dos cabeceras describen **una API real y
> coherente** que simplemente no se llegó a escribir.

- **Ninguna de las tres está en la fachada `Calculo.h`**, lo que evita que un
  consumidor tropiece con ellas por accidente. `SExtremoDominioReal`, que sí
  funciona, queda igualmente fuera y hay que incluirlo a mano.
- `SDomRNumDominioSimple` devuelve un `SDominioSimpleReal *`, así que el nombre
  debería ser `SDomRDominioSimple`: el prefijo `Num` está reservado en el resto
  del stack para las funciones que devuelven un recuento.
- `SDomSimRDestruir` y `SDomRDestruir` devuelven `int`, mientras que todos los
  demás destructores del stack devuelven `void`.
- Varios parámetros se llaman `pdomsObj` en vez de `p_domsObj`, sin el guion bajo
  del convenio.
