# SLog

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/SLog.h` (137 líneas)              |
| Fuente       | `src/main/c/org/gjs/c/common/SLog.c` (1.195 líneas) |
| Prefijo      | `SLog`                                              |
| Struct       | `SLog`                                              |
| Funciones    | 80                                                  |
| Incluido por | `CommonLog.h`                                       |
| Test         | `SLogTest.c` → `TestSLog()`                         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El log de la aplicación. Es el componente entero: el otro módulo con código son
dos funciones de validación de niveles.

```c
typedef struct
{
    SCadena *     p_cadNomProceso;
    SFicTexto *   p_ficLog;
    SFechaHora *  p_fechLog;

    int           iEncabezado;
    int           iPantalla;
    int           iSalida;
    int           iNivel;
    int           iIniciado;
    int           iHoraEnNombre;
    int           iHoraAlInicioNombre;
    char          cSepHoraNombre;
    int           iPIDEnNombre;
    int           iAnotarTipoMensaje;
    int           iPartirLinea;

    unsigned long ulNumLineas;
} SLog;
```

Ocho de los quince campos son interruptores. Es un objeto muy configurable: se
decide qué lleva cada línea, qué lleva el nombre del fichero y a dónde va la
salida.

## API

### Construcción

| Función                                                    | Descripción                               |
| ---------------------------------------------------------- | ----------------------------------------- |
| `SLog * SLogCrearDef ()`                                   | Nombre `"aplicacion"`, directorio actual. |
| `SLogCrearDirLit ( p_cDir )` / `SLogCrearDir ( p_cadDir )` | Sólo directorio.                          |
| `SLogCrearLit ( p_cDir, p_cFic )` / `SLogCrear ( … )`      | Directorio y fichero.                     |
| `SLogCrearRutaLit ( p_cRuta )` / `SLogCrearRuta ( … )`     | Ruta completa.                            |
| `void SLogDestruir ( SLog ** )`                            | Destrucción.                              |
| `int SLogEsValido ( SLog * )`                              | Estado.                                   |

Siete constructores, cada uno con su variante `Lit` para `const char *` y su
variante para [SCadena](../../gjs-c-common-text/doc/SCadena.md).

### Arranque

| Función                                        | Descripción                                      |
| ---------------------------------------------- | ------------------------------------------------ |
| `void SLogIniciar ( SLog * )`                  | Abre el fichero y escribe la cabecera de bloque. |
| `SLogIniciarDirLit` / `SLogIniciarDir`         | Iniciando en otro directorio.                    |
| `SLogIniciarRutaLitExt` / `SLogIniciarRutaExt` | Con directorio y fichero.                        |
| `SLogIniciarRutaLit` / `SLogIniciarRuta`       | Con ruta completa.                               |
| `void SLogFinalizar ( SLog * )`                | Cierra el bloque.                                |
| `int SLogEstaIniciado ( SLog * )`              | Estado.                                          |

### Salidas

| Función                                                         | Descripción |
| --------------------------------------------------------------- | ----------- |
| `SLogActivarSalida` / `…Desactivar…` / `SLogSalidaActivada`     | El fichero. |
| `SLogActivarPantalla` / `…Desactivar…` / `SLogPantallaActivada` | La consola. |

**Las dos empiezan desactivadas.** `SLogInicializar` pone `iSalida` e
`iPantalla` a 0, así que un log recién creado no escribe en ninguna parte
aunque se le llame a `SLogIniciar`.

### Nivel

| Función                                           | Descripción      |
| ------------------------------------------------- | ---------------- |
| `int SLogNivel ( SLog * )`                        | El nivel actual. |
| `void SLogEstablecerNivel ( SLog *, int iNivel )` | Lo cambia.       |

Por defecto `LOG_NIVEL_ERROR`. Ver [NivelesLog](NivelesLog.md).

### Nombre del fichero

| Función                                                             | Descripción                             |
| ------------------------------------------------------------------- | --------------------------------------- |
| `SLogFichero` / `SLogDirectorioFichero` / `SLogRutaFichero`         | Consulta.                               |
| `SLogEstablecerFichero…` / `…Directorio…` / `…Ruta…`                | Cambio, en variantes `Lit` y `SCadena`. |
| `SLogActivarHoraEnNombre` / `…Desactivar…` / `…Activada`            | La fecha-hora.                          |
| `SLogPonerHoraEnNombreAlInicio` / `…AlFinal`                        | Dónde va.                               |
| `SLogApareceHoraEnNombreAlInicio` / `…AlFinal`                      | Dónde está.                             |
| `SLogSeparadorHoraEnNombre` / `SLogEstablecerSeparadorHoraEnNombre` | El carácter separador.                  |
| `SLogActivarPIDEnNombre` / `…Desactivar…` / `…Activado`             | El PID.                                 |
| `SLogEliminar ( SLog * )`                                           | Borra el fichero.                       |

### Formato de línea

| Función                                                                  | Descripción                     |
| ------------------------------------------------------------------------ | ------------------------------- |
| `SLogActivarEncabezadoLinea` / `…Desactivar…` / `…Activado`              | El proceso y la hora iniciales. |
| `SLogActivarAnotacionTipoMensaje` / `…Desactivar…` / `…Activada`         | El `ERROR: `                    |
| `SLogActivarParticionLinea` / `…Desactivar…` / `…Activada`               | Partir líneas largas.           |
| `SLogNombreProceso` / `SLogEstNombreProcesoLit` / `SLogEstNombreProceso` | El nombre del proceso.          |

### Anotación

| Función                                      | Nivel                                                                                |
| -------------------------------------------- | ------------------------------------------------------------------------------------ |
| `SLogAnotar` / `SLogAnotarLit`               | El del log.                                                                          |
| `SLogAnotarNivel` / `SLogAnotarNivelLit`     | El que se le pase.                                                                   |
| `SLogAnotarDepuracion` / `…Lit`              | `LOG_NIVEL_DEPURACION`                                                               |
| `SLogAnotarAviso` / `…Lit`                   | `LOG_NIVEL_AVISO`                                                                    |
| `SLogAnotarError` / `…Lit`                   | `LOG_NIVEL_ERROR`                                                                    |
| `SLogAnotarForzado` / `SLogAnotarLitForzado` | `LOG_NIVEL_FORZADO`, siempre.                                                        |
| `SLogAnotarSaltoLinea`                       | Una línea en blanco.                                                                 |
| `SLogAnotar…ConFormato`                      | Cinco variantes variádicas.                                                          |
| `SLogAnotarPilaErrores`                      | Vuelca la pila de [SistemaErrores](../../gjs-c-common-system/doc/SistemaErrores.md). |
| `SLogAnotarErrorSistema`                     | El último error del sistema.                                                         |

`SLogAnotarPilaErrores` es la función que justifica que el componente dependa de
`gjs-c-common-system`: enlaza la traza de errores del sistema con el log.

### Rotación

No hay API: es automática. `SLogGestionarCambioFichero` se llama tras cada
escritura y, al llegar a `LOG_MAX_LINEAS` (30.000), anota *"(Continua en el
fichero siguiente)."*, finaliza, genera un nombre nuevo, reinicia y anota
*"(Continuacion del fichero anterior)."*.

## Dependencias

- [SFicTexto](../../gjs-c-common-io/doc/FicherosBasicos.md) — el fichero.
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — la composición de líneas.
- [SFechaHora](../../gjs-c-common-time/doc/SFechaHora.md) — la marca de tiempo.
- [SistemaErrores](../../gjs-c-common-system/doc/SistemaErrores.md) — la pila.

## Test

`SLogTest.c` → `TestSLog()`. Comprueba el estado por defecto y busca líneas
concretas en el fichero generado. **No prueba mensajes largos.**

## Observaciones

### Corregido el 2026-08-02: el bucle de partición

Hasta esta fecha, **un mensaje que no cupiera en la línea colgaba el proceso y
llenaba el disco**. El bucle `while ( iFinal == 0 )` calculaba mal el recorte:

```c
SCadEliminarUltimosCaracteres ( p_cadTexto, iTamPar - SCadLongitud ( p_cadTexto ) - 3 );
```

En esa rama se cumple `iTamPar <= SCadLongitud ( p_cadTexto )`, así que el
número de caracteres a eliminar era **negativo**;
`CadEliminarCaracteresExt` rechazaba la posición resultante y no eliminaba nada.
El texto no menguaba, la condición de salida no llegaba nunca y el bucle volvía
a empezar, abriendo y escribiendo el fichero en cada vuelta: **7,7 MB de la
misma línea en 10 segundos**, medidos.

La corrección restablece la invariante que faltaba —*cada vuelta vacía el texto
o le quita al menos un carácter*— y de paso **conecta `iPartirLinea`**, que no
consultaba nadie:

```c
if ( iTamPar <= 0 )                                   /* el encabezado llena la linea */
{
    SCadLimpiar ( p_cadTexto );
}
else if ( SCadLongitud ( p_cadTexto ) <= iTamPar )    /* cabe entero */
{
    SCadConcatenar ( p_cadLinea, p_cadTexto );
    SCadLimpiar ( p_cadTexto );
}
else if ( SLogParticionLineaActivada ( p_logObj ) == 1 )
{
    p_cadTrozo = SCadExtraerPrimeros ( p_cadTexto, iTamPar );
    SCadConcatenar ( p_cadLinea, p_cadTrozo );
    SCadDestruir ( &p_cadTrozo );
    SCadEliminarPrimerosCaracteres ( p_cadTexto, iTamPar );   /* del PRINCIPIO */
}
else                                                  /* trunca con "..." */
{
    iTamUtil = ( iTamPar > 3 ) ? ( iTamPar - 3 ) : 0;
    …
    SCadConcatenarLiteral ( p_cadLinea, "..." );
    SCadLimpiar ( p_cadTexto );
}
```

Se añadió además un tope de `LOG_MAX_LINEAS_MENSAJE` (100) líneas por mensaje,
que corta con `"(mensaje truncado: demasiadas lineas)"`.

Verificado sobre la librería recompilada, con `timeout` para que un fallo de
avance saliera como cuelgue:

| Caso                 | Líneas | Resultado                        |
| -------------------- | ------ | -------------------------------- |
| 10 caracteres        | 1      | Sale entero                      |
| 470 caracteres       | 1      | Sale entero                      |
| 600, sin partición   | 1      | Truncado, termina en `...`       |
| 600, con partición   | 2      | **600 caracteres recuperados**   |
| 4.000, con partición | 9      | **4.000 caracteres recuperados** |

Ni pérdida ni duplicación de caracteres, y ningún caso agota el `timeout`. El
tope de líneas se comprobó aparte, bajándolo temporalmente a 3.

> **El tope de mensaje no puede dispararse hoy**, y conviene saber por qué:
> `CadLongitud` corta en `CAD_BASE_MAX_TAM` = 8.191 caracteres, de modo que
> `SCadGenerar` nunca recibe más y el peor caso son ~18 líneas. Medido: un
> mensaje de 60.000 caracteres se anota como 8.191. Es un límite del stack
> entero, no de este módulo, pero significa que **`SLogAnotar…` trunca en
> silencio a 8.191 caracteres**.

> **`SLogRutaFichero` tiene la condición invertida:**
>
> ```c
> if ( p_logObj->iIniciado == 0 ) { p_cRes = SFicTxtRuta ( p_logObj->p_ficLog ); }
> else                            { p_cRes = NULL; }
> ```
>
> Devuelve la ruta mientras el log **no** está iniciado y `NULL` en cuanto lo
> está, que es justo cuando interesa saber en qué fichero se está escribiendo.
> Comprobado: tras `SLogIniciar` devuelve `NULL` aunque el fichero exista y esté
> recibiendo líneas.

- **El fichero se abre y se cierra en cada línea.** `SFicTxtAbrir` /
  `SFicTxtEscribirLinea` / `SFicTxtCerrar` por anotación. Es robusto —no se
  pierde nada si el proceso muere— y muy caro: tres llamadas al sistema por
  línea de log.
- **No hay protección entre hilos.** Dos hilos anotando a la vez sobre el mismo
  `SLog` se pisan `p_fechLog` y `ulNumLineas`, y pueden intercalar escrituras.
  El stack tiene [mutex](../../gjs-c-common-system/doc/Sincronizacion.md) y este
  módulo no los usa.
- **`iGestionando` de `SLogGestionarCambioFichero` es un `static` local**, no un
  campo del objeto: dos `SLog` distintos comparten la bandera de reentrada.
- **La función se declara `static` y se define sin `static`.** No cambia la
  vinculación —sigue siendo interna— pero es inconsistente con las otras tres
  auxiliares del fichero.
- **`SLogEstablecerSeparadorHoraEnNombre ( SLog *, char _cSep )`** nombra el
  parámetro `_cSep`, con guion bajo inicial y sin la notación del resto del
  stack.
- **`SLog.h` usa `_SLOG_H` como guardián**, sin el prefijo `_ORG_GJS_C_CC_` que
  llevan todas las demás cabeceras. Un `SLog.h` de otra librería en el mismo
  proyecto se anularía con éste.
- **Los mensajes de nivel `DEPURACION` no llevan marca de tipo**:
  `_LogTxtNivelMensaje` sólo conoce `INFORMACION`, `AVISO` y `ERROR`, y devuelve
  `""` para los demás. Una línea de depuración queda indistinguible de una
  forzada.
