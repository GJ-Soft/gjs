# SBloqueMultiPlataforma

| Dato         | Valor                                                              |
| ------------ | ------------------------------------------------------------------ |
| Cabecera     | `src/main/include/SBloqueMultiPlataforma.h`                        |
| Fuente       | `src/main/c/org/gjs/c/common/SBloqueMultiPlataforma.c`             |
| Prefijo      | `SBlqMpl`                                                          |
| Struct       | `SBloqueMultiPlataforma`                                           |
| Funciones    | 87                                                                 |
| Test         | `SBloqueMultiPlataformaTest.c` → `TestSBloqueMultiPlataforma()`    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un [SBloque](SBloque.md) cuyo contenido tipado está en el formato binario de
`TiposMultiPlataforma` (en `gjs-c-common-base`): cada tipo ocupa siempre los
mismos bytes y en el mismo orden (little-endian), así que **lo que se escribe en
una plataforma se lee igual en cualquier otra**. Es el bloque para ficheros y
comunicaciones.

Tiene la misma API que `SBloque`, con el prefijo `SBlqMpl`. La diferencia está
en las lecturas y escrituras tipadas:

| Tipo                       | `SBloque` (formato de la máquina) | `SBloqueMultiPlataforma` |
| -------------------------- | --------------------------------- | ------------------------ |
| `int`, `unsigned int`      | 4                                 | 4                        |
| `long`, `unsigned long`    | 4 en Windows, 8 en Cygwin y Linux | **8 siempre**            |
| `float`                    | 4                                 | 4                        |
| `double`                   | 8                                 | 8                        |
| orden de bytes             | el de la máquina                  | little-endian siempre    |

Que el tipo sea otro (`SBloqueMultiPlataforma *` y no `SBloque *`) impide leer
por error un bloque portable con las funciones del formato de la máquina.

## Estructura

```c
typedef struct
{
	SBloque * p_blqDatos;
} SBloqueMultiPlataforma;
```

El objeto es **dueño** del bloque que envuelve: `SBlqMplDestruir` lo destruye.
`SBlqMplBloque` lo devuelve sin cederlo.

## API

### Creación y destrucción

| Función                                                              | Descripción                                               |
| -------------------------------------------------------------------- | --------------------------------------------------------- |
| `SBlqMplCrear ( int iTam )`                                          | Bloque nuevo de `iTam` bytes a cero.                      |
| `SBlqMplAsignar ( byte *, int iTam, int iLiberar )`                  | Envuelve memoria existente, como `SBlqAsignar`.           |
| `SBlqMplEncapsular ( SBloque * )`                                    | Envuelve un bloque y pasa a ser su dueño.                 |
| `SBlqMplCrearEntero`, `…EnteroLargo`, `…EnteroSinSigno`, `…EnteroLargoSinSigno`, `…Real`, `…RealDoble` | Bloque justo del tamaño del tipo: 4, 8, 4, 8, 4 y 8. |
| `SBlqMplCrearCadena ( const char * )`                                | Bloque de la medida de la cadena con su nulo, con ella escrita. |
| `SBlqMplDestruir ( SBloqueMultiPlataforma ** )`                      | Destruye el objeto y su bloque, y deja el puntero a NULL. |

### Valor del bloque entero

`SBlqMplEntero`, `SBlqMplEnteroLargo`, `SBlqMplEnteroSinSigno`,
`SBlqMplEnteroLargoSinSigno`, `SBlqMplReal`, `SBlqMplRealDoble` leen y
`SBlqMplEscribirEntero` … `SBlqMplEscribirRealDoble` escriben el valor que
ocupa **todo** el bloque. El bloque tiene que medir **exactamente** lo que el
tipo: si no, la lectura devuelve 0 con `ERR_LECTURA_MEMORIA` y la escritura
devuelve 0.

`SBlqMplCadena` lee la cadena del principio del bloque (nueva, del llamante) y
`SBlqMplEscribirCadena` la escribe allí con su nulo, si cabe entera.

### En posición y secuencial

| Lectura                                  | Escritura                                  |
| ---------------------------------------- | ------------------------------------------ |
| `SBlqMplLeerEnteroEnPos ( obj, iPos )`   | `SBlqMplEscribirEnteroEnPos ( obj, iPos, v )` |
| `SBlqMplLeerEnteroLargoEnPos`            | `SBlqMplEscribirEnteroLargoEnPos`          |
| `SBlqMplLeerEnteroSinSignoEnPos`         | `SBlqMplEscribirEnteroSinSignoEnPos`       |
| `SBlqMplLeerEnteroLargoSinSignoEnPos`    | `SBlqMplEscribirEnteroLargoSinSignoEnPos`  |
| `SBlqMplLeerRealEnPos`                   | `SBlqMplEscribirRealEnPos`                 |
| `SBlqMplLeerRealDobleEnPos`              | `SBlqMplEscribirRealDobleEnPos`            |
| `SBlqMplLeerCadenaEnPos`                 | `SBlqMplEscribirCadenaEnPos`               |

Cada una tiene su `…Ext`, que toma la posición por puntero y la deja detrás de
lo leído o escrito:

```c
int iPos = 0;
SBlqMplEscribirEnteroEnPosExt ( p_blqObj, &iPos, 42 );          /* iPos = 4 */
SBlqMplEscribirEnteroLargoEnPosExt ( p_blqObj, &iPos, -7L );    /* iPos = 12, en Windows también */
SBlqMplEscribirCadenaEnPosExt ( p_blqObj, &iPos, "gjs" );       /* iPos = 16 */
```

### Bytes y operaciones de bloque

Delegan en las de [SBloque](SBloque.md) sin cambiar nada, porque trabajan con
bytes y no con tipos: `SBlqMplTam`, `SBlqMplDatos`, `SBlqMplDuplicarDatos`,
`SBlqMplDatosEnPos`, `SBlqMplEsValido`, `SBlqMplLeerByte`/`EscribirByte` (y sus
`Ext`), `SBlqMplLeerBuffer`/`EscribirBuffer` (y sus `Ext`), `SBlqMplEsIgual`,
`SBlqMplEsIgualBloque`, `SBlqMplEsIgualExt`, `SBlqMplLimpiar`,
`SBlqMplLiberacionMemoriaActivada`, `SBlqMplCopiarDe`, `SBlqMplCopiarEn`,
`SBlqMplCopiar`, `SBlqMplCopiarBloque`, `SBlqMplDuplicar`,
`SBlqMplEsCompatible`, `SBlqMplEsCompatibleBloque`, `SBlqMplTamCompatible`,
`SBlqMplVolcar`, `SBlqMplVolcarBloque`, `SBlqMplExtraer` (y sus `Ext`),
`SBlqMplHash` y `SBlqMplBloque`.

Las que reciben un `SBloque *` (`…Bloque`) permiten mezclar con bloques
normales; las que crean uno nuevo (`SBlqMplDuplicar`, `SBlqMplExtraer`)
devuelven un `SBloqueMultiPlataforma`.

## Comportamiento

- **Todo o nada.** Lo leído o escrito tiene que caber entero entre la posición y
  el final del bloque. Si no cabe, la posición es negativa o el bloque es nulo,
  la lectura devuelve 0 y anota `ERR_LECTURA_MEMORIA`, y la escritura devuelve
  0 sin escribir nada. Un 0 leído de verdad no anota nada.
- **Las `…Ext` sólo avanzan si los bytes estaban en el bloque.** Si no, dejan
  la posición como estaba; sin posición (`NULL`) no hacen nada.
- **`long` en Windows.** Se guarda en 8 bytes; al leer en Windows un valor que no
  cabe en 32 bits se devuelve 0 con `ERR_CONVERSION_IMPOSIBLE`, y las `…Ext`
  **no avanzan**, como en cualquier lectura que falla. Así quien lee sabe que ha
  fallado mirando la posición, sin confundirlo con un 0 de verdad.
- **Cadenas.** Se escriben con su nulo y se leen hasta él, que tiene que estar
  dentro del bloque; la leída es nueva y la libera el llamante con
  `MemLiberarCadena`. Los caracteres van tal cual: el formato no fija la
  codificación.
- **Errores al crear.** Si no se puede reservar el objeto, el bloque que se
  acababa de crear (`SBlqMplCrear`, `SBlqMplDuplicar`, `SBlqMplExtraer`…) se
  destruye; no se pierde memoria.

## Dependencias

- [SBloque](SBloque.md), al que envuelve.
- `TiposMultiPlataforma` de `gjs-c-common-base`, para el formato.

## Test

`SBloqueMultiPlataformaTest.c` comprueba, contra bytes fijos:

- los tamaños de los bloques de cada tipo (el de `long`, 8 también en Windows) y
  la cadena con su nulo;
- el valor del bloque entero de cada tipo, y que un bloque de otro tamaño no
  sirve;
- la escritura y lectura en posiciones sin alinear, el último valor que cabe y
  el primero que no, la posición negativa e `INT_MAX`, y que leer un 0 no es un
  error;
- la escritura y lectura secuencial de siete campos, con la posición exacta tras
  cada uno, el bloque lleno y la posición nula;
- un `long` y un `unsigned long` de 2^32: bien con `long` de 8 bytes, y en
  Windows `ERR_CONVERSION_IMPOSIBLE` sin mover la posición;
- duplicar, extraer, encapsular, el hash y los nulos.
