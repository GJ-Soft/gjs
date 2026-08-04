# Ficheros

| Dato      | Valor                                          |
| --------- | ---------------------------------------------- |
| Cabecera  | `src/main/include/Ficheros.h` (32 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Ficheros.cpp` |
| Espacio   | `org::gjs::cpp::common`                        |
| Funciones | 6                                              |
| Test      | `FicherosTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Leer y escribir ficheros de texto **enteros, en una llamada**.

```cpp
std::vector<std::string> LeerFichero ( const std::string & sRuta );

void GuardarFichero ( const std::string & sRuta, const std::vector<std::string> & vecLineas );
void GuardarFichero ( const std::string & sRuta, const std::string & sContenido );

void ImprimirFichero ( const std::string & sRuta );
void EliminarFichero ( const std::string & sRuta );
bool FicherosIguales ( const std::string & sRuta1, const std::string & sRuta2 );
```

Seis funciones frente a los siete tipos de fichero y las 300 funciones de
[gjs-c-common-io](../../gjs-c-common-io/README.md). No es el mismo alcance: eso
es una capa de entrada/salida completa y esto es la comodidad de tratar un
fichero pequeño como un vector de líneas.

```cpp
std::vector<std::string> vecLineas = LeerFichero ( "config.txt" );

for ( const std::string & sLinea : vecLineas ) { … }

GuardarFichero ( "salida.txt", vecLineas );
```

`FicherosIguales` es la que usan las pruebas del stack para comparar lo
generado con lo esperado, igual que
[FicTxtContenidoCoincide](../../gjs-c-common-support/doc/Pruebas.md) en C.

## Dependencias

`<string>`, `<vector>` y `<fstream>`.

## Test

`FicherosTest.cpp` → `TestFicheros()`.

## Observaciones

- **Cuatro de las seis devuelven `void`** y no dicen si han funcionado. Un
  `GuardarFichero` sobre un directorio sin permiso o un `EliminarFichero` de algo
  que no existe no informan de nada. Si el criterio del componente es señalar los
  fallos con excepciones —que es lo que hace el resto—, aquí faltaría lanzar
  [SistemaExcepcion](SistemaExcepcion.md), y decirlo en la cabecera.
- **`LeerFichero` carga el fichero entero en memoria.** Es lo que promete y está
  bien para configuración o para pruebas; para un log de un giga, no. La
  cabecera no acota el tamaño, y no hay versión que recorra por líneas.
- **No hay `ExisteFichero` aquí**: está en [Sistema](Sistema.md), junto con
  `ExisteDirectorio`. Comprobar antes de leer obliga a mirar en otra cabecera.
- **No se dice qué pasa con el terminador de línea.** No hay opción de estilo
  DOS o UNIX, como sí tiene
  [SFicTexto](../../gjs-c-common-io/doc/FicherosBasicos.md) en el stack C, así
  que un fichero leído y vuelto a guardar puede cambiar de terminador sin aviso.
  Es exactamente el problema que dejó inservible a `SMsjCargar` en C.
- **`FicherosIguales` no dice en qué se diferencian.** Devuelve `bool`; para una
  función que se usa en pruebas, saber la primera línea que no cuadra vale más
  que el sí o el no.
- **`ImprimirFichero` escribe por `std::cout` sin permitir otro destino.** Una
  sobrecarga con `std::ostream &` la haría útil fuera de la consola.
