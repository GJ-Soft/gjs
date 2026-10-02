# Entorno, comandos y usuarios

| Dato          | Valor                                                         |
| ------------- | ------------------------------------------------------------- |
| Módulos       | 3                                                             |
| Cabeceras     | `VariablesEntorno.h`, `SistemaComandos.h`, `SistemaUsuario.h` |
| Prefijos      | `VarEnt`, `Sis`, `SisUsr`                                     |
| Funciones     | 3 + 1 + 10                                                    |
| Incluidos por | `Sistema.h` (`SistemaUsuario.h` **no**)                       |
| Tests         | Uno por módulo                                                |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Lo que rodea al proceso: sus variables de entorno, los comandos que puede
lanzar y bajo qué identidad corre.

## `VariablesEntorno`

| Función                                                                  | Descripción                                |
| ------------------------------------------------------------------------ | ------------------------------------------ |
| `char * VarEntObtValor ( const char * p_cVariable )`                     | El valor, o `NULL`. **Hay que liberarlo.** |
| `int VarEntEstValor ( const char * p_cVariable, const char * p_cValor )` | Lo fija.                                   |
| `int VarEntExiste ( const char * p_cVariable )`                          | 1 si tiene valor.                          |

La escritura es el punto delicado y está bien resuelto:

```c
#if ( defined ( WIN ) && ! defined ( CYGWIN ) )
    _putenv_s ( p_cVariable, ES_NULO ( p_cValor ) ? "" : p_cValor )
#else
    setenv ( p_cVariable, ES_NULO ( p_cValor ) ? "" : p_cValor, 1 )
#endif
```

Las dos funciones **copian** la cadena al entorno. `putenv`, que es lo que
había antes, guarda el puntero recibido: al liberar el búfer la entrada del
entorno quedaba apuntando a memoria muerta. El comentario del código lo deja
anotado.

La condición `defined ( WIN ) && ! defined ( CYGWIN )` distingue Windows puro
—donde va `_putenv_s`— de Cygwin, donde hay que usar `setenv`. Desde que
desapareció el modo "Cygwin estilo Windows", `CYGWIN` y `WIN` no pueden darse a
la vez, así que la segunda mitad de la condición es redundante; se deja porque
no estorba y documenta la intención.

En lectura, `VarEntObtValor` no devuelve `getenv` tal cual: pasa el valor por
[SCadena](../../gjs-c-common-text/doc/SCadena.md) para quitarle los caracteres
de control y los blancos de los extremos.

## `SistemaComandos`

```c
int SisEjecutarComando ( const char * p_cComando, const char * p_cParametros, int iSegundoPlano );
```

Una sola función, con dos implementaciones muy distintas:

| Modo    | Cómo                                                             |
| ------- | ---------------------------------------------------------------- |
| Windows | `ShellExecute ( …, "open", comando, parámetros, NULL, SW_HIDE )` |
| POSIX   | Compone `"comando parámetros"` y llama a `system ()`             |

En POSIX el segundo plano se consigue añadiendo `" &"` a la orden; en Windows,
`ShellExecute` ya vuelve enseguida.

Para lanzar un programa **controlando el proceso resultante** —heredar
descriptores, cerrar consola, obtener el PID— el módulo es
[SistemaProcesos](SistemaProcesos.md) con `SisCrearSubproceso`.

## `SistemaUsuario`

| Función                                                                          | Descripción              |
| -------------------------------------------------------------------------------- | ------------------------ |
| `unsigned int SisUsrObtenerUsuario ( int type )`                                 | UID.                     |
| `unsigned int SisUsrObtenerGrupo ( int type )`                                   | GID.                     |
| `char * SisUsrObtenerNombre ( unsigned int uiId )`                               | Nombre de un UID.        |
| `char * SisUsrObtenerNombreGrupo ( unsigned int uiIdGrupo )`                     | Nombre de un GID.        |
| `char * SisUsrObtenerUsuarioLogin ()`                                            | Usuario de la sesión.    |
| `SisUsrActivarRoot` / `SisUsrDesactivarRoot`                                     | Sube y baja privilegios. |
| `SisUsrActivarGrupoRoot` / `SisUsrDesactivarGrupoRoot`                           | Igual para el grupo.     |
| `int SisUsrEstablecerUsuario ( const char * p_cUsuario, const char * p_cGrupo )` | Cambia de identidad.     |

El par activar/desactivar es el patrón habitual de un binario *setuid*: se
arranca con privilegios, se bajan enseguida y se suben sólo para la operación
que los necesita.

## Dependencias

[SCadena](../../gjs-c-common-text/doc/SCadena.md) y
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md) en los tres módulos.

## Tests

`VariablesEntornoTest.c`, `SistemaComandosTest.c`, `SistemaUsuarioTest.c`.

## Observaciones

- **`SisEjecutarComando` pasa la orden a `system ()` sin escapar nada.** El
  comando y los parámetros se concatenan con un espacio y se entregan al
  intérprete, así que un parámetro que contenga `;`, `|`, `$(…)` o comillas se
  ejecuta como orden. Es aceptable para cadenas fijas del programa; no lo es
  para nada que venga de fuera. `SisCrearSubproceso` de
  [SistemaProcesos](SistemaProcesos.md) no tiene ese problema porque no pasa por
  el intérprete.
- **`SisEjecutarComando` devuelve 1 sin haber esperado al proceso.** En Windows
  comprueba `> 32` —el convenio de `ShellExecute`— y espera 10 ms fijos; en
  POSIX, con `" &"`, `system` vuelve antes de que el programa haya arrancado. El
  1 significa "se ha lanzado", no "ha funcionado".
- **`VarEntObtValor` no devuelve el valor literal de la variable.** Le quita los
  blancos de los extremos y los caracteres de control, y si lo que queda está
  vacío devuelve `NULL`. Una variable fijada a `" "` se lee como inexistente, y
  `VarEntExiste` dice que no existe una variable puesta a cadena vacía —que es
  justo lo que escribe `VarEntEstValor` cuando se le pasa `NULL`—.
- **`SisUsrObtenerUsuario ( int type )` es el único parámetro del componente sin
  notación húngara y en inglés**, y la cabecera no dice qué valores admite: no
  hay constantes `SIS_USR_*` que lo acompañen, así que hay que leer la
  implementación para saber si `type` distingue real de efectivo.
- **`SistemaUsuario.h` no entra por la fachada** pese a tener diez funciones y
  test propio. Hay que incluirla a mano.
- **`SisUsrActivarRoot` no puede funcionar si no se arrancó con privilegios**, y
  la interfaz no lo distingue: devuelve 0 tanto si no había permisos como si la
  llamada falló por otra causa.
