# CVariablesEntorno

| Dato     | Valor                                    |
| -------- | ---------------------------------------- |
| Cabecera | `CVariablesEntorno.h` (65 líneas)        |
| Fuente   | `CVariablesEntorno.cpp` (111 líneas)     |
| Espacio  | `org::gjs::cpp::common`                  |
| Métodos  | 4                                        |
| Test     | `CVariablesEntornoTest.cpp` (116 líneas) |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Las variables de entorno del proceso, con las cuatro operaciones de siempre.

```cpp
CVariablesEntorno entorno;

if ( entorno.ExisteVariable ( "LOG_DIR" ) )
{
    std::string * pValor = entorno.ObtValor ( "LOG_DIR" );
    ...
    delete pValor;                       // ver observaciones
}

entorno.EstValor ( "LOG_DIR", "/var/log/miapp" );
entorno.LimpiarValor ( "TMPDIR" );
```

## La API

| Método           | Debajo                                                        |
| ---------------- | ------------------------------------------------------------- |
| `ObtValor`       | `getenv`                                                      |
| `ExisteVariable` | `getenv`, y comprueba si vino algo                            |
| `EstValor`       | `putenv`, con la cadena `NOMBRE=valor` en un `unique_ptr`     |
| `LimpiarValor`   | `putenv` con el valor vacío                                   |

`EstValor` hace lo correcto con `putenv`, que es la parte delicada: la función
**se queda con el puntero**, que pasa a formar parte del entorno del proceso, así
que la cadena se reserva en un `std::unique_ptr < char [] >`, que la suelta
**si `putenv` falla**; si no, `release ()` se la cede al entorno. Hay un
comentario en el código que lo explica. Antes era `strdup` y `free`; a `putenv`
le da igual, porque no la libera nunca. Sin memoria, `make_unique` lanza
`std::bad_alloc`, donde `strdup` devolvía `NULL` y la función `false`.

---

## Test

`CVariablesEntornoTest.cpp` prueba el ciclo entero sobre una variable propia:
que no exista, crearla, leerla, cambiarla, borrarla y comprobar que ya no está.

---

## Observaciones

- **`ObtValor` devuelve `std::string *`.** Puntero desnudo a un objeto reservado
  dentro del método, sin decir en la cabecera quién lo libera ni qué se devuelve
  cuando la variable no existe. Es el mismo patrón que
  [SistemaInformacion](Informacion.md) y
  [SistemaProcesos](Procesos.md), y aquí duele más porque es la operación que
  más se usa. Devolver `std::string` por valor —o `std::optional<std::string>`,
  que además distingue «no está» de «está vacía»— quita el problema entero.
- **La clase no tiene estado.** Cuatro métodos, ningún campo, constructor y
  destructor vacíos. Es un espacio de nombres escrito como clase: `getenv` y
  `putenv` operan sobre el entorno del proceso, no sobre el objeto, de modo que
  dos instancias de `CVariablesEntorno` son indistinguibles y comparten todo.
  Cuatro funciones libres con prefijo `SisEnt` habrían encajado con el resto del
  componente, que es justo así.
- **`ObtValor` es `const` y `ExisteVariable` no**, aunque las dos llaman a
  `getenv` y ninguna toca nada. Es una asimetría sin causa.
- **`EstValor` con valor vacío y `LimpiarValor` hacen lo mismo**, y la cabecera
  no dice si «poner una variable a vacío» y «borrarla» son la misma cosa. En
  POSIX no lo son: `unsetenv` la quita del entorno y `setenv` con cadena vacía la
  deja presente y vacía. La clase no ofrece la primera.
- **No usa `setenv`/`unsetenv`, que es la pareja moderna de POSIX**, sino
  `putenv` para todo. `putenv` es la portable —existe también en Windows como
  `_putenv`— y la que obliga a copiar la cadena; las otras dos copian ellas
  mismas.
- **Queda un `TODO` pendiente**: `// TODO: Limpiar blancos , etc como en C`. La
  versión C recortaba los espacios del nombre y del valor antes de asignarlos, y
  ésta no.
- **No hay forma de recorrer el entorno**, ni de saber cuántas variables hay.
  `environ` está ahí en POSIX y `GetEnvironmentStrings` en Windows; la clase no
  lo expone.
- **El prefijo `C` y los verbos `Obt`/`Est`** vienen de la librería de 2008, y
  son los que separan a este componente del convenio del resto del stack C++.
  Ver [MODULOS](MODULOS.md#las-cuatro-clases).
- **Ocho caracteres perdidos** (`U+FFFD`) en los comentarios del `.cpp`.
