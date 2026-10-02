# Errores y estado

| Dato      | Valor                                                                         |
| --------- | ----------------------------------------------------------------------------- |
| Cabeceras | `SistemaErrores.h` (49), `SistemaTiposErrores.h` (41), `SistemaEstado.h` (52) |
| Fuentes   | `SistemaErrores.cpp` (277), `SistemaEstado.cpp` (165)                         |
| Espacio   | `org::gjs::cpp::common`                                                       |
| Prefijos  | `SisErr`, `Sis`                                                               |
| Declara   | 13 + 3                                                                        |
| Tests     | `SistemaErroresTest.cpp`, `SistemaEstadoTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Leer el último error del sistema —`errno` en POSIX, `GetLastError` en Windows—
sin saber cuál de los dos hay debajo, y traducirlo a un texto legible.

```cpp
if ( SisHayError () )
{
    std::cerr << SisErrMensajeExt ( "MiModulo", "MiRutina" ) << std::endl;
    SisErrLimpiar ();
}
```

## La API

| Grupo    | Funciones                                                                  |
| -------- | -------------------------------------------------------------------------- |
| Consulta | `SisHayError`, `SisHayErrorDeMemoriaAgotada`, `SisErrTipo`, `SisErrCodigo` |
| Texto    | `SisErrDescripcion`, `SisErrMensaje`, `SisErrMensajeExt`                   |
| Salida   | `SisErrImprimir`                                                           |
| Limpieza | `SisErrLimpiar`, `SisMaxError`                                             |
| Pila     | `SisErrApilar`, `SisErrImprimirPila`, `SisErrLimpiarPila`                  |

El parámetro `iRefrescar` que llevan `SisHayError` y `SisErrApilar` decide si se
vuelve a leer el error del sistema o se usa el que ya estaba capturado. Por
defecto refresca.

### La pila de errores

`SisErrApilar( módulo, rutina )` guarda el error actual **junto con dónde se
detectó**, de modo que un fallo que atraviesa varias capas deja un rastro:

```
[MiModulo::MiRutina] 2 - No such file or directory
[Cargador::Abrir]    2 - No such file or directory
```

Es la respuesta de la librería a que `errno` no tenga contexto: el sistema dice
*qué* falló y la pila añade *dónde*.

## `SistemaEstado`

Dos funciones, y las dos dicen lo mismo desde ángulos distintos: **cuándo
arrancó el sistema operativo**.

```cpp
long SisFechaInicio ();     // AAAAMMDD
long SisHoraInicio  ();     // HHMMSS
```

Usan los formatos numéricos de
[gjs-cpp-common-time](../../gjs-cpp-common-time/README.md).

---

## Tests

`SistemaErroresTest.cpp` provoca un error conocido —abrir un fichero que no
existe— y comprueba que el código y el texto lleguen. `SistemaEstadoTest.cpp`
comprueba que la fecha y la hora de arranque sean plausibles.

---

## Observaciones

### La cabecera que no llega

- **`SistemaErrores.h` no está en la fachada.** Trece funciones públicas que hay
  que incluir a mano, sabiendo que existen.
- **Y `SistemaTiposErrores.h` tampoco**, ni directa ni indirectamente: sólo
  llega por `CommonSystemConfig.h`, que **no se publica**. Define los seis tipos
  de error que devuelve `SisErrTipo()`, de modo que desde fuera del componente
  esa función devuelve un `int` **sin nada con lo que compararlo**. Es el hueco
  más claro de la fachada.

### Contratos

- **`iRefrescar` es un `int` que se usa como booleano**, con valor por defecto
  `1`. Igual que `iMostrarCodigo` en `SisErrMensaje`. Vienen de la versión C.
- **`SisErrDescripcion` tiene el parámetro comentado en la propia declaración**:

  ```cpp
  std::string SisErrDescripcion (); // int iError = 0 );
  ```

  Se puede leer como que hubo una versión que aceptaba un código concreto y se
  quitó, o como que iba a añadirse. Tal como está, sólo describe el error actual.
- **El error es estado global del proceso**, no del hilo. `errno` sí es por hilo
  en las plataformas modernas, y `GetLastError` también; lo que no está claro es
  si la pila de `SisErrApilar` lo es. Si no lo es, dos hilos que fallen a la vez
  mezclan sus rastros.
- **`SisMaxError` está en el grupo de limpieza y no limpia nada**: devuelve el
  código de error más alto que el sistema puede dar. Colocada entre
  `SisErrLimpiar` y `SisErrApilar`, despista.
- **No hay forma de consultar la pila**, sólo de imprimirla y limpiarla.
  `SisErrImprimirPila` escribe por la salida estándar; un programa que quiera
  meter ese rastro en su propio registro —por ejemplo en
  [gjs-cpp-common-log](../../gjs-cpp-common-log/README.md)— no puede.

### `SistemaEstado`

- **Es el módulo más pequeño del componente**: dos funciones en 165 líneas de
  implementación, casi todas de conversión entre los formatos de fecha de cada
  plataforma.
- **Tiene comentado un tercer método**, `SisFechaHoraInicio`, que devolvería
  el instante completo en un solo `long long`, que es justo lo que hoy hay que
  componer a mano.
- **Devuelve `long` en formato `AAAAMMDD`**, el convenio numérico del stack. La
  cabecera no lo dice: hay que ir a
  [gjs-cpp-common-time](../../gjs-cpp-common-time/doc/Fechas.md) para saber cómo
  se lee ese número.
