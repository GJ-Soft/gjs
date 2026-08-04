# STexto

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/STexto.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/STexto.c` (910 líneas) |
| Prefijos     | `STxt` y `Txt` — **dos, ver Observaciones**         |
| Struct       | `STexto`                                            |
| Funciones    | 33                                                  |
| Incluido por | `Texto.h`                                           |
| Test         | `STextoTest.c` → `TestSTexto()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un documento de **varias líneas con cursor bidimensional**. Es la estructura de
más alto nivel de la librería: lo que usaría un editor de texto sencillo.

```c
typedef struct
{
    SListaCadenas * p_lisLineas;
    int             iLineaAct;
    int             iColumnaAct;
} STexto;
```

Las líneas se guardan en una [SListaCadenas](SListaCadenas.md) y la posición se
lleva en dos enteros, aunque el módulo también sabe trabajar con objetos
[SCursor](../../gjs-c-common-base-types/doc/Cursores.md).

## API

### Ciclo de vida

| Función                                          | Descripción                   |
| ------------------------------------------------ | ----------------------------- |
| `STexto * STxtCrear ()`                          | Texto vacío.                  |
| `STexto * STxtGenerar ( const char * p_cTexto )` | Texto a partir de un literal. |
| `void STxtDestruir ( STexto ** )`                | Destruye y anula el puntero.  |
| `int STxtEsValido ( STexto * )`                  | 1 si es utilizable.           |
| `int STxtInicializar ( STexto *, const char * )` | Recarga con otro contenido.   |
| `void STxtVaciar ( STexto * )`                   | Vacía el texto.               |

### Consulta

`STxtNumLineas`, `STxtLineaActual`, `STxtLinea ( …, int iLinea )`,
`STxtCaracterActual`, `STxtCaracterSig`, `STxtEstaPosicionado`,
`STxtPosEsValida ( …, int iLinea, int iColumna )`,
`STxtExtraer ( …, iLinIni, iColIni, iLinFin, iColFin )`.

`STxtExtraer` devuelve el tramo entre dos posiciones como
[SCadena](SCadena.md), que es la operación de "seleccionar y copiar".

### Cursor propio

| Grupo     | Funciones                                                                                                          |
| --------- | ------------------------------------------------------------------------------------------------------------------ |
| Posición  | `STxtCursor`, `STxtCursorLinea`, `STxtCursorColumna`                                                               |
| Documento | `STxtIrInicio`, `STxtIrFinal`, `STxtIrA ( …, iLinea, iColumna )`                                                   |
| Carácter  | `STxtSig`, `STxtAnt`                                                                                               |
| Línea     | `STxtIrInicioLinea`, `STxtIrFinalLinea`, `STxtIrPrimeraLinea`, `STxtIrUltimaLinea`, `STxtSigLinea`, `STxtAntLinea` |

### Cursores externos

El módulo puede mover un `SCursor` ajeno sin tocar su propia posición, lo que
permite tener varias marcas sobre el mismo texto:

```c
int  STxtCursorEsValido  ( STexto *, SCursor * );
void STxtCursorSig       ( STexto *, SCursor * );
void STxtCursorAnt       ( STexto *, SCursor * );
void STxtCursorAvanzar   ( STexto *, SCursor *, int iPosiciones );
void STxtCursorRetroceder( STexto *, SCursor *, int iPosiciones );
```

### Edición y ficheros (prefijo `Txt`)

| Función                                                           | Descripción            |
| ----------------------------------------------------------------- | ---------------------- |
| `void TxtInsertarCaracter ( STexto *, char )`                     | Inserta un carácter.   |
| `void TxtInsertarCadena ( STexto *, char * )`                     | Inserta una cadena.    |
| `void TxtInsertarLinea ( STexto *, char * )`                      | Inserta una línea.     |
| `void TxtEliminarCaracter ( STexto * )`                           | Borra un carácter.     |
| `void TxtEliminarLinea ( STexto * )`                              | Borra la línea actual. |
| `void TxtImprimir ( STexto * )`                                   | Vuelca el texto.       |
| `void TxtCargarFichero ( STexto *, char * sFichero, long lMode )` | Lee de fichero.        |
| `void TxtSalvarFichero ( STexto *, char * sFichero )`             | Escribe a fichero.     |

## Dependencias

- [SListaCadenas](SListaCadenas.md) — las líneas.
- [SCadena](SCadena.md) — cada línea.
- [Cursores](../../gjs-c-common-base-types/doc/Cursores.md) — `SCursor`.

## Test

`STextoTest.c` → `TestSTexto()`.

## Observaciones

> **Toda la edición está en el prefijo equivocado.** Veinticinco funciones usan
> `STxt` y ocho `Txt`, y no es una división arbitraria: las `Txt*` son
> justamente **las que modifican el texto** y las de fichero. Además cambian de
> convenio de nombres de parámetro —`STexto *ptxtDatos`, `char *sCadena`, en vez
> de `p_txtObj` y `p_cCadena`— lo que confirma que proceden de otra base de
> código. Es el mismo síntoma que en [SLinea](SLinea.md).

> **El módulo lee y escribe ficheros.** `TxtCargarFichero` y `TxtSalvarFichero`
> hacen entrada/salida en una librería de texto que **no depende de
> `gjs-c-common-io`**, así que la implementación tiene que estar usando las
> rutinas de C directamente. Es una fuga de capa: el manejo de ficheros del stack
> vive en otro módulo.

- Las ocho funciones `Txt*` devuelven `void`: no informan de si la inserción
  cupo, si el fichero se pudo abrir o si el borrado hizo algo. `TxtCargarFichero`
  recibe además un `long lMode` sin documentar.
- `TxtInsertarCadena` y `TxtInsertarLinea` reciben `char *` no constante, cuando
  no tienen por qué modificar el argumento.
- La posición se guarda en `iLineaAct` / `iColumnaAct` como enteros sueltos, pero
  `STxtCursor` devuelve un `SCursor`. Conviven las dos representaciones sin que
  la cabecera aclare cuál manda.
- No hay deshacer ni marcas de modificación, lo que limita su uso como base de un
  editor real.
