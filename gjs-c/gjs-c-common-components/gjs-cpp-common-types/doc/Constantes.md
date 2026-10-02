# Constantes

| Dato     | Valor                                       |
| -------- | ------------------------------------------- |
| Cabecera | `src/main/include/Constantes.h` (72 líneas) |
| Fuente   | **Ninguno** — todo en la cabecera           |
| Espacio  | `org::gjs::cpp::common`                     |
| Test     | `ConstantesTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La **fecha de compilación**, descompuesta en año, mes y día, calculada en
tiempo de compilación a partir del `__DATE__` del preprocesador.

`__DATE__` da algo como `"Aug  3 2026"`: el mes en letras y el día sin cero a la
izquierda. Estas constantes lo convierten a cifras:

```cpp
const char FECHA_ANO [ 4+1 ] = { __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10], '\0' };

const char FECHA_MES [ 2+1 ] =
{
    ( __DATE__[0] == 'O' || __DATE__[0] == 'N' || __DATE__[0] == 'D' ) ? '1' : '0',
    ( __DATE__[0] == 'J' ) ? ( ( __DATE__[1] == 'a' ) ? '1' : ( ( __DATE__[2] == 'n' ) ? '6' : '7' ) ) :
    ( __DATE__[0] == 'F' ) ? '2' :
    …
};

const char FECHA_DIA [ 2+1 ] = { __DATE__[4] == ' ' ? '0' : __DATE__[4], __DATE__[5], '\0' };
```

El mes se resuelve con una cadena de ternarios sobre las tres letras: la primera
distingue casi todos los meses, y donde no basta —`Jan`/`Jun`/`Jul`,
`Mar`/`May`, `Apr`/`Aug`— se mira la segunda o la tercera. El día pone el cero a
la izquierda que `__DATE__` deja en blanco.

Sirve para sellar un binario con la fecha en que se construyó, sin tocar el
sistema de compilación.

## Dependencias

`<stdio.h>`.

## Test

`ConstantesTest.cpp` → `TestConstantes()`.

## Observaciones

> ~~**`FECHA_AÑO` lleva una eñe en el identificador.**~~ **Resuelto el
> 2026-09-16: ahora es `FECHA_ANO`.**
>
> Los identificadores con caracteres fuera de ASCII sólo son válidos desde
> C++11, y con soporte real del compilador: GCC los admite en UTF‑8 desde la
> versión 10, y otros compiladores tratan el fichero fuente con otra
> codificación y no lo aceptan.
>
> Compilar, compilaba. Lo que lo destapó fue el analizador estático: cppcheck
> no sabe leer esos caracteres ( `unhandledChar`, código 195 ) y marcaba **toda**
> la ejecución como «con errores críticos», no sólo este fichero. Era el único
> identificador acentuado del stack entero.
>
> Se renombró también el local `sAño` de `ConstantesTest.cpp`, por lo mismo.

- **Son `const char[]` en una cabecera**, de modo que cada unidad de compilación
  que incluya la fachada obtiene su propia copia de las tres. Con `constexpr` y
  `inline` —o mejor, `std::string_view`— se evitaría.
- **No hay una constante con la fecha completa.** Componer `AAAAMMDD` obliga a
  concatenar las tres, que es lo que se querría para pasársela a
  `AplicInicializar` o a un [Version](../../gjs-cpp-common-support/README.md).
- **Ni la hora.** `__TIME__` está disponible y no se usa, de modo que dos
  compilaciones del mismo día son indistinguibles.
- **La cadena de ternarios no es verificable de un vistazo**, y un error en una
  letra daría un mes equivocado sólo en ese mes. El test es la única red: merece
  la pena que cubra los doce casos, cosa que sólo se puede comprobar leyéndolo,
  porque `__DATE__` vale lo que valga el día que se compile.
- **Se apoya en la localización C de `__DATE__`.** El estándar fija el formato en
  inglés, así que es seguro; conviene saber que ésa es la razón de comparar
  contra `'J'`, `'F'`, `'M'`…
