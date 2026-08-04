# Entorno

| Dato      | Valor                                       |
| --------- | ------------------------------------------- |
| Cabecera  | `src/main/include/CppEntorno.h` (53 líneas) |
| Fuente    | `Entorno.cpp` (221 líneas)                  |
| Espacio   | `org::gjs::cpp::common`                     |
| Prefijo   | `Ent`                                       |
| Funciones | 10                                          |
| Test      | `EntornoTest.cpp` (91 líneas)               |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Arrancar y cerrar el entorno de ejecución de un programa **en una llamada**, y
llevar los tres directorios de trabajo.

```cpp
#include <CppEntorno.h>

if ( EntInicializar ( true, "MiPrograma", 2, 3, 4, 20260804, "/tmp/miprograma" ) )
{
    EntEstablecerDirectorioDatos ( "/var/lib/miprograma", false, true );
    EntEstablecerDirectorioLog   ( "/var/log/miprograma", false, true );

    ...

    EntFinalizar ();
}
```

`CppEntorno.h` es a la vez la fachada ampliada del componente y la cabecera de
este módulo: no hay un `Entorno.h`.

## La API

| Grupo         | Funciones                                                          |
| ------------- | ------------------------------------------------------------------ |
| Ciclo de vida | `EntInicializar`, `EntFinalizar`, `EntEstaInicializado`            |
| Consulta      | `EntDirectorioDatos`, `EntDirectorioSeguridad`, `EntDirectorioLog` |
| Cambio        | `EntEstablecerDirectorioDatos`, `…Seguridad`, `…Log`               |

Los tres `EntEstablecer…` aceptan dos banderas: `bCrear` —crea el directorio si
no existe, cierto por defecto— y `bVaciar` —lo vacía después, falso por
defecto—.

## Los tres directorios

`EntInicializar` los deja **los tres apuntando al directorio temporal**:

```cpp
g_p_sEntDirDatos     = SisDirectorioTemporal ();
g_p_sEntDirSeguridad = SisDirectorioTemporal ();
g_p_sEntDirLog       = SisDirectorioTemporal ();
```

Tres reservas distintas, no tres alias: `SisDirectorioTemporal()` de
[gjs-cpp-common-system](../../gjs-cpp-common-system/doc/Informacion.md) devuelve
un `new std::string` en cada llamada. Por eso `EntFinalizar` puede borrar los
tres, y `EntEstablecerDirectorioDatos` borra el viejo antes de poner el nuevo.

La idea es que el programa los reparta después: los datos a su sitio, el registro
al suyo, y lo de seguridad —claves, certificados— aparte.

---

## Test

`EntornoTest.cpp` prueba el ciclo: que antes no esté inicializado, que después sí,
que los directorios respondan, y que `EntFinalizar` lo deshaga.

---

## Observaciones

### La firma cambia de forma según la plataforma

```cpp
#if ( defined ( WIN ) )
bool EntInicializar ( bool bConsola, const string & sNombre, int iVersion, int iSubversion,
                      int iRevision = 0, unsigned long ulFecha = 0,
                      const string & sDirTemporal = "",
                      bool bVaciarDirTemporal = false );
#else
bool EntInicializar ( bool bConsola, const string & sNombre, int iVersion, int iSubversion,
                      int iRevision = 0, unsigned long ulFecha = 0,
                      const string & sDirTemporal = "",
                      const string & sNomProceso = "",          // <- solo POSIX
                      bool bVaciarDirTemporal = false );
#endif
```

El parámetro de más en POSIX va **en medio**, así que a partir de ahí las
posiciones se desplazan: `bVaciarDirTemporal` es el octavo argumento en Windows
y el noveno en POSIX.

Consecuencia: **una llamada con ocho argumentos posicionales significa cosas
distintas en cada plataforma**. En Windows vacía el temporal; en POSIX, ese
`true` se convierte en el nombre de proceso —o no compila, según el tipo—. El
código portable tiene que rodearlo con guardas, que es justo lo que la función
venía a evitar.

Poner `sNomProceso` **al final** lo arreglaría sin tocar nada más: los ocho
primeros quedarían iguales en las dos plataformas.

### Los directorios pueden quedarse a nulo sin que nadie lo diga

`SisDirectorioTemporal()` devuelve `NULL` si no puede resolver el temporal. En
POSIX lo resuelve a partir de un global que **sólo rellena
`SisInicializarDirectorios`**, y `EntInicializar` sólo la llama si le pasan un
directorio temporal:

```cpp
if ( ! sDirTemporal.empty() )
{
    SisInicializarDirectorios ( sDirTemporal );
}
g_p_sEntDirDatos = SisDirectorioTemporal ();     // NULL si lo anterior no corrio
```

O sea: **`EntInicializar ( true, "MiPrograma", 1, 0 )` en POSIX deja los tres
directorios a nulo**, devuelve `true`, y `EntDirectorioDatos()` devuelve `NULL`
al primero que pregunte. El caso más sencillo de la API es el que lo produce.

### Contratos

- **Las tres consultas devuelven `const std::string *`.** La propiedad la
  conserva el módulo —quien lo borre revienta `EntFinalizar`— y eso no está
  escrito. Devolver `const std::string &` diría lo mismo sin dar ocasión.
- **Los tres `EntEstablecer…` devuelven `void`** y pueden no hacer nada: si el
  directorio no existe y `bCrear` es falso, o si no se puede crear, el módulo se
  queda con el que tenía y no avisa.
- **`bVaciar` en un `EntEstablecer…` borra el contenido del directorio.** Es una
  operación destructiva detrás de un parámetro por defecto, en una función que se
  llama «establecer»; conviene leerlo dos veces antes de usarlo con un directorio
  que no sea temporal.
- **`EntInicializar` devuelve `false` si ya estaba inicializado**… no: devuelve
  `g_bEntInicializado`, que en ese caso es `true`. Llamarla dos veces no hace
  nada la segunda vez y responde que sí, que es lo razonable y no está dicho.
- **Si `AplicInicializar` falla, el entorno queda a medias.** Los directorios ya
  se han reservado y `SisProcInicializar` ya ha corrido, pero
  `g_bEntInicializado` se queda en falso — y entonces `EntFinalizar` no limpia
  nada, porque empieza con `if ( g_bEntInicializado )`. Es una fuga en el camino
  de error.

### Restos

- **Quedan tres bloques comentados** en la inicialización y el cierre:
  `_WinSckInicializar` / `_WinSckFinalizar` —el arranque de Winsock, que hoy hace
  falta para los sockets de
  [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md) en Windows— y
  `signal ( SIGPIPE, sigpipe_handle )` para UNIX. Con un `PENDIENTE: Tratar el
  error` dentro del primero.

  Que el arranque de Winsock esté comentado es lo llamativo: los sockets del
  stack funcionan hoy porque Cygwin no lo exige, y en Windows puro haría falta.
- **`ErrLimpiar ()` en `EntFinalizar` también está comentada**, así que el estado
  de error del sistema no se limpia al cerrar.
- **Hay un bloque bajo `#if defined ( MODO_DEPURACION_2 ) || defined (
  MODO_DEPURACION )`** con un `// TODO: Esto todavia no se ha pasado a lo nuevo`.
  `MODO_DEPURACION` lo define `Precompilacion.h` en las compilaciones de
  depuración, de modo que **ese código sin migrar sí entra** en ese modo.
