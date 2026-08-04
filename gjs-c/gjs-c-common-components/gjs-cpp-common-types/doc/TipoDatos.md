# TipoDatos

| Dato     | Valor                                      |
| -------- | ------------------------------------------ |
| Cabecera | `src/main/include/TipoDatos.h` (34 líneas) |
| Fuente   | `TipoDatos.cpp`                            |
| Espacio  | `org::gjs::cpp::common`                    |
| Test     | `TipoDatosTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo de tipos del modelo de datos, como **`enum class`**.

```cpp
enum class TipoDatos : int
{
    INDEFINIDO = 0,
    ENTERO     = 1,
    REAL       = 2,
    CADENA     = 3,
    BOOLEANO   = 4,
};

std::string ToString ( TipoDatos tipo );
```

Cinco valores y una función de volcado. Al ser `enum class` con tipo base
explícito, los valores **no se convierten solos a `int`** —hay que escribir el
molde— y no contaminan el espacio de nombres: se escribe `TipoDatos::ENTERO`.

Es la diferencia con el catálogo `TIP_*` del stack C, que son `#define` sueltos
sin tipo. Aquí el compilador no deja pasar un `int` cualquiera donde se espera
un tipo de dato.

Sobre él se construye [Tipo](Tipo.md), que le añade comparación y predicados.

## Dependencias

`<string>`.

## Test

`TipoDatosTest.cpp` → `TestTipoDatos()`.

## Observaciones

- **Cinco tipos para todo el modelo de datos.** No hay fecha, ni hora, ni
  binario, ni un entero sin signo o de precisión larga, que sí distingue el
  catálogo del stack C —donde `TipTam` cubre una docena—. Un
  [Valor](Valor.md) se puede construir desde `long long` o `unsigned long`, y al
  describirlo con un [Atributo](Atributo.md) sólo cabe decir `ENTERO`.

  La falta de fecha es la que más se nota: el stack tiene
  [gjs-cpp-common-time](../../gjs-cpp-common-time/README.md) entero para ellas,
  y aquí una fecha sólo puede ser `CADENA`.
- **`ToString` es una función libre con un nombre que ya está muy sobrecargado.**
  En [gjs-cpp-common-base](../../gjs-cpp-common-base/doc/Conversiones.md) hay
  más de treinta `ToString`, y ésta se suma al conjunto por argumento. Funciona
  —la resolución por tipo es exacta— y hace que `ToString ( tipo )` se escriba
  igual que todo lo demás.
- **No hay la función inversa.** Ni `ToTipoDatos ( const std::string & )`, de
  modo que un tipo leído de un fichero de configuración hay que traducirlo a
  mano. El catálogo equivalente en C sí tiene el par completo: `TipSisNombre` y
  `TipSisId`.
- **`INDEFINIDO = 0` es el valor por defecto de un `TipoDatos` sin inicializar**,
  lo que está bien pensado: un tipo recién construido no miente diciendo que es
  entero.
- **La coma final tras `BOOLEANO = 4,`** es legal y deliberada en muchos estilos
  —facilita añadir valores—; conviene saber que no es un descuido.
