# Información del sistema

| Dato      | Valor                                                                                                                          |
| --------- | ------------------------------------------------------------------------------------------------------------------------------ |
| Cabeceras | `SistemaInformacion.h` (96), `TiposSistema.h` (71), `Sistemas.h` (91), `Procesadores.h` (64), `ArquitecturasProcesador.h` (41) |
| Fuentes   | `SistemaInformacion.cpp` (737), `TiposSistema.cpp` (126)                                                                       |
| Espacio   | `org::gjs::cpp::common`                                                                                                        |
| Prefijos  | `Sis`, `TipSis`                                                                                                                |
| Declara   | 27 + 8                                                                                                                         |
| Tests     | `SistemaInformacionTest.cpp`, `TiposSistemaTest.cpp`                                                                           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Responder a «¿dónde estoy corriendo?»: qué familia de sistema operativo, qué
versión, qué procesador, cuántos núcleos, qué sabe hacer la CPU y dónde están
los directorios del sistema.

```cpp
if ( SisEsPosix () )        { ... }
if ( SisEsWindows () )      { ... }

int    iCPUs   = SisNumProcesadores ();
double dVersion = SisVersion ();
std::string * pTmp = SisDirectorioTemporal ();
```

## Los cuatro catálogos

Cuatro cabeceras de sólo constantes, que dan sentido a los `int` que devuelven
las funciones:

| Catálogo                    | Constantes | Qué enumera                                   |
| --------------------------- | ---------- | --------------------------------------------- |
| `TiposSistema.h`            | 11         | POSIX, DOS, WINDOWS, MACKINTOSH               |
| `Sistemas.h`                | 13         | Los sistemas concretos dentro de cada familia |
| `Procesadores.h`            | 30         | Modelos de procesador                         |
| `ArquitecturasProcesador.h` | 6          | Intel, MIPS, Alpha, PPC…                      |

`TiposSistema` es el único con funciones propias, y sigue el patrón de catálogo
del stack: `TipSisNombre( id )` / `TipSisId( nombre )` más un predicado por
valor (`TipSisEsPosix`, `TipSisEsWindows`…).

## La API

| Grupo       | Funciones                                                                                                        |
| ----------- | ---------------------------------------------------------------------------------------------------------------- |
| Familia     | `SisTipo`, `SisSistema`, `SisVersion`                                                                            |
| Predicados  | `SisEsDos`, `SisEsWindows`, `SisEsPosix`, `SisEsMackintosh`                                                      |
| Capacidades | `SisIntegraGUI`, `SisPermiteBifurcarProcesos`                                                                    |
| Procesador  | `SisArquitecturaProcesador` + cuatro predicados, `SisProcesador`, `SisNumProcesadores`                           |
| CPU         | `SisProcesadorAdmiteMMX`, `…EmulaPuntoFlotante`, `…PuedeFallarPuntoFlotante`, `…AdmiteInstruccionesDeBytesAlpha` |
| Memoria     | `SisTamPagina`, `SisMemTamBloqueMinimo`, `SisMemAplicDireccionMinima` / `…Maxima`                                |
| Directorios | `SisDirectorioSistema` (sólo WIN), `SisDirectorioTemporal`, `SisInicializarDirectorios`                          |
| Velocidad   | `SisVelocidadCPU`                                                                                                |

---

## Test

`SistemaInformacionTest.cpp` comprueba coherencia más que valores concretos —que
`SisNumProcesadores()` sea positivo, que exactamente uno de los cuatro
predicados de familia sea cierto—, que es lo único que se puede afirmar sin
saber en qué máquina corre. `TiposSistemaTest.cpp` prueba la ida y vuelta
nombre ↔ identificador.

---

## Observaciones

- **Siete funciones tienen la rama POSIX vacía** y devuelven el valor por
  defecto sin avisar:

  | Función                                        | Devuelve en POSIX  |
  | ---------------------------------------------- | ------------------ |
  | `SisProcesadorAdmiteMMX`                       | `false`            |
  | `SisProcesadorEmulaPuntoFlotante`              | `false`            |
  | `SisProcesadorPuedeFallarPuntoFlotante`        | `false`            |
  | `SisProcesadorAdmiteInstruccionesDeBytesAlpha` | `false`            |
  | `SisMemAplicDireccionMinima`                   | nulo               |
  | `SisMemAplicDireccionMaxima`                   | nulo               |
  | `SisDirectorioSistema`                         | ni siquiera existe |

  Es decir: **compilando en el modo por defecto, todo lo que este módulo dice
  del procesador es «no»**. En Linux la respuesta está en `/proc/cpuinfo` y en
  `getauxval`, y las cuatro primeras se resolverían leyendo un fichero.
- **`SisDirectorioSistema` sólo se declara en Windows** (`#if defined ( WIN )`),
  mientras que las otras seis existen siempre y mienten. Dos maneras distintas
  de tratar el mismo problema en la misma cabecera; la primera es la honesta,
  porque el fallo lo da el compilador y no el tiempo de ejecución.
- **`SisDirectorioSistema` y `SisDirectorioTemporal` devuelven `std::string *`.**
  Puntero desnudo, sin decir quién libera. Devolver `std::string` por valor no
  cuesta nada desde C++11.
- **`SisVersion` devuelve un `double`.** Compone la versión mayor y menor en un
  número real —`10.0`, `6.1`— calculando cuántos dígitos tiene la menor con
  `log10` y dividiendo. Funciona para las versiones de Windows, y con una versión
  del tipo `5.10` da lo mismo que `5.1`. Un par de enteros, o una cadena, no
  tendrían el problema.
- **La comparación de versiones es de coma flotante**, con lo que eso implica:
  `SisVersion() == 6.1` puede ser falso por el último bit.
- **`SisVelocidadCPU` no tiene contrato escrito**: ni unidades ni qué devuelve si
  no puede medirla.
- **Los cuatro catálogos son macros `#define`, no enumerados.** No hay
  comprobación de tipo: `SisTipo()` devuelve un `int` que igual vale
  `TIP_SIS_POSIX` que un modelo de procesador. Un `enum class` daría el mismo
  código y el compilador ayudaría.
- **`Procesadores.h` enumera 30 modelos** de los años en que se escribió la
  librería. Cualquier procesador de los últimos quince años cae en el valor
  desconocido.
