# InfoMemoria

| Dato         | Valor                                       |
| ------------ | ------------------------------------------- |
| Cabecera     | `src/main/include/InfoMemoria.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/InfoMemoria.c` |
| Prefijo      | `Mem`, `_GesMem` (interno)                  |
| Incluido por | `Base.h`                                    |
| Test         | — (sin test asociado)                       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Contabilidad de la memoria dinámica reservada a través de
[Memoria](Memoria.md): cuántos bloques hay vivos, cuántos se han reservado y
liberado en total, y cuánta memoria suman. Sirve para detectar fugas durante el
desarrollo.

**Todo el módulo está condicionado a `MODO_DEPURACION`.** En una compilación
normal tanto la cabecera como el fuente quedan vacíos y no se enlaza nada.

## Niveles

| Macro               | Qué añade                                                                                                                        |
| ------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| `MODO_DEPURACION`   | Contadores globales agregados.                                                                                                   |
| `MODO_DEPURACION_2` | Además, tabla de bloques individuales (hasta 65536) y traza por consola de cada reserva y liberación. Implica `MODO_DEPURACION`. |

## API

| Función                                           | Descripción                      |
| ------------------------------------------------- | -------------------------------- |
| `unsigned long MemReservadaBloques ()`            | Bytes actualmente reservados.    |
| `unsigned long MemReservadaTotal ()`              | Idéntica a la anterior.          |
| `unsigned long MemNumBloquesReservados ()`        | Total acumulado de reservas.     |
| `unsigned long MemNumBloquesLiberados ()`         | Total acumulado de liberaciones. |
| `unsigned long MemNumBloquesActuales ()`          | Bloques vivos ahora mismo.       |
| `void MemImprimirInforme ( int iMostrarBloques )` | Vuelca el informe por consola.   |

### Interfaz interna

`Memoria.c` avisa a este módulo mediante dos funciones que no aparecen en la
cabecera y se declaran `extern` en el punto de uso:

```c
void _MemBloqueReservado ( void * p_vDir, unsigned long ulTam );
void _MemBloqueLiberado  ( void * p_vDir, unsigned long ulTam );
```

Bajo `MODO_DEPURACION_2` estas funciones alimentan además la tabla
`_g_p_mblqTabla` a través de `_GesMemInicializar`, `_GesMemBuscar`,
`_GesMemReservar` y `_GesMemLiberar`.

## Comportamiento

Los contadores son cuatro variables globales (`g_ulNumBloquesReservados`,
`g_ulNumBloquesLiberados`, `g_ulNumBloques`, `g_ulTamBloques`) que se actualizan
en cada notificación. Están protegidos frente a bajar de cero, pero **no son
seguros frente a hilos**.

`MemImprimirInforme` imprime los bloques vivos y la memoria total; con
`MODO_DEPURACION_2` y `iMostrarBloques` a 1 lista también la dirección y el
tamaño de cada bloque no liberado.

La tabla de `MODO_DEPURACION_2` crece de forma monótona hasta
`_MEM_MAX_BLOQUES` (65536): las entradas liberadas se marcan pero no se
reutilizan, y la búsqueda es lineal, así que en programas con mucha rotación de
memoria el coste se nota.

## Dependencias

Ninguna hacia otros módulos. Es [Memoria](Memoria.md) quien depende de éste.

## Test

No tiene uno propio: al estar todo condicionado a `MODO_DEPURACION`, tendría
que compilarse con ese macro activo. Sí lo usa
[`SIndiceLiteralesTest.c`](../../gjs-c-common-types/doc/Localizacion.md), que
con `MODO_DEPURACION` compara `MemNumBloquesActuales` antes y después para
cazar fugas; sin el macro, ese caso no se compila.

## Observaciones

- `MemReservadaBloques` y `MemReservadaTotal` devuelven exactamente lo mismo
  (`g_ulTamBloques`); presumiblemente la segunda debería incluir también la
  memoria de la tabla de control.
- El `PENDIENTE` del fuente recuerda que en GNU no se contabiliza la memoria
  realmente reservada por falta de un equivalente a `_msize`/`HeapSize`, y
  sugiere apoyarse en `mallinfo`.
- Las trazas de `MODO_DEPURACION_2` imprimen la dirección con
  `(unsigned int) p_vDir`, lo que **trunca los punteros en 64 bits**.
