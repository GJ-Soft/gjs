# Clases y módulos de gjs-cpp-common-base

[README](../README.md)

31 cabeceras y 24 fuentes en 9.008 líneas: 10 clases y once conjuntos de
funciones libres.

---

## Clases

### Raíz y contratos

| Clase         | Cabecera        | Deriva de   | Test | Documento                     |
| ------------- | --------------- | ----------- | ---- | ----------------------------- |
| `Objeto`      | `Objeto.h`      | —           | ✔    | [Objeto](Objeto.md)           |
| `IToString`   | `IToString.h`   | —           | ✔    | [IToString](IToString.md)     |
| `IComparable` | `IComparable.h` | `IToString` | ✔    | [IComparable](IComparable.md) |

### Excepciones

| Clase                   | Cabecera                  | Deriva de            | Test | Documento                                         |
| ----------------------- | ------------------------- | -------------------- | ---- | ------------------------------------------------- |
| `Excepcion`             | `Excepcion.h`             | `std::runtime_error` | ✔    | [Excepcion](Excepcion.md)                         |
| `FinExcepcion`          | `FinExcepcion.h`          | `Excepcion`          | —    | [FinExcepcion](FinExcepcion.md)                   |
| `NoEncontradoExcepcion` | `NoEncontradoExcepcion.h` | `Excepcion`          | —    | [NoEncontradoExcepcion](NoEncontradoExcepcion.md) |
| `SistemaExcepcion`      | `SistemaExcepcion.h`      | `Excepcion`          | —    | [SistemaExcepcion](SistemaExcepcion.md)           |

### Utilidad

| Clase       | Cabecera      | Deriva de | Test | Documento                 |
| ----------- | ------------- | --------- | ---- | ------------------------- |
| `Conversor` | `Conversor.h` | —         | ✔    | [Conversor](Conversor.md) |
| `HayError`  | `HayError.h`  | —         | —    | [HayError](HayError.md)   |
| `Depurador` | `Depurador.h` | `Objeto`  | —    | [Depurador](Depurador.md) |

---

## Funciones libres

| Módulo                | Cabeceras                           | Funciones  | Test | Documento                                       |
| --------------------- | ----------------------------------- | ---------- | ---- | ----------------------------------------------- |
| Cadenas               | `Cadenas.h`                         | 52         | ✔    | [Cadenas](Cadenas.md)                           |
| Conversiones          | `ToString.h`, `ToInt.h`, `ToReal.h` | 45         | ✔    | [Conversiones](Conversiones.md)                 |
| Concatenar            | `Concatenar.h`                      | 3          | ✔    | [Concatenar](Concatenar.md)                     |
| Colecciones           | `Colecciones.h`                     | 4          | ✔    | [Colecciones](Colecciones.md)                   |
| Codificación          | `Codificacion.h`                    | 4          | ✔    | [Codificacion](Codificacion.md)                 |
| Reales                | `Real.h`                            | 6          | ✔    | [Real](Real.md)                                 |
| Expresiones regulares | `ExpresionesRegulares.h`            | 1          | ✔    | [ExpresionesRegulares](ExpresionesRegulares.md) |
| Ficheros              | `Ficheros.h`                        | 6          | ✔    | [Ficheros](Ficheros.md)                         |
| Sistema               | `Sistema.h`                         | 25         | ✔    | [Sistema](Sistema.md)                           |
| Memoria               | `Memoria.h`, `InfoMemoria.h`        | 5 + macros | ✔    | [Memoria](Memoria.md)                           |
| ASCII                 | `ASCIICodigos.h`, `ASCIIEstandar.h` | 36         | ✔    | [ASCII](ASCII.md)                               |

---

## Cabeceras de configuración

| Cabecera           | Qué aporta                                   | Documento                         |
| ------------------ | -------------------------------------------- | --------------------------------- |
| `CppBase.h`        | La fachada: 30 `#include`                    | —                                 |
| `Precompilacion.h` | Normalización de macros de plataforma        | [Configuración](Configuracion.md) |
| `BaseConfig.h`     | Límites y constantes                         | [Configuración](Configuracion.md) |
| `Prototipos.h`     | `PROCEDIMIENTO`, `FUNCION_BOOL`              | [Configuración](Configuracion.md) |
| `Funciones.h`      | La familia `PPRCV`, `PPRCI`, `PPRCL`…        | [Configuración](Configuracion.md) |
| `TerminalANSI.h`   | Colores y atributos de terminal, en `::ansi` | [Configuración](Configuracion.md) |

---

## La fachada `CppBase.h`

Treinta `#include`, en orden de dependencia: primero la plataforma
(`Precompilacion.h`, `BaseConfig.h`, `Memoria.h`), después las utilidades
(`Cadenas.h`, `ToString.h`, `Concatenar.h`…), luego los contratos (`Objeto.h`,
`IComparable.h`) y por último las excepciones y la capa de sistema.

Trae todo el componente: no hay nada fuera de la fachada, a diferencia de lo que
ocurre en varios componentes del stack C.

`EnvolturasSistema.cpp` es el único fuente sin cabecera propia: envuelve
llamadas del sistema para el resto del módulo.
