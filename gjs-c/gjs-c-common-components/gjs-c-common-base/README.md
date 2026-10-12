# gjs-c-common-base

Librería base en **C** del stack GJS. Es la capa más baja de la pila: define los
tipos elementales, las constantes de precompilación, la gestión de memoria, el
subsistema de errores y un conjunto de utilidades de propósito general (cadenas,
bits, conversiones, hash, orden de bytes, ASCII, Unicode…) sobre las que se
construye el resto de componentes C del proyecto.

Históricamente el código procede de la librería **GBase** (2008), portada desde
C++ a C: muchos ficheros `.c` conservan en su cabecera el nombre original `.cpp`.

---

## Coordenadas Maven

| Dato         | Valor                         |
| ------------ | ----------------------------- |
| `groupId`    | `org.gjsoft.c.common`            |
| `artifactId` | `gjs-c-common-base`           |
| `version`    | `1.0.0`                  |
| `packaging`  | `nar` (biblioteca **shared**) |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`  |

El artefacto se empaqueta con el `nar-maven-plugin`; las cabeceras de
`src/main/include` se publican en el NAR `noarch` y quedan disponibles para los
módulos consumidores con `#include <...>`.

---

## Estructura del proyecto

```
gjs-c-common-base
├── pom.xml
├── README.md                     ← este fichero
├── doc/
│   ├── MODULOS.md                ← índice y orquestación de todos los módulos
│   └── <Modulo>.md               ← un documento por módulo
└── src
    ├── main
    │   ├── include/              ← 32 cabeceras (API pública)
    │   └── c/org/gjs/c/common/   ← 23 fuentes
    └── test
        └── c/org/gjs/c/common/   ← Test.c (main) + 21 ficheros *Test.c
```

---

## Uso

Basta con incluir la cabecera fachada:

```c
#include <Base.h>
```

`Base.h` arrastra `BaseConfig.h` (que a su vez normaliza la precompilación e
incluye las cabeceras del sistema) y todas las cabeceras de módulo, **excepto
`SConversor.h`**, que hay que incluir explícitamente:

```c
#include <Base.h>
#include <SConversor.h>
```

Ejemplo mínimo:

```c
#include <Base.h>

int main ( void )
{
    char * p_cCad = CadDuplicar ( "Hola" );

    if ( ES_VALIDO ( p_cCad ) )
    {
        CadImprimir ( p_cCad );
        MemLiberar ( (void **) &p_cCad );
    }
    if ( ErrHayError () == 1 )
    {
        ErrImprimir ();
    }
    return ( 0 );
}
```

---

## Convenios de la librería

### Nombres

Cada módulo usa un **prefijo** propio en todos sus símbolos públicos
(`Cad`, `Mem`, `Err`, `Conv`, `Tip`, `Bool`, `Hex`, `Num`, `Bytes`, `ASCII`,
`Hash`, `Vers`, `Frm`, `SConv`, `Nib`, `Byte`, `Word`, `DWord`, `By`/`By2`/`By4`).
Las constantes y macros van en mayúsculas con el prefijo del módulo
(`ERR_`, `TIP_`, `BOOL_`, `ASCII_`, `BMP_`, `ANSI_`…).

Los parámetros siguen una notación húngara:

| Prefijo                   | Tipo                                         |
| ------------------------- | -------------------------------------------- |
| `i` / `l` / `s`           | `int` / `long` / `short`                     |
| `ui` / `ul`               | `unsigned int` / `unsigned long`             |
| `ll` / `ull`              | `long long` / `unsigned long long`           |
| `f` / `d`                 | `float` / `double`                           |
| `c` / `uc`                | `char` / `unichar`                           |
| `by` / `w` / `dw` / `nib` | `byte` / `word` / `dword` / `nibble`         |
| `p_` / `p_p_`             | puntero / puntero a puntero                  |
| `g_` / `_`                | variable global / símbolo interno del módulo |

### Valores de retorno

- Los predicados devuelven `int` con valores `1` (cierto) y `0` (falso);
  el módulo [Booleano](doc/Booleano.md) formaliza esos valores.
- Las funciones de longitud devuelven `-1` ante parámetros inválidos.
- Las comparaciones devuelven `COMP_IGUAL`, `COMP_MENOR`, `COMP_MAYOR`
  (`ConstantesBase.h`).
- Las funciones que construyen cadenas devuelven memoria reservada con
  `MemReservar`: **el llamante debe liberarla** con `MemLiberar` /
  `MemLiberarCadena`.

### Errores

No se usan códigos de retorno de error: las rutinas anotan el fallo en un estado
global mediante la macro `ERROR_ESTABLECER ( codigo )` y el llamante lo consulta
con `ErrHayError()`, `ErrCodigo()`, `ErrMensaje()`… Ver
[Errores](doc/Errores.md) y `BaseErrores.h`.

### Memoria

Toda la reserva y liberación pasa por [Memoria](doc/Memoria.md)
(`MemReservar` / `MemLiberar`), nunca por `malloc`/`free` directos: en Windows se
usa el *heap* del proceso (`HeapAlloc`) y en POSIX `malloc`, y en modo depuración
se contabilizan los bloques ([InfoMemoria](doc/InfoMemoria.md)). La memoria
devuelta por `MemReservar` viene puesta a cero.

---

## Compilación

Se compila con Maven, como el resto del repositorio. Hay tres modos operativos
(el cuarto, Linux/POSIX nativo, está pendiente):

| Modo                    | Consola          | Comando             | Estado                                          |
| ----------------------- | ---------------- | ------------------- | ----------------------------------------------- |
| Cygwin (**el normal**)  | mintty (Cygwin)  | `mvn clean install` | **Verificado**: `BUILD SUCCESS`, 21/21 tests OK |
| Windows puro            | PowerShell / cmd | `mvn clean install` | **Verificado** (2026-09)                        |
| Linux                   | consola Linux    | `mvn clean install` | Sin verificar: no hay máquina                   |

El artefacto resultante es un NAR de biblioteca compartida más el NAR `noarch`
con las cabeceras.

> Cuidado: los dos modos de Cygwin generan el **mismo AOL**
> (`x86_64-pc-cygwin-Windows-gcc`) y por tanto el mismo nombre de artefacto, así
> que se pisan mutuamente en el repositorio local. Lo instalado es siempre lo del
> último `mvn install`, sea cual sea el modo con el que se compiló.

El modo determina los macros que ve el preprocesador
(`POSIX`/`WIN`, `CYGWIN`, `A64`/`A32`, `GNU`/`CC`); la normalización la
hace `Precompilacion.h` a partir de los `-D` que inyecta el pom padre. Ver el
detalle en [`doc/MODULOS.md`](doc/MODULOS.md#cabeceras-de-configuración).

> No compilar los `.c` invocando `gcc` a mano: el juego de `-D`, los `-I` y el
> estándar del lenguaje los fija el `nar-maven-plugin` desde los poms padre.

---

## Tests

Las pruebas son un ejecutable propio, no un framework externo. `src/test/c/.../Test.c`
contiene el `main`, un array de nombres y otro de punteros a función
(`PFUNINTV`), y ejecuta los **21** casos registrados:

```
Test.exe             # ejecuta todos los tests
Test.exe NibbleTest  # ejecuta un único test por nombre
```

Los ejecuta el `nar-maven-plugin` en la fase `test`, así que basta con:

```
mvn test
```

Cada fichero `<Modulo>Test.c` expone una función `Test<Modulo>()` que devuelve
`1` (OK) o `0` (KO) y traza el resultado con colores ANSI (`TerminalANSI.h`).
El proceso devuelve `0` si todo va bien y `-1` si algún test falla, lo que hace
fallar el build.

Los módulos `Finalizacion` e `InfoMemoria` no tienen test asociado, y las macros
`BMP_*` de [Bits](doc/Bits.md) tampoco están cubiertas.

Última ejecución conocida: **21 suites, 21 OK, 0 KO**, en los dos modos de Cygwin.

> El build emite un aviso del plugin —`No file matching pattern
> (libgjs-c-common-base-….so)`— porque en Cygwin la biblioteca se genera como
> `.dll`. Es inocuo: el ejecutable de test enlaza y se ejecuta.

---

## Documentación de los módulos

El detalle de cada módulo (propósito, API, comportamiento, dependencias y
observaciones) está en documentos independientes, orquestados desde:

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- Este módulo compila y pasa los tests en los **dos** modos de Cygwin, y sus 23
  fuentes y 22 ficheros de test no producen ningún aviso con `-Wall`. La
  advertencia sobre ramas `#if defined ( POSIX )` sin terminar sigue vigente para
  el resto del stack C, no para `gjs-c-common-base`.
- `unichar` es `unsigned short`: UTF-16 **sin pares suplentes**, no representa
  puntos de código por encima de U+FFFF. Además, [UniChar](doc/UniChar.md) pasa
  `unichar *` a `wcstombs`/`mbstowcs`, que esperan `wchar_t *`; hoy coinciden
  (en Cygwin `wchar_t` son 2 bytes sin signo), pero dejarían de hacerlo en el
  modo Linux nativo pendiente, donde son 4.
- `MemReservarVector` y `MemReservarTabla` multiplican sus factores sin
  comprobar desbordamiento. Ver [Memoria](doc/Memoria.md).
- Cada documento de módulo tiene una sección *Observaciones* con los detalles
  detectados en su código.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
