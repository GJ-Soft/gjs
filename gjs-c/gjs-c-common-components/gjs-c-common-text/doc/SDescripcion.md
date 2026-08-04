# SDescripcion

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/SDescripcion.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SDescripcion.c` |
| Prefijo      | `SDesc`                                      |
| Struct       | `SDescripcion`                               |
| Funciones    | 11                                           |
| Incluido por | `Texto.h`                                    |
| Test         | `SDescripcionTest.c` → `TestSDescripcion()`  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un texto explicativo de longitud media: la descripción de un campo, de una
tabla o de una opción. Es la hermana de [SNombre](SNombre.md) con más holgura.

```c
typedef struct
{
    SCadena * p_cadValor;
} SDescripcion;
```

El tope por defecto es `DESC_MAX_TAM_DEF`, **255 caracteres**
(`TextoConstantes.h`).

## API

| Función                                                | Descripción                                |
| ------------------------------------------------------ | ------------------------------------------ |
| `SDescripcion * SDescCrearDef ()`                      | Descripción con el tope por defecto (255). |
| `SDescripcion * SDescCrear ( int iMaxTam )`            | Con el tope indicado.                      |
| `void SDescDestruir ( SDescripcion ** )`               | Destruye y anula el puntero.               |
| `int SDescMaxLongitud ( SDescripcion * )`              | Longitud máxima.                           |
| `int SDescLongitud ( SDescripcion * )`                 | Longitud actual.                           |
| `SCadena * SDescValor ( SDescripcion * )`              | Cadena interna.                            |
| `const char * SDescValorConstante ( SDescripcion * )`  | Contenido de sólo lectura.                 |
| `int SDescEstablecerCad ( SDescripcion *, SCadena * )` | Fija el valor desde una `SCadena`.         |
| `int SDescEstablecer ( SDescripcion *, const char * )` | Fija el valor desde un literal.            |
| `int SDescLimpiar ( SDescripcion * )`                  | Vacía la descripción.                      |
| `int SDescEstaVacio ( SDescripcion * )`                | 1 si está vacía.                           |

## Dependencias

- [SCadena](SCadena.md) — el almacenamiento y todas las operaciones.

## Test

`SDescripcionTest.c` → `TestSDescripcion()`.

## Observaciones

- **Es el mismo módulo que [SNombre](SNombre.md) con otro tope por defecto.**
  Once funciones con la misma firma, misma estructura de un campo, misma
  delegación en `SCadena`. La única diferencia real es 255 frente a 35.
- `SDescEstaVacio` está en **masculino** pese a que el sustantivo es femenino y
  el resto de la API concuerda en femenino (`SDescCrear` devuelve "una
  descripción"). Es sólo el nombre, pero rompe la concordancia que sigue el resto
  del stack (`SCadEsValida`, `SLisEsValida`…).
- Como [SNombre](SNombre.md), no ofrece comparación ni validación de contenido:
  para eso hay que bajar a la `SCadena` con `SDescValor`.
- No hay soporte de texto multilínea: para eso está [STexto](STexto.md).
