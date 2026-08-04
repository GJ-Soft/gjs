# Conversiones: ToString, ToInt y ToReal

| Dato      | Valor                                                 |
| --------- | ----------------------------------------------------- |
| Cabeceras | `ToString.h` (71), `ToInt.h` (50), `ToReal.h` (38)    |
| Fuentes   | `ToString.cpp`, `ToInt.cpp`, `ToReal.cpp`             |
| Espacio   | `org::gjs::cpp::common`                               |
| Funciones | 45                                                    |
| Tests     | `ToStringTest.cpp`, `ToIntTest.cpp`, `ToRealTest.cpp` |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Convertir **cualquier cosa a texto**, y el texto de vuelta a número. Es la
familia que usa el resto del stack para volcar y para leer.

Frente al [Conversor](Conversor.md), que es un objeto con estado, aquí son
funciones libres sobrecargadas: se llaman igual sea cual sea el tipo, y el
compilador elige.

```cpp
std::string s = ToString ( 42 );                     // "42"
std::string t = ToString ( vecNombres );             // volcado del vector
long        l = ToInt ( "123" );
double      d = ToDouble ( "3.1416" );
std::string u = ToString ( "{} tiene {} anyos", sNombre, iEdad );
```

## `ToString`

| Grupo        | Sobrecargas                                                                   |
| ------------ | ----------------------------------------------------------------------------- |
| Enteros      | `short`, `int`, `long`, `long long` y sus versiones sin signo                 |
| Reales       | `float`, `double`, `long double`                                              |
| Caracteres   | `char`, `unsigned char`, `char *`, `const char *`                             |
| Texto ancho  | `std::wstring`, `wchar_t *`, `const wchar_t *`                                |
| Booleano     | `bool`                                                                        |
| Tiempo       | `const tm *`, y `ToTimeString ( time_t )`                                     |
| Interfaz     | `IToString &`, `IToString *`                                                  |
| Contenedores | Plantillas para `list<T>`, `vector<T>` y `map<string,T>`, por valor y puntero |
| Formato      | `ToString ( sFormato, Args&&... )` variádica                                  |

La última es la interesante: se apoya en **`<format>` de C++20**, de modo que el
formato es `{}` y no `%d`, y el compilador comprueba los tipos.

Las plantillas de contenedor aceptan **cualquier `T`** que sepa convertirse,
mientras que las seis declaradas en [IToString](IToString.md) sólo aceptan
`IToString *`.

## `ToInt`

Diez sobrecargas —texto estrecho, texto ancho e `IToString`— que devuelven
`long`, más ocho `ToLLong` que devuelven `long long`.

## `ToReal`

Ocho sobrecargas de `ToDouble`, con las mismas familias de entrada.

## Dependencias

`<format>`, `<string>`, `<list>`, `<vector>`, `<map>`, `<ctime>` y
[IToString](IToString.md).

## Tests

`ToStringTest.cpp` → `[Test ToString]`, `ToIntTest.cpp` → `[Test ToInt]`,
`ToRealTest.cpp` → `[Test ToDouble]`.

## Observaciones

- **`ToInt` devuelve `long`, no `int`.** El nombre dice una cosa y la firma
  otra; quien asigne a un `int` se come un estrechamiento silencioso. Con
  `ToLLong` al lado devolviendo `long long`, lo coherente sería que `ToInt`
  devolviera `int` y existiera un `ToLong`.
- **`ToReal.h` no declara ningún `ToReal`.** Sólo hay `ToDouble`, de modo que el
  nombre del fichero no corresponde con su contenido, y no hay conversión a
  `float` pese a que `ToString` sí la tiene en el otro sentido.
- **`ToString ( long )` está declarada dos veces** en la misma cabecera: una en
  el primer bloque, con nombre de parámetro, y otra en la lista de tipos
  primitivos. Es legal y redundante.
- **Ninguna de las tres familias dice qué pasa con una entrada inválida.**
  `ToInt ( "hola" )` no tiene un contrato escrito: ni excepción documentada, ni
  valor centinela, ni parámetro de salida. Es la misma carencia que
  [SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md) tiene en el stack C,
  con la diferencia de que aquí hay excepciones disponibles y `std::stol` ya
  lanza `std::invalid_argument`: bastaría con documentar que se propaga.

  El [Conversor](Conversor.md) sí resuelve esto, con `ConversionValida()`. Dos
  caminos para lo mismo, uno con detección de error y otro sin ella.
- **Las plantillas de contenedor están declaradas en la cabecera y definidas en
  el `.cpp`**, lo que sólo funciona si se instancian explícitamente allí. Un
  `ToString ( std::list<MiTipo> )` con un tipo nuevo del usuario fallaría al
  enlazar.
- **`<format>` es C++20**, coherente con el `gnu++20` del pom, pero ata el
  componente a compiladores recientes: GCC lo soporta desde la versión 13.
- `ToTimeString` rompe la nomenclatura de la familia: es el único que no se llama
  `ToString`, pudiendo ser una sobrecarga más para `time_t`.
