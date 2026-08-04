# Módulos de gjs-cpp-common-system

[README](../README.md)

22 cabeceras y 18 fuentes en 8.803 líneas: **4 clases** y unas 130 funciones
libres, repartidas en 150 declaraciones públicas.

---

## Índice

| Módulo                  | Cabecera                  | Declara | Fuente       | Test                            | Documento                               |
| ----------------------- | ------------------------- | ------- | ------------ | ------------------------------- | --------------------------------------- |
| `SistemaProcesos`       | `SistemaProcesos.h`       | 36      | 1.331 líneas | `SistemaProcesosTest.cpp`       | [Procesos](Procesos.md)                 |
| `SistemaInformacion`    | `SistemaInformacion.h`    | 27      | 737          | `SistemaInformacionTest.cpp`    | [Informacion](Informacion.md)           |
| `SistemaMemoria`        | `SistemaMemoria.h`        | 14      | 464          | `SistemaMemoriaTest.cpp`        | [Memoria](Memoria.md)                   |
| `SistemaErrores`        | `SistemaErrores.h`        | 13      | 277          | `SistemaErroresTest.cpp`        | [Errores](Errores.md)                   |
| `SistemaSignals`        | `SistemaSignals.h`        | 11      | 594          | `SistemaSignalsTest.cpp`        | [Senales](Senales.md)                   |
| `CGestorSignals`        | `CGestorSignals.h`        | 10      | 464          | `CGestorSignalsTest.cpp`        | [Senales](Senales.md)                   |
| `TiposSistema`          | `TiposSistema.h`          | 8       | 126          | `TiposSistemaTest.cpp`          | [Informacion](Informacion.md)           |
| `SistemaRed`            | `SistemaRed.h`            | 6       | 353          | `SistemaRedTest.cpp`            | [Red](Red.md)                           |
| `SistemaSincronizacion` | `SistemaSincronizacion.h` | 5       | 120          | `SistemaSincronizacionTest.cpp` | [Sincronizacion](Sincronizacion.md)     |
| `CContadorCiclos`       | `CContadorCiclos.h`       | 4       | 99           | `CContadorCiclosTest.cpp`       | [Tiempo](Tiempo.md)                     |
| `CTemporizador`         | `CTemporizador.h`         | 4       | 93           | `CTemporizadorTest.cpp`         | [Tiempo](Tiempo.md)                     |
| `CVariablesEntorno`     | `CVariablesEntorno.h`     | 4       | 111          | `CVariablesEntornoTest.cpp`     | [VariablesEntorno](VariablesEntorno.md) |
| `SistemaEstado`         | `SistemaEstado.h`         | 3       | 176          | `SistemaEstadoTest.cpp`         | [Errores](Errores.md)                   |
| `SistemaTiempo`         | `SistemaTiempo.h`         | 2       | 85           | `SistemaTiempoTest.cpp`         | [Tiempo](Tiempo.md)                     |
| `SistemaComandos`       | `SistemaComandos.h`       | 1       | 99           | **—**                           | [Procesos](Procesos.md)                 |
| `Sistema`               | — (la fachada)            | 2       | 72           | **—**                           | esta página                             |
| `TestAndSet`            | `TestAndSet.h`            | macros  | 13           | **—**                           | [Sincronizacion](Sincronizacion.md)     |
| **`SistemaRegistro`**   | **no existe**             | —       | **1.861**    | **—**                           | [SistemaRegistro](SistemaRegistro.md)   |

Llama la atención la última fila: el fichero más grande del componente no tiene
cabecera, ni test, ni documento propio en el sentido normal — sólo un informe de
lo que le pasa.

---

## La fachada `CppCommonSystem.h`

Incluye **ocho módulos de funciones y las cuatro clases**, y declara ella misma
dos funciones que no están en ninguna otra cabecera:

```cpp
void SisInicializar ( const std::string & sNomProceso = "", const std::string & sDirTemporal = "" );
void SisFinalizar ();
```

Las implementa `Sistema.cpp`, que es el único fuente del componente sin cabecera
propia legítima: su API vive en la fachada.

### Lo que la fachada deja fuera

| Cabecera                                                    | ¿Debería estar?                                                                |
| ----------------------------------------------------------- | ------------------------------------------------------------------------------ |
| `SistemaErrores.h`                                          | **Sí.** Es API pública —trece funciones— y hay que incluirla a mano            |
| `SistemaSincronizacion.h`                                   | **Sí**, por el mismo motivo                                                    |
| `TestAndSet.h`                                              | Discutible: son dos macros de bajo nivel                                       |
| `TiposSistema.h`                                            | Llega de rebote, vía `SistemaInformacion.h`                                    |
| `Sistemas.h`, `Procesadores.h`, `ArquitecturasProcesador.h` | Llegan de rebote, igual                                                        |
| `SistemaTiposErrores.h`                                     | Llega vía `CommonSystemConfig.h`, que **no se publica**: desde fuera, no llega |
| `CommonSystemConfig.h`                                      | No: es configuración interna                                                   |

La última fila es la que importa: `SistemaTiposErrores.h` define los tipos de
error que devuelve `SisErrTipo()`, y **un consumidor de la fachada no los tiene**.

---

## Las cuatro clases

| Clase               | Qué envuelve                         | Estado interno           |
| ------------------- | ------------------------------------ | ------------------------ |
| `CTemporizador`     | La espera del sistema                | Un `int` de milisegundos |
| `CContadorCiclos`   | El contador de ciclos del procesador | Tres valores             |
| `CVariablesEntorno` | Las variables de entorno del proceso | **ninguno**              |
| `CGestorSignals`    | La tabla de manejadores de señales   | Cinco tablas y un enlace |

**Todas llevan prefijo `C`**, que no usa ninguna otra clase del stack C++
—`Fecha`, `Socket`, `Comando`, `Hora`…—, y métodos con los prefijos `Obt` y
`Est` en vez de `get` y `set`. Es la nomenclatura de la librería original de
2008, que aquí no se llegó a alinear.

---

## Windows y POSIX

Es el componente donde más pesa la diferencia. Además de las ramas dentro de
cada función, hay piezas que **sólo existen en un lado**:

| Pieza                                       | POSIX         | Windows          |
| ------------------------------------------- | ------------- | ---------------- |
| `CGestorSignals` (la clase entera)          | sí            | **no**           |
| `SisProcInicializar` / `SisProcFinalizar`   | sí            | **no**           |
| `SisInicializarVariableSinc` / `Finalizar…` | sí            | **no**           |
| `SisDirectorioSistema`                      | **no**        | sí               |
| `SisWinIdProceso`                           | **no**        | sí               |
| Señales programables                        | 30            | 15               |
| `SistemaRegistro`                           | **no aplica** | sí, y no compila |

Que la API cambie de forma según la plataforma es inevitable en un componente
así; lo que no está resuelto es **avisarlo**: no hay una función que diga «esto
aquí no está», de modo que el usuario lo descubre al compilar.
