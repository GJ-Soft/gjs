# NivelesLog

| Dato         | Valor                                                  |
| ------------ | ------------------------------------------------------ |
| Cabecera     | `src/main/include/NivelesLog.h` (21 líneas)            |
| Fuente       | `src/main/c/org/gjs/c/common/NivelesLog.c` (36 líneas) |
| Prefijo      | `NivelLog`                                             |
| Funciones    | 2                                                      |
| Incluido por | `CommonLog.h`                                          |
| Test         | `NivelesLogTest.c` → `TestNivelesLog()`                |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo de niveles de registro y sus dos validadores. Es el módulo más
pequeño del stack C con implementación: 36 líneas para dos funciones.

## Los niveles

| Constante               | Valor | Anotable | Establecible |
| ----------------------- | ----- | -------- | ------------ |
| `LOG_NIVEL_NINGUNO`     | -1    | —        | ✔            |
| `LOG_NIVEL_DEPURACION`  | 0     | —        | —            |
| `LOG_NIVEL_INFORMACION` | 1     | ✔        | ✔            |
| `LOG_NIVEL_AVISO`       | 2     | ✔        | ✔            |
| `LOG_NIVEL_ERROR`       | 3     | ✔        | ✔            |
| `LOG_NIVEL_FORZADO`     | 100   | ✔        | ✔            |

Y tres derivadas:

| Constante           | Vale                        |
| ------------------- | --------------------------- |
| `LOG_NIVEL_DEFECTO` | `LOG_NIVEL_ERROR` (3)       |
| `LOG_NIVEL_MIN`     | `LOG_NIVEL_INFORMACION` (1) |
| `LOG_NIVEL_MAX`     | `LOG_NIVEL_FORZADO` (100)   |

## API

| Función                                     | Devuelve 1 si…                                 |
| ------------------------------------------- | ---------------------------------------------- |
| `int NivelLogEsValido ( int iNivel )`       | Está entre `MIN` y `MAX`, es decir de 1 a 100. |
| `int NivelLogEsEstablecible ( int iNivel )` | Lo anterior, **o** es `LOG_NIVEL_NINGUNO`.     |

La distinción es la razón de ser del módulo:

- **Válido** = se puede *anotar* un mensaje con ese nivel. Lo comprueba
  `SLogAnotarNivelLit` antes de escribir.
- **Establecible** = se puede fijar como umbral del log. Añade
  `LOG_NIVEL_NINGUNO`, que como umbral significa "no anotes nada" y como nivel
  de mensaje no tiene sentido.

```c
SLogEstablecerNivel ( p_logObj, LOG_NIVEL_NINGUNO );   /* silencia el log */
SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_NINGUNO, … ); /* se descarta */
```

## El salto de 3 a 100

`LOG_NIVEL_FORZADO` no es "más grave que error": es un nivel aparte, que
[SLog](SLog.md) trata como caso especial. Un mensaje forzado se escribe
**cualquiera que sea el umbral** —incluso con el log en `NINGUNO`— y sale sin
marca de tipo. Es lo que usa la rotación de fichero para dejar sus dos líneas de
continuidad.

El hueco de 4 a 99 deja sitio para niveles intermedios sin renumerar, igual que
hacen los rangos de
[Procesadores.h](../../gjs-c-common-system/doc/Catalogos.md).

## Dependencias

Ninguna: la cabecera no incluye nada y el fuente sólo se incluye a sí mismo.

## Test

`NivelesLogTest.c` → `TestNivelesLog()`.

## Observaciones

- **`LOG_NIVEL_DEPURACION` no es válido ni establecible.** Vale 0, y `MIN` es 1,
  así que `NivelLogEsValido ( LOG_NIVEL_DEPURACION )` devuelve 0. Como
  `SLogAnotarNivelLit` exige que el nivel sea válido para escribir,
  **`SLogAnotarDepuracion` y `SLogAnotarDepuracionLit` no anotan nunca**: las dos
  funciones existen, están declaradas, implementadas y probadas, y su mensaje se
  descarta siempre.

  Se arregla poniendo `LOG_NIVEL_MIN` a `LOG_NIVEL_DEPURACION`. Que el nivel
  esté por debajo del mínimo parece deliberado —para que la depuración no se
  active por descuido—, pero el efecto es que no hay forma de activarla.
- **`_LogTxtNivelMensaje` tampoco conoce la depuración**, y devolvería `""` si
  llegara a ella. Los dos módulos coinciden en dejarla fuera.
- **Los valores chocan con los de `Log.h`.** Esa cabecera define
  `LOG_NIVEL_NINGUNO` como 7, `LOG_NIVEL_AVISO` como 4 y `LOG_NIVEL_ERROR` como
  5, entre otras. Mientras `Log.h` siga comentada fuera de la fachada no hay
  conflicto; en cuanto se active, redefinición. Ver
  [Pendientes](Pendientes.md).
- **Las dos funciones aceptan cualquier `int`** y no distinguen "nivel
  desconocido" de "nivel fuera de rango": devuelven 0 en los dos casos, sin
  registrar nada en
  [Errores](../../gjs-c-common-base/doc/Errores.md).
- No hay conversión de nivel a texto ni de texto a nivel, a diferencia de los
  demás catálogos del stack —
  [TiposSistema](../../gjs-c-common-system/doc/Catalogos.md) tiene `TipSisNombre`
  y `TipSisId`—. Los textos `"INFOR"`, `"AVISO"` y `"ERROR"` viven en
  `LogConfig.h`, que no se publica, y sólo los usa `SLog.c`.
