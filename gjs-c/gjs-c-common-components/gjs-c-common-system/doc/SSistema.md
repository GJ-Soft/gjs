# SSistema

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/SSistema.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/SSistema.c` (1.860 líneas) |
| Prefijo      | `SSis`                                                  |
| Struct       | `SSistema`                                              |
| Funciones    | 19 declaradas · **34 implementadas sin declarar**       |
| Incluido por | **Nadie** — fuera de la fachada                         |
| Test         | `SSistemaTest.c` → `TestSSistema()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La versión **objeto** de [SistemaInformacion](SistemaInformacion.md): en lugar
de funciones sueltas que consultan el sistema cada vez, un objeto que se
construye una vez y cachea lo que ha averiguado.

```c
typedef struct
{
    int  iTipo;
    int  iSistema;
    int  iEjecComando;
    int  iOrdenBytes;
    int  iAdmiteSubprocesos;
    long lFechaInicial;

    SCadena * p_cadDirSistema;
    SCadena * p_cadDirFuentes;
    SCadena * p_cadDirTemporal;
} SSistema;
```

`lFechaInicial` es lo que no ofrece la versión de funciones: el momento en que
se creó el objeto, para poder medir contra él.

La cabecera lleva la marca `PENDIENTE: Falta terminar de adaptar de CPP`. Es un
tipo traído de la versión C++ del stack y no terminado.

## API declarada

### Ciclo de vida y sistema

| Función                                                            | Descripción                      |
| ------------------------------------------------------------------ | -------------------------------- |
| `SSistema * SSisCrear ()`                                          | Construye y consulta el sistema. |
| `void SSisDestruir ( SSistema ** )`                                | Destrucción.                     |
| `int SSisTipo ( SSistema * )` / `SSisSistema ( SSistema * )`       | `TIP_SIS_*` y `SIS_*`.           |
| `SSisEsDos` / `SSisEsWindows` / `SSisEsPosix` / `SSisEsMackintosh` | Predicados.                      |

### Orden de bytes

| Función                                                | Descripción         |
| ------------------------------------------------------ | ------------------- |
| `int SSisOrdenBytes ( SSistema * )`                    | El orden detectado. |
| `SSisOrdenBytesEsNormal` / `SSisOrdenBytesEsInvertido` | Los dos predicados. |

Es la única parte del componente que se ocupa del orden de bytes, y el objeto lo
detecta al construirse (`SSisObtenerOrdenBytes`). Enlaza con
[OrdenBytes](../../gjs-c-common-base/doc/OrdenBytes.md) de `gjs-c-common-base`.

### Directorios, comandos y estado

| Función                                                           | Descripción               |
| ----------------------------------------------------------------- | ------------------------- |
| `SCadena * SSisDirSistema` / `SSisDirFuentes` / `SSisDirTemporal` | Los tres directorios.     |
| `int SSisAdmiteSubprocesos ( SSistema * )`                        | Si se pueden crear.       |
| `long SSisFechaInicial ( SSistema * )`                            | Cuándo se creó el objeto. |
| `int SSisAdmiteEjecucionDeComandos ( SSistema * )`                | Si hay intérprete.        |
| `SSisEjecutarComando` / `SSisEjecutarComandoExt`                  | Lanza una orden.          |

## Test

`SSistemaTest.c` → `TestSSistema()`.

## Observaciones

> **`SSistema.c` implementa 34 funciones públicas que la cabecera no declara.**
>
> Las declaraciones están escritas, pero dentro de bloques `/* PENDIENTE … */`:
>
> | Grupo             | Funciones implementadas y no declaradas                                                                                     |
> |-------------------|------------------------------------------------------------------------------------------------------------------------------|
> | Arquitectura      | `SSisTamPalabraMemoria`                                                                                                      |
> | Ejecutables       | `SSisEsEjecutableDOS`, `SSisEsEjecutableUNIX`                                                                                |
> | Memoria           | `SSisMemoriaTotal`, `…Utilizada`, `…Disponible`, y las mismas para `Datos`, `Pila` y `Bloqueada`, más `SSisMemoriaFisica`     |
> | Segmentos         | `SSisTamPagina`, `SSisDirSegmentoCodigo`, `…Datos`, `…Pila`, `SSisDirBaseSegmentos`, `SSisLimInfSegmentos`, `SSisLimSupSegmentos` |
> | Validación        | `SSisDirValida`, `SSisDirAbsValida`, `…CodigoValida`, `…DatosValida`, `…PilaValida`                                          |
> | Descriptores      | `SSisDescriptoresESTotales`, `…Utilizados`, `…Disponibles`                                                                    |
> | Límites           | `SSisMaxTamFichero`, `SSisMaxTiempoCPU`, `SSisMaxNumProcesosPorUsuario`                                                       |
>
> El código está compilado y dentro de la librería: son símbolos exportados que
> ningún `#include` alcanza. Para usarlos hay que declararlos a mano en el
> fichero que los llame.
>
> Descomentar el bloque no basta, porque las declaraciones no coinciden con las
> implementaciones:
>
> - La cabecera declara `SSisDirValida ( SSistema *, long )`; el código
>   implementa `SSisDirValida ( long )`.
> - La cabecera escribe `MSSisaxNumProcesosPorUsuario`, con las letras
>   descolocadas; el código implementa `SSisMaxNumProcesosPorUsuario`.
>
> Es el defecto simétrico del de
> [SDominioReal](../../gjs-c-common-calculation/doc/Dominios.md) en
> `calculation`, donde lo declarado no estaba implementado. Aquí lo implementado
> no está declarado.

- **`SSistema.h` no entra por la fachada.** Ni `Sistema.h` la incluye ni ninguna
  otra cabecera, así que hay que incluirla a mano pese a tener 19 funciones
  declaradas y test propio.
- **No hay `SSisEsValido`**, único entre los objetos del componente.
- **Duplica a [SistemaInformacion](SistemaInformacion.md)**: `SSisTipo`,
  `SSisSistema`, `SSisEsWindows` y compañía responden lo mismo que `SisTipo`,
  `SisSistema` y `SisEsWindows`, y la memoria implementada sin declarar solapa
  con [SistemaMemoria](SistemaMemoria.md). Son tres módulos para el mismo
  conjunto de preguntas.
- **`SSisEjecutarComando` es un tercer camino** para lo mismo que hacen
  `SisEjecutarComando` de [Entorno](Entorno.md) y `SisCrearSubproceso` de
  [SistemaProcesos](SistemaProcesos.md).
- **`SSisTamPalabraMemoria` y los dos predicados de arquitectura de 32/64 bits
  están comentados en la cabecera**, y de los tres sólo el primero llegó a
  implementarse. Es justo el dato que hace falta para interpretar un fichero
  binario escrito en otro modo de compilación.
- **1.860 líneas para 19 funciones alcanzables.** Más de la mitad del fichero
  sostiene código inalcanzable.
