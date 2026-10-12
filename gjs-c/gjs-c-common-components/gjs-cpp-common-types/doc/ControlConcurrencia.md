# ControlConcurrencia

| Dato      | Valor                                                   |
| --------- | ------------------------------------------------------- |
| Cabecera  | `src/main/include/ControlConcurrencia.h` (43 líneas)    |
| Fuente    | `ControlConcurrencia.cpp`                               |
| Espacio   | `org::gjs::cpp::common`                                 |
| Derivadas | `GestorSesiones` en `gjs-cpp-common-io`, **en privado** |
| Test      | `ControlConcurrenciaTest.cpp`                           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un cerrojo para **heredar**, no para tener. Da a una clase la capacidad de
protegerse sin exponerla en su interfaz.

```cpp
class ControlConcurrencia
{
private:
    std::mutex                   mtxAcceso;
    std::atomic<std::thread::id> idBloqueante { std::thread::id () };

public:
    ControlConcurrencia ();
    virtual ~ControlConcurrencia ();

protected:
    void Bloquear ();
    void Desbloquear ();
};
```

Los dos métodos son **`protected`**: sólo la clase derivada los usa. Y la
herencia prevista es **privada**, como hace
`GestorSesiones : private ControlConcurrencia` en
[gjs-cpp-common-io](../../gjs-cpp-common-io/README.md): el gestor se protege por
dentro y de fuera nadie ve que hay un mutex.

`idBloqueante` guarda **qué hilo tiene el cerrojo**, en un `std::atomic`, que es
lo que permite detectar una reentrada del mismo hilo —el caso que con un
`std::mutex` a secas produce un interbloqueo consigo mismo—.

Es la respuesta C++ a lo que en el stack C son
[SMutex y las variables de sincronización](../../gjs-c-common-system/doc/Sincronizacion.md),
con la diferencia de que aquí el mutex es el de la biblioteca estándar y no una
envoltura de `sem_open`.

## Dependencias

`<mutex>`, `<atomic>`, `<thread>`.

## Test

`ControlConcurrenciaTest.cpp` → `TestControlConcurrencia()`.

## Observaciones

- **No hay guarda RAII.** `Bloquear` y `Desbloquear` a mano significa que un
  `return` temprano o una excepción entre las dos dejan el cerrojo echado para
  siempre. Es justo el problema que `std::lock_guard` y `std::unique_lock`
  resuelven, y que en un componente C++20 no tendría que existir: una clase
  anidada `Guarda` que bloquee en el constructor y suelte en el destructor sería
  media docena de líneas.

  Y el riesgo es real aquí, porque quien hereda —un gestor de sesiones que habla
  por red— es código con muchos caminos de salida y con excepciones.
- **Es reentrante y cuenta la profundidad** (desde 2026-10-11).
  `idBloqueante` es el hilo dueño: `Bloquear` desde ese hilo no vuelve a tomar
  el mutex, y `Desbloquear` desde otro no hace nada. `iProfundidad` lleva los
  `Bloquear` sin su `Desbloquear`, y el mutex sólo se suelta al volver a 0.
  Antes no se contaba: en un `Bloquear` / `Bloquear` / `Desbloquear` el cerrojo
  quedaba libre mientras el exterior seguía dentro, y otro hilo entraba a la
  vez. Lo fija `TestControlConcurrencia02`.
- **El destructor es virtual en una clase pensada para herencia privada**, donde
  no hace falta: nadie va a destruir un `GestorSesiones` por un puntero a
  `ControlConcurrencia`, porque la conversión no es accesible. Cuesta un puntero
  a tabla virtual por objeto.
- **No hay `Bloqueado()` ni `IntentarBloquear()`.** Sin la primera no se puede
  comprobar el estado; sin la segunda, `std::mutex::try_lock` queda inaccesible
  para la derivada, que es lo que hace falta para no quedarse esperando.
- **No se puede copiar ni mover**, correctamente, porque `std::mutex` no lo
  permite; conviene saber que eso se hereda a toda clase que derive de ésta.
