# WinHerramientas

| Dato      | Valor                                            |
| --------- | ------------------------------------------------ |
| Cabecera  | `src/main/include/WinHerramientas.h` (33 líneas) |
| Fuente    | `WinHerramientas.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                          |
| Funciones | 1 — **sólo Windows**                             |
| Test      | `WinHerramientasTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Cargar una DLL y ejecutar una de sus funciones, en una sola llamada.

```cpp
#if ( defined ( WIN ) )

bool DLLEjecutar ( std::string sRutaDLL, std::string sFuncion );

#endif
```

Toda la cabecera está dentro de `#if ( defined ( WIN ) )`: fuera de Windows no
declara nada, de modo que el compilador avisa en el `#include` en lugar de
dejar que la llamada devuelva un valor falso. Es el mismo criterio de
[SistemaImpresoras](../../gjs-c-common-system/doc/Windows.md) en el stack C.

## Dependencias

`BaseConfig.h` y la API de Windows.

## Test

`WinHerramientasTest.cpp` → `TestWinHerramientas()`. En el modo normal no hay
nada que probar, así que la suite pasa sin ejercitar código.

## Observaciones

- **La función que se ejecuta no recibe argumentos ni devuelve nada.** El nombre
  se pasa como cadena y el resultado es un `bool` que sólo dice si se pudo
  llamar. Sirve para un punto de entrada del estilo de `DllRegisterServer` y
  para poco más; cargar un complemento y usarlo requiere obtener el puntero a
  función, que es lo que hace
  [SisLibPrimitiva](../../gjs-c-common-system/doc/SistemaLibrerias.md) en el
  stack C.
- **Los dos parámetros se pasan por valor**, copiando dos `std::string` en cada
  llamada, donde el resto del componente usa `const std::string &`.
- **No hay descarga ni caché.** Cada llamada carga la DLL, ejecuta y
  presumiblemente la suelta; llamar en un bucle recarga la biblioteca cada vez.
- **Un solo `bool` para todos los fallos**: DLL que no existe, función que no
  está, o función que falló. Con el componente raíz ofreciendo
  [SistemaExcepcion](../../gjs-cpp-common-base/doc/SistemaExcepcion.md), lo
  coherente sería lanzar.
- **Es lo único de Windows en el componente**, y llama la atención en un módulo
  que por lo demás es el modelo de datos: una carga dinámica de bibliotecas
  encaja mejor en
  [gjs-cpp-common-system](../../gjs-cpp-common-system/README.md).
- **El prefijo `Win` en el nombre del fichero** no lo usa ningún otro del stack
  C++; la convención en el resto es la rama `#if` dentro de la cabecera del
  módulo que corresponda.
