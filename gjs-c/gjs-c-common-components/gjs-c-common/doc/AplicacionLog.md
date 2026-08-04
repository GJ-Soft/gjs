# AplicacionLog

| Dato         | Valor                                                      |
| ------------ | ---------------------------------------------------------- |
| Cabecera     | `src/main/include/AplicacionLog.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/AplicacionLog.c` (540 líneas) |
| Prefijo      | `AplicLog`                                                 |
| Funciones    | 29                                                         |
| Incluido por | `CCommon.h`                                                |
| Test         | `AplicacionLogTest.c` → `TestAplicacionLog()`              |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

**El log de la aplicación, sin objeto.** Envuelve un único
[SLog](../../gjs-c-common-log/doc/SLog.md) global para que anotar no requiera
llevar un puntero por todo el programa:

```c
AplicLogInicializar ( EntDirectorioLog (), "miprograma" );
AplicLogAnotar ( "Procesados %d registros en %.2f s", iNum, dTiempo );
AplicLogAnotarError ( "No se pudo abrir %s", p_cRuta );
AplicLogFinalizar ( "Fin de la ejecucion" );
```

Es la diferencia con el componente de abajo: allí se crea y se configura un
objeto; aquí hay uno solo y las funciones son variádicas.

## API

### Arranque

| Función                                                 | Descripción                                |
| ------------------------------------------------------- | ------------------------------------------ |
| `int AplicLogInicializarDef ( p_cFichero )`             | En el directorio por defecto.              |
| `int AplicLogInicializar ( p_cDirectorio, p_cFichero )` | Directorio y fichero.                      |
| `int AplicLogInicializarExt ( … )`                      | Con nivel y las cuatro opciones de nombre. |
| `int AplicLogEstaInicializado ()`                       | Estado.                                    |
| `void AplicLogFinalizar ( const char * p_cMensaje )`    | Anota el mensaje, cierra y destruye.       |
| `void AplicLogEliminar ()`                              | Borra el fichero.                          |

`AplicLogInicializarExt` recibe
`( p_cDirectorio, p_cFichero, iNivel, iActivado, iHorEnNombre, iHoraAlInicioNombre, cSepHoraNombre, iPIDEnNombre )`
y traduce cada bandera a la llamada `SLog…` correspondiente. Es la forma de
dejar configurado el log en una sola línea.

`AplicLogFinalizar` acepta un mensaje de despedida, que se anota sólo si el log
estaba iniciado.

### Anotación

Todas variádicas, con formato tipo `printf`:

| Función                     | Nivel                   |
| --------------------------- | ----------------------- |
| `AplicLogAnotar`            | `LOG_NIVEL_INFORMACION` |
| `AplicLogAnotarAviso`       | `LOG_NIVEL_AVISO`       |
| `AplicLogAnotarError`       | `LOG_NIVEL_ERROR`       |
| `AplicLogAnotarDepuracion`  | `LOG_NIVEL_DEPURACION`  |
| `AplicLogAnotarForzado`     | `LOG_NIVEL_FORZADO`     |
| `AplicLogAnotarPilaErrores` | La pila del sistema.    |
| `AplicLogAnotarSaltoLinea`  | Una línea en blanco.    |

Todas devuelven `int`, a diferencia de las de
[SLog](../../gjs-c-common-log/doc/SLog.md), que devuelven `void`: aquí el 0
indica que no se pudo componer el texto.

### Configuración

| Función                                                              | Descripción              |
| -------------------------------------------------------------------- | ------------------------ |
| `AplicLogActivar` / `AplicLogDesactivar` / `AplicLogActivado`        | La salida a fichero.     |
| `AplicLogActivarSalidaPorConsola` / `…Desactivar…` / `…Activada`     | La salida a pantalla.    |
| `AplicLogActivarEncabezadoLinea` / `…Desactivar…` / `…Activado`      | El encabezado.           |
| `AplicLogActivarAnotacionTipoMensaje` / `…Desactivar…` / `…Activada` | La marca de nivel.       |
| `AplicLogNivel` / `AplicLogEstablecerNivel`                          | El umbral.               |
| `AplicLogFichero`                                                    | El fichero en uso.       |
| `SLog * AplicLog ()`                                                 | **El objeto de dentro.** |

`AplicLog ()` es la válvula de escape: devuelve el `SLog` global para las
operaciones que este envoltorio no expone.

## Dependencias

[SLog](../../gjs-c-common-log/doc/SLog.md) y
[SCadena](../../gjs-c-common-text/doc/SCadena.md) para el formateo.

## Test

`AplicacionLogTest.c` → `TestAplicacionLog()`.

## Observaciones

- **Un mensaje largo se trunca sin avisar.** Debajo,
  [SLog](../../gjs-c-common-log/doc/SLog.md) parte o trunca lo que no cabe en la
  línea según su interruptor de partición, y por encima de eso el propio stack
  corta en 8.191 caracteres. Ninguna de las dos cosas se refleja en el `int` que
  devuelven estas funciones, que sólo distingue si se pudo componer el texto.
- **`AplicLogAnotarDepuracion` no anota nunca.** Delega en el nivel
  `LOG_NIVEL_DEPURACION`, que
  [NivelesLog](../../gjs-c-common-log/doc/NivelesLog.md) deja por debajo de
  `LOG_NIVEL_MIN` y por tanto `NivelLogEsValido` rechaza. La función existe,
  devuelve 1 y su mensaje se descarta.
- **`AplicLogFichero` devuelve `NULL` mientras el log está iniciado**, porque
  debajo llama a `SLogRutaFichero`, que tiene la condición invertida. Es decir:
  no hay forma de saber en qué fichero se está escribiendo.
- **El estado global no está protegido.** `g_p_logAplicGestor` y
  `g_iAplicLogInicializado` son estáticos y no hay ni mutex ni bandera atómica;
  dos hilos anotando a la vez comparten el mismo `SLog`, que tampoco los tiene.
- **`AplicLogInicializarExt` interpreta `cSepHoraNombre == ' '` como "no
  cambiar"**, de modo que no se puede fijar el espacio como separador
  explícitamente. Da igual, porque el espacio ya es el valor por defecto, pero
  el parámetro no tiene forma de expresar "déjalo como está" frente a "ponlo a
  espacio".
- **`iActivado` se recibe y no se documenta qué activa**: si la salida a
  fichero, la de consola o las dos. Es el único de los ocho parámetros que no
  tiene una función `AplicLogActivar…` con el mismo nombre.
- **`AplicLog ()` deja salir el objeto interno**, con lo que un llamante puede
  destruirlo o reconfigurarlo a espaldas del envoltorio, que seguiría creyéndose
  inicializado.
- `AplicLogFinalizar` destruye el `SLog` **siempre**, incluso si no llegó a
  iniciarse, y deja `g_iAplicLogInicializado` a 0: es reentrante, pero no avisa
  de que no había nada que finalizar.
