# SListaCadenas

| Dato         | Valor                                                      |
| ------------ | ---------------------------------------------------------- |
| Cabecera     | `src/main/include/SListaCadenas.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SListaCadenas.c` (715 líneas) |
| Prefijo      | `SLisCad`                                                  |
| Struct       | `SListaCadenas`                                            |
| Funciones    | 39                                                         |
| Incluido por | `Texto.h`                                                  |
| Test         | `SListaCadenasTest.c` → `TestSListaCadenas()`              |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Lista de [SCadena](SCadena.md) con cursor. Es la especialización para texto de
la familia de [Listas](../../gjs-c-common-base-types/doc/Listas.md) de
`gjs-c-common-base-types`, y el almacenamiento sobre el que se apoya
[STexto](STexto.md) para guardar sus líneas.

```c
typedef struct
{
    SListaPtr * p_lisDatos;
} SListaCadenas;
```

## API

Sigue exactamente el modelo de
[SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md), cambiando
`char *` por `SCadena *`.

### Ciclo de vida y consulta

`SLisCadCrear`, `SLisCadDestruir`, `SLisCadEsValida`, `SLisCadEstaVacia`,
`SLisCadNumElementos`, `SLisCadVaciar`.

### Acceso por índice

| Función                                                    | Descripción                |
| ---------------------------------------------------------- | -------------------------- |
| `SCadena * SLisCadElemento ( SListaCadenas *, int iElem )` | Cadena de la posición.     |
| `int SLisCadEstablecerElem ( …, int iElem, SCadena * )`    | Sustituye.                 |
| `int SLisCadInsertarElem ( …, int iPosAnt, SCadena * )`    | Inserta tras la posición.  |
| `int SLisCadInsertarAlInicio ( …, SCadena * )`             | Inserta al principio.      |
| `int SLisCadInsertarAlFinal ( …, SCadena * )`              | Inserta al final.          |
| `int SLisCadEliminarElem ( …, int iElem )`                 | Elimina el de la posición. |

### Cursor

`SLisCadPosicion`, `SLisCadActual`, `SLisCadInicio`, `SLisCadFinal`,
`SLisCadSiguiente`, `SLisCadAnterior`, `SLisCadMoverA`, `SLisCadDeposicionar`,
`SLisCadEsNulo`, `SLisCadEstaEnInicio`, `SLisCadEstaEnFinal`.

Y las de modificación sobre el cursor: `SLisCadEstablecer`, `SLisCadInsertar`,
`SLisCadInsertarDelante`, `SLisCadInsertarDetras`, `SLisCadEliminar`.

### Búsqueda

| Función                                                  | Descripción               |
| -------------------------------------------------------- | ------------------------- |
| `int SLisCadExiste ( SListaCadenas *, SCadena * )`       | 1 si está.                |
| `int SLisCadBuscar ( SListaCadenas *, SCadena * )`       | Posición donde está.      |
| `int SLisCadBuscarExt ( SListaCadenas *, const char * )` | Ídem buscando un literal. |

### Las dos formas de insertar

Como en
[SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md), cada operación
de inserción viene por duplicado:

| Forma                 | Qué hace con la cadena                                             |
| --------------------- | ------------------------------------------------------------------ |
| `SLisCadInsertar…`    | Guarda el puntero: la lista pasa a ser responsable de la `SCadena` |
| `SLisCadInsertar…Dup` | **Duplica** la `SCadena` y guarda la copia                         |

Ocho funciones `…Dup` en total: `SLisCadEstablecerElemDup`,
`SLisCadInsertarElemDup`, `SLisCadInsertarDupAlInicio`,
`SLisCadInsertarDupAlFinal`, `SLisCadEstablecerDup`, `SLisCadInsertarDup`,
`SLisCadInsertarDupDelante`, `SLisCadInsertarDupDetras`.

## Dependencias

- [Listas](../../gjs-c-common-base-types/doc/Listas.md) — `SListaPtr`.
- [SCadena](SCadena.md) — el contenido.

## Test

`SListaCadenasTest.c` → `TestSListaCadenas()`.

## Observaciones

- **A diferencia de `SListaLiterales`, las variantes `Dup` reciben el mismo tipo
  que las normales** (`SCadena *`, no `const SCadena *`). En `SListaLiterales` la
  firma delataba cuál duplicaba, porque las `Dup` tomaban `const char *`. Aquí no
  hay forma de saberlo por el tipo: hay que leer el nombre con cuidado.
- **No tiene `Extraer`**: se puede eliminar un elemento (destruyéndolo) pero no
  sacarlo de la lista conservándolo, a diferencia de
  [SLista](../../gjs-c-common-base-types/doc/Listas.md), que sí ofrece
  `SLisExtraerElem`.
- Tampoco expone la `SListaPtr` interna, así que no hay válvula de escape hacia
  las operaciones que esta API no cubre.
- `SLisCadBuscarExt` busca por literal, pero no existe el `SLisCadExisteExt`
  correspondiente: para saber si un literal está hay que usar `Buscar` y
  comprobar el resultado.
