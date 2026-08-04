# SLinea

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/SLinea.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SLinea.c` (840 líneas) |
| Prefijos     | `SLin` y `Lin` — **dos, ver Observaciones**         |
| Struct       | `SLinea`                                            |
| Funciones    | 45                                                  |
| Incluido por | `Texto.h`                                           |
| Test         | `SLineaTest.c` → `TestSLinea()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una línea de texto **con cursor y anchura máxima**: lo que hace falta para
editar texto posición a posición, con inserción, sobrescritura, alineación y
justificación.

```c
typedef struct
{
    SCadena *     p_cadTexto;
    SIndicador *  p_indPosicion;
} SLinea;
```

El cursor es un
[SIndicador](../../gjs-c-common-base-types/doc/Cursores.md), que es quien sabe
si un movimiento es posible antes de hacerlo.

## API

### Ciclo de vida

`SLinCrear ( int iMaxLong )`, `SLinGenerar ( SCadena * )`,
`SLinGenerarLiteral ( const char * )`, `SLinDuplicar`, `SLinDuplicarVacia`,
`SLinDestruir`, `SLinEsValida`, `SLinVaciar`, `SLinAsignar`,
`SLinSonCompatibles`.

`SLinDuplicarVacia` crea una línea con las mismas características pero sin
contenido, útil al partir texto.

### Consulta

`SLinValorCadena`, `SLinValorLiteral`, `SLinPosicion`, `SLinLongitud`,
`SLinLongitudMax`, `SLinEstaVacia`, `SLinEstaEnInicio`, `SLinEstaEnFinal`,
`SLinEspacioLibre`, `SLinQuedaEspacioLibre`, `SLinNumPalabras`,
`SLinNumCaracteres`.

### Cursor

`SLinIni`, `SLinFin`, `SLinSig`, `SLinAnt`, `SLinMover ( …, int iPos )`.

### Comprobar antes de escribir

Es lo característico del módulo: **cada operación de escritura tiene su
predicado previo**, heredado del `SIndicador`.

| Comprobación                | Operación              |
| --------------------------- | ---------------------- |
| `SLinPuedeInsertar`         | `SLinInsertar`         |
| `SLinPuedeInsertarLiteral`  | `SLinInsertarLiteral`  |
| `SLinPuedeInsertarCaracter` | `SLinInsertarCaracter` |
| `SLinPuedeEscribir`         | `SLinEscribir`         |
| `SLinPuedeEscribirLiteral`  | `SLinEscribirLiteral`  |
| `SLinPuedeEscribirCaracter` | `SLinEscribirCaracter` |

**Insertar** desplaza lo que hay a la derecha; **escribir** sobrescribe.

### Insertar con resto

Las variantes `Ext` devuelven **lo que no cupo**, que es justo lo que necesita un
formateador de párrafos para pasar el sobrante a la línea siguiente:

```c
int SLinInsertarExt ( SLinea *, SCadena * p_cadValor, SCadena ** p_p_cadResto );
int SLinInsertarLiteralExt ( SLinea *, const char * p_cValor, char ** p_p_cResto );
int SLinInsertarCaracterExt ( SLinea *, char cValor, char * p_cResto );
```

### Eliminar

`SLinEliminarCaracter`, `SLinEliminarCaracteres ( …, int iNum )`.

### Formato y búsqueda (prefijo `Lin`)

| Función                                                                      | Descripción                     |
| ---------------------------------------------------------------------------- | ------------------------------- |
| `LinAlinearIzq` / `LinAlinearDer` / `LinAlinearCen`                          | Alineación.                     |
| `LinJustificar`                                                              | Justificación a ambos márgenes. |
| `LinLimpiarBlancos`                                                          | Quita blancos sobrantes.        |
| `LinPrimeraPalabra` / `LinUltimaPalabra` / `LinSigPalabra` / `LinAntPalabra` | Cursor por palabras.            |
| `LinRepeticiones` / `LinRepeticionesPatron`                                  | Conteo.                         |
| `LinBuscarPrimero` / `LinBuscarSig` / `LinBuscarAnt` / `LinBuscarUltimo`     | Búsqueda.                       |
| `LinReemplazarPrimero` / `…Sig` / `…Ant` / `…Ultimo` / `…Todos`              | Sustitución.                    |

Más `SLinImprimir`.

## Dependencias

- [SCadena](SCadena.md) — el texto.
- [Cursores](../../gjs-c-common-base-types/doc/Cursores.md) — `SIndicador`.

## Test

`SLineaTest.c` → `TestSLinea()`.

## Observaciones

> **El módulo usa dos prefijos.** Veintiséis funciones llevan `SLin` y
> diecinueve `Lin`, sin que haya un criterio visible: `SLinEliminarCaracter` y
> `LinLimpiarBlancos` conviven en la misma cabecera. Las `Lin*` son búsqueda,
> reemplazo, alineación y movimiento por palabras, lo que sugiere que vienen de
> una base de código anterior que se incorporó sin renombrar.

- **Las funciones `Lin*` de búsqueda y reemplazo reciben `char * *`**, es decir,
  puntero a puntero a carácter, para lo que parece ser un texto a buscar:
  `LinBuscarPrimero ( SLinea *, char * * p_cena )`. El nombre del parámetro
  (`p_cena`) sugiere que era `p_cCadena`. Lo natural para buscar sería
  `const char *`; conviene mirar la implementación antes de llamarlas.
- `SLinInsertarCaracterExt` devuelve el resto en un `char *` simple, mientras que
  las otras dos variantes `Ext` usan puntero a puntero. Al ser un solo carácter
  puede tener sentido, pero rompe la simetría de la familia.
- `LinRepeticionesPatron` devuelve `long` como `LinRepeticiones`, pero el resto
  del módulo trabaja con `int`.
