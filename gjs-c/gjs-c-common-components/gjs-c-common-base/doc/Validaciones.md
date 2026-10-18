# Validaciones

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/Validaciones.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Validaciones.c` |
| Prefijo      | `Validar`, `FUN_VALIDAR_`                    |
| Incluido por | `Base.h`                                     |
| Test         | `ValidacionesTest.c` → `TestValidaciones()`  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Nombres para las **funciones de validación**: las que reciben un valor (o dos,
para un rango) y devuelven 1 si es aceptable y 0 si no. Con ellos, una
estructura de las capas superiores puede guardar «la regla que deben cumplir
sus valores» sin depender de cómo se escriba cada regla.

## Tipos

Son alias de los punteros de [Funciones.h](MODULOS.md#funcionesh), todos con
retorno `int`.

Un valor:

| Tipo                                       | Alias de     | Valida                   |
| ------------------------------------------ | ------------ | ------------------------ |
| `FUN_VALIDAR_CADENA`                       | `PFUNINTT`   | `const char *`           |
| `FUN_VALIDAR_CARACTER`                     | `PFUNINTC`   | `char`                   |
| `FUN_VALIDAR_ENTERO`                       | `PFUNINTI`   | `int`                    |
| `FUN_VALIDAR_ENTERO_LARGO`                 | `PFUNINTL`   | `long`                   |
| `FUN_VALIDAR_ENTERO_CORTO`                 | `PFUNINTS`   | `short`                  |
| `FUN_VALIDAR_REAL`                         | `PFUNINTF`   | `float`                  |
| `FUN_VALIDAR_REAL_DOBLE`                   | `PFUNINTD`   | `double`                 |
| `FUN_VALIDAR_ENTERO_SIN_SIGNO`             | `PFUNINTUI`  | `unsigned int`           |
| `FUN_VALIDAR_ENTERO_LARGO_SIN_SIGNO`       | `PFUNINTUL`  | `unsigned long`          |
| `FUN_VALIDAR_ENTERO_CORTO_SIN_SIGNO`       | `PFUNINTUS`  | `unsigned short`         |
| `FUN_VALIDAR_ENTERO_DOBLE_LARGO`           | `PFUNINTQ`   | `long long`              |
| `FUN_VALIDAR_ENTERO_DOBLE_LARGO_SIN_SIGNO` | `PFUNINTUQ`  | `unsigned long long`     |

Dos valores del mismo tipo, para los rangos:

| Tipo                                             | Alias de      | Argumentos           |
| ------------------------------------------------ | ------------- | -------------------- |
| `FUN_VALIDAR_RANGO_ENTERO`                       | `PFUNINTII`   | `int`                |
| `FUN_VALIDAR_RANGO_ENTERO_LARGO`                 | `PFUNINTLL`   | `long`               |
| `FUN_VALIDAR_RANGO_ENTERO_CORTO`                 | `PFUNINTSS`   | `short`              |
| `FUN_VALIDAR_RANGO_REAL`                         | `PFUNINTFF`   | `float`              |
| `FUN_VALIDAR_RANGO_REAL_DOBLE`                   | `PFUNINTDD`   | `double`             |
| `FUN_VALIDAR_RANGO_ENTERO_SIN_SIGNO`             | `PFUNINTUIUI` | `unsigned int`       |
| `FUN_VALIDAR_RANGO_ENTERO_LARGO_SIN_SIGNO`       | `PFUNINTULUL` | `unsigned long`      |
| `FUN_VALIDAR_RANGO_ENTERO_CORTO_SIN_SIGNO`       | `PFUNINTUSUS` | `unsigned short`     |
| `FUN_VALIDAR_RANGO_ENTERO_DOBLE_LARGO`           | `PFUNINTQQ`   | `long long`          |
| `FUN_VALIDAR_RANGO_ENTERO_DOBLE_LARGO_SIN_SIGNO` | `PFUNINTUQUQ` | `unsigned long long` |

## API

| Función                                                                       | Descripción                       |
| ----------------------------------------------------------------------------- | --------------------------------- |
| `int ValidarCadena ( const char * p_cValor, FUN_VALIDAR_CADENA fValidacion )` | Aplica la validación a la cadena. |

Devuelve lo que devuelva `fValidacion`. Con cadena o validación nulas devuelve 0
y deja `ERR_PARAMETROS` en [Errores](Errores.md): la validación nunca recibe un
`NULL`, así que no necesita comprobarlo.

## Dependencias

- `Funciones.h`, para los punteros a función.
- [Memoria](Memoria.md) (`ES_VALIDO`) y [Errores](Errores.md), en el fuente.

## Test

`ValidacionesTest.c` → `TestValidaciones()`: una validación que acepta y otra
que rechaza, y los dos argumentos nulos, con su código de error.

## Observaciones

- Sólo hay función de aplicación para las cadenas. Los demás tipos se aplican
  llamando al puntero directamente, que para un valor por copia no tiene nada
  que comprobar salvo que el puntero no sea nulo.
- Los tipos de rango no dicen qué es cada uno de sus dos argumentos (los dos
  extremos, o el valor y un límite): lo fija quien los use.
