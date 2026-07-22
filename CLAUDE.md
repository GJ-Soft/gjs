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
formalmente puede afectar a **Python** (muy sensible al formato de las rutas). Hay 3
modos disponibles (habrá un 4º, Linux/POSIX nativo, aún no disponible).

Toolchain: Maven 3.9.11 (`C:\Desarrollo\apache-maven-3.9.11`), Java 21
(`C:\Program Files\Java\jdk-21`).

Consola Cygwin (para humanos):
`C:\Desarrollo\Cygwin64\bin\mintty.exe -i /Cygwin-Terminal.ico -`

| Modo | Consola (humano) | Comando |
|---|---|---|
| Cygwin POSIX | mintty (Cygwin) | `mvn clean install` |
| Cygwin estilo Windows | mintty (Cygwin) | `mvn clean install -Dcygwin.style=windows` |
| Windows puro | PowerShell / cmd | `mvn clean install` |
| Linux POSIX | consola Linux | *(pendiente, aún no disponible)* |

### Cómo lo lanza Claude (no interactivo)

Claude **no** puede usar `mintty` (es interactivo). Equivalentes verificados:

- **Cygwin** (POSIX o estilo Windows) — herramienta **Bash**:
  `C:/Desarrollo/Cygwin64/bin/bash.exe -lc 'cd /cygdrive/c/GJS/Desarrollo/Maven/gjs/<ruta-modulo> && mvn clean install'`
  (añadir `-Dcygwin.style=windows` para el estilo Windows). El `-l` (login shell)
  replica el entorno de `mintty` (por eso `mvn` está en el `PATH`).
  Ejemplo módulo C/C++: `.../gjs/gjs-c/gjs-c-common-components/gjs-c-common-base`.
- **Windows puro** — herramienta **PowerShell**: `mvn clean install` en el
  directorio del módulo.

Para lanzarlo tú desde **PowerShell** hacia Cygwin, usa el token de parada `--%`
(evita que PowerShell se coma la comilla final):
`C:\Desarrollo\Cygwin64\bin\bash.exe --% -lc 'cd /cygdrive/c/... && mvn clean install'`

### Macros por modo — confirmado (pom padre + `Precompilacion.h`)

Cadena: propiedad `cygwin.style` → perfil en `gjs-c-common-parent` → `platformOptions`
= `-DCYGWIN_POSIX` (por defecto, cuando `cygwin.style != windows`) o `-DCYGWIN_WIN`
(con `-Dcygwin.style=windows`) → llega al compilador vía `${gjs.nar.platform.options}`.
El compilador es `gcc`/`g++` **resuelto por el `PATH` de la consola** (Cygwin → gcc de
Cygwin, define `__CYGWIN__`; Windows → gcc de MinGW-w64, no lo define).

**Macros efectivos por modo:**

| Modo | Compilador (por PATH) | `__CYGWIN__` | Macros |
|---|---|---|---|
| Cygwin POSIX (`-DCYGWIN_POSIX`, por defecto) | gcc de Cygwin | sí | `POSIX` + `CYGWIN` |
| Cygwin estilo Windows (`-DCYGWIN_WIN`) | gcc de Cygwin | sí | `WIN` + `CYGWIN` |
| Windows puro | gcc de MinGW-w64 | no | `WIN` |
| Linux POSIX (futuro) | gcc de Linux | no | `POSIX` |

La conmutación la hace `Precompilacion.h` a partir de `CYGWIN_WIN`/`CYGWIN_POSIX`
(los `-D` del pom): `CYGWIN_WIN → WIN`, en otro caso `→ POSIX`; `CYGWIN` se define
solo si hay `__CYGWIN__` **y** uno de esos dos macros.

Notas:
- `#if defined(WIN) && !defined(CYGWIN)` acierta en los tres
  (Cygwin-POSIX → `setenv`, Windows-puro → `_putenv_s`).
- **El build por defecto desde Cygwin compila las ramas `#if defined(POSIX)`**
  (varias marcadas `PENDIENTE`). Mientras esas ramas no estén terminadas, usar
  `-Dcygwin.style=windows` para volver al comportamiento `WIN`.
- Estado 2026-07: todos los módulos compilan en **Windows puro**. Pendiente verificar
  **Cygwin+WIN** y **Cygwin+POSIX** (este último ejercita por primera vez las ramas
  POSIX).
