# FTP

| Dato      | Valor                                           |
| --------- | ----------------------------------------------- |
| Clases    | `ClienteFTP`, `ServidorFTP`                     |
| Cabeceras | `ClienteFTP.h` (78), `ServidorFTP.h` (63)       |
| Fuentes   | `ClienteFTP.cpp` (481), `ServidorFTP.cpp` (492) |
| Espacio   | `org::gjs::cpp::common`                         |
| Test      | `ClienteServidorFTPTest.cpp` (512 líneas)       |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

FTP sobre la pila de [IETF](IETF.md): un cliente con las operaciones de siempre
—entrar, moverse, listar, subir y bajar— y un servidor que sirve un directorio.

```cpp
ClienteFTP cliente ( "localhost", 21, "vladimiro", "patin1" );
if ( cliente.AbrirSesion() )
{
    cliente.setBinario();
    cliente.CambiarDirectorioRemoto ( "informes" );

    std::vector<std::string> vecContenido;
    cliente.ContenidoDirectorioRemoto ( vecContenido );

    cliente.BajarFichero ( "enero.pdf", "./descargas/enero.pdf" );
    cliente.CerrarSesion();
}
```

## Las dos conexiones

FTP usa **dos sockets**: uno de control, por el que van los comandos, y otro de
datos, que se abre para cada transferencia y se cierra al acabar. De ahí los dos
puertos —21 y 20 por convenio, `IETF_PUERTO_FTP` e `IETF_PUERTO_DATOS_FTP`— y de
ahí los dos modos:

| Modo       | Quién abre el socket de datos                            | Estado aquí         |
| ---------- | -------------------------------------------------------- | ------------------- |
| **Pasivo** | El cliente, al puerto que le dice el servidor con `PASV` | funciona            |
| **Activo** | El servidor, al puerto que le dice el cliente con `PORT` | **sin implementar** |

En pasivo, `PrepararSocketDatos` manda `PASV`, lee la respuesta —que trae la
dirección en seis campos separados por comas— y saca el puerto de los dos
últimos:

```cpp
iPuertoDatos = ToInt( vecCampos[ n-2 ] ) * 256 + ToInt( vecCampos[ n-1 ] );
```

que es exactamente el cálculo que manda el protocolo.

## La API del cliente

| Grupo         | Métodos                                                                                             |
| ------------- | --------------------------------------------------------------------------------------------------- |
| Sesión        | `AbrirSesion`, `CerrarSesion`, `SesionAbierta`, `EsValido`                                          |
| Modo          | `isModoActivo`, `isModoPasivo`, `setModoActivo`, `setModoPasivo`                                    |
| Tipo          | `isAscii`, `isBinario`, `setAscii`, `setBinario`                                                    |
| Servidor      | `EstadoServidor`, `PingServidor`, `InfoSistemaServidor`                                             |
| Directorios   | `DirectorioRemoto`, `CambiarDirectorioRemoto`, `CrearDirectorioRemoto`, `ContenidoDirectorioRemoto` |
| Transferencia | `BajarFichero`, `SubirFichero`                                                                      |

`setAscii` y `setBinario` no son banderas locales: mandan `TYPE A` o `TYPE I` y
sólo cambian el estado si el servidor contesta bien.

## El servidor

`ServidorFTP` se construye con **el directorio que va a servir** y, opcionalmente,
el fichero de usuarios y el de contexto. Acepta los 34 comandos de
`lisComandosFtp`, valida la aridad de cada uno en `EsComandoValido` y los
despacha en `ProcesarComandoSesion`.

Hereda de [`ServidorIETF`](IETF.md) **en privado**, de modo que la superficie
pública queda reducida a `Iniciar`, `Parar`, los puertos y `EsValido`.

---

## Test

`ClienteServidorFTPTest.cpp` levanta un `ServidorFTPTest` en los puertos 44338 y
44339 sobre `src/test/resources/servidorFTP`, y un cliente que abre sesión, se
mueve por los directorios, lista y transfiere. Es la prueba de integración más
completa del componente.

---

## Observaciones

### Defectos

- **El modo activo está declarado y no existe.** `setModoActivo( iPuerto )` deja
  la bandera puesta, y a partir de ahí:

  ```cpp
  bool ClienteFTP::BajarFichero ( ... )
  {
      if ( bModoActivo )
      {
          // No implementado
      }
      else { ... }
      return( bRes );      // falso, sin decir por que
  }
  ```

  Lo mismo en `SubirFichero`, y `PrepararSocketDatos` y `AbrirSocketDatos` no
  hacen nada en ese modo. Es decir: **quien llame a `setModoActivo` obtiene un
  cliente que falla en todas las transferencias y devuelve `false` sin
  distinguirlo de un error de red**. O se implementa el `PORT`, o el método
  debería negarse a poner la bandera.
- **`BajarFichero` y `SubirFichero` no comprueban el socket de datos.**

  ```cpp
  sockDatos = AbrirSocketDatos();
  do { *sockDatos >> sRespuesta; } while ( ... );
  ```

  `AbrirSocketDatos` devuelve `NULL` cuando `iPuertoDatos` es 0, que es lo que
  pasa si el `PASV` falló o el servidor contestó otra cosa. El desreferenciado
  no está protegido: un `PASV` fallido es un cierre por violación de acceso, no
  un `false`.
- **La sincronización del socket de datos es una espera fija.**
  `AbrirSocketDatos` hace `Esperar( 100 )` antes de conectar, para dar tiempo al
  servidor a abrir su escucha. Cien milisegundos valen en `localhost` y no
  garantizan nada en una red real ni en una máquina cargada.
- **`ClienteFTP.h` hace `using namespace org::gjs::cpp::common;` en el ámbito
  global**, igual que `ClienteIETF.h` y `ClienteHTTP.h`. Ver
  [IETF](IETF.md#observaciones).
- **`ServidorFTP` es abstracta sin motivo aparente.** Re-declara como `= 0`
  cuatro *callbacks* que [ServidorComandos](Comandos.md) y
  [ServidorSesion](Sesiones.md) ya daban implementadas y vacías:

  ```cpp
  void ComandoRecibido( Comando & comando ) = 0;
  void ComandoProcesado( Comando & comando, bool & bResultado ) = 0;
  void SesionIniciada( const std::string & sUsuario ) = 0;
  void SesionFinalizada( const std::string & sUsuario ) = 0;
  ```

  Es C++ válido —volver a declarar pura una virtual heredada—, pero convierte
  cuatro puntos de traza opcionales en obligaciones: **no se puede usar un
  `ServidorFTP` sin derivar de él y escribir los cuatro**, aunque sea con el
  cuerpo vacío. El test tiene que hacerlo. Si la intención era declarar los
  reemplazos, sobra el `= 0`.
- **Queda un bloque muerto con un error de sintaxis dentro.** Entre las líneas
  127 y 147 de `ServidorFTP.cpp` hay un `/* … */` con cuatro métodos escritos
  como `ServidorIETF::` —la clase equivocada— que además se llaman a sí mismos:

  ```cpp
  void ServidorIETF::SesionIniciada( const string & sUsuario )
  {
      ServidorFTP::SesionIniciada( sUsuario ;      // falta el parentesis
  }
  ```

  Comentado no molesta; descomentarlo no compila, y si compilara sería recursión
  infinita.

### Diseño

- **Un solo directorio para todos.** La cabecera lo dice:
  `// TODO: Subdirectorios por usuario + concurrencia (multiples usuarios en
  diferentes directorios)`. `GestorUsuarios` ya guarda el subdirectorio de cada
  usuario y `ServidorFTP` todavía no lo usa: el servidor sirve `sDirectorioRaiz`
  a todo el mundo.
- **El constructor cambia el directorio actual del proceso**, como el de
  [ServidorHTTP](HTTP.md). Es global y afecta a todo lo demás que corra en el
  mismo proceso; el test lo restaura a mano al final.
- **`bModoBinario` del cliente y del servidor son variables distintas y sin
  relación.** El cliente cambia el suyo cuando el servidor acepta el `TYPE`, y
  el del servidor lo lleva su propio `ProcesarComandoSesion`. Que coincidan
  depende de que nadie se salte el protocolo.
- **La transferencia va por `std::string`.** `BajarFichero` acumula lo que llega
  en un `string` y lo vuelca al `ofstream` trozo a trozo; `SubirFichero` lee en
  un buffer de 2 KB y lo copia a un `string` para enviarlo. Funciona con datos
  binarios porque `string` admite ceros intercalados, y significa una copia de
  más por bloque.
- **El bucle de bajada termina cuando llega un bloque vacío**, que es lo mismo
  que devuelve un socket cerrado y un socket sin datos todavía. La transferencia
  se corta en el primer hueco.
- **Faltan comandos por implementar**, anotados en el propio fuente:
  `IETF_CMD_AYUDA`, `IETF_CMD_CUENTA`, `IETF_CMD_RESERVAR` e `IETF_CMD_ANEXAR`
  están en la lista de comandos aceptados pero no en el despacho.
