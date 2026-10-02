# SistemaLibrerias

| Dato         | Valor                                                         |
| ------------ | ------------------------------------------------------------- |
| Cabecera     | `src/main/include/SistemaLibrerias.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SistemaLibrerias.c` (652 líneas) |
| Prefijo      | `SisLib`                                                      |
| Funciones    | 12                                                            |
| Incluido por | `Sistema.h`                                                   |
| Test         | `SistemaLibreriasTest.c` → `TestSistemaLibrerias()`           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Cargar librerías dinámicas en tiempo de ejecución y sacarles información: dónde
está el fichero, qué versión tiene, en qué dirección se ha mapeado y qué
símbolos exporta.

Es la base de cualquier sistema de complementos: cargar un `.dll` o un `.so` que
no se conocía al compilar y llamar a sus funciones.

## API

### Carga y símbolos

| Función                                                                          | Descripción                  |
| -------------------------------------------------------------------------------- | ---------------------------- |
| `int SisLibCargar ( const char * p_cLibreria )`                                  | Carga la librería.           |
| `int SisLibEstaCargada ( const char * p_cLibreria )`                             | 1 si ya está.                |
| `void * SisLibPrimitiva ( const char * p_cLibreria, const char * p_cPrimitiva )` | Dirección de un símbolo.     |
| `void * SisLibRutinaPuntoDeEntrada ( const char * p_cLibreria )`                 | Su punto de entrada.         |
| `SListaLiterales * SisLibCargadas ()`                                            | Las cargadas por el proceso. |

`SisLibPrimitiva` es la función que importa: devuelve un `void *` que el
llamante convierte al tipo de función que espera.

```c
typedef int (*PFN_CALC) ( int );

if ( SisLibCargar ( "miplugin.dll" ) == 1 )
{
    PFN_CALC f = (PFN_CALC) SisLibPrimitiva ( "miplugin.dll", "Calcular" );
    if ( f != NULL ) { printf ( "%d\n", f ( 42 ) ); }
}
```

Nótese que **no hay descriptor**: las doce funciones identifican la librería por
su nombre, no por un manejador devuelto en la carga.

### Fichero

| Función                                                       | Descripción                |
| ------------------------------------------------------------- | -------------------------- |
| `char * SisLibRutaFichero ( const char * p_cLibreria )`       | Ruta completa del fichero. |
| `char * SisLibDirectorioFichero ( const char * p_cLibreria )` | Su directorio.             |
| `char * SisLibFichero ( const char * p_cLibreria )`           | Su nombre.                 |

### Memoria y versión

| Función                                                                                                     | Descripción         |
| ----------------------------------------------------------------------------------------------------------- | ------------------- |
| `void * SisLibDireccionMemoria ( const char * p_cLibreria )`                                                | Dónde está mapeada. |
| `unsigned long SisLibTamMemoria ( const char * p_cLibreria )`                                               | Cuánto ocupa.       |
| `char * SisLibCadenaVersion ( const char * p_cLibreria )`                                                   | Versión como texto. |
| `int SisLibVersion ( p_cLibreria, int * p_iVersion, int * p_iSubversion, int * p_iRevision, int * p_iBug )` | Sus cuatro números. |

Los cuatro niveles de `SisLibVersion` son los mismos que maneja
[Versiones](../../gjs-c-common-base/doc/Versiones.md) en `gjs-c-common-base`.

## Dependencias

[SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md) y `Funciones.h`.
En Windows, `LoadLibrary`, `GetProcAddress` y la API de recursos de versión.

## Test

`SistemaLibreriasTest.c` → `TestSistemaLibrerias()`.

## Observaciones

> **Implementado para POSIX el 2026-09-18.** No queda ninguna rama POSIX
> pendiente: de las doce funciones, once valen en los dos mundos y la duodécima
> —`SisLibRutinaPuntoDeEntrada`— pasó a declararse **sólo bajo `WIN`**.
>
> El reparto no es el evidente, y conviene saber por qué:
>
> - **Cargar y resolver** van con `dlopen` / `dlsym` / `dlclose`.
> - **Enumerar, la ruta, la dirección base y el tamaño** van con
>   `/proc/self/maps`. No se usa `dl_iterate_phdr` ni `dlinfo`, que sería lo
>   natural en glibc, porque **Cygwin no los trae** —ni siquiera existe
>   `link.h`—, y hacía falta algo que valiera en los dos.
> - **`SisLibEstaCargada` mira el mapa, no le pregunta al enlazador.** Lo suyo
>   sería `dlopen` con `RTLD_NOLOAD`, pero **Cygwin ignora esa bandera**
>   (comprobado: carga la librería igualmente), así que usarla convertiría la
>   consulta en una carga y contestaría que sí a cualquier librería que exista
>   en el disco. Por lo mismo, `SisLibPrimitiva` comprueba el mapa **antes** de
>   hacer `dlopen`.
> - **`SisLibVersion` saca la versión del nombre del fichero**
>   (`libfoo.so.1.2.3`), que es la convención POSIX equivalente al
>   `DllGetVersion` de las DLL del shell de Windows. Los `.dll` de Cygwin no la
>   llevan y devuelve 0.
>
> **`SisLibRutinaPuntoDeEntrada` es sólo de Windows**, y por eso ya no figura
> como pendiente: está dentro de un `#if ( defined ( WIN ) )` en la cabecera y
> en el fuente, así que fuera de Windows **no existe** y un código que la llame
> no compila, en vez de recibir un `NULL` que no significa nada.
>
> El motivo es de fondo, no de esfuerzo: el "punto de entrada" es del formato
> PE —la rutina que el cargador llama al enganchar la librería, `DllMain`—. Un
> objeto compartido de ELF no tiene eso: tiene constructores y destructores, que
> son varios y no una dirección, y su `e_entry` no se usa.
>
> El nombre se busca por el fichero de la ruta: valen `"cygwin1.dll"`,
> `"/usr/bin/cygwin1.dll"` y `"cygwin1"`. A diferencia de Windows, **distingue
> mayúsculas**.

- **Identificar la librería por su nombre en cada llamada es frágil.** No hay
  descriptor: `SisLibPrimitiva ( "milib.dll", … )` tiene que volver a resolver la
  librería, y dos librerías con el mismo nombre de fichero en directorios
  distintos son indistinguibles.
- **`SisLibPrimitiva` devuelve `void *` para un puntero a función**, conversión
  que el estándar de C no garantiza aunque POSIX la exija y funcione en la
  práctica. Es la firma habitual de `dlsym`, así que no hay mucho que hacer, pero
  conviene saberlo.
- **No hay `SisLibDescargar`.** Se puede cargar y consultar, no soltar: una vez
  cargada, la librería se queda hasta que termine el proceso. Falta el
  `FreeLibrary` / `dlclose`.
- **Un fallo de carga no dice por qué.** `SisLibCargar` devuelve 0 sin registrar
  nada en [SistemaErrores](SistemaErrores.md), de modo que "no existe el
  fichero", "faltan dependencias" y "no está implementado en este modo" son
  indistinguibles.
- `SisLibCargadas` devuelve una
  [SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md) que el llamante
  debe destruir, pero el nombre no lo sugiere.
