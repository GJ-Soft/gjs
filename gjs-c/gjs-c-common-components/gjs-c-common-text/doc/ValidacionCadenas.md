# ValidacionCadenas

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabecera     | `src/main/include/ValidacionCadenas.h`                      |
| Fuente       | `src/main/c/org/gjs/c/common/ValidacionCadenas.c`           |
| Prefijo      | `Cad` / `SCad`                                              |
| Funciones    | 6                                                           |
| Incluido por | `Texto.h`                                                   |
| Test         | `ValidacionCadenasTest.c` → `TestValidacionCadenas()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Las tres reglas de contenido que usa la familia [SCampo](SCampo.md): qué es un
**código**, qué es un **nombre** y qué es una **descripción**. Cada una viene por
duplicado, sobre `SCadena *` y sobre `const char *`.

Es el único sitio donde están escritas esas reglas. [SCodigo](SCodigo.md),
[SNombre](SNombre.md) y [SDescripcion](SDescripcion.md) no las repiten: le pasan
la función correspondiente a `SCampCrear` y se olvidan.

## API

| Función                                     | Regla                                                       |
| ------------------------------------------- | ----------------------------------------------------------- |
| `int SCadEsCodigoValido ( SCadena * )`      | No vacía, sólo alfanuméricos, empieza por letra.            |
| `int SCadEsNombreValido ( SCadena * )`      | No vacía, sin blancos, imprimible, ASCII, empieza por letra. |
| `int SCadEsDescripcionValida ( SCadena * )` | Sólo caracteres imprimibles.                                |
| `int CadEsCodigoValido ( const char * )`    | Igual, sobre `char *`.                                      |
| `int CadEsNombreValido ( const char * )`    | Igual, sobre `char *`.                                      |
| `int CadEsDescripcionValida ( const char * )` | Igual, sobre `char *`.                                     |

Las seis devuelven `1`/`0` y tratan el puntero nulo como no válido.

### Las tres reglas, en detalle

| Regla        | Longitud > 0 | Blancos | No imprimibles | Fuera de ASCII | Empieza por letra | Signos      |
| ------------ | ------------ | ------- | -------------- | -------------- | ----------------- | ----------- |
| Código       | exigida      | no      | no             | no             | exigido           | sólo `_` `:` |
| Nombre       | exigida      | no      | no             | no             | exigido           | sí          |
| Descripción  | no exigida   | sí      | no             | sí             | no                | sí          |

- **Imprimible** aquí significa código ≥ 32 y distinto de 127, con el
  **tabulador (9) admitido**. El salto de línea no lo es: una descripción es de
  una sola línea. Para varias está [STexto](STexto.md).
- **Alfanumérico** significa `[A-Za-z0-9_:]`, el mismo conjunto que el `[^\w:]`
  del gemelo C++ `gjs-cpp-common-base`. La raya inferior y los dos puntos pasan;
  el guion, el punto y el espacio, no.
- La descripción **no comprueba el juego de caracteres**, así que admite acentos
  y cualquier byte por encima de 127. El código y el nombre no.

```c
if ( CadEsCodigoValido ( "IMP_TOTAL" ) == 1 )    /* 1 */
if ( CadEsCodigoValido ( "1IMPORTE" ) == 1 )     /* 0: empieza por dígito */
if ( CadEsNombreValido ( "importe total" ) == 1 )/* 0: lleva un blanco */
if ( CadEsDescripcionValida ( "" ) == 1 )        /* 1: la vacía vale */
```

## Dependencias

- [SCadena](SCadena.md) y [Cadenas](Cadenas.md) — los predicados
  `…ContieneBlancos`, `…ContieneCaracteresNoImprimibles`,
  `…ContieneCaracteresNoAlfanumericos` y `…ContieneCaracteresNoEstandar`.
- [ASCII](ASCII.md) — `ASCIIEsLetra`, para el primer carácter.

## Test

`ValidacionCadenasTest.c` → `TestValidacionCadenas()`.

## Observaciones

- **La cadena vacía es una descripción válida pero no un nombre ni un código.**
  De ahí que un [SCodigo](SCodigo.md) o un [SNombre](SNombre.md) recién creados
  respondan `0` a `…EsValido`, mientras que una [SDescripcion](SDescripcion.md)
  recién creada responde `1`.
- **Un nombre admite más que un código**, no menos: `importe-total` es un nombre
  válido y no es un código válido, porque el guion no es alfanumérico. Al revés,
  todo código válido es un nombre válido.
- `ASCIIEsLetra` acepta letras acentuadas y nórdicas de la página OEM 850, pero
  eso no llega a abrir la puerta: el `…ContieneCaracteresNoEstandar` del nombre y
  el `…ContieneCaracteresNoAlfanumericos` del código rechazan antes cualquier
  byte por encima de 127.
- El módulo **no tiene cabecera de bloque** con autor y versión, a diferencia del
  resto de la librería.
