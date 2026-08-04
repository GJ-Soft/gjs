# UtilesTest

| Dato      | Valor                                       |
| --------- | ------------------------------------------- |
| Cabecera  | `src/main/include/UtilesTest.h` (59 líneas) |
| Fuente    | **`UtilesTest .cpp`** (257 líneas)          |
| Espacio   | `org::gjs::cpp::common::test`               |
| Funciones | 21                                          |
| Test      | `UtilesTestTest.cpp` (503 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Las **verificaciones**: comprobar un valor contra el esperado, dejar constancia
en el registro si no coinciden, y acumular el resultado.

```cpp
static bool MiCaso ()
{
    bool bRes = true;

    VerificarValor ( "suma",       Sumar ( 2, 3 ),   5,       bRes );
    VerificarValor ( "nombre",     obj.getNombre (), "Pepe",  bRes );
    VerificarEsCierto ( "es par",  EsPar ( 4 ),               bRes );
    VerificarNoEsNulo ( "creado",  p_obj,                     bRes );

    VerificarFichero ( sRutaSalida, 6, bRes );

    return ( bRes );
}
```

## El convenio: `bool & bRes`

Todas reciben **el resultado acumulado por referencia** y lo ponen a falso si la
comprobación no pasa. Nunca lo ponen a cierto, de modo que un `bRes` que empieza
en `true` acaba en `false` si falló alguna, y **el caso sigue ejecutándose hasta
el final**: se ven todas las diferencias de una vez, no sólo la primera.

Es la decisión que distingue a este módulo de un `assert`, y la que hace que los
casos del stack se puedan escribir de corrido.

El primer parámetro, `sInfoCaso`, es la etiqueta que sale en el registro cuando
la comprobación falla.

## Las 21 funciones

| Familia                      | Sobrecargas | Comprueba                                                |
| ---------------------------- | ----------- | -------------------------------------------------------- |
| `VerificarValor`             | 14          | Igualdad, para cada tipo                                 |
| `VerificarEsCierto`          | 1           | Que un `bool` sea cierto                                 |
| `VerificarEsFalso`           | 1           | Que sea falso                                            |
| `VerificarEsNulo`            | 1           | Que un puntero sea nulo                                  |
| `VerificarNoEsNulo`          | 1           | Que no lo sea                                            |
| `VerificarExistenciaFichero` | 1           | Que el fichero esté                                      |
| `VerificarFichero`           | 4           | Su número de líneas, su contenido, o contra otro fichero |

Las catorce de `VerificarValor` cubren `std::string`, `const char *`, `long`,
`int`, `bool`, `double`, `float`, `std::wstring`, `wchar_t *` y —las dos más
útiles— `IComparable &` y `IComparable *`, que son las que comparan objetos del
stack con su `operator==`.

Las cuatro de `VerificarFichero` son lo que permite probar los módulos que
escriben a disco: comparar contra un número de líneas, contra un vector de
líneas, contra una cadena o **contra otro fichero de referencia**.

---

## Test

`UtilesTestTest.cpp` es **la suite más larga del componente**, 503 líneas: cada
sobrecarga con su caso que pasa y su caso que falla.

---

## El fichero huérfano

Hay una segunda cabecera, `ControlTest.h`, que es **casi el mismo fichero**:
declara las mismas 21 funciones, en el mismo orden, en el mismo espacio de
nombres. Es el nombre viejo del módulo, heredado de `gjs-c-common-test`.

Tres cosas la hacen digna de mención:

1. **Comparte la guarda de inclusión con `UtilesTest.h`**:

   ```cpp
   #ifndef _ORG_GJS_C_CC_CPP_TEST_UTILESTEST_H
   #define _ORG_GJS_C_CC_CPP_TEST_UTILESTEST_H
   ```

   idéntica en las dos. Quien incluyera las dos se quedaría **con la que llegase
   primero, sin aviso**. Es el mismo defecto que ya está anotado en el stack C
   entre `SLista.h` y `SListaHash.h`.
2. **No compilaría si alguien la incluyera.** Declara `const wstring &` sin
   cualificar, y ninguna de sus inclusiones trae `using namespace std;`.
3. **Su `.cpp` no le corresponde.** `ControlTest.cpp` —52 líneas— define
   `IniTest()` y `FinTest()`, dos funciones que **no están declaradas en ninguna
   cabecera**, y ni siquiera incluye `ControlTest.h`.

Hoy no rompe nada porque **nadie incluye `ControlTest.h`**: no está en la fachada
y no aparece en ningún `#include` del repositorio. Es dos ficheros de peso muerto
con una trampa dentro; borrarlos no cambia nada de lo que compila.

---

## Observaciones

- **El fichero fuente se llama `UtilesTest .cpp`**, con un espacio entre el
  nombre y el punto. Compila porque el `nar-maven-plugin` recoge los fuentes por
  patrón, y es la clase de nombre que rompe cualquier orden que no lleve la ruta
  entrecomillada, y que despista al buscarlo.
- **`VerificarValor` para reales compara con `==`.** Las sobrecargas de `double`
  y `float` no admiten tolerancia, en un stack que tiene
  [`MatEsIgual`](../../gjs-cpp-common-calculation/doc/CalculoOperaciones.md) y
  [`EsIgual`](../../gjs-cpp-common-types/doc/Calculo.md) justo para eso. Comparar
  reales con igualdad exacta en una prueba es la receta del fallo intermitente;
  una sobrecarga con un cuarto parámetro de precisión lo resolvería.
- **Hay una sobrecarga `( long, int )` y no la simétrica `( int, long )`.**
  `VerificarValor ( "x", lResultado, 5, bRes )` resuelve; con los tipos al revés,
  la promoción decide, y no está claro cuál gana.
- **Las dos de `IComparable` toman referencias no constantes**, así que no se
  puede verificar contra un objeto constante ni contra un temporal. Viene de que
  el `operator==` de esa jerarquía tampoco es `const`.
- **Ninguna devuelve nada.** El resultado va al `bool &`, de modo que no se puede
  encadenar ni preguntar «¿pasó ésta?» sin mirar `bRes` antes y después.
- **Qué escriben y dónde no está en la cabecera.** Las 21 dejan constancia por el
  registro de [gjs-cpp-common-log](../../gjs-cpp-common-log/README.md), así que
  **si el registro no está inicializado, una comprobación que falla no dice
  nada**: `bRes` se pone a falso en silencio y el caso da KO sin explicación. Es
  lo que hace que el armazón dependa del log para ser útil.
- **`VerificarFichero` lee el fichero entero en cada llamada.** Comprobar cinco
  cosas de un fichero son cinco lecturas.
- **La cabecera hace `using namespace org::gjs::cpp::common;` en el ámbito
  global**, como otras cuatro del componente.
