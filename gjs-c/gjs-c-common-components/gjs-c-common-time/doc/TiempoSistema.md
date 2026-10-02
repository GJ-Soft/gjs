# TiempoSistema

| Dato         | Valor                                         |
| ------------ | --------------------------------------------- |
| Cabecera     | `src/main/include/TiempoSistema.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/TiempoSistema.c` |
| Prefijo      | `Tiempo`                                      |
| Funciones    | 7                                             |
| Incluido por | `Tiempo.h`                                    |
| Test         | `TiempoSistemaTest.c` → `TestTiempoSistema()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La frontera con el reloj del sistema operativo: leer la fecha y la hora
actuales, esperar, y convertir a y desde la época UNIX.

Es el único módulo de la librería que consulta el exterior; todo lo demás opera
sobre valores que se le dan.

## API

### Lectura del reloj

| Función                         | Devuelve                                                              |
| ------------------------------- | --------------------------------------------------------------------- |
| `long TiempoHoy ()`             | La fecha de hoy en formato `AAAAMMDD`.                                |
| `long TiempoAhora ()`           | La hora actual en formato `HHMMSS`.                                   |
| `double TiempoHoyAhora ()`      | Fecha y hora combinadas, como en [TiempoNumerico](TiempoNumerico.md). |
| `long long TiempoHoyAhoraLL ()` | Ídem sobre `long long`.                                               |

### Espera

| Función                                           | Descripción           |
| ------------------------------------------------- | --------------------- |
| `void TiempoEsperar ( unsigned long ulSegundos )` | Detiene la ejecución. |

### Época UNIX

| Función                                             | Descripción                              |
| --------------------------------------------------- | ---------------------------------------- |
| `double TiempoTransformarAUNIX ( double dTiempo )`  | Del formato de la librería a época UNIX. |
| `double TiempoTransformarDeUNIX ( double dTiempo )` | De época UNIX al formato de la librería. |

Son la vía para interoperar con `time_t` y con cualquier sistema externo.

```c
long lHoy = TiempoHoy ();       /* 20260801 */
long lAhora = TiempoAhora ();   /* 143005   */

TiempoEsperar ( 5 );            /* cinco segundos */
```

## Dependencias

- `<unistd.h>` fuera de Windows, vía `TiempoConfig.h`.
- [Fechas](Fechas.md) y [Horas](Horas.md) para componer los formatos.

## Test

`TiempoSistemaTest.c` → `TestTiempoSistema()`.

## Observaciones

- **La cabecera incluye `<Precompilacion.h>` directamente**, en lugar de
  `Base.h`, que es lo que hace el resto del stack. Le basta porque sólo
  declara tipos nativos, pero rompe el patrón.
- **`TiempoEsperar` no dice qué hace bajo Windows.** Fuera de Windows
  `TiempoConfig.h` incluye `<unistd.h>`, lo que apunta a `sleep`; en Windows
  tendrá que ser `Sleep` en milisegundos. La resolución es de **segundos
  enteros**: no hay forma de esperar menos.
- **No hay control de errores.** `TiempoHoy` y `TiempoAhora` devuelven `long` sin
  valor reservado para el fallo, así que si la consulta al sistema fallara no
  habría manera de distinguirlo de una fecha válida.
- Las funciones de conversión UNIX trabajan con `double`, no con `time_t`, de
  modo que la llamada queda a cargo del programador. La cabecera no indica si la
  época de referencia lleva ya aplicada la zona horaria o es UTC.
- El prefijo `Tiempo` lo comparte con dos funciones de
  [TiempoNumerico](TiempoNumerico.md), lo que impide saber de qué módulo viene
  una llamada sólo por el nombre.
