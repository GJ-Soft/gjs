# Secuencias

| Dato      | Valor                                       |
| --------- | ------------------------------------------- |
| Cabecera  | `src/main/include/Secuencias.h` (24 líneas) |
| Fuente    | `Secuencias.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                     |
| Funciones | 1, plantilla                                |
| Test      | `SecuenciasTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Comparar dos arrays al estilo de C.

```cpp
template<typename T> bool SonIguales ( const T val1[], const T val2[] );
```

Es la cabecera más pequeña del componente: una plantilla y nada más.

## Dependencias

`<string>`, `<list>`.

## Test

`SecuenciasTest.cpp` → `TestSecuencias()`.

## Observaciones

> **La firma no recibe el tamaño, y sin él la comparación no puede ser
> correcta.**
>
> ```cpp
> template<typename T> bool SonIguales ( const T val1[], const T val2[] );
> ```
>
> En C++ un parámetro declarado `const T val1[]` **es un puntero**: la
> información de longitud se pierde al llamar. Dentro de la función sólo se
> puede recorrer hasta un centinela —el `'\0'` de una cadena, un `NULL` en un
> array de punteros—, y eso limita la plantilla a los tipos que tengan uno, cosa
> que ni el nombre ni la firma dicen. Con `T = int` no hay valor de parada, y
> recorrer hasta encontrarlo lee fuera del array.
>
> Las tres formas de arreglarlo, de menos a más idiomática:
>
> ```cpp
> template<typename T> bool SonIguales ( const T val1[], const T val2[], size_t tam );
> template<typename T, size_t N> bool SonIguales ( const T (&val1)[N], const T (&val2)[N] );
> template<typename T> bool SonIguales ( const std::vector<T> & v1, const std::vector<T> & v2 );
> ```
>
> La segunda deduce el tamaño del propio tipo y no deja pasar arrays de longitud
> distinta; la tercera es la que encaja con el resto del componente.

- **Se solapa con `SonIguales` de
  [Colecciones](../../gjs-cpp-common-base/doc/Colecciones.md)**, en el
  componente raíz, que compara `std::list` y `std::vector` de cadenas. Mismo
  nombre, misma idea, dos componentes, y aquí sin el tamaño.
- **Y las dos duplican `operator==`**, que la biblioteca estándar ya define para
  sus contenedores.
- **La cabecera incluye `<string>` y `<list>`** y no usa ninguno de los dos: la
  única declaración es la plantilla sobre arrays.
- **Al ser plantilla, la definición tiene que estar visible.** Está en el
  `.cpp`, de modo que sólo sirve para los tipos que allí se instancien
  explícitamente; un `SonIguales` sobre un tipo del usuario falla al enlazar. Es
  el mismo caso que las plantillas de
  [ToString](../../gjs-cpp-common-base/doc/Conversiones.md).
