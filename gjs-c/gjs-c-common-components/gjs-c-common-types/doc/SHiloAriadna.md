# SHiloAriadna

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/SHiloAriadna.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SHiloAriadna.c` |
| Prefijo      | `SHilAri`                                    |
| Struct       | `SHiloAriadna`                               |
| Funciones    | 9                                            |
| Incluido por | `TiposDatos.h`                               |
| Test         | `SHiloAriadnaTest.c` → `TestSHiloAriadna()`  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **traza de recorrido**: la pila de textos que registra por dónde se ha
pasado, para poder volver sobre los pasos o mostrar la ruta al usuario.

El nombre viene del hilo de Ariadna del mito del laberinto, y describe bien el
uso: navegación por menús anidados, migas de pan, contexto de una operación en
curso.

```c
typedef struct
{
    SPilaLiterales * p_pilTextos;
} SHiloAriadna;
```

Es un envoltorio delgado sobre
[SPilaLiterales](../../gjs-c-common-base-types/doc/Pilas.md).

## API

| Función                                                 | Descripción                  |
| ------------------------------------------------------- | ---------------------------- |
| `SHiloAriadna * SHilAriCrear ()`                        | Hilo vacío.                  |
| `void SHilAriDestruir ( SHiloAriadna ** )`              | Destruye y anula el puntero. |
| `int SHilAriEsValido ( SHiloAriadna * )`                | 1 si es utilizable.          |
| `int SHilAriNumElementos ( SHiloAriadna * )`            | Profundidad actual.          |
| `int SHilAriEstaVacio ( SHiloAriadna * )`               | 1 si no hay tramos.          |
| `int SHilAriApilar ( SHiloAriadna *, char * p_cTexto )` | Entra en un tramo.           |
| `int SHilAriDesapilar ( SHiloAriadna * )`               | Sale del tramo actual.       |
| `int SHilAriVaciar ( SHiloAriadna * )`                  | Vuelve al principio.         |
| `int SHilAriImprimir ( SHiloAriadna * )`                | Vuelca la ruta por consola.  |

```c
SHiloAriadna * p_hilObj = SHilAriCrear ();

SHilAriApilar ( p_hilObj, "Principal" );
SHilAriApilar ( p_hilObj, "Configuración" );
SHilAriApilar ( p_hilObj, "Usuarios" );

SHilAriImprimir ( p_hilObj );        /* la ruta completa */
SHilAriDesapilar ( p_hilObj );       /* vuelve a Configuración */

SHilAriDestruir ( &p_hilObj );
```

Encaja con [SAccion](SAccion.md): `TIP_ACC_MENU` apila un tramo y
`TIP_ACC_VOLVER` lo desapila.

## Dependencias

- [SPilaLiterales](../../gjs-c-common-base-types/doc/Pilas.md) — el
  almacenamiento.

## Test

`SHiloAriadnaTest.c` → `TestSHiloAriadna()`.

## Observaciones

- **`SHilAriDesapilar` devuelve `int`, no el texto desapilado.** Al contrario que
  `SPilLitDesapilar`, que sí devuelve la cadena, aquí se pierde: para leer el
  tramo antes de salir de él no hay función, porque **tampoco existe un
  `SHilAriPrimero`** que consulte la cima sin sacarla.
- **No se puede recorrer el hilo.** `SHilAriImprimir` lo vuelca por consola, pero
  no hay forma de obtener los tramos uno a uno para pintarlos en otro sitio ni de
  componer la ruta como cadena. Con nueve funciones, la única salida del
  contenido es `printf`.
- `SHilAriApilar` recibe `char *` no constante, cuando no tiene por qué modificar
  el texto. La cabecera no dice si copia la cadena o se queda con el puntero, lo
  que importa al apilar un literal frente a un búfer reutilizado.
- No expone la `SPilaLiterales` interna, así que no hay válvula de escape hacia
  las operaciones que esta API no cubre.
