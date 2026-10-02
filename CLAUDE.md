# gjs — Monorepo (Maven)

Raíz del monorepo: `C:\GJS\Desarrollo\Maven\gjs` (dentro del workspace más amplio
`C:\GJS\Desarrollo\Maven`, que contiene también otros proyectos: `gjs-c`,
`gjs-lp`, `nar-maven-plugin`, `gjs-c-common-anthropic`, `ComponentesComunes`, etc.).

Todo se orquesta con **Maven**. El monorepo `gjs` agrupa:

- **Parent poms**: `gjs-parent` (raíz de todo), `gjs-no-java-parent` (base de lo
  no-Java), y los parents por lenguaje: `gjs-c/gjs-c-parents`,
  `gjs-java/gjs-java-base-parents` + `gjs-java/gjs-java-parents`,
  `gjs-python/gjs-python-parents`, `gjs-npm/gjs-npm-parents`.
- **Librerías de componentes comunes**: `gjs-c` (C/C++, en
  `gjs-c/gjs-c-common-components`), `gjs-java`, `gjs-python`, `gjs-npm`
  (TypeScript/front).
- **Extensiones / plugins de Maven**: `gjs-maven`, `gjs-plugin`.
- **Arquetipos de Maven**: `gjs-archetypes`.

> Nota histórica: hasta 2026-07 se trabajó sobre copias en
> `C:\GJS\Desarrollo\ClaudeCode`; esas copias se borraron. La versión buena y única
> es la de `Maven\gjs`.


## Compilación

El modo de compilación solo afecta internamente a los módulos **C/C++**, pero
formalmente puede afectar a **Python** (muy sensible al formato de las rutas).
Hay **3 modos**, y el que se usa **no se elige con una propiedad `-D`**: lo
decide el entorno desde el que se lanza Maven.

Toolchain: Maven 3.9.11 (`C:\Desarrollo\apache-maven-3.9.11`), Java 21
(`C:\Program Files\Java\jdk-21`).

Consola Cygwin (para humanos):
`C:\Desarrollo\Cygwin64\bin\mintty.exe -i /Cygwin-Terminal.ico -`

| Modo | Consola (humano) | Comando | Se activa porque |
|---|---|---|---|
| Cygwin | mintty (Cygwin) | `mvn clean install` | Windows **y** la variable de entorno `CYGWIN` está definida |
| Windows puro | PowerShell / cmd | `mvn clean install` | Windows **y** `CYGWIN` **no** está definida |
| Linux | consola Linux | `mvn clean install` | familia de SO Unix |

### Cómo lo lanza Claude (no interactivo)

Claude **no** puede usar `mintty` (es interactivo). Equivalentes verificados:

- **Cygwin** — herramienta **Bash**:
  `C:/Desarrollo/Cygwin64/bin/bash.exe -lc 'cd /cygdrive/c/GJS/Desarrollo/Maven/gjs/<ruta-modulo> && mvn clean install'`
  El `-l` (login shell) replica el entorno de `mintty`: de ahí salen tanto `mvn`
  en el `PATH` como la variable `CYGWIN` que activa el perfil.
  Ejemplo módulo C/C++: `.../gjs/gjs-c/gjs-c-common-components/gjs-c-common-base`.
- **Windows puro** — herramienta **PowerShell**: `mvn clean install` en el
  directorio del módulo.

Para lanzarlo tú desde **PowerShell** hacia Cygwin, usa el token de parada `--%`
(evita que PowerShell se coma la comilla final):
`C:\Desarrollo\Cygwin64\bin\bash.exe --% -lc 'cd /cygdrive/c/... && mvn clean install'`

### Macros por modo — confirmado (pom padre + `Precompilacion.h`)

Cadena: perfil de `gjs-c-common-parent` (activado por el entorno, ver la tabla de
arriba) → `platformOptions` → llega al compilador vía
`${gjs.nar.platform.options}`, igual para `<c>` que para `<cpp>`. El perfil
además fija el **prefijo del toolchain**, así que el compilador no depende del
`PATH`: en Windows puro es `x86_64-w64-mingw32-gcc`/`g++` aunque se lance desde
Cygwin.

| Modo | `platformOptions` | Toolchain | AOL | Macros efectivos |
|---|---|---|---|---|
| Cygwin | `-DCYGWIN -DPOSIX` | gcc/g++ de Cygwin | `x86_64-pc-cygwin` | `CYGWIN` + `POSIX` |
| Windows puro | `-DWIN` | `x86_64-w64-mingw32-` | `x86_64-w64-mingw32` | `WIN` |
| Linux | `-DPOSIX` | gcc/g++ de Linux | `x86_64-pc-linux-gnu` | `POSIX` |

`Precompilacion.h` (idéntico en los dos stacks) solo remata lo que llega del pom:
`CYGWIN` y `WIN` a la vez son un `#error`; `CYGWIN` implica `POSIX`; y si no
llega ni `WIN` ni `POSIX`, se asume `WIN`.

> **No existe un modo «Cygwin estilo Windows».** Hubo uno, con la propiedad
> `cygwin.style` y los macros `CYGWIN_WIN` / `CYGWIN_POSIX`, y se quitó: no hay
> perfil en el pom ni rastro en `Precompilacion.h`. Si ves esos nombres en algún
> sitio, es documentación vieja. Quedan menciones por limpiar en
> `docs/instalacion.md`, `gjs-c-common-base/doc/MODULOS.md` y varios `README.md`.

Notas:
- `#if defined(WIN) && !defined(CYGWIN)` acierta en los tres
  (Cygwin → `setenv`, Windows puro → `_putenv_s`).
- **Desde Cygwin se compilan las ramas `#if defined(POSIX)`**, no las de `WIN`.
  Ya no hay forma de volver al comportamiento `WIN` desde Cygwin: para eso se
  compila en Windows puro.
- **Para probar a mano fuera de Maven**, usa las mismas banderas que el pom, y
  **no** te apoyes en las cabeceras de `target/nar/`: son copias de la última
  build y pueden estar rancias. Pon `src/main/include` **antes** en el `-I`.
