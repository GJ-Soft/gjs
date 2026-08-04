# SContenido

| Dato         | Valor                                      |
| ------------ | ------------------------------------------ |
| Cabecera     | `src/main/include/SContenido.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SContenido.c` |
| Prefijo      | `SCon`                                     |
| Struct       | `SContenido`                               |
| Funciones    | 26                                         |
| Incluido por | `Tipos.h`                                  |
| Test         | `SContenidoTest.c` → `TestSContenido()`    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Envuelve un [SBloque](SBloque.md) añadiendo una capa de propiedad propia. Es el
"valor" que guardan los contenedores cuando no necesitan encadenarse: donde
[SElemento](SElemento.md) es contenido **más** enlaces de lista, `SContenido` es
sólo el contenido.

## Modelo de datos

```c
typedef struct
{
    SBloque *  p_blqDatos;
    int        iLiberar;
} SContenido;
```

Hay **dos banderas de propiedad en juego**: la de `SContenido` (si destruye su
`SBloque`) y la del propio `SBloque` (si ese bloque libera sus bytes).

## API

### Construcción y destrucción

| Función                                                                  | Descripción                       |
| ------------------------------------------------------------------------ | --------------------------------- |
| `SContenido * SConCrear ( int iTam )`                                    | Contenido propio de `iTam` bytes. |
| `SContenido * SConCrearEntero ()`                                        | Del tamaño de un `int`.           |
| `SContenido * SConCrearEnteroLargo ()`                                   | Del tamaño de un `long`.          |
| `SContenido * SConCrearReal ()`                                          | Del tamaño de un `float`.         |
| `SContenido * SConCrearRealDoble ()`                                     | Del tamaño de un `double`.        |
| `SContenido * SConCrearCadena ()`                                        | Para una cadena.                  |
| `SContenido * SConEncapsular ( SBloque * )`                              | Envuelve un bloque existente.     |
| `SContenido * SConEncapsularDir ( byte *, int iTamDatos, int iLiberar )` | Envuelve memoria cruda.           |
| `SContenido * SConDuplicar ( SContenido * )`                             | Copia independiente.              |
| `void SConDestruir ( SContenido ** )`                                    | Destruye y anula el puntero.      |

### Consulta

| Función                                              | Descripción                   |
| ---------------------------------------------------- | ----------------------------- |
| `int SConEsValido ( SContenido * )`                  | 1 si es utilizable.           |
| `SBloque * SConDatos ( SContenido * )`               | Bloque interno (no destruir). |
| `int SConTieneDatos ( SContenido * )`                | 1 si hay contenido.           |
| `int SConLiberacionMemoriaActivada ( SContenido * )` | Valor de `iLiberar`.          |

### Lectura y escritura tipadas

Lectura: `SConEntero`, `SConEnteroLargo`, `SConReal`, `SConRealDoble`,
`SConCadena`.

Escritura: `SConEscribirEntero`, `SConEscribirEnteroLargo`, `SConEscribirReal`,
`SConEscribirRealDoble`, `SConEscribirCadena` y
`SConEscribirByte ( SContenido *, int iPos, byte )`.

### Modificación

| Función                                                                      | Descripción                  |
| ---------------------------------------------------------------------------- | ---------------------------- |
| `int SConModificar ( SContenido *, SBloque * )`                              | Sustituye el bloque interno. |
| `int SConModificarDir ( SContenido *, byte *, int iTamDatos, int iLiberar )` | Sustituye por memoria cruda. |

## Comportamiento

### Propiedad

`SConDestruir` destruye el `SBloque` interno **sólo si `iLiberar` vale 1**; en
otro caso libera únicamente la estructura y el bloque queda vivo a cargo de
quien lo creó.

| Constructor                         | `iLiberar`     | Al destruir                            |
| ----------------------------------- | -------------- | -------------------------------------- |
| `SConCrear` y variantes tipadas     | 1              | Destruye el bloque interno             |
| `SConEncapsular`                    | según el caso  | Ver la implementación antes de confiar |
| `SConEncapsularDir ( …, iLiberar )` | el que se pase | Respeta lo indicado                    |

Es el mismo esquema que en [SElemento](SElemento.md), y conviene tratarlo igual:
si se encapsula algo que se va a seguir usando fuera, pasar `iLiberar` a 0.

### Comparación con módulos vecinos

| Módulo                    | Qué añade sobre el anterior                       |
| ------------------------- | ------------------------------------------------- |
| [SBloque](SBloque.md)     | Bytes + tamaño + propiedad                        |
| `SContenido`              | Propiedad de segundo nivel sobre el bloque        |
| [SElemento](SElemento.md) | Lo de `SContenido` más enlaces anterior/siguiente |

## Dependencias

- [SBloque](SBloque.md) — todo el almacenamiento y la lectura/escritura tipada.

## Test

`SContenidoTest.c` → `TestSContenido()`.

## Observaciones

- **La doble bandera de propiedad es fácil de confundir.** Un `SContenido` con
  `iLiberar = 1` que envuelve un `SBloque` con `iLiberar = 0` destruye la
  estructura del bloque pero no sus bytes; la combinación inversa deja el bloque
  vivo. Al encapsular conviene decidir explícitamente las dos.
- `SConActivarLiberacionMemoria` y `SConDesactivarLiberacionMemoria` están
  **declaradas y comentadas** en la cabecera: no se puede cambiar la bandera
  después de construir, sólo consultarla con
  `SConLiberacionMemoriaActivada`.
- La API de lectura tipada es más corta que la de [SBloque](SBloque.md): no hay
  variantes sin signo (`SConEnteroSinSigno` y compañía no existen), aunque
  `SElemento` sí las tiene. Para esos tipos hay que bajar al bloque con
  `SConDatos`.
