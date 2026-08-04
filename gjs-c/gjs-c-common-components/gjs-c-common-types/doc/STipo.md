# STipo

| Dato         | Valor                                 |
| ------------ | ------------------------------------- |
| Cabecera     | `src/main/include/STipo.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/STipo.c` |
| Prefijo      | `STip`                                |
| Struct       | `STipo`                               |
| Funciones    | 23                                    |
| Incluido por | `TiposDatos.h`                        |
| Test         | `STipoTest.c` → `TestSTipo()`         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo de tipos como **objeto**. Envuelve el código `TIP_*` de
[Tipos](../../gjs-c-common-base/doc/Tipos.md) y expone las mismas consultas en
forma de métodos.

```c
typedef struct
{
    int iCodigo;
} STipo;
```

Un solo campo: igual que [SFecha](../../gjs-c-common-time/doc/SFecha.md) en el
módulo de tiempo, el objeto no aporta almacenamiento, sino interfaz.

## API

### Ciclo de vida

| Función                                         | Descripción                  |
| ----------------------------------------------- | ---------------------------- |
| `STipo * STipCrearDef ()`                       | Tipo sin determinar.         |
| `STipo * STipCrear ( int iCodigo )`             | Desde un código `TIP_*`.     |
| `STipo * STipCrearLit ( const char * p_cTipo )` | Desde el nombre del tipo.    |
| `void STipDestruir ( STipo ** )`                | Destruye y anula el puntero. |

`STipCrearLit` usa los literales del catálogo (`"Numero"`, `"Cadena"`,
`"Fecha"`…), lo que permite construir un tipo desde configuración en texto.

### Acceso

| Función                                              | Descripción       |
| ---------------------------------------------------- | ----------------- |
| `int STipCodigo ( STipo * )`                         | Código numérico.  |
| `void STipEstablecerCodigo ( STipo *, int iCodigo )` | Cambia el código. |
| `const char * STipLiteral ( STipo * )`               | Nombre del tipo.  |

### Predicados

Los mismos que ofrece [Tipos](../../gjs-c-common-base/doc/Tipos.md) en forma de
función suelta:

| Función                                                               | Cierto para                                     |
| --------------------------------------------------------------------- | ----------------------------------------------- |
| `STipEsValido`                                                        | Cualquier tipo del catálogo salvo `TIP_NINGUNO` |
| `STipEsEstrictamenteValido`                                           | Ídem excluyendo también `TIP_DESCONOCIDO`       |
| `STipEsNinguno` / `STipEsDesconocido`                                 | Los dos especiales                              |
| `STipEsNumero` / `STipEsCadena` / `STipEsBooleano`                    | Tipos básicos                                   |
| `STipEsFecha` / `STipEsBinario` / `STipEsObjeto`                      | Ídem                                            |
| `STipEsNatural` / `STipEsEntero` / `STipEsReal` / `STipEsHexadecimal` | Subtipos numéricos                              |
| `STipEsDeTamVariable`                                                 | 1 si el tipo no tiene tamaño fijo               |
| `STipTam`                                                             | Tamaño en bytes, 0 si variable, −1 si no aplica |

## Dependencias

- [Tipos](../../gjs-c-common-base/doc/Tipos.md) — todo el conocimiento del
  catálogo; este módulo sólo lo envuelve.

## Test

`STipoTest.c` → `TestSTipo()`.

## Observaciones

- **Aporta poco sobre la capa que envuelve.** `Tipos` ya ofrece exactamente los
  mismos predicados sobre un `int`; `STipo` añade el ciclo de vida, la
  construcción desde literal y poco más, a cambio de una reserva de memoria por
  cada tipo.
- **Le faltan predicados que sí tiene `Tipos`**: no hay `STipEsCaracter`,
  `STipEsByte`, `STipEsTiempo`, `STipEsHora` ni `STipEsFechaHora`, todos
  presentes en la capa de valores. La cobertura es de 12 de los 20 predicados.
- `STipEstablecerCodigo` devuelve `void`, así que **no valida**: se le puede
  asignar un código que no esté en el catálogo y el objeto queda inconsistente.
  `STipEsValido` lo detectaría después.
- `STipLiteral` devuelve `NULL` para un código no catalogado, heredando el
  comportamiento de `TipLiteral`.
- El nombre choca con `STipo` del módulo... no hay colisión real, pero el
  prefijo `STip` se parece mucho al `Tip` de la librería base, y ambos operan
  sobre lo mismo.
