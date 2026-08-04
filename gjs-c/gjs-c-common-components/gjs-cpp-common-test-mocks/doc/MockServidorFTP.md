# MockServidorFTP

| Dato      | Valor                                            |
| --------- | ------------------------------------------------ |
| Cabecera  | `src/main/include/MockServidorFTP.h` (53 líneas) |
| Fuente    | `MockServidorFTP.cpp` (76 líneas)                |
| Espacio   | `org::gjs::cpp::common::test::mock`              |
| Deriva de | `ServidorFTP`                                    |
| Métodos   | 6 privados y dos constructores                   |
| Test      | `MockServidorFTPTest.cpp` (79 líneas)            |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un servidor FTP **listo para usar en una prueba**: sirve un directorio de los
recursos de test y deja constancia de lo que le llega.

```cpp
MockServidorFTP servidor ( 44338, 44339, "servidorFTP", "usuarios.info" );

if ( servidor.EsValido () )
{
    servidor.Iniciar ();
    // ... el cliente que se quiere probar ...
    servidor.Parar ();
}
```

## Qué aporta sobre `ServidorFTP`

Dos cosas, y las dos quitan trabajo repetido de las pruebas:

### 1. Resuelve las rutas contra los recursos de la prueba

```cpp
MockServidorFTP::MockServidorFTP ( int iPuerto, int iPuertoDatos,
                                   const string & sSubdirectorioRaiz,
                                   const string & sFicheroUsuarios ) :
    ServidorFTP ( iPuerto, iPuertoDatos,
                  ResolverDirectorioRelativo ( DirectorioTestRecursos (), Concatenar ( "./", sSubdirectorioRaiz ) ),
                  ResolverDirectorioRelativo ( DirectorioTestRecursos (), Concatenar ( "./data/", sFicheroUsuarios ) ) )
```

El llamante dice `"servidorFTP"` y `"usuarios.info"`, y el doble los convierte en
rutas absolutas contra
[`DirectorioTestRecursos()`](../../gjs-cpp-common-test/doc/ContextoTest.md). Sin
esto, cada prueba tendría que saber que el ejecutable se lanza desde
`target/test-nar/test-reports`.

El fichero de usuarios se busca siempre bajo `data/`, y el directorio a servir
cuelga directo de los recursos.

> El comentario del constructor documenta un detalle que se pagó averiguando:
> las partes relativas se prefijan con `"./"` **porque
> `ResolverDirectorioRelativo` sólo compone la ruta cuando empieza por `.` o
> `..`**; sin el prefijo devolvería el directorio de recursos sin añadir nada.

### 2. Rellena las *callbacks* obligatorias

[`ServidorFTP`](../../gjs-cpp-common-io/doc/FTP.md) es **abstracta**: redeclara
como `= 0` cuatro métodos que sus bases ya daban implementados, así que no se
puede instanciar. El doble los implementa registrando por
[gjs-cpp-common-log](../../gjs-cpp-common-log/README.md):

```
{SERVIDORFTP} Recibido comando [USER vladimiro]
{SERVIDORFTP} Inicio sesion de [vladimiro]
{SERVIDORFTP} Procesado comando [RETR datos.csv]
```

El prefijo `{SERVIDORFTP}` es lo que permite separar en el registro lo que dice
el servidor de lo que dice el cliente.

---

## Test

`MockServidorFTPTest.cpp` prueba **el camino de error**: que construir el doble
con un fichero de usuarios que no existe lance `Excepcion` y no deje un servidor
en pie. Guarda y restaura el directorio actual, porque el constructor de
`ServidorFTP` lo cambia.

Lo dice su propio comentario: *«un test funcional completo exigiría levantar el
servidor y un cliente»*. Es la decisión correcta para el tamaño del módulo, y
deja el camino normal sin ejecutar.

---

## Observaciones

### Los dos métodos que no reemplazan nada

```cpp
// MockServidorFTP.h
bool ExcepcionProducida ( std::exception & ex );
void ExcepcionProducidaEnPeticion ( std::exception & ex );
```

```cpp
// Servidor.h, la clase base
virtual bool ExcepcionProducida ( const std::exception & ex );
virtual void ExcepcionProducidaEnPeticion ( const std::exception & ex );
```

**Falta el `const`.** Una firma distinta no reemplaza nada: los dos métodos del
doble son funciones nuevas que **no llama nadie**, y lo que se ejecuta cuando el
servidor tiene una excepción son las versiones por defecto de `Servidor`, que
escriben por `std::cerr`.

O sea: el doble cree que registra los errores por el log —con su prefijo
`{SERVIDORFTP}` y con `LogErrorEx`, que añade el `what()`— y en realidad salen
por la salida de error estándar, sin prefijo y mezclados con todo lo demás.

Dos detalles que lo redondean:

- **`override` lo habría detectado al compilar.** Los otros cuatro métodos del
  doble sí reemplazan —coinciden con las declaraciones puras de `ServidorFTP`—,
  y ninguno de los seis lleva la palabra clave.
- **La copia artesanal no tiene el fallo.** `ServidorFTPTest`, dentro de
  `ClienteServidorFTPTest.cpp` de
  [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md), declara los dos con
  `const exception &`. La versión escrita a mano para una prueba concreta está
  bien y la oficial no, que es un buen motivo para no tener las dos.

El arreglo son dos palabras: `const` en las dos firmas. Añadir `override` a los
seis evita la próxima.

### Si se arregla, el servidor pasará a pararse

`ExcepcionProducida` devuelve `true`, y en
[`Servidor`](../../gjs-cpp-common-io/doc/ClienteServidor.md) ese valor **decide
si el bucle de aceptación termina**: cierto significa parar. La implementación
por defecto de la base devuelve `false`, o sea aguantar y seguir.

Hoy da igual, porque el método no se llama. En cuanto se corrija la firma, el
doble **se detendrá a la primera excepción**, que es un cambio de comportamiento
real en las pruebas que lo usen. Puede ser lo que se quiere —una prueba que falla
rápido— y conviene decidirlo a propósito y no descubrirlo.

### Otras

- **Los seis métodos son privados**, siguiendo el patrón de la jerarquía: son
  puntos de extensión que llama la base, no API del doble.
- **El fichero de usuarios por defecto es `"usuarios.info"`**, que es el que hay
  en los recursos de prueba de
  [gjs-cpp-common-io](../../gjs-cpp-common-io/doc/Sesiones.md). El doble asume la
  convención de otro módulo sin decirlo en la cabecera.
- **No hay forma de consultar lo que pasó.** El doble registra y no acumula: no
  puede decir cuántos comandos recibió ni cuáles. Un doble de prueba que llevara
  la cuenta —`NumComandosRecibidos()`, `UltimoComando()`— permitiría comprobar
  desde el test lo que hoy sólo se puede leer en el registro.
- **`MockServidorFTP.h` incluye `<thread>` y no lo usa.**
- **La cabecera hace `using namespace org::gjs::cpp::common;` en el ámbito
  global.**
