# Calculo

| Dato      | Valor                                    |
| --------- | ---------------------------------------- |
| Cabecera  | `src/main/include/Calculo.h` (29 líneas) |
| Fuente    | `Calculo.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                  |
| Funciones | 5                                        |
| Test      | `CalculoTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un número aleatorio y la comparación de reales con épsilon.

```cpp
double GenerarNumeroAleatorio ();
double Epsilon ();

bool EsIgual ( double dA, double dB );
bool EsMayor ( double dA, double dB );
bool EsMenor ( double dA, double dB );
```

`Epsilon()` expone la tolerancia que usan las tres comparaciones, de modo que
quien necesite comparar de otra forma puede partir del mismo valor.

`EsMayor` y `EsMenor` son lo que añade sobre el módulo equivalente del
componente raíz: no basta con `>` cuando dos números pueden diferir en el último
bit —lo que se quiere es «mayor, y además distinto más allá de la tolerancia»—.

## Dependencias

`<cmath>`, `<random>`.

## Test

`CalculoTest.cpp` → `TestCalculo()`.

## Observaciones

> **Es la tercera implementación de lo mismo en el stack C++**, y la segunda que
> se puede incluir a la vez que otra:
>
> | Dónde                                                     | Qué ofrece                                     |
> |-----------------------------------------------------------|------------------------------------------------|
> | [Real](../../gjs-cpp-common-base/doc/Real.md), en `::real` | `equals` y `equalsWithPrec`, tres tipos, tolerancia y dígitos configurables |
> | **Aquí**, en `::common`                                    | `EsIgual`, `EsMayor`, `EsMenor`, sólo `double`, tolerancia fija |
> | `gjs-cpp-common-calculation`                               | `Epsilon` y las operaciones matemáticas        |
>
> Las dos primeras entran juntas por la fachada `CppCommonTypes.h`. La de `base`
> está en su propio subespacio, así que no chocan los nombres, pero sí conviven
> dos criterios distintos de igualdad entre reales en el mismo programa: uno
> escalado al épsilon de la máquina y multiplicado por una tolerancia que el
> llamante elige, y otro fijo.
>
> Y hay un tercero un componente más arriba, en `calculation`, que es donde
> cabría esperarlo por el nombre.

- **`Epsilon()` es una función y no una constante.** Con `constexpr` —como sí
  hace [Real](../../gjs-cpp-common-base/doc/Real.md) con sus tres épsilon— el
  valor estaría disponible en tiempo de compilación y no habría llamada por
  comparación.
- **Sólo `double`.** No hay versiones para `float` ni `long double`, que sí
  tiene el módulo de `base`, de modo que comparar dos `float` obliga a
  promocionarlos y a comparar con la tolerancia del `double`.
- **`GenerarNumeroAleatorio` devuelve un valor en [0, 1)** de un `mt19937_64`
  por hilo, sembrado desde `random_device` (desde 2026-10-11; antes, `rand`
  con `srand ( time ( 0 ) )`, un estado para todo el proceso que se pisaba
  entre hilos). No es para criptografía. La cabecera sigue sin decirlo, y no
  se puede fijar la semilla para reproducir una prueba —que es lo primero que
  hace falta en un test—. Y en un módulo llamado
  «cálculo», un generador de aleatorios y una comparación de reales son dos
  cosas sin relación.
- **`EsIgual`, `EsMayor` y `EsMenor` sin `EsMayorIgual` ni `EsMenorIgual`**, que
  con tolerancia no son la negación de los anteriores y hay que escribirlas a
  mano.
