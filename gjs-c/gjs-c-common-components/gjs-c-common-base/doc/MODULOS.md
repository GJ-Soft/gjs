# Módulos de gjs-c-common-base

Índice y orquestación de los módulos de la librería. Un **módulo** es un fuente
`.c` con su cabecera `.h` asociada; además existen varias cabeceras sin fuente
(configuración, constantes y tipos) que se describen al final de este documento.

Volver al [README](../README.md).

---

## Capas

Los módulos se apilan en cuatro niveles. Un módulo sólo depende de módulos de su
nivel o inferiores.

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 4. Servicios de alto nivel                                            │
  │    SConversor · Versiones · Hash                                      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 3. Texto, números y conversión                                        │
  │    CadenasBase · FormatoCadena · ConversionesTipos · Numeros          │
  │    ASCIIEstandar · UniChar · Hexadecimal · Tipos                      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. Infraestructura                                                    │
  │    Memoria · InfoMemoria · Errores · Finalizacion · OrdenBytes        │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Primitivas sin dependencias                                        │
  │    Bits · Nibble · Byte · Word · DWord · Booleano · Intercambios      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. Configuración (cabeceras sin fuente)                               │
  │    Precompilacion · BaseConfig · Base · ConstantesBase · BaseErrores  │
  │    ASCIICodigos · JuegosCaracteres · Funciones · TerminalANSI         │
  └───────────────────────────────────────────────────────────────────────┘
```

Hay un ciclo funcional inevitable en el nivel 2-3: `Memoria` notifica sus fallos
a `Errores`, y `Errores` reserva sus mensajes con `Memoria` y `CadenasBase`. Se
resuelve porque ninguno de los tres necesita inicialización previa.

---

## Índice de módulos

| Módulo                                    | Prefijo             | Propósito                                               | Test |
| ----------------------------------------- | ------------------- | ------------------------------------------------------- | ---- |
| [ASCIIEstandar](ASCIIEstandar.md)         | `ASCII`             | Consulta y clasificación de caracteres ASCII (0-127)    | ✔    |
| [Bits](Bits.md)                           | `By`, `BMP_`        | Máscaras de bits y macros de mapas de bits              | ✔    |
| [Booleano](Booleano.md)                   | `Bool`              | Enteros usados como booleanos                           | ✔    |
| [Byte](Byte.md)                           | `Byte`              | Descomposición de bytes en nibbles y paso a hexadecimal | ✔    |
| [CadenasBase](CadenasBase.md)             | `Cad`               | Creación, medida, copia y comparación de cadenas        | ✔    |
| [ConversionesTipos](ConversionesTipos.md) | `Conv`              | Conversiones entre tipos básicos y cadena               | ✔    |
| [DWord](DWord.md)                         | `DWord`             | Composición/descomposición de palabras de 4 bytes       | ✔    |
| [Errores](Errores.md)                     | `Err`               | Subsistema global de errores                            | ✔    |
| [Finalizacion](Finalizacion.md)           | —                   | Terminación forzada por error grave                     | —    |
| [FormatoCadena](FormatoCadena.md)         | `Frm`               | Formateo de cadenas con lista variable de argumentos    | ✔    |
| [Hash](Hash.md)                           | `Hash`              | Funciones hash por tabla de sustitución                 | ✔    |
| [Hexadecimal](Hexadecimal.md)             | `Hex`               | Dígitos hexadecimales                                   | ✔    |
| [InfoMemoria](InfoMemoria.md)             | `Mem`               | Contabilidad de memoria en modo depuración              | —    |
| [Intercambios](Intercambios.md)           | `Intercambiar`      | Intercambio de valores entre dos variables              | ✔    |
| [Memoria](Memoria.md)                     | `Mem`               | Reserva, liberación y manipulación de bloques           | ✔    |
| [Nibble](Nibble.md)                       | `Nib`               | Valor numérico de medio byte                            | ✔    |
| [Numeros](Numeros.md)                     | `Num`               | Conteo de dígitos y partes entera/decimal               | ✔    |
| [OrdenBytes](OrdenBytes.md)               | `Bytes`             | Detección y cambio del orden de bytes (endianness)      | ✔    |
| [SConversor](SConversor.md)               | `SConv`             | Objeto conversor multi-representación                   | ✔    |
| [Tipos](Tipos.md)                         | `Tip`               | Catálogo de super-tipos de datos                        | ✔    |
| [UniChar](UniChar.md)                     | `Unicode`, `CadUni` | Tipo `unichar` y conversión ASCII ↔ Unicode             | ✔    |
| [Versiones](Versiones.md)                 | `Vers`              | Cadenas de versión `a.b.c.d`                            | ✔    |
| [Word](Word.md)                           | `Word`              | Composición/descomposición de palabras de 2 bytes       | ✔    |

---

## Grafo de dependencias entre módulos

Sólo se muestran las dependencias directas declaradas con `#include` en cada
fuente (se omiten `BaseConfig.h` y las cabeceras de configuración, que las usa
prácticamente todo el mundo).

```
Nibble          → (ninguna)
Bits            → (ninguna)
Booleano        → (ninguna)
Word            → (ninguna)
DWord           → (ninguna)
Hexadecimal     → (ninguna)
Numeros         → (ninguna)
Intercambios    → Memoria
Finalizacion    → Memoria
Memoria         → Errores, Finalizacion
Errores         → Memoria, CadenasBase, FormatoCadena
CadenasBase     → Memoria, Errores
FormatoCadena   → Memoria, CadenasBase, Errores
Byte            → Memoria, CadenasBase, Hexadecimal
UniChar         → Memoria, CadenasBase
Tipos           → Memoria
OrdenBytes      → Memoria, Errores
InfoMemoria     → (ninguna; la alimenta Memoria)
ASCIIEstandar   → ASCIICodigos
Versiones       → Memoria, CadenasBase, Errores
Hash            → Memoria, CadenasBase
ConversionesTipos → Memoria, CadenasBase, Numeros
SConversor      → Memoria, CadenasBase, ConversionesTipos
```

---

## Cabeceras de configuración

Cabeceras sin fuente asociado. No son módulos, pero son las piezas que hacen
funcionar a todos los demás.

### `Precompilacion.h`

Normaliza las constantes de precompilación. Es lo primero que se incluye y
establece cuatro ejes:

| Eje              | Valores                                                 |
| ---------------- | ------------------------------------------------------- |
| Máquina          | `A64`, `A32`, `A16`, `A8` — deducido de `INTPTR_MAX`    |
| Sistema / estilo | `POSIX`, `WIN`, más `CYGWIN` como calificador adicional |
| Compilador       | `GNU` (por defecto), `CC`                               |
| Depuración       | `MODO_DEPURACION`, `MODO_DEPURACION_2`                  |
| Otros            | `ALM_ERRORES`                                           |

Reglas de conmutación:

- `CYGWIN` y `WIN` a la vez son un `#error`: Cygwin se compila siempre como
  POSIX.
- `CYGWIN` implica `POSIX`.
- Sin `WIN` y sin `POSIX`: se asume `WIN`.
- `CC` fuerza `POSIX`.
- `MODO_DEPURACION_2` implica `MODO_DEPURACION`.
- `FORMATO_PRINTF ( f, a )` marca las funciones con formato al estilo de
  `printf` (el parámetro `f` es el formato, los argumentos empiezan en `a`, o 0
  si llegan en un `va_list`). Con gcc o clang es `format ( gnu_printf, f, a )`:
  el compilador comprueba en cada llamada que los argumentos casan con el
  formato. `gnu_printf` porque en MinGW `printf` es el formato del runtime de
  Microsoft, y aquí lo interpreta `FrmCadena`. Lo llevan las 24 funciones con
  formato del stack (las `…ConFormato`, `ConDep…`, `ErrEstablecerConFormato`,
  `SErrCrear…Form` y `FrmCadena`); al ponerlo destapó tres llamadas de
  `SRuta.c` que pasaban una `SCadena *` a un `%s`.
- En `WIN` se eleva `WINVER` y `_WIN32_WINNT` a `0x0A00` (Windows 10) como mínimo; hasta el 2026-10-11 era `0x0500` (Windows 2000), que escondía las API de Vista en adelante.

Los `-D` vienen del pom padre `gjs-c-common-parent`, de un perfil que **activa
el entorno** (la variable `CYGWIN`), no una propiedad. El mismo perfil fija el
prefijo del toolchain, así que el compilador tampoco depende del `PATH`:

| Modo         | `platformOptions`  | Compilador               | Macros resultantes |
| ------------ | ------------------ | ------------------------ | ------------------ |
| Cygwin       | `-DCYGWIN -DPOSIX` | gcc de Cygwin            | `CYGWIN` + `POSIX` |
| Windows puro | `-DWIN`            | `x86_64-w64-mingw32-gcc` | `WIN`              |
| Linux        | `-DPOSIX`          | gcc de Linux             | `POSIX`            |

> El modo "Cygwin estilo Windows" (`-Dcygwin.style=windows`, macros
> `CYGWIN_WIN` / `CYGWIN_POSIX`) **ya no existe**.

### `BaseConfig.h`

Configuración efectiva de la librería. Incluye `Precompilacion.h`, después las
cabeceras del sistema que correspondan al entorno (`windows.h` o
`stdio/stdlib/unistd/…`) y define:

- Tipos elementales: `bit`, `nibble`, `byte`, `byte2`, `byte4`, `byte8`,
  `word`, `dword` (con los macros testigo `BYTE2`, `BYTE4` y `BYTE8` según el
  entorno soporte cada uno). Para 64 bits enteros se usa directamente
  `long long` / `unsigned long long`, estándar desde C99.
- Compatibilidad Windows fuera de Windows: `BYTE`, `WORD`, `DWORD`, `MAKEWORD`,
  `LOBYTE`, `HIBYTE`. `DWORD` se protege además con `!defined ( WIN )` porque en
  Cygwin LP64 `unsigned long` son 64 bits y rompería la ABI de Windows.
- Macros de mínimo/máximo: `MIN`, `MAX`, `MIN3`, `MAX3`, `MIN4`, `MAX4`.
- Límites de la librería: `CAD_BASE_TAM_DEFECTO` (1023), `CAD_BASE_MAX_TAM`
  (8191), `MAX_ERRORES` (512), `ERR_MAX_TAM_MSJ` (1024),
  `MEM_MAX_NUM_BLOQUES` / `MEM_MAX_TAM_BLOQUE` (16384),
  `CONV_MAX_TAM_CADENA` (64), `CLASE_MAX_TAM_NOMBRE` (50).
- Tamaños y dígitos máximos por tipo: `TIP_TAM_*`, `TIP_MAX_DIG_*`,
  `TIP_MAX_TAM_CAD_*`.
- Literales: `CAD_VACIA`, `VALOR_NULO` (`"null"`), `ERR_MSJ_OK`,
  `ERR_MSJ_DEFECTO`, `CAD_BASE_TXT_VALOR_NULO`, `CAD_BASE_TXT_DEMASIADO_LARGO`.

Al final incluye `BaseErrores.h`, `ASCIICodigos.h`, `JuegosCaracteres.h`,
`UniChar.h` y `Tipos.h`.

### `Base.h`

Cabecera fachada. Es la única que debería incluir el código cliente. Arrastra
`BaseConfig.h` y las cabeceras de todos los módulos **salvo `SConversor.h`**,
que hay que incluir aparte.

### `ConstantesBase.h`

Resultados de comparación: `COMP_DIFERENTE` (0), `COMP_IGUAL` (1),
`COMP_MENOR` (2), `COMP_MAYOR` (3).

### `BaseErrores.h`

Códigos de error propios de la librería (rango reservado 0-10):

| Código                        | Valor |
| ----------------------------- | ----- |
| `ERR_OK`                      | 0     |
| `ERR_MEMORIA_INVALIDA`        | 1     |
| `ERR_MEMORIA_INSUFICIENTE`    | 2     |
| `ERR_MEMORIA_PROCESO`         | 3     |
| `ERR_PARAMETROS`              | 4     |
| `ERR_POSICION_INVALIDA`       | 5     |
| `ERR_ESTRUCTURA_INVALIDA`     | 6     |
| `ERR_IMPOSIBLE_ABRIR_FICHERO` | 100   |

De ellos, sólo los cinco primeros tienen descripción predefinida en
[Errores](Errores.md); el resto exige pasar el texto con
`ERROR_ESTABLECER_FORM`.

### `ASCIICodigos.h`

Constantes `ASCII_*` para los 128 códigos ASCII, agrupadas por categorías
(control, englobamiento, puntuación, acentos, aritméticos, comparación,
especiales, dígitos, mayúsculas y minúsculas). Las usa
[ASCIIEstandar](ASCIIEstandar.md).

### `JuegosCaracteres.h`

Constantes `JUEG_CAR_*` con los identificadores numéricos de las páginas de
código (EBCDIC, OEM, ANSI, ISO-8859, Mac, EUC, ISCII, Unicode…), con la
numeración de Windows. [UniChar](UniChar.md) usa `JUEG_CAR_OEM_LATIN_I` (850).

### `Funciones.h`

Catálogo de `typedef` de punteros a función y procedimiento, nombrados por su
firma: `PPRC<args>` para los que devuelven `void` y `PFUN<retorno><args>` para
el resto (`PFUNINTV`, `PFUNLONGT`, `PFUNPCHARPV`…). Hay una familia por tipo de
retorno: `INT`, `LONG`, `UINT`, `ULONG`, `CHAR`, `PCHAR`, `LIT`, `FLT`, `DBL` y
`PVOID`, la de los que devuelven `void *` (`PFUNPVOIDV`, `PFUNPVOIDPV`…; hasta el
2026-10-12 eran `PFUNVOIDV` y `PFUNVOIDULIUL`, sin más). También define los
alias sencillos `PTR_FUNCION` y
`PTR_PROCEDIMIENTO`. Los tests usan `PFUNINTV` (`int (*)(void)`) como tipo de
cada caso de prueba, y [Hash](Hash.md) apoya en `PFUNUINTPV` su alias
`PFUNHASH`.

### `TerminalANSI.h`

Secuencias de escape ANSI para color y estilo en terminal: `ANSI_RESETEAR`,
`ANSI_NEGRITA_INI`, `ANSI_SUBRAYADO_INI`, `ANSI_INVERSO_INI`, los ocho colores
de primer plano (`ANSI_ROJO`, `ANSI_VERDE`…) y los ocho de fondo
(`ANSI_FONDO_*`). Las usan los tests para colorear su salida.

---

## Cómo añadir un módulo nuevo

1. Crear `src/main/include/<Modulo>.h` y `src/main/c/org/gjs/c/common/<Modulo>.c`,
   con el prefijo propio en todos los símbolos públicos y el guard
   `_ORG_GJS_C_CC_<MODULO>_H`.
2. Añadir el `#include <<Modulo>.h>` a `Base.h`, en el orden de dependencias.
3. Crear `src/test/c/org/gjs/c/common/<Modulo>Test.c` con una función
   `int Test<Modulo> ()` que devuelva `BOOL_VAL_CIERTO` / `BOOL_VAL_FALSO`.
4. Registrar el test en `Test.c`: incrementar `NUM_TESTS`, añadir el `extern`,
   el nombre en `testArrayInit()` y el puntero en `functionArrayInit()`.
5. Crear `doc/<Modulo>.md` y añadir la fila correspondiente al índice de este
   documento.
