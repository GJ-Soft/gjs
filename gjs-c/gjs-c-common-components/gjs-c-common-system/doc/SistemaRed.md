# SistemaRed

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/SistemaRed.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SistemaRed.c` (518 líneas) |
| Prefijo      | `SisRed`                                                |
| Funciones    | 6                                                       |
| Incluido por | `Sistema.h`                                             |
| Test         | `SistemaRedTest.c` → `TestSistemaRed()`                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Lo mínimo de red: cómo se llama esta máquina y si otras están accesibles. No es
una librería de sockets ni de protocolos; es la parte de "red" que se considera
información del sistema.

## API

| Función                                                         | Descripción                  |
| --------------------------------------------------------------- | ---------------------------- |
| `char * SisRedNombreOrdenador ()`                               | Nombre corto de la máquina.  |
| `char * SisRedNombreDNSOrdenador ()`                            | Nombre canónico completo.    |
| `SListaLiterales * SisRedOrdenadoresAccesibles ()`              | Máquinas visibles en la red. |
| `int SisRedServidorEsAccesible ( const char * p_cServidor )`    | 1 si responde.               |
| `int SisRedEstacionEsAccesible ( const char * p_cEstacion )`    | Idem para una estación.      |
| `int SisRedEnviarMensaje ( p_cDestino, p_cOrigen, p_cMensaje )` | Mensaje a otra máquina. **Sólo WIN.** |

Cómo se resuelve cada una en cada modo:

| Función                       | Windows              | POSIX / Cygwin                          |
| ----------------------------- | -------------------- | --------------------------------------- |
| `SisRedNombreOrdenador`       | `gethostname`        | `gethostname`                           |
| `SisRedNombreDNSOrdenador`    | `gethostname` + `getaddrinfo` con `ai_canonname` | igual       |
| `SisRedServidorEsAccesible`   | `NetServerGetInfo`   | `getaddrinfo` + `connect` TCP al 445     |
| `SisRedEstacionEsAccesible`   | `NetWkstaGetInfo`    | `getaddrinfo` + `connect` TCP al 445     |
| `SisRedOrdenadoresAccesibles` | `NetServerEnum`      | **lista vacía** ( limitación conocida )  |
| `SisRedEnviarMensaje`         | `NetMessageBufferSend` | **no se declara**                      |

`SisRedNombreDNSOrdenador` resuelve el nombre corto contra el DNS para quedarse
con el canónico, que es lo que distingue `servidor` de `servidor.empresa.local`.

## Dependencias

[SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md),
[SBuffer](../../gjs-c-common-base-types/doc/SBuffer.md) y
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md).

En Windows, la API de red de Lan Manager: `NetMessageBufferSend`,
`NetServerGetInfo`, `NetServerEnum`.

## Test

`SistemaRedTest.c` → `TestSistemaRed()`.

## Observaciones

- **Las dos de accesibilidad ya funcionan fuera de Windows** ( 2026-09-19 ). En
  Windows se le pregunta al servicio de la máquina remota; en POSIX se hace lo
  mismo por debajo: resolver el nombre con `getaddrinfo` e intentar una conexión
  TCP al puerto de SMB ( 445 ), que es justo el servicio al que pregunta
  Windows. El `connect` va **sin bloquear** y con una espera de 2 s, porque si la
  máquina está apagada un `connect` normal se queda colgado minutos. Se prueban
  todas las direcciones que devuelva la resolución ( IPv4 e IPv6 ) y basta con
  que una conteste.
- **No se usa ICMP** ( el `ping` ), que sería lo primero que viene a la cabeza:
  abrir un socket de ese tipo pide privilegios de *root*, y una librería no
  puede contar con eso.
- **`SisRedEnviarMensaje` es sólo WIN**, como `SisTituloProceso`. Se apoya en
  `NetMessageBufferSend`, el servicio de mensajería de Windows, que no tiene
  equivalente: no hay mecanismo estándar en POSIX para hacerle llegar un aviso
  emergente a otra máquina. Fuera de Windows **no se declara**, para que quien la
  llame se encuentre un error de compilación en vez de un 0 que no significa
  nada.
- **`SisRedEnviarMensaje` tampoco funciona en Windows**, y sigue en pie la nota
  de siempre. El servicio Messenger está desactivado por defecto desde Vista, así
  que `NetMessageBufferSend` contesta error salvo que alguien lo levante a mano.
  Eso es del sistema, no del código.
- **`SisRedOrdenadoresAccesibles` devuelve la lista vacía en POSIX**, y es una
  limitación conocida, no un descuido. En Windows lo contesta `NetServerEnum`,
  que interroga al servicio de navegación de SMB de la red local. Fuera de
  Windows no hay nada equivalente en la biblioteca estándar: enumerar las
  máquinas de la red pide o hablar SMB ( `libsmbclient` ) o mDNS ( Avahi ),
  dependencias externas que este stack no tiene. Quien necesite la lista, que
  pregunte máquina a máquina con las dos de accesibilidad.
- **`SisRedServidorEsAccesible` y `SisRedEstacionEsAccesible` son conceptos de
  dominio Windows NT**, no de red en general: distinguen un servidor de una
  estación de trabajo según el rol declarado en el dominio. Fuera de ese contexto
  la distinción no significa nada, y en POSIX las dos hacen exactamente lo
  mismo: "¿responde esta máquina?".
- **`SisRedServidorEsAccesible` tenía la lógica invertida** en la rama Windows:
  devolvía 0 al acertar y 1 al fallar, justo lo contrario que su gemela
  `SisRedEstacionEsAccesible`, que hace la misma llamada. Arreglado.
- **No hay nada de direcciones IP.** Ni obtener la propia, ni resolver un nombre
  a IP, ni comprobar conectividad. `getaddrinfo` ya está en el código, usado sólo
  para sacar el nombre canónico.
- **`SisRedNombreOrdenador` reserva el búfer con un tamaño fijo** y no reintenta
  si `gethostname` no cabe; un nombre largo se trunca sin aviso.
- El módulo devuelve `char *` y `SListaLiterales *` que el llamante debe liberar,
  sin que la cabecera lo indique.
