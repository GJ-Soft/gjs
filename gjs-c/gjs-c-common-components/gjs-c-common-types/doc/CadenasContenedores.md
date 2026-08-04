# Contenedores de cadenas

| Dato          | Valor                                                                                             |
| ------------- | ------------------------------------------------------------------------------------------------- |
| Módulos       | 5                                                                                                 |
| Cabeceras     | `SVectorCadenas.h`, `SSecuenciaCadenas.h`, `STablaCadenas.h`, `SPilaCadenas.h`, `SArbolCadenas.h` |
| Prefijos      | `SVecCad`, `SSecCad`, `STabCad`, `SPilCad`, `SArbCad`                                             |
| Funciones     | 10 + 11 + 12 + 12 + 43                                                                            |
| Incluidos por | `TiposDatos.h`                                                                                    |
| Tests         | Uno por módulo                                                                                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Especializaciones en [SCadena](../../gjs-c-common-text/doc/SCadena.md) de los
contenedores de
[gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md).

| Módulo              | Envuelve       | Equivalente genérico                                          |
| ------------------- | -------------- | ------------------------------------------------------------- |
| `SVectorCadenas`    | `SVector *`    | [Vectores](../../gjs-c-common-base-types/doc/Vectores.md)     |
| `SSecuenciaCadenas` | `SSecuencia *` | [Secuencias](../../gjs-c-common-base-types/doc/Secuencias.md) |
| `STablaCadenas`     | `STabla *`     | [Tablas](../../gjs-c-common-base-types/doc/Tablas.md)         |
| `SPilaCadenas`      | `SPila *`      | [Pilas](../../gjs-c-common-base-types/doc/Pilas.md)           |
| `SArbolCadenas`     | `SArbol *`     | [Árboles](../../gjs-c-common-base-types/doc/Arboles.md)       |

Son a `SCadena` lo que los
[contenedores de reales dobles](../../gjs-c-common-calculation/doc/RealesDobles.md)
son a `double`, y lo que `SListaLiterales` es a `char *`.

## Las cuatro sencillas

`SVectorCadenas`, `SSecuenciaCadenas`, `STablaCadenas` y `SPilaCadenas` tienen
entre 10 y 12 funciones cada una: el ciclo de vida, el acceso propio de su
estructura y `Existe`.

```c
SVectorCadenas * p_vecObj = SVecCadCrear ( 10 );

SVecCadAsignar ( p_vecObj, 0, p_cadObj );
SCadena * p_cad = SVecCadElemento ( p_vecObj, 0 );

SVecCadDestruir ( &p_vecObj );
```

## `SArbolCadenas` — la excepción

Con **43 funciones** es cuatro veces mayor que sus hermanas, porque hereda toda
la navegación por cursor del
[árbol genérico](../../gjs-c-common-base-types/doc/Arboles.md): movimiento a
raíz, padre, hijos y hermanos, recorridos en preorden y postorden, más las
operaciones sobre el nodo actual.

Es, de hecho, la variante de árbol más completa del stack: `SArbolLiterales` en
`base-types` tiene 44 funciones y es la que más se le parece.

## Dependencias

- Los contenedores genéricos de
  [gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md).
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — el contenido.

## Tests

`SVectorCadenasTest.c`, `SSecuenciaCadenasTest.c`, `STablaCadenasTest.c`,
`SPilaCadenasTest.c`, `SArbolCadenasTest.c`.

## Observaciones

**Hay tres familias de contenedores de texto repartidas por el stack**, y
conviene saber cuál se está usando:

| Familia                                | Elemento    | Módulo Maven |
| -------------------------------------- | ----------- | ------------ |
| `SListaLiterales`, `SVectorLiterales`… | `char *`    | `base-types` |
| `SListaCadenas`                        | `SCadena *` | `text`       |
| Estos cinco                            | `SCadena *` | `types`      |

`SListaCadenas` vive en `text` y los otros cinco aquí, pese a guardar lo mismo:
no hay `SListaCadenas` en este componente, ni vector, tabla, pila o árbol en
aquel. La familia está partida entre dos módulos Maven.

- **Falta la lista**: de los seis contenedores genéricos, este componente
  especializa cinco. La lista de cadenas hay que buscarla en
  [gjs-c-common-text](../../gjs-c-common-text/doc/SListaCadenas.md).
- Las cuatro sencillas **no tienen la doble forma de inserción** (`…Dup`) que sí
  ofrecen `SListaCadenas` y `SListaLiterales`: la cabecera no aclara si el
  contenedor copia la `SCadena` o se queda con el puntero.
- Ninguna expone el contenedor genérico interno, así que no hay válvula de escape
  hacia las operaciones que estas APIs reducidas no cubren.
