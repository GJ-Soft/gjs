# MemoriaGlobal

| Dato      | Valor                                          |
| --------- | ---------------------------------------------- |
| Cabecera  | `src/main/include/MemoriaGlobal.h` (30 líneas) |
| Fuente    | `MemoriaGlobal.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                        |
| Funciones | 5                                              |
| Test      | `MemoriaGlobalTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **diccionario global de cadenas**, accesible desde cualquier punto del
programa sin pasar un objeto.

```cpp
void        MemGlobGuardar   ( const std::string & sClave, const std::string & sValor );
std::string MemGlobRecuperar ( const std::string & sClave );
void        MemGlobEliminar  ( const std::string & sClave );
bool        MemGlobExiste    ( const std::string & sClave );
void        MemGlobLimpiar   ();
```

Sirve para lo que en otros marcos se llama contexto: dejar apuntado el
identificador de la petición, el usuario en curso o la configuración que se
acaba de leer, y recuperarlo abajo sin arrastrarlo por la pila.

## La conexión con el stack C

Estas cinco funciones son **exactamente el MDC que
[`MDC.h`](../../gjs-c-common-log/doc/Pendientes.md) declara en
`gjs-c-common-log` y que nunca se implementó**:

| En `MDC.h` (C, sin implementar) | Aquí               |
| ------------------------------- | ------------------ |
| `MDCGuardar`                    | `MemGlobGuardar`   |
| `MDCRecuperar`                  | `MemGlobRecuperar` |
| `MDCEliminar`                   | `MemGlobEliminar`  |
| `MDCLimpiar`                    | `MemGlobLimpiar`   |
| —                               | `MemGlobExiste`    |

Las cuatro funciones de la cabecera C tienen aquí su gemela, con una más. De
modo que lo que en el stack C está declarado y pendiente, en el C++ está escrito
y probado.

Vale la pena tenerlo presente al abordar aquel pendiente: hay una
implementación de referencia, y la conclusión que se saque aquí —sobre
concurrencia, sobre todo— se aplica igual allí.

## Dependencias

`<string>`, `<list>`.

## Test

`MemoriaGlobalTest.cpp` → `TestMemoriaGlobal()`.

## Observaciones

- **La cabecera no dice si es seguro entre hilos**, y es la pregunta que
  cualquiera se hace ante un almacén global. El componente tiene
  [ControlConcurrencia](ControlConcurrencia.md) al lado; si no se usa aquí,
  conviene decirlo, porque un contexto global es justo lo que varios hilos
  tocarían a la vez.
- **Y un MDC de verdad es por hilo, no global.** Ésa es la razón de ser del
  patrón: cada hilo lleva su propia etiqueta de petición. Una tabla compartida
  hace lo contrario —todos ven lo mismo—, que sirve para configuración y no para
  trazar peticiones concurrentes. Con `thread_local` la diferencia es una
  palabra.
- **`MemGlobRecuperar` devuelve `std::string` por valor** y no dice qué pasa con
  una clave ausente: cadena vacía, presumiblemente, indistinguible de un valor
  vacío. `MemGlobExiste` está para eso, a costa de dos búsquedas.
- **No hay forma de listar las claves**, ni de recorrer el contenido. Para
  volcar el contexto en una traza —que es lo que hace un MDC— habría que
  recordar de fuera qué se guardó.
- **El nombre despista.** `MemoriaGlobal` suena a gestión de memoria, y está en
  un componente que además tiene [Ptr](Ptr.md) y hereda los `MemReservar` de
  base. `ContextoGlobal` o `MDC` dirían mejor lo que es.
- **Ninguna función informa de fallo.** Las tres que modifican devuelven `void`.
