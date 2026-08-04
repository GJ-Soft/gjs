# Cliente y Servidor

| Dato      | Valor                                    |
| --------- | ---------------------------------------- |
| Clases    | `Cliente`, `Servidor`                    |
| Cabeceras | `Cliente.h` (51), `Servidor.h` (66)      |
| Fuentes   | `Cliente.cpp` (90), `Servidor.cpp` (197) |
| Espacio   | `org::gjs::cpp::common`                  |
| Test      | `ClienteServidorTest.cpp`                |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El esqueleto sobre el que se monta todo lo demás: un servidor concurrente que
acepta conexiones y las atiende en hilos, y un cliente que envía y espera
respuesta. Ninguna de las dos clases sabe nada de protocolos; eso lo pone
[Comandos](Comandos.md) encima.

Las dos son **abstractas**: cada una deja un método puro que el usuario tiene
que escribir.

```cpp
class MiServidor : public Servidor
{
public:
    MiServidor ( int iPuerto ) : Servidor ( iPuerto ) {}
private:
    void ProcesarMensaje ( const std::string & sMensaje, bool & bResponder,
                           std::string & sRespuesta, bool & bResultado,
                           bool & bFin, SocketAtencion * socket ) override
    {
        sRespuesta = sMensaje;      // eco
        bResponder = true;
        bResultado = true;
        bFin = ( sMensaje == "FIN" );
    }
};

MiServidor servidor ( 8080 );
servidor.Iniciar();     // vuelve enseguida: el trabajo va en un hilo
...
servidor.Parar();
```

---

## `Servidor`

Hereda de `SocketServidor` en privado y de `Contador` en público —de
[gjs-cpp-common-types](../../gjs-cpp-common-types/README.md)—, que le lleva la
cuenta de peticiones atendidas con éxito y con error.

### El modelo de hilos

```
  Iniciar()  ->  hilo RutinaAtencion
                     │
                     └─ while( !bParar ):  Aceptar()  ->  hilo RutinaPeticion  ( detach )
                                                              │
                                                              └─ while( !bFin && !bParar ):
                                                                     recibir -> ProcesarMensaje -> responder
```

**Un hilo por conexión**, desacoplado (`detach`). No hay límite de conexiones
simultáneas ni reserva previa de hilos.

### Parar un `accept` bloqueante

`Parar()` tiene un apaño explicado en el propio código y que merece leerse:

```cpp
bParar = true;
SocketCliente * pDespertar = new SocketCliente( "127.0.0.1", getPuerto() );
thServidor->join();
delete pDespertar;
```

En winsock, cerrar el socket **no desbloquea** un `accept` en curso. La solución
es conectarse al propio puerto para que `accept` devuelva, ver que `bParar` está
puesto y salir del bucle. La conexión se mantiene abierta hasta después del
`join` para asegurar que la recoge.

`RutinaAtencion` distingue esa conexión efímera y la cierra sin atenderla.

### Los puntos de extensión

| Método                         | Obligatorio | Cuándo                              |
| ------------------------------ | ----------- | ----------------------------------- |
| `ProcesarMensaje`              | **sí**      | Por cada mensaje recibido           |
| `PeticionRecibida`             | no          | Al empezar a atender una conexión   |
| `PeticionFinalizada`           | no          | Al terminarla, con el resultado     |
| `ExcepcionProducida`           | no          | Excepción en el bucle de aceptación |
| `ExcepcionProducidaEnPeticion` | no          | Excepción atendiendo una petición   |

`ExcepcionProducida` **devuelve un `bool` que decide si el servidor para**: si
devuelve cierto, el bucle de aceptación termina. Por defecto devuelve falso, o
sea que el servidor aguanta el error y sigue.

## `Cliente`

Mucho más simple: hereda de `SocketCliente` en privado y añade `EnviarMensaje`
con y sin respuesta. Deja puro `ExcepcionProducida`, que además es **privado**,
así que el usuario lo implementa sin poder llamarlo.

---

## Dependencias

`Propiedades` y `Contador` de
[gjs-cpp-common-types](../../gjs-cpp-common-types/README.md), y `<thread>`.

## Test

`ClienteServidorTest.cpp` levanta un servidor de eco en un hilo y le lanza dos
clientes.

---

## Observaciones

### Concurrencia

- **`bParar` y `bEjecucion` son `bool` normales, leídos y escritos por varios
  hilos.** El hilo principal escribe `bParar` en `Parar()` y los hilos de
  atención y de petición lo leen en sus bucles. Sin `std::atomic` ni cerrojo,
  formalmente es una carrera de datos; en la práctica funciona porque el
  compilador no tiene mucho margen para cachear la variable a través de las
  llamadas a socket, pero es una garantía que no está escrita en ninguna parte.
- **`bEjecucion` se pone a cierto en `Iniciar` y nunca vuelve a falso.** Tras un
  `Parar()`, un segundo `Iniciar()` no hace nada: el servidor no se puede
  reiniciar. El destructor llama a `Parar()`, así que el ciclo normal funciona;
  arrancar-parar-arrancar, no.
- **Los hilos de petición van con `detach`.** Al parar el servidor no se espera
  a que terminen: `Parar()` sólo hace `join` del hilo de aceptación. Una
  petición larga sigue viva sobre un objeto que puede estar destruyéndose.
- **`RutinaPeticion` accede a `bParar` del servidor** desde un hilo desacoplado,
  de modo que la carrera anterior alcanza también a la vida del objeto.

### Contratos

- **`ProcesarMensaje` tiene seis parámetros, cinco de ellos de salida por
  referencia** (`bResponder`, `sRespuesta`, `bResultado`, `bFin`, más el socket).
  Es la firma que arrastra toda la jerarquía de arriba, y en cada nivel se
  reenvía entera. Una estructura de respuesta habría evitado propagar cinco
  referencias por siete niveles de herencia.
- **`bResultado` no se inicializa antes de llamar a `ProcesarMensaje`.** En
  `RutinaPeticion` se declara `bool bRes = false;` fuera del bucle y se pasa por
  referencia en cada vuelta, así que **conserva el valor de la iteración
  anterior** si el usuario no lo escribe. Lo que acaba contando el `Contador` es
  el resultado del último mensaje que lo tocó, no el de la petición.
- **El mensaje vacío se ignora en silencio.** Hay un `TODO` comentado
  preguntándose si hace falta una llamada de vuelta tipo «ruido recibido». Como
  está, un `recv` que devuelve cadena vacía —incluido el EOF— vuelve a dar la
  vuelta al bucle sin condición de salida propia: quien cierra el bucle es la
  excepción del socket o el `bFin` del protocolo.
- **`Servidor::Contexto()` devuelve `Propiedades` por valor**, o sea una copia
  del contexto entero en cada llamada.
- **`Cliente::ExcepcionProducida` es privado y puro.** Funciona —el patrón NVI
  lo permite—, pero deja al derivado con un método que debe escribir y no puede
  invocar, ni siquiera para encadenar.
