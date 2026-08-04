# CaptorSalida

| Dato      | Valor                                         |
| --------- | --------------------------------------------- |
| Cabecera  | `src/main/include/CaptorSalida.h` (45 líneas) |
| Fuente    | `CaptorSalida.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                       |
| Deriva de | —                                             |
| Test      | `CaptorSalidaTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

**Desviar `std::cout` a memoria** para poder comprobar lo que un código imprime.

```cpp
class CaptorSalida
{
private:
    std::streambuf *         p_bufViejo = NULL;
    std::stringstream        ssContenido;
    bool                     bActivado = false;
    std::vector<std::string> vecLineas;

public:
    CaptorSalida ();
    ~CaptorSalida ();

    void Ini ();
    void Fin ();
    bool EstaActivado ();
    std::vector<std::string> getLineas ();
};
```

`Ini()` guarda el búfer de `std::cout` y lo sustituye por el propio; `Fin()` lo
devuelve a su sitio y parte lo capturado en líneas.

```cpp
CaptorSalida cap;

cap.Ini ();
ImprimirInforme ();
cap.Fin ();

std::vector<std::string> vecSalida = cap.getLineas ();
```

Es la pieza que en el stack C hace
[SimularEntradaConsola](../../gjs-c-common-support/doc/Pruebas.md) para la
entrada, aquí para la salida y con la ventaja de que `std::streambuf` permite
hacerlo sin tocar descriptores del sistema.

## Dependencias

`<sstream>`, `<iostream>`, `<vector>`.

## Test

`CaptorSalidaTest.cpp` → `TestCaptorSalida()`.

## Observaciones

> **Es una utilidad de prueba publicada en la librería de producción**, y entra
> por la fachada `CppCommonTypes.h`. Cualquier programa que la incluya se lleva
> una clase capaz de secuestrar `std::cout`.
>
> Es el mismo caso que
> [SimulacionUsuarioConsola](../../gjs-c-common-support/doc/Pruebas.md) en el
> stack C, y el sitio natural sería
> [gjs-cpp-common-test](../../gjs-cpp-common-test/README.md).

- **El destructor no restaura el búfer.** Sólo `Fin()` lo hace, así que un
  `CaptorSalida` que salga de ámbito por una excepción entre `Ini()` y `Fin()`
  deja `std::cout` apuntando a un `std::stringstream` **ya destruido**: a partir
  de ahí, cualquier escritura por la salida estándar del programa es
  comportamiento indefinido, y el síntoma aparece lejos del sitio.

  Con el destructor llamando a `Fin()` cuando `bActivado` sigue cierto, la clase
  sería segura y además se convertiría en la guarda RAII que su forma pide —el
  mismo arreglo que necesita [ControlConcurrencia](ControlConcurrencia.md)—.
- **`Ini()` no comprueba si ya estaba activado.** Dos llamadas seguidas
  sobrescriben `p_bufViejo` con el búfer del propio captor, y a partir de ahí
  `Fin()` no puede devolver el original.
- **Sólo captura `std::cout`.** Ni `std::cerr` ni `std::clog`, que es donde va a
  parar la mitad de lo que interesa comprobar en una prueba —los mensajes de
  error—.
- **`getLineas()` y `EstaActivado()` no son `const`.**
- **No hay forma de ver lo capturado sin cerrar.** `getLineas` sólo tiene sentido
  después de `Fin()`, y la cabecera no lo dice.
