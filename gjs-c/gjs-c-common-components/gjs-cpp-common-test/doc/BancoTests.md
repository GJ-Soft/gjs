# BancoTests

| Dato     | Valor                                       |
| -------- | ------------------------------------------- |
| Cabecera | `src/main/include/BancoTests.h` (52 líneas) |
| Fuente   | `BancoTests.cpp` (93 líneas)                |
| Espacio  | `org::gjs::cpp::common::test`               |
| Métodos  | 5                                           |
| Test     | `BancoTestsTest.cpp` (104 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El **programa de pruebas**: registra las suites por nombre y las ejecuta, todas o
la que se pida por la línea de órdenes.

```cpp
int main ( int argc, char * argv[] )
{
    BancoTests banco;

    banco.NuevoTest ( "FechaTest", TestFecha );
    banco.NuevoTest ( "HoraTest",  TestHora );

    return ( banco.Ejecutar ( argc, argv ) ? 0 : -1 );
}
```

```
$ Test.exe              # todas
$ Test.exe HoraTest     # solo esa
```

## La API

| Método                       | Qué hace                                           |
| ---------------------------- | -------------------------------------------------- |
| `NuevoTest ( nombre, func )` | Registra una suite                                 |
| `NumTests ()`                | Cuántas hay                                        |
| `Ejecutar ( sTest )`         | Una, o todas si la cadena está vacía o es `"null"` |
| `Ejecutar ( argc, argv )`    | Toma el nombre de `argv[1]`, o todas si no viene   |

Por dentro es un
[`MapaVector<FUNCION_BOOL>`](../../gjs-cpp-common-types/doc/MapaVector.md), que
es lo que da las dos formas de acceso: **por nombre** para la selección, y **por
posición** para recorrerlas.

Eso tiene una consecuencia que conviene saber: **las suites se ejecutan en el
orden en que se registraron**, no en orden alfabético. Es lo contrario de lo que
hacen los `Test.cpp` escritos a mano del resto del stack, que usan un
`std::map<string, …>` y por tanto van en orden alfabético — y por eso un KO
aparece donde no se espera
(ver [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md#el-fallo-con-código-255)).

---

## Test

`BancoTestsTest.cpp` prueba el registro, el recuento y las dos formas de
ejecutar. Los ficheros `Ejemplo1Test.cpp` y `Ejemplo2Test.cpp` de la carpeta de
pruebas son las suites de mentira que se registran.

---

## Observaciones

- **`"null"` es un nombre reservado y no está documentado.** `Ejecutar ( "null" )`
  ejecuta todas, igual que la cadena vacía. Viene de que `Ejecutar ( argc, argv )`
  usa `"null"` como valor inicial cuando no hay argumento, y se ha filtrado a la
  API pública: una suite que se llamara `null` no se podría seleccionar.
- **Un nombre desconocido escribe por `cerr` y devuelve falso.** Es razonable
  —equivocarse de nombre es un error— y es la única salida del componente que no
  pasa por el registro.
- **`NuevoTest` no comprueba si el nombre ya está.** `MapaVector::push_back`
  admite el duplicado, y a partir de ahí `Ejecutar ( "MiTest" )` corre una de las
  dos y el recorrido completo corre las dos.
- **No hay recuento.** `BancoTests` devuelve un `bool` y no dice **cuántas
  suites** pasaron ni cuáles fallaron, aunque cada [`Test`](Test.md) lleve su
  propia cuenta por dentro. Con N suites, lo único que sale es «alguna falló».
  Sumar los contadores de cada suite sería el resumen que hoy hay que buscar en
  el registro.
- **La suite que devuelve falso no detiene el recorrido**, que es lo correcto:
  todas se ejecutan y el resultado es la conjunción. Merece decirse porque es
  justo lo que **no** hacen los `Test.cpp` a mano del stack, encadenados con `&&`.
- **`Ejecutar ( argc, argv )` sólo mira `argv[1]`.** Ni más de una suite, ni
  opciones, ni `--help`. Es lo mismo que hacen a mano los demás componentes, y
  para eso están [`Argumentos`](../../gjs-cpp-common/doc/Argumentos.md) un
  componente más abajo.
- **El destructor llama a `mapTests.clear()`**, que es lo que haría el destructor
  del propio mapa. Inofensivo y redundante.
