# SistemaMemoria

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabecera     | `src/main/include/SistemaMemoria.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SistemaMemoria.c` (442 líneas) |
| Prefijo      | `Sis`                                                       |
| Funciones    | 14                                                          |
| Incluido por | `Sistema.h`                                                 |
| Test         | `SistemaMemoriaTest.c` → `TestSistemaMemoria()`             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Cuánta memoria hay en la máquina y cuánta queda. Todas las cifras son
`unsigned long long`, así que el módulo no tiene el problema de los 4 GB que
arrastran otras partes del stack.

No confundir con:

| Módulo                                                    | Responde a                                |
| --------------------------------------------------------- | ----------------------------------------- |
| `SistemaMemoria`                                          | Cuánta memoria hay **en la máquina**      |
| [SistemaInformacion](SistemaInformacion.md)               | Qué direcciones puede usar **el proceso** |
| [Memoria](../../gjs-c-common-base/doc/Memoria.md)         | Reservar y liberar                        |
| [InfoMemoria](../../gjs-c-common-base/doc/InfoMemoria.md) | Cuánto ha reservado **el propio stack**   |

## API

Cuatro grupos con el mismo esquema `Total` / `Disponible` / `Ocupada`:

| Grupo                 | Funciones                                                                           |
| --------------------- | ----------------------------------------------------------------------------------- |
| Virtual               | `SisMemoriaTotal`, `SisMemoriaDisponible`, `SisMemoriaOcupada`                      |
| Física                | `SisMemoriaFisicaTotal`, `…FisicaDisponible`, `…FisicaOcupada`                      |
| Fichero de paginación | `SisMemoriaFicPaginacionTotal`, `…FicPaginacionDisponible`, `…FicPaginacionOcupada` |
| Heap                  | `SisMemoriaHeapTotal`, `SisMemoriaHeapMin`, `SisMemoriaHeapMax`                     |

Y dos porcentajes: `double SisMemoriaDisponiblePorc ()` y
`double SisMemoriaOcupadaPorc ()`.

```c
printf ( "RAM: %llu / %llu (%.1f%% libre)\n",
         SisMemoriaFisicaDisponible (),
         SisMemoriaFisicaTotal (),
         SisMemoriaDisponiblePorc () );
```

## Implementación

| Modo    | Física y paginación          | Virtual                   |
| ------- | ---------------------------- | ------------------------- |
| Windows | `GlobalMemoryStatusEx`       | `GlobalMemoryStatusEx`    |
| POSIX   | `sysinfo` (`struct sysinfo`) | `getrlimit ( RLIMIT_AS )` |

`SisMemoriaFisicaDisponible` suma `freeram + bufferram`, que es la lectura
razonable: la memoria de búferes se puede recuperar. `SisMemoriaHeapTotal` es
`Max - Min` y usa `sysconf ( _SC_PAGESIZE )`.

## Dependencias

Ninguna del stack: sólo el sistema operativo.

## Test

`SistemaMemoriaTest.c` → `TestSistemaMemoria()`.

## Observaciones

- **`SisMemoriaTotal` no devuelve la memoria de la máquina en POSIX.** Usa
  `getrlimit ( RLIMIT_AS )`, que es el **límite de espacio de direcciones del
  proceso**, no memoria del sistema. En Cygwin y en Linux ese límite suele ser
  `RLIM_INFINITY`, así que la función devuelve un número astronómico —o 0 si el
  `getrlimit` falla— mientras que en Windows devuelve `ullTotalVirtual`. Las dos
  ramas responden a preguntas distintas.
- **Y eso contamina los porcentajes**: `SisMemoriaDisponiblePorc` y
  `…OcupadaPorc` se calculan sobre la memoria virtual, no sobre la física, así
  que en POSIX salen de un divisor sin sentido. El dato que casi siempre se
  quiere es el de la rama física.
- **`sysinfo` no es POSIX, es Linux.** Compila en Cygwin porque Cygwin lo emula,
  pero no existe en macOS ni en los BSD. Cuando llegue el cuarto modo de
  compilación esto seguirá funcionando en Linux y no en el resto.
- **Un fallo devuelve 0, igual que un valor legítimamente nulo.** Las catorce
  funciones ponen `ullRes = 0` en la rama de error, sin registrar nada en
  [SistemaErrores](SistemaErrores.md), así que el llamante no puede distinguir
  "no hay swap" de "no he podido consultarlo".
- `SisMemoriaHeapMin` y `…HeapMax` devuelven direcciones del montón como
  `unsigned long long`, no como `void *`, a diferencia de
  `SisMemAplicDireccionMinima` de [SistemaInformacion](SistemaInformacion.md),
  que sí devuelve punteros. Los dos módulos exponen la misma clase de dato con
  tipos distintos.
