# SistemaRed

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/SistemaRed.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SistemaRed.c` (387 líneas) |
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
| `int SisRedEnviarMensaje ( p_cDestino, p_cOrigen, p_cMensaje )` | Mensaje a otra máquina.      |

Las dos primeras son las que funcionan en los dos modos:

| Función                    | Implementación                                   |
| -------------------------- | ------------------------------------------------ |
| `SisRedNombreOrdenador`    | `gethostname`                                    |
| `SisRedNombreDNSOrdenador` | `gethostname` + `getaddrinfo` con `ai_canonname` |

La segunda resuelve el nombre corto contra el DNS para quedarse con el
canónico, que es lo que distingue `servidor` de `servidor.empresa.local`.

## Dependencias

[SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md),
[SBuffer](../../gjs-c-common-base-types/doc/SBuffer.md) y
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md).

En Windows, la API de red de Lan Manager: `NetMessageBufferSend`,
`NetServerGetInfo`, `NetServerEnum`.

## Test

`SistemaRedTest.c` → `TestSistemaRed()`.

## Observaciones

- **Cuatro de las seis funciones son un `PENDIENTE` fuera de Windows**:
  `SisRedEnviarMensaje`, `SisRedOrdenadoresAccesibles`,
  `SisRedServidorEsAccesible` y `SisRedEstacionEsAccesible` devuelven 0 o `NULL`
  en el modo normal. Las dos que sí funcionan en los dos modos son las de
  nombre de máquina.
- **`SisRedEnviarMensaje` tampoco funciona en Windows**, y el código lo dice:
  *"PENDIENTE: La siguiente rutina no parce funcionar"*. Se apoya en
  `NetMessageBufferSend`, que dependía del servicio Messenger, retirado de
  Windows a partir de Vista. La función no tiene arreglo por esa vía.
- **`SisRedServidorEsAccesible` y `SisRedEstacionEsAccesible` son conceptos de
  dominio Windows NT**, no de red en general: distinguen un servidor de una
  estación de trabajo según el rol declarado en el dominio. Fuera de ese
  contexto la distinción no significa nada, y lo que se querría —"¿responde esta
  máquina?"— no está.
- **No hay nada de direcciones IP.** Ni obtener la propia, ni resolver un nombre
  a IP, ni comprobar conectividad. `getaddrinfo` ya está en el código, usado sólo
  para sacar el nombre canónico.
- **`SisRedNombreOrdenador` reserva el búfer con un tamaño fijo** y no reintenta
  si `gethostname` no cabe; un nombre largo se trunca sin aviso.
- El módulo devuelve `char *` y `SListaLiterales *` que el llamante debe liberar,
  sin que la cabecera lo indique.
