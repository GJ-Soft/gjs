# Red

| Dato      | Valor                            |
| --------- | -------------------------------- |
| Cabecera  | `SistemaRed.h` (65 líneas)       |
| Fuente    | `SistemaRed.cpp` (464 líneas)    |
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
| `SisRedNombreDNSOrdenador`    | El nombre completo de DNS         | `GetComputerNameEx`    | `getaddrinfo` (`AI_CANONNAME`) |
| `SisRedOrdenadoresAccesibles` | Lista de máquinas visibles        | `NetServerEnum`        | **lista vacía** ( limitación conocida ) |
| `SisRedServidorEsAccesible`   | ¿Está ese servidor?               | `NetServerGetInfo`     | `getaddrinfo` + `connect` TCP al 445 |
| `SisRedEstacionEsAccesible`   | ¿Está esa estación?               | `NetWkstaGetInfo`      | `getaddrinfo` + `connect` TCP al 445 |
| `SisRedEnviarMensaje`         | Aviso emergente a otra máquina    | `NetMessageBufferSend` | **no se declara** ( sólo WIN )       |

---

## Test

`SistemaRedTest.cpp` es el más corto del componente: 62 líneas que comprueban
que el nombre de la máquina no venga vacío. No puede hacer mucho más sin
depender de la red en la que corra.

---

## Observaciones

### Fuera de Windows

- **Las dos de accesibilidad ya funcionan** ( 2026-09-19 ). En Windows se le
  pregunta al servicio de la máquina remota; en POSIX se hace lo mismo por
  debajo: resolver el nombre con `getaddrinfo` e intentar una conexión TCP al
  puerto de SMB ( 445 ), que es justo el servicio al que pregunta Windows. El
  `connect` va **sin bloquear** y con una espera de 2 s, porque si la máquina
  está apagada un `connect` normal se queda colgado minutos. Se prueban todas
  las direcciones que devuelva la resolución ( IPv4 e IPv6 ) y basta con que una
  conteste.
- **No se usa ICMP** ( el `ping` ): abrir un socket de ese tipo pide privilegios
  de *root*, y una librería no puede contar con eso.
- **`SisRedEnviarMensaje` es sólo WIN.** Se apoya en `NetMessageBufferSend`, el
  servicio de mensajería de Windows, que no tiene equivalente: no hay mecanismo
  estándar en POSIX para hacerle llegar un aviso emergente a otra máquina. Fuera
  de Windows **no se declara**, para que quien la llame se encuentre un error de
  compilación en vez de un `false` que no significa nada. La rama POSIX clásica
  sería `wall` o `write`, que tampoco es lo mismo.
- **Ni en Windows funciona**, y sigue en pie la nota de siempre: el servicio
  Messenger está desactivado por defecto desde Vista, así que
  `NetMessageBufferSend` contesta error salvo que alguien lo levante a mano. Eso
  es del sistema, no del código.
- **`SisRedOrdenadoresAccesibles` devuelve la lista vacía en POSIX**, y es una
  limitación conocida, no un descuido. `NetServerEnum` interroga al servicio de
  navegación de SMB de la red local, y fuera de Windows no hay nada equivalente
  en la biblioteca estándar: enumerar las máquinas de la red pide o hablar SMB
  ( `libsmbclient` ) o mDNS ( Avahi ), dependencias externas que este stack no
  tiene. Quien necesite la lista, que pregunte máquina a máquina con las dos de
  accesibilidad.

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
  si la consulta falló, y en POSIX también si el 445 está cerrado en una máquina
  que sí está encendida.
- **En POSIX las dos de accesibilidad hacen exactamente lo mismo.** La distinción
  servidor / estación es del dominio de Windows NT, un rol declarado en el
  dominio; fuera de ahí no significa nada, y las dos contestan a la misma
  pregunta: «¿responde esta máquina?».
- **No hay nada de direcciones IP**: ni la propia, ni resolución de nombres, ni
  interfaces. Lo poco que hay de eso está en `ResolverIP` de
  [gjs-cpp-common-base](../../gjs-cpp-common-base/README.md), en otro componente.
