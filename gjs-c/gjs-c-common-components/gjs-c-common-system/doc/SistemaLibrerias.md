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

> **El módulo entero está sin implementar fuera de Windows.** No hay una sola
> llamada a `dlopen` ni a `dlsym` en las 652 líneas: la rama Windows usa
> `LoadLibrary` y `GetProcAddress`, y la rama `#else` es un `PENDIENTE` que
> devuelve 0 o `NULL` en las doce funciones.
>
> En el modo de compilación normal `SisLibCargar` devuelve 0 siempre y
> `SisLibPrimitiva` devuelve `NULL` siempre. Es el módulo con más código muerto
> del componente: 652 líneas que no hacen nada en el modo por defecto.
>
> La traducción no es difícil —`dlopen`/`dlsym`/`dladdr` cubren carga, símbolos y
> dirección de mapeo—, pero versión y tamaño en memoria no tienen equivalente
> directo en ELF.

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
