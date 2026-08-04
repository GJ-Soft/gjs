# Memoria

| Dato      | Valor                                |
| --------- | ------------------------------------ |
| Cabecera  | `SistemaMemoria.h` (66 líneas)       |
| Fuente    | `SistemaMemoria.cpp` (464 líneas)    |
| Espacio   | `org::gjs::cpp::common`              |
| Prefijo   | `SisMemoria`                         |
| Funciones | 14                                   |
| Test      | `SistemaMemoriaTest.cpp` (92 líneas) |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Cuánta memoria hay y cuánta queda, en cuatro escalas.

```cpp
unsigned long long ullLibre = SisMemoriaDisponible ();
double dOcupadaPorc         = SisMemoriaOcupadaPorc ();
```

## La API

Cuatro grupos con la misma forma —total, disponible y ocupada—, y dos
porcentajes:

| Grupo                 | Funciones                                                                        |
| --------------------- | -------------------------------------------------------------------------------- |
| Global                | `SisMemoriaTotal`, `SisMemoriaDisponible`, `SisMemoriaOcupada`                   |
| Porcentaje            | `SisMemoriaDisponiblePorc`, `SisMemoriaOcupadaPorc`                              |
| Física                | `SisMemoriaFisicaTotal`, `SisMemoriaFisicaDisponible`, `SisMemoriaFisicaOcupada` |
| Fichero de paginación | `SisMemoriaFicPaginacionTotal`, `…Disponible`, `…Ocupada`                        |
| Montón                | `SisMemoriaHeapTotal`, `SisMemoriaHeapMin`, `SisMemoriaHeapMax`                  |

Todas devuelven `unsigned long long`, que es la decisión correcta: en una máquina
con más de 4 GB, un `unsigned long` de 32 bits —el de Windows puro— se queda
corto.

## De dónde salen los números

| Plataforma | Fuente                                                      |
| ---------- | ----------------------------------------------------------- |
| Windows    | `GlobalMemoryStatusEx`, nueve veces                         |
| POSIX      | `sysinfo` de `<sys/sysinfo.h>`, más `sysconf` y `getrlimit` |
| Montón     | `/proc/self/maps` en POSIX; **nada en Windows**             |

---

## Test

`SistemaMemoriaTest.cpp` comprueba coherencia: que el total sea mayor que cero,
que ocupada más disponible no pase del total, y que los porcentajes caigan entre
0 y 100. Es lo correcto para valores que cambian entre ejecuciones.

---

## Observaciones

- **Once de las catorce están bien resueltas**, y son la mejor parte del
  componente: existen en las dos plataformas, no llevan ninguna marca
  `PENDIENTE`, el tipo de retorno aguanta máquinas grandes y el test comprueba
  invariantes en vez de valores fijos.
- **Las tres del montón no.** `SisMemoriaHeapMax` tiene esto en la rama Windows:

  ```cpp
  # if ( defined ( WIN ) )
      // Error:
      ullRes = 0;
  ```

  y en POSIX lee **la primera línea de `/proc/self/maps`**, que es la primera
  región del espacio de direcciones —normalmente el código del ejecutable—, no
  el montón. `SisMemoriaHeapTotal` es la resta de las otras dos, así que hereda
  el error: **en Windows devuelve 0 y en POSIX un número que no es el montón**.
  Ninguna de las tres está cubierta por el test, que sólo mira las once buenas.
- **«Memoria global» es un concepto de Windows.** `GlobalMemoryStatusEx`
  distingue memoria física y fichero de paginación, y llama «total» a la suma.
  En POSIX el equivalente de `sysinfo` no reparte igual, así que los tres
  primeros valores no significan exactamente lo mismo en un sistema y en otro.
  No está documentado en la cabecera.
- **Los tres del montón pretenden medir el del proceso, no el del sistema**, a
  diferencia de los otros once. La cabecera no lo distingue:
  `SisMemoriaHeapTotal` se lee igual que `SisMemoriaTotal` y hablan de cosas
  distintas.
- **Cero es a la vez un valor válido y el código de error.** Ninguna función
  puede decir «no lo sé»; si la llamada al sistema falla, devuelven 0, que en
  `SisMemoriaDisponible` es una respuesta alarmante y verosímil.
- **Los porcentajes se calculan sobre el total global**, así que arrastran la
  diferencia de significado anterior.
- **No hay memoria por proceso**, que es lo que suele hacer falta cuando se mira
  esto desde un programa: cuánta está usando *este* proceso. `SistemaProcesos`
  tampoco la tiene.
