# gjs-cpp-common-base

**La raíz del stack C++ de GJS.** Es el único componente sin dependencias: todo
lo demás se apoya en él.

Aporta lo que la biblioteca estándar deja fuera o resuelve de otra forma:
una jerarquía de excepciones con módulo y rutina, dos interfaces —`IToString` e
`IComparable`— sobre las que se construyen los contenedores del stack, un
`Conversor` de tipos, medio centenar de utilidades de cadena y una capa fina
sobre el sistema operativo.

31 cabeceras y 24 fuentes en **9.008 líneas**, con 10 clases.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjs.c.common`             |
| `artifactId` | `gjs-cpp-common-base`          |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjs.c:gjs-cpp-lib-parent` |
| Estándar     | **`gnu++20`**                  |
| Depende de   | **Nada**                       |

---

## Uso

La cabecera fachada es `CppBase.h`, y el espacio de nombres
`org::gjs::cpp::common`:

```cpp
#include <CppBase.h>

using namespace org::gjs::cpp::common;

int main ()
{
    InicializarBase ();

    try
    {
        std::string sTexto = Trim ( LeerFichero ( "datos.txt" ) [ 0 ] );

        if ( EsEntero ( sTexto ) )
        {
            long lValor = ToInt ( sTexto );
            std::cout << Concatenar ( "valor = ", ToString ( lValor ) ) << std::endl;
        }
    }
    catch ( Excepcion & ex )
    {
        std::cerr << ex.whatExt () << std::endl;
    }
    return ( 0 );
}
```

`InicializarBase()` prepara la capa de sistema; conviene llamarla al arrancar.

---

## Las dos jerarquías

El componente ofrece **dos raíces distintas**, y conviene no confundirlas:

```
Objeto                          IToString  (interfaz)
  └── Depurador                   └── IComparable  (interfaz)
```

| Raíz          | Qué es                         | Qué aporta                                                              |
| ------------- | ------------------------------ | ----------------------------------------------------------------------- |
| `Objeto`      | Clase base al estilo Java      | `hash`, `equals`, `clonar`, `toString`, `esValido`, `getTipo`, `getTam` |
| `IToString`   | Interfaz pura                  | `toString()` y volcado de `list`, `vector` y `map`                      |
| `IComparable` | Interfaz, extiende `IToString` | `getHash()` y los seis operadores de comparación                        |

**No están conectadas**: `Objeto` no implementa `IToString`, aunque tenga su
propio `toString()`. En la práctica el stack usa las interfaces —los
contenedores de `gjs-cpp-common-types` derivan de `IToString`— y `Objeto` sólo
lo hereda `Depurador`.

## Las excepciones

```
std::runtime_error
  └── Excepcion                    módulo + rutina + mensaje
        ├── FinExcepcion           fin de proceso con código
        ├── NoEncontradoExcepcion  tipo + objeto que no aparece
        └── SistemaExcepcion       envuelve un errno
```

`Excepcion` es la diferencia de fondo con el stack C, que señala los errores con
`ERROR_ESTABLECER` y valores de retorno. Aquí cada excepción lleva **de dónde
viene**: `getModulo()`, `getRutina()` y `getMensaje()`, y un `whatExt()` que los
compone.

---

## Convenios

- Espacio de nombres `org::gjs::cpp::common`, con `::real` para la comparación
  de reales y `::ansi` para los códigos de terminal.
- Métodos en `getXxx` / `setXxx`; funciones libres en mayúscula inicial
  (`ToString`, `Trim`, `Concatenar`).
- Notación húngara en los parámetros, heredada del stack C:
  `sCadena`, `iValor`, `p_cRuta`, `lMiliseg`.
- Las cabeceras que empiezan por `I` son interfaces puras.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). No
requiere ningún otro componente instalado.

---

## Tests

**18 suites**.

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, sin un solo KO.

---

## Documentación de las clases

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`Objeto` y las interfaces no se hablan.** Dos diseños de raíz conviviendo,
  con `hash()`/`getHash()` y `toString()` duplicados y con tipos distintos.
  Ver [Objeto](doc/Objeto.md).
- **`Cadenas.h` declara `ContieneCaracteresNoImprimibles` dos veces**, y
  `ToString.h` declara `ToString ( long )` dos veces.
- **`Prototipos.h` y `Funciones.h` son dos catálogos de lo mismo**:
  `PROCEDIMIENTO` y `FUNCION_BOOL` frente a la familia `PPRCV`, `PPRCI`, `PPRCL`…
  Ver [Configuración](doc/Configuracion.md).
- **`ToReal.h` sólo declara `ToDouble`**, y `ToInt` devuelve `long`. Los nombres
  de los ficheros no corresponden con lo que hay dentro. Ver
  [Conversiones](doc/Conversiones.md).
- **`Depurador` e `InfoMemoria` desaparecen fuera de `MODO_DEPURACION`**: el
  primero se queda en una clase vacía, el segundo no declara nada.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
