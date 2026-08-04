# Parejas y referencias

| Dato          | Valor                                |
| ------------- | ------------------------------------ |
| Módulos       | 2                                    |
| Cabeceras     | `SPareja.h`, `SReferencia.h`         |
| Prefijos      | `SPrj`, `SRef`                       |
| Structs       | `SPareja`, `SReferencia`             |
| Incluidos por | `Tipos.h`                            |
| Tests         | `SParejaTest.c`, `SReferenciaTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Dos formas de **asociar dos cosas**:

| Módulo        | Asocia                        | Uso típico                       |
| ------------- | ----------------------------- | -------------------------------- |
| `SPareja`     | Dos punteros cualesquiera     | Tuplas, resultados dobles        |
| `SReferencia` | Un alias de texto con un dato | Diccionarios, tablas de símbolos |

Son la carga de [SListaParejas y SListaReferencias](Listas.md), que es donde se
usan de verdad.

## `SPareja`

```c
typedef struct
{
    void * p_vPrimero;
    void * p_vSegundo;
    int    iLiberar;
} SPareja;
```

### Los tres constructores

Lo característico del módulo es que la política de memoria se elige **en el
constructor**, y hay uno por cada opción:

| Constructor                                  | `iLiberar`     | Al destruir             |
| -------------------------------------------- | -------------- | ----------------------- |
| `SPrjCrear ( void *, void *, int iLiberar )` | El que se pase | Según se haya indicado  |
| `SPrjCrearGestionando ( void *, void * )`    | 1              | Libera los dos miembros |
| `SPrjCrearSoloPtr ( void *, void * )`        | 0              | No libera nada          |

Los dos últimos son atajos legibles sobre el primero, y quitan la duda de qué
significa el `1` o el `0` en la llamada.

### Resto de la API

| Función                                              | Descripción                  |
| ---------------------------------------------------- | ---------------------------- |
| `void SPrjDestruir ( SPareja ** )`                   | Destruye y anula el puntero. |
| `int SPrjEsValido ( SPareja * )`                     | 1 si es utilizable.          |
| `void * SPrjObtenerPrimero ( SPareja * )`            | Primer miembro.              |
| `void * SPrjObtenerSegundo ( SPareja * )`            | Segundo miembro.             |
| `void SPrjEstablecerPrimero ( SPareja *, void * )`   | Cambia el primero.           |
| `void SPrjEstablecerSegundo ( SPareja *, void * )`   | Cambia el segundo.           |
| `int SPrjLiberacionMemoriaActivada ( SPareja * )`    | Valor de `iLiberar`.         |
| `void SPrjActivarLiberacionMemoria ( SPareja * )`    | Pasa a liberar.              |
| `void SPrjDesactivarLiberacionMemoria ( SPareja * )` | Deja de liberar.             |

## `SReferencia`

```c
typedef struct
{
    char * p_cAlias;
    void * p_vDatos;
} SReferencia;
```

Asocia un nombre a un dato. **El alias es propiedad de la referencia** (se
guarda como `char *` y el constructor lo recibe como `const char *`, lo que
indica que lo duplica); el dato no.

### API

| Grupo                 | Funciones                                                                                              |
| --------------------- | ------------------------------------------------------------------------------------------------------ |
| Ciclo de vida         | `SRefCrear ( const char * p_cAlias, void * p_vDatos )`, `SRefDestruir`, `SRefEsValida`, `SRefDuplicar` |
| Consulta              | `SRefObtenerAlias`, `SRefObtenerDatos`                                                                 |
| Modificación          | `SRefEstablecer`, `SRefEstablecerAlias`, `SRefEstablecerDatos`                                         |
| Comparación           | `SRefEsIgual`, `SRefEsMenor`, `SRefEsMayor`                                                            |
| Comparación por alias | `SRefEsIgualLit`, `SRefEsMenorLit`, `SRefEsMayorLit`                                                   |
| Otros                 | `SRefHash`                                                                                             |

Las comparaciones ordenan **por alias**, que es lo que permite meter referencias
en una [lista ordenada o un conjunto](Conjuntos.md) y buscar por nombre.

`SRefObtenerAlias` devuelve `const char *`: es el alias interno, no hay que
liberarlo ni modificarlo.

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md) — cadenas y
  hash.

## Tests

`SParejaTest.c` → `TestSPareja()`, `SReferenciaTest.c` → `TestSReferencia()`.

## Observaciones

- **`SPareja` tiene una sola bandera para los dos miembros.** No se puede pedir
  que libere el primero y no el segundo, que es justo lo que hace falta cuando se
  empareja un dato propio con uno prestado. En ese caso hay que usar
  `SPrjCrearSoloPtr` y liberar a mano.
- `SPrjEstablecerPrimero` y `SPrjEstablecerSegundo` devuelven `void` y **no
  liberan el valor anterior**, ni siquiera con `iLiberar` a 1. Sustituir un
  miembro de una pareja que gestiona memoria filtra el valor viejo.
- **`SReferencia` no tiene bandera de propiedad para el dato**, a diferencia de
  `SPareja`. El alias siempre es suyo y el dato nunca: no hay forma de que una
  referencia libere el dato al destruirse.
- `SRefEsMenor` y `SRefEsMayor` comparan alias, así que dos referencias con el
  mismo alias y distinto dato son "iguales" para el orden. En un
  [conjunto](Conjuntos.md) eso significa que no se puede tener el mismo alias dos
  veces, que suele ser lo deseable en un diccionario.
