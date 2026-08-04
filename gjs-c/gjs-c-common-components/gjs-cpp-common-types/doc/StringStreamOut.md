# StringStreamOut

| Dato      | Valor                                            |
| --------- | ------------------------------------------------ |
| Cabecera  | `src/main/include/StringStreamOut.h` (47 líneas) |
| Fuente    | `StringStreamOut.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                          |
| Deriva de | `std::stringstream`                              |
| Test      | `StringStreamOutTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un flujo que escribe **a la vez en memoria y en la consola**. Lo que se le manda
queda guardado y además sale por `std::cout`.

```cpp
class StringStreamOut : public std::stringstream
{
public:
    StringStreamOut ();
    ~StringStreamOut ();

    StringStreamOut & put   ( char c );
    StringStreamOut & write ( const char * s, std::streamsize n );

    template<typename T> StringStreamOut & operator<< ( T val )
    {
        std::cout << val;
        static_cast<std::ostream &> ( *this ) << val;
        return ( *this );
    }

    StringStreamOut & operator<< ( const std::string & val );
    StringStreamOut & operator<< ( std::streambuf * sb );
    StringStreamOut & operator<< ( std::ostream & (*pf) ( std::ostream & ) );
    StringStreamOut & operator<< ( std::ios & (*pf) ( std::ios & ) );
    StringStreamOut & operator<< ( std::ios_base & (*pf) ( std::ios_base & ) );
};
```

Es el patrón que en Unix hace el programa `tee`: el mensaje se ve al momento y
queda registrado para comprobarlo después.

Las cuatro sobrecargas de puntero a función son las que hacen que
`ssSalida << std::endl` funcione: los manipuladores del flujo no son valores,
son funciones, y sin esas firmas la plantilla no los aceptaría bien.

## Dependencias

`<sstream>`, `<iostream>`.

## Test

`StringStreamOutTest.cpp` → `TestStringStreamOut()`.

## Observaciones

- **La plantilla `operator<<` toma el argumento por valor.** `T val` copia todo
  lo que se le pase; con la sobrecarga explícita para `const std::string &` el
  caso frecuente queda cubierto, pero cualquier otro tipo grande se copia.
  `template<typename T> StringStreamOut & operator<< ( const T & val )` lo
  evitaría.
- **El destino es siempre `std::cout`, fijo.** No hay forma de duplicar hacia
  `std::cerr` ni hacia un fichero; un parámetro `std::ostream &` en el
  constructor haría la clase general.
- **Deriva de `std::stringstream` públicamente**, de modo que quien reciba una
  referencia a la base puede escribir por ella y **saltarse la duplicación**: el
  `operator<<` de `std::ostream` no es virtual y no se redefine, se tapa. Pasar
  un `StringStreamOut` a una función que reciba `std::ostream &` hace que todo
  lo que escriba vaya sólo a memoria.

  Es el riesgo de heredar de los flujos de la estándar: la personalización se
  hace con `std::streambuf`, no tapando operadores. Con un búfer propio que
  escribiera en los dos sitios, la duplicación funcionaría venga por donde
  venga.
- **`put` y `write` tampoco son virtuales en la base**, así que aplica lo mismo.
- **El destructor no hace nada declarado** y la clase no libera recursos: podría
  omitirse.
- **Se solapa con [CaptorSalida](CaptorSalida.md)**, que resuelve el mismo
  problema —ver lo impreso y guardarlo— por la vía correcta, sustituyendo el
  `std::streambuf` de `std::cout`. Dos clases en el mismo componente para captar
  la salida, con estrategias distintas.
