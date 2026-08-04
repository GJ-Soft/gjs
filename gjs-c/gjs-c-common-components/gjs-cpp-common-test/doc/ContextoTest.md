# ContextoTest

| Dato      | Valor                                         |
| --------- | --------------------------------------------- |
| Cabecera  | `src/main/include/ContextoTest.h` (33 líneas) |
| Fuente    | `ContextoTest.cpp` (115 líneas)               |
| Espacio   | `org::gjs::cpp::common::test`                 |
| Funciones | 5                                             |
| Test      | `ContextoTestTest.cpp` (105 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

**Dónde está cada cosa cuando corre una prueba.** El ejecutable de test no se
lanza desde la raíz del proyecto sino desde
`target/test-nar/test-reports`, así que localizar los recursos a mano acaba en
rutas como `"../../../src/test/resources/data/fichero.txt"` repartidas por todos
los ficheros de prueba.

```cpp
std::string sFichero = Concatenar ( DirectorioTestRecursos (), "/data/entrada.txt" );
std::string sSalida  = Concatenar ( DirectorioTestResultados (), "/salida.txt" );
```

## Los cinco directorios

| Función                    | Qué devuelve                        | Propiedad Maven               |
| -------------------------- | ----------------------------------- | ----------------------------- |
| `DirectorioProyecto`       | La raíz del módulo                  | `project.basedir`             |
| `DirectorioTrabajo`        | El `target`                         | `project.build.directory`     |
| `DirectorioTest`           | Las fuentes de prueba               | `project.build.testDirectory` |
| `DirectorioTestRecursos`   | `src/test/resources`                | —                             |
| `DirectorioTestResultados` | Donde dejar lo que la prueba genere | —                             |

Cada una intenta primero leer la propiedad de un fichero
`../internal/test.properties` —que Maven rellenaría con sus propias variables— y,
si no está, **cae en una ruta relativa calculada** desde el directorio actual con
`ResolverDirectorioRelativo`.

---

## Test

`ContextoTestTest.cpp` comprueba que las cinco devuelvan algo y que las rutas
existan.

---

## Observaciones

### El mecanismo de propiedades no se usa nunca

El fichero de propiedades se lee en `_PrepararContexto()`:

```cpp
static Propiedades * propContexto = NULL;

void _PrepararContexto ()
{
    if ( propContexto == NULL )
    {
        propContexto = new Propiedades ( "../internal/test.properties" );
    }
}
```

y **`_PrepararContexto` no está declarada en `ContextoTest.h`**. Tampoco
`_LiberarContexto`. Las dos son funciones del `.cpp` sin declaración en ninguna
cabecera, de modo que **nadie fuera del fichero puede llamarlas**, y dentro del
fichero no las llama nadie tampoco.

Consecuencia: `propContexto` **siempre vale `NULL`**, las cinco funciones se van
siempre por la rama de reserva, y el fichero `test.properties` —con las rutas
reales que sabe Maven— no se lee jamás. Lo que queda funcionando es el cálculo
por rutas relativas, que depende de que el ejecutable se lance desde el
directorio que el `nar-maven-plugin` usa hoy.

Son dos líneas de arreglo: declarar las dos funciones en la cabecera y llamar a
`_PrepararContexto` desde donde corresponda —el constructor de
[`BancoTests`](BancoTests.md) sería el sitio—, o hacer la carga perezosa dentro
de cada consulta.

### `DirectorioTest` tiene la reserva muerta

Las tres primeras funciones siguen el mismo patrón, salvo una diferencia:

```cpp
string DirectorioProyecto ()
{
    string sDir;                       // vacia
    ...
    if ( sDir.size () == 0 ) { sDir = ResolverDirectorioRelativo ( ..., "../../.." ); }
    return ( sDir );
}

string DirectorioTest ()
{
    string sDir = "..";                // <- ya trae valor
    ...
    if ( sDir.size () == 0 ) { ... }   // <- nunca se cumple
    return ( sDir );
}
```

`DirectorioTest` arranca con `".."`, así que su rama de reserva **no se ejecuta
nunca** y la función devuelve una **ruta relativa sin resolver**, mientras que
sus dos hermanas devuelven rutas absolutas. Quien las mezcle en un
`Concatenar` obtiene cosas de dos clases distintas.

### Otras

- **El nombre `_PrepararContexto` empieza por guión bajo** y no es `static`, así
  que ocupa el espacio de nombres global del enlazador con un identificador
  reservado. Si alguna vez se declaran, el nombre debería cambiar.
- **La ruta del fichero de propiedades está en un `#define` del `.cpp`**,
  relativa (`../internal/test.properties`), y no aparece en ninguna
  documentación. Quien quiera hacer funcionar el mecanismo tiene que saber que el
  fichero va ahí.
- **Ninguna de las cinco dice qué devuelve si no puede resolver el directorio**:
  la cadena vacía y una ruta que no existe se parecen bastante desde el lado del
  llamante.
- **No hay una función que cree el directorio de resultados.**
  `DirectorioTestResultados()` dice dónde escribir, y si no existe, escribir ahí
  falla. Cada prueba que genere ficheros tiene que crearlo por su cuenta con
  [`SisCrearDirectorio`](../../gjs-cpp-common-io/doc/SistemaFicheros.md).
- **Las cinco leen el directorio actual en cada llamada**, así que un módulo que
  cambie el directorio del proceso —como hacen los constructores de
  [`ServidorFTP` y `ServidorHTTP`](../../gjs-cpp-common-io/doc/FTP.md)— hace que
  las rutas relativas dejen de apuntar donde apuntaban. Es justo el escenario en
  el que este módulo debería ser fiable.
