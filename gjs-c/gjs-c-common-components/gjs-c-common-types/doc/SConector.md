# SConector

| Dato         | Valor                                     |
| ------------ | ----------------------------------------- |
| Cabecera     | `src/main/include/SConector.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SConector.c` |
| Prefijo      | `SCnct`                                   |
| Struct       | `SConector`                               |
| Funciones    | 12                                        |
| Incluido por | `TiposDatos.h`                            |
| Test         | `SConectorTest.c` → `TestSConector()`     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **puntero con etiqueta de tipo**: envuelve cualquier objeto junto a un código
que dice qué es.

```c
typedef struct
{
    void * p_vObjeto;
    int    iTipo;
} SConector;
```

Resuelve el problema de meter objetos heterogéneos en un contenedor genérico —
una [SListaPtr](../../gjs-c-common-base-types/doc/Listas.md) guarda `void *` sin
saber qué contiene; un `SConector` añade la etiqueta que permite recuperar el
tipo al sacarlo.

## API

| Función                                                          | Descripción                                    |
| ---------------------------------------------------------------- | ---------------------------------------------- |
| `SConector * SCnctCrear ( void * p_vObjeto )`                    | Envuelve sin tipo.                             |
| `SConector * SCnctCrearExt ( void * p_vObjeto, int iTipo )`      | Envuelve con tipo.                             |
| `void SCnctDestruir ( SConector ** )`                            | Destruye **sólo el conector**.                 |
| `void SCnctDestruirExt ( SConector **, int iDestruirContenido )` | Destruye conector y, opcionalmente, contenido. |
| `SPtr * SCnctPtr ( SConector * )`                                | Lo envuelve en un `SPtr`.                      |
| `int SCnctEsValido ( SConector * )`                              | 1 si es utilizable.                            |
| `void * SCnctObjeto ( SConector * )`                             | El objeto envuelto.                            |
| `int SCnctTipo ( SConector * )`                                  | Código de tipo.                                |
| `int SCnctEstablecer ( SConector *, void *, int )`               | Cambia objeto y tipo.                          |
| `int SCnctEstablecerObjeto ( SConector *, void * )`              | Cambia el objeto.                              |
| `int SCnctEstablecerTipo ( SConector *, int )`                   | Cambia el tipo.                                |
| `void SCnctLimpiar ( SConector * )`                              | Vacía el conector.                             |

`SCnctPtr` pasa la propiedad del conector al `SPtr`: después se libera con
`SPtrDestruir`, que llama a `SCnctDestruir`, y no por separado. Como
`SCnctDestruir`, **no** libera el objeto conectado: sigue siendo del llamante,
que lo destruye aparte. Con objeto nulo devuelve un `SPtr` vacío; si falla la
reserva del `SPtr`, devuelve `NULL` y el conector sigue siendo del llamante.

```c
SConector * p_cnctObj = SCnctCrearExt ( p_valObj, TIP_OBJETO );

if ( SCnctTipo ( p_cnctObj ) == TIP_OBJETO )
{
    SValor * p_val = (SValor *) SCnctObjeto ( p_cnctObj );
}
SCnctDestruirExt ( &p_cnctObj, 1 );   /* destruye también el contenido */
```

## Dependencias

`Base.h`, y [SPtr](../../gjs-c-common-base-types/doc/SPtr.md) de gjs-c-common-base-types para `SCnctPtr`.

## Test

`SConectorTest.c` → `TestSConector()`.

## Observaciones

- **La propiedad se decide al destruir, no al construir.** Es al revés que en el
  resto del stack, donde la bandera `iLiberar` va en la estructura y se fija en
  el constructor —así funcionan
  [SBloque](../../gjs-c-common-base-types/doc/SBloque.md),
  [SElemento](../../gjs-c-common-base-types/doc/SElemento.md) y
  [SPareja](../../gjs-c-common-base-types/doc/ParejasReferencias.md). Aquí quien
  destruye tiene que **acordarse** de si el conector era dueño.
- **`SCnctDestruirExt` no puede saber cómo destruir el contenido.** Al guardar un
  `void *` sin destructor asociado, lo más que puede hacer es un `MemLiberar`
  genérico, que para un objeto del stack —una `SCadena`, un `SValor`— libera la
  estructura pero **no sus campos internos**. Conviene destruir el contenido a
  mano y llamar a `SCnctDestruir` a secas.
- **Hasta el 2026-10-18, `SCnctDestruir` liberaba también el contenido**, en
  contra de lo que siempre dijo esta tabla: llamaba a
  `SCnctDestruirExt ( …, 1 )`. Ahora pasa `0`. Un consumidor que contara con la
  liberación implícita ahora pierde ese bloque; uno que liberaba el contenido a
  mano antes de destruir el conector cometía una doble liberación, que desaparece.
- **El código de tipo no está acotado a ningún catálogo.** La cabecera no dice si
  `iTipo` usa los `TIP_*` de la librería base o valores propios de la aplicación,
  y no hay validación.
- `SCnctCrear` deja el tipo sin fijar, sin que se diga qué valor toma: cabe
  suponer `TIP_DESCONOCIDO` o cero, pero no está garantizado.
