# SDatosTexto

| Dato         | Valor                                       |
| ------------ | ------------------------------------------- |
| Cabecera     | `src/main/include/SDatosTexto.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SDatosTexto.c` |
| Prefijo      | `SDatTxt`                                   |
| Struct       | `SDatosTexto`                               |
| Funciones    | 43                                          |
| Incluido por | `TiposDatos.h`                              |
| Test         | `SDatosTextoTest.c` → `TestSDatosTexto()`   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **búfer de texto en el que se escribe secuencialmente**: se van añadiendo
cadenas, caracteres y saltos de línea, y el búfer lleva la cuenta de dónde va.

Es lo que hace falta para componer un informe, una consulta o un mensaje largo
sin concatenar cadenas a mano.

```c
typedef struct
{
    SDatos * p_datTexto;
    int      iTamFijo;
    int      iPos;
    int      iPrimerLibre;
} SDatosTexto;
```

Se apoya en [SDatos](../../gjs-c-common-base-types/doc/SDatos.md) y añade
posición de escritura y la noción de **tamaño fijo**.

## API

### Ciclo de vida

| Función                                   | Descripción                     |
| ----------------------------------------- | ------------------------------- |
| `SDatosTexto * SDatTxtCrearDef ()`        | Búfer con tamaño por defecto.   |
| `SDatosTexto * SDatTxtCrear ( … )`        | Con tamaño dado.                |
| `SDatosTexto * SDatTxtEncapsular ( … )`   | Envuelve un `SDatos` existente. |
| `SDatosTexto * SDatTxtDuplicar ( … )`     | Copia independiente.            |
| `void SDatTxtDestruir ( SDatosTexto ** )` | Destruye y anula el puntero.    |
| `SDatTxtLimpiar` / `SDatTxtLiberar`       | Vaciar y liberar.               |

### Escritura

Es el grupo característico del módulo:

| Función                     | Escribe                                               |
| --------------------------- | ----------------------------------------------------- |
| `SDatTxtEscribir`           | Una [SCadena](../../gjs-c-common-text/doc/SCadena.md) |
| `SDatTxtEscribirLit`        | Un literal `const char *`                             |
| `SDatTxtEscribirCar`        | Un carácter                                           |
| `SDatTxtEscribirEspacio`    | Un espacio                                            |
| `SDatTxtEscribirEspacios`   | Varios espacios                                       |
| `SDatTxtEscribirSaltoLinea` | Un salto de línea                                     |
| `SDatTxtEscribirLinea`      | Una cadena y salto de línea                           |
| `SDatTxtEscribirLineaLit`   | Ídem con literal                                      |

`EscribirEspacios` y `EscribirLinea` son los atajos que hacen cómodo el
formateo tabulado.

### Posición

| Función                                  | Descripción                   |
| ---------------------------------------- | ----------------------------- |
| `SDatTxtPosicion`                        | Posición actual de escritura. |
| `SDatTxtPosicionar ( …, int )`           | Mueve a una posición.         |
| `SDatTxtPosicionarEnInicio` / `…EnFinal` | Extremos.                     |

### Tamaño fijo

| Función                               | Descripción                                            |
| ------------------------------------- | ------------------------------------------------------ |
| `SDatTxtActivarTamFijo`               | El búfer deja de crecer.                               |
| `SDatTxtDesactivarTamFijo`            | Vuelve a crecer bajo demanda.                          |
| `SDatTxtEsDeTamFijo`                  | Estado.                                                |
| `SDatTxtEstaLleno`                    | 1 si no cabe más (sólo tiene sentido con tamaño fijo). |
| `SDatTxtEstablecerTam` / `SDatTxtTam` | Tamaño.                                                |

Con tamaño fijo el búfer se comporta como un campo de anchura acotada; sin él,
crece.

### Lectura

`SDatTxtContenido`, `SDatTxtContenidoValor`, `SDatTxtDuplicarContenidoValor`,
`SDatTxtDuplicarDatos`, `SDatTxtDatos`, `SDatTxtCaracter`,
`SDatTxtEstablecerCaracter`, `SDatTxtLinea`, `SDatTxtNumLineas`,
`SDatTxtLongitud`, `SDatTxtEstaVacio`, `SDatTxtImprimir`.

`SDatTxtNumLineas` y `SDatTxtLinea` permiten releer lo escrito línea a línea.

### Asignación

`SDatTxtAsignar`, `SDatTxtAsignarDat`, `SDatTxtAsignarContenido`,
`SDatTxtAsignarContenidoLit`, `SDatTxtAsignarContenidoEnPos`,
`SDatTxtAsignarContenidoEnPosLit`.

## Dependencias

- [SDatos](../../gjs-c-common-base-types/doc/SDatos.md) — el almacenamiento.
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — las variantes sin `Lit`.

## Test

`SDatosTextoTest.c` → `TestSDatosTexto()`.

## Observaciones

- **Se solapa con [STexto](../../gjs-c-common-text/doc/STexto.md)** de
  `gjs-c-common-text`, que también representa texto multilínea con posición.
  La diferencia es el enfoque: `STexto` es un documento **editable** con cursor
  bidimensional y lista de líneas; `SDatosTexto` es un búfer de **escritura
  secuencial** sobre memoria contigua. Elegir mal lleva a echar en falta la mitad
  de la API.
- **`SDatTxtEncapsular` no dice si se queda con el `SDatos`** que recibe. En
  [Entidades](../../gjs-c-common-database/doc/Entidades.md) ese mismo verbo significa tomar posesión, y en
  [SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md) el equivalente
  destruye lo que recibe; conviene comprobarlo antes de reutilizar el objeto.
- Las funciones de escritura devuelven `int`, pero la cabecera no aclara si es
  "se pudo escribir" o el número de caracteres escritos, que es la información
  que hace falta con el tamaño fijo activado.
- `SDatTxtPosicionar` permite mover la posición de escritura a cualquier punto,
  lo que convierte el búfer en algo entre secuencial y de acceso aleatorio sin
  que quede claro qué ocurre al escribir en medio: si sobrescribe o desplaza.
- La estructura tiene `iPos` e `iPrimerLibre` como campos distintos, lo que
  sugiere que la posición de escritura y el final del contenido se llevan por
  separado; la API expone `SDatTxtPosicion` y `SDatTxtLongitud`, pero no explica
  la relación entre ambos.
