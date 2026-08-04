# SConector

| Dato         | Valor                                     |
| ------------ | ----------------------------------------- |
| Cabecera     | `src/main/include/SConector.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SConector.c` |
| Prefijo      | `SCnct`                                   |
| Struct       | `SConector`                               |
| Funciones    | 11                                        |
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
| `int SCnctEsValido ( SConector * )`                              | 1 si es utilizable.                            |
| `void * SCnctObjeto ( SConector * )`                             | El objeto envuelto.                            |
| `int SCnctTipo ( SConector * )`                                  | Código de tipo.                                |
| `int SCnctEstablecer ( SConector *, void *, int )`               | Cambia objeto y tipo.                          |
| `int SCnctEstablecerObjeto ( SConector *, void * )`              | Cambia el objeto.                              |
| `int SCnctEstablecerTipo ( SConector *, int )`                   | Cambia el tipo.                                |
| `void SCnctLimpiar ( SConector * )`                              | Vacía el conector.                             |

```c
SConector * p_cnctObj = SCnctCrearExt ( p_valObj, TIP_OBJETO );

if ( SCnctTipo ( p_cnctObj ) == TIP_OBJETO )
{
    SValor * p_val = (SValor *) SCnctObjeto ( p_cnctObj );
}
SCnctDestruirExt ( &p_cnctObj, 1 );   /* destruye también el contenido */
```

## Dependencias

Ninguna más allá de `Base.h`.

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
- **El código de tipo no está acotado a ningún catálogo.** La cabecera no dice si
  `iTipo` usa los `TIP_*` de la librería base o valores propios de la aplicación,
  y no hay validación.
- `SCnctCrear` deja el tipo sin fijar, sin que se diga qué valor toma: cabe
  suponer `TIP_DESCONOCIDO` o cero, pero no está garantizado.
