# Entorno

| Dato         | Valor                                                |
| ------------ | ---------------------------------------------------- |
| Cabecera     | `src/main/include/CEntorno.h`                        |
| Fuente       | `src/main/c/org/gjs/c/common/Entorno.c` (283 líneas) |
| Prefijo      | `Ent`                                                |
| Funciones    | 16                                                   |
| Incluido por | **Nadie** — fuera de `CCommon.h`                     |
| Test         | `EntornoTest.c` → `TestEntorno()`                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Arrancar y parar la aplicación entera. Es la función que llama un `main` en su
primera línea y en la última, y la que da sentido a que exista este componente:
todo lo demás del stack son piezas; esto es el montaje.

## API

### Ciclo de vida

| Función                                                             | Descripción               |
| ------------------------------------------------------------------- | ------------------------- |
| `int EntInicializar ( iConsola, p_cNombre, iVersion, iSubversion )` | Arranque con lo mínimo.   |
| `int EntInicializarExt ( … )`                                       | Con todos los parámetros. |
| `void EntFinalizar ()`                                              | Parada ordenada.          |
| `int EntEstaInicializado ()`                                        | Estado.                   |

`EntInicializarExt` es la que hace el trabajo, y **su firma cambia con la
plataforma**:

```c
#if ( defined ( WIN ) )
int EntInicializarExt ( int iConsola, const char * p_cNombre,
                        int iVersion, int iSubversion, int iRevision,
                        unsigned long ulFecha, const char * p_cDirTemporal,
                        int iVaciarDirTemporal );
#else
int EntInicializarExt ( int iConsola, const char * p_cNombre,
                        int iVersion, int iSubversion, int iRevision,
                        unsigned long ulFecha, const char * p_cDirTemporal,
                        const char * p_cNomProceso, int iVaciarDirTemporal );
#endif
```

Fuera de Windows hay un parámetro más, `p_cNomProceso`, porque allí el nombre
del proceso hay que registrarlo a mano con `SisProcInicializar`.

Lo que hace, en orden:

1. Fija el directorio temporal del sistema si se le ha pasado uno.
2. Apunta los tres directorios de trabajo al temporal.
3. Registra el nombre de proceso (sólo fuera de Windows).
4. Llama a
   [`AplicInicializar`](../../gjs-c-common-support/doc/Aplicacion.md).
5. Vacía el directorio temporal si se le ha pedido.
6. Guarda el PID del proceso que ha inicializado.

### Los tres directorios

| Consulta                    | Cambio                             | Cambio con opciones                   |
| --------------------------- | ---------------------------------- | ------------------------------------- |
| `EntDirectorioDatos ()`     | `EntEstablecerDirectorioDatos`     | `EntEstablecerDirectorioDatosExt`     |
| `EntDirectorioSeguridad ()` | `EntEstablecerDirectorioSeguridad` | `EntEstablecerDirectorioSeguridadExt` |
| `EntDirectorioLog ()`       | `EntEstablecerDirectorioLog`       | `EntEstablecerDirectorioLogExt`       |

Las variantes `Ext` reciben `( p_cDir, int iVaciar, int iCrear )`: crean el
directorio si no existe y lo vacían después de fijarlo. Sin `Ext`, el directorio
tiene que existir ya —si no existe, la llamada no hace nada y la ruta anterior
se mantiene—.

### Modo test

| Función                         | Descripción       |
| ------------------------------- | ----------------- |
| `int EntEstaEnModoTest ()`      | 1 si está activo. |
| `void EntActivarModoTest ()`    | Lo activa.        |
| `void EntDesactivarModoTest ()` | Lo desactiva.     |

Su único efecto en el stack es **encender la
[consola de depuración](ConsolaDepuracion.md)**: sus siete funciones empiezan
por `if ( EntEstaEnModoTest () == 1 )` y, fuera del modo test, no hacen nada y
devuelven éxito. Las trazas de depuración salen al ejecutar las pruebas y
desaparecen solas en producción, sin `#if` ni recompilar.

## El PID del inicializador

`EntFinalizar` no hace nada si el proceso que la llama no es el que inicializó:

```c
if ( g_pidProcesoInicializador == getpid () )
{
    /* … liberar … */
}
```

Es la protección frente a `fork`: un proceso hijo que termine —o que llame a
`EntFinalizar` en su salida— no desmonta el entorno del padre ni libera memoria
que el padre sigue usando.

## Dependencias

Todo el stack, a través de `CCommon.h`. En particular
[AplicacionInformacion](../../gjs-c-common-support/doc/Aplicacion.md),
[SistemaInformacion](../../gjs-c-common-system/doc/SistemaInformacion.md) y
[SistemaFicheros](../../gjs-c-common-io/doc/SistemaFicheros.md).

## Test

`EntornoTest.c` → `TestEntorno()`.

## Observaciones

> **`CEntorno.h` no entra por la fachada.** `CCommon.h` incluye los diez
> componentes y los cuatro módulos propios, pero no ésta — y `EntInicializar` es
> la primera llamada de cualquier programa del stack.
>
> La dependencia va al revés: `CEntorno.h` incluye `CCommon.h`. De modo que lo
> correcto es incluir `<CEntorno.h>` y olvidarse de `<CCommon.h>`, cosa que ni
> el nombre ni la documentación sugieren.

- **La firma de `EntInicializarExt` cambia entre plataformas.** No es un
  parámetro ignorado ni un valor por defecto: el número de argumentos es
  distinto, así que el código portable necesita un `#if ( defined ( WIN ) )`
  alrededor de la llamada. Se podría evitar dejando el parámetro en las dos
  ramas e ignorándolo en Windows.
- **`EntInicializarExt` puede devolver 0 y quedar inicializado.** Si el vaciado
  del directorio temporal falla, pone `iRes = 0` pero también
  `g_iEntInicializado = 1`. El llamante que aborte al ver el 0 deja el entorno a
  medio montar; el que continúe funciona.
- **Y devuelve 1 si ya estaba inicializado**, al revés que
  [`AplicInicializar`](../../gjs-c-common-support/doc/Aplicacion.md), que
  devuelve 0 en ese caso. Dos capas contiguas con convenios opuestos para la
  misma situación.
- **`EntEstablecerDirectorio…` no informa de nada.** Devuelven `void`: si el
  directorio no existe la ruta simplemente no cambia, y el programa sigue
  escribiendo donde estuviera antes —el temporal del sistema—.
- **`iParar` se usa sin inicializar** en el bloque de `MODO_DEPURACION` de
  `EntFinalizar`. Sólo se compila en depuración, pero ahí el `if ( iParar == 1 )`
  lee basura.
- Quedan dos bloques comentados en el arranque y la parada: la inicialización de
  *sockets* en Windows (`_WinSckInicializar`) y el manejo de `SIGPIPE` fuera de
  él. Ninguna de las dos cosas se hace hoy.
- El módulo se llama `Entorno` (fuente `Entorno.c`, test `EntornoTest.c`,
  prefijo `Ent`) pero su cabecera es `CEntorno.h`, con la `C` de la versión C++
  del stack. Lo mismo ocurre con `CCommon.h`.
