# gjs-c-common-support

Librería de **soporte de aplicación** en C del stack GJS: lo que necesita un
programa para presentarse al usuario y guardar su configuración.

Identidad y versión de la aplicación, consola con marcos y cuadros de diálogo,
fichero de propiedades, validación de códigos de usuario y portapapeles.

10 módulos en 2.776 líneas. Es el primer componente del stack que **habla con el
usuario** en lugar de con el sistema o con los datos.

---

## Coordenadas Maven

| Dato         | Valor                                                                                                                              |
| ------------ | ---------------------------------------------------------------------------------------------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                                                                                                                 |
| `artifactId` | `gjs-c-common-support`                                                                                                             |
| `version`    | `1.0.0`                                                                                                                       |
| `packaging`  | `nar` (biblioteca **shared**)                                                                                                      |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`                                                                                                       |
| Depende de   | `gjs-c-common-base`, `gjs-c-common-base-types`, `gjs-c-common-text`, `gjs-c-common-time`, `gjs-c-common-io`, `gjs-c-common-system` |

---

## Uso

La cabecera fachada es `Aplicacion.h`:

```c
#include <Base.h>
#include <Aplicacion.h>

AplicInicializar ( "MiPrograma", 1, 0, 3, 20260802, 1 );
AplicImprimirInfoVersion ();

if ( CajMsjMostrar ( TIP_CAJ_MSJ_PREGUNTA, "Salir", "¿Seguro?" ) == CAJ_MSJ_RES_SI )
{
    AplicFinalizar ();
}
```

El último parámetro de `AplicInicializar` dice si la aplicación es de consola,
que es lo que decide cómo se presentan luego los mensajes.

---

## Los dos modos de presentación

Todo el componente se apoya en una decisión: **si hay ventanas, se usan; si no,
se dibuja en la consola**. A diferencia de
[gjs-c-common-system](../gjs-c-common-system/README.md), aquí las dos ramas
están implementadas de verdad.

| Módulo                   | En Windows                        | Fuera de Windows                         |
| ------------------------ | --------------------------------- | ---------------------------------------- |
| `CajaMensajes`           | `MessageBox` con iconos y botones | Marco dibujado en la consola y `getchar` |
| `AplicacionConsola`      | `GetConsoleScreenBufferInfo`      | `ioctl ( TIOCGWINSZ )`                   |
| `AplicacionPortapapeles` | API del portapapeles              | **No existe**                            |

Los marcos se dibujan con caracteres de dibujo Unicode
(`┌ ─ ┐ │ └ ┘ ╔ ═ ╗ ║ ╚ ╝`) o con los códigos de la página 850, según esté
definido `CON_BORDES_UNICODE` en `AplicacionConfig.h`.

---

## Convenios

Los del stack. Prefijos: `Aplic` (información e inicialización), `AplicCon`
(consola), `AplicPples` (portapapeles), `CajMsj`, `TipCajMsj`, `SVer`, `SProp`,
`FicTxt`.

### Límites

| Constante                 | Valor | Qué acota                    |
| ------------------------- | ----- | ---------------------------- |
| `APL_MIN_TAM_COD_USUARIO` | 4     | Código de usuario, mínimo    |
| `APL_MAX_TAM_COD_USUARIO` | 30    | Código de usuario, máximo    |
| `APL_MAX_TAM_CLV_USUARIO` | 30    | Clave de usuario             |
| `CON_MAX_TAM_CADENA`      | 255   | Lectura de consola           |
| `CON_ANCHO_DEFECTO`       | 80    | Ancho cuando no hay terminal |

Están en `AplicacionConfig.h`, que vive en el árbol de fuentes y no se publica.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
los seis componentes anteriores del stack.

---

## Tests

**8 suites**. Sin test: `SimulacionUsuarioConsola` y `UtilidadesFicheros`, que
son precisamente los dos módulos de apoyo a las pruebas.

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, 8/8 suites en OK.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`RespuestasCajaMensajes.h` no la incluye nadie**, ni siquiera
  `CajaMensajes.h`, pese a que `CajMsjMostrar` devuelve una de sus constantes.
  Además sus valores **cambian entre Windows y POSIX**. Ver
  [CajaMensajes](doc/CajaMensajes.md).
- **`SPropiedades` pierde memoria en tres sitios**: el `SFicTexto` de
  `SPropCargar` y el de `SPropGuardar` no se destruyen, y `_ParsearPropiedad`
  sobrescribe el valor entrecomillado sin liberar el anterior. Ver
  [SPropiedades](doc/SPropiedades.md).
- **`SimulacionUsuarioConsola` y `UtilidadesFicheros` son utilidades de prueba
  publicadas en la librería de producción**, y entran por la fachada:
  `SimularEntradaConsola` redirige `stdin` del proceso. Ver
  [Pruebas](doc/Pruebas.md).
- El guardián de `Aplicacion.h` es `_ORG_GJS_C_CC_APLICION_H`, sin las letras
  `AC`. Es coherente consigo mismo, así que no rompe nada.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
