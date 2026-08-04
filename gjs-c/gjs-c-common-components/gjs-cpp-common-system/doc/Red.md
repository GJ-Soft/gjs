# Red

| Dato      | Valor                            |
| --------- | -------------------------------- |
| Cabecera  | `SistemaRed.h` (58 líneas)       |
| Fuente    | `SistemaRed.cpp` (353 líneas)    |
| Espacio   | `org::gjs::cpp::common`          |
| Prefijo   | `SisRed`                         |
| Funciones | 6                                |
| Test      | `SistemaRedTest.cpp` (62 líneas) |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La máquina dentro de su red: cómo se llama, a quién ve y cómo mandarle un aviso
a otra estación.

No tiene nada que ver con los sockets de
[gjs-cpp-common-io](../../gjs-cpp-common-io/README.md): aquí no se abre ninguna
conexión, se consulta al sistema.

```cpp
std::wstring wsNombre = SisRedNombreOrdenador ();
std::list<std::wstring> * pOrdenadores = SisRedOrdenadoresAccesibles ();
```

## La API

| Función                       | Qué hace                          | En Windows             | En POSIX            |
| ----------------------------- | --------------------------------- | ---------------------- | ------------------- |
| `SisRedNombreOrdenador`       | El nombre NetBIOS / el `hostname` | `GetComputerName`      | `gethostname`       |
| `SisRedNombreDNSOrdenador`    | El nombre completo de DNS         | `GetComputerNameEx`    | **sin implementar** |
| `SisRedOrdenadoresAccesibles` | Lista de máquinas visibles        | `NetServerEnum`        | `getaddrinfo`       |
| `SisRedServidorEsAccesible`   | ¿Está ese servidor?               | `NetServerEnum`        | **sin implementar** |
| `SisRedEstacionEsAccesible`   | ¿Está esa estación?               | `NetServerEnum`        | **sin implementar** |
| `SisRedEnviarMensaje`         | Aviso emergente a otra máquina    | `NetMessageBufferSend` | **sin implementar** |

---

## Test

`SistemaRedTest.cpp` es el más corto del componente: 62 líneas que comprueban
que el nombre de la máquina no venga vacío. No puede hacer mucho más sin
depender de la red en la que corra.

---

## Observaciones

### Lo que no funciona fuera de Windows

- **Cuatro de las seis funciones tienen la rama POSIX vacía**, marcada
  `PENDIENTE`: el nombre DNS, las dos de accesibilidad y el envío de mensajes.
  En el modo de compilación por defecto —Cygwin POSIX— **este módulo sabe decir
  cómo se llama la máquina y poco más**.
- **`SisRedEnviarMensaje` no tiene equivalente moderno.** Envuelve
  `NetMessageBufferSend`, el servicio de mensajería de Windows NT que Microsoft
  retiró hace años; ni siquiera en Windows actual funciona. La rama POSIX
  clásica sería `wall` o `write`, que tampoco es lo mismo.
- **`NetServerEnum` enumera el dominio de red de Windows**, y `getaddrinfo`
  —lo que hace la rama POSIX de `SisRedOrdenadoresAccesibles`— resuelve un
  nombre. No son la misma operación: la función devuelve cosas distintas según
  dónde se compile, y eso no está escrito en ningún sitio.

### `std::wstring`

- **Es el único módulo de todo el stack C++ que usa cadenas anchas.** Viene de
  la API de red de Windows, que es nativa en UTF-16, y se ha filtrado hasta la
  cabecera pública.
- **Y las mezcla.** La firma que mejor lo enseña:

  ```cpp
  bool SisRedEnviarMensaje ( const std::wstring & sDestino,
                             const std::wstring & sOrigen,
                             const std::string  & sMensaje );
  ```

  Los nombres de máquina son anchos y el texto del mensaje es estrecho, en la
  misma llamada. Quien la use tiene que convertir en un sentido para los dos
  primeros argumentos y no para el tercero.
- **En POSIX no hay motivo para el `wchar_t`.** `gethostname` devuelve `char *`,
  así que la rama POSIX convierte a ancho para cumplir una firma que sólo
  necesitaba Windows. Es el coste de haber puesto el tipo de una plataforma en
  la API común.
- **`SisRedOrdenadoresAccesibles` devuelve `std::list<std::wstring> *`**: puntero
  desnudo a una lista reservada dentro, sin decir quién la libera.

### Otras

- **Ninguna función distingue «no accesible» de «no se pudo comprobar».**
  `SisRedServidorEsAccesible` devuelve `false` tanto si el servidor no está como
  si la consulta falló — o si se compiló en POSIX, donde siempre devuelve
  `false`.
- **No hay nada de direcciones IP**: ni la propia, ni resolución de nombres, ni
  interfaces. Lo poco que hay de eso está en `ResolverIP` de
  [gjs-cpp-common-base](../../gjs-cpp-common-base/README.md), en otro componente.
