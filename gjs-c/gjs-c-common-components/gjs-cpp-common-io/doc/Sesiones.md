# Sesiones

| Dato    | Valor                                                                               |
| ------- | ----------------------------------------------------------------------------------- |
| Clases  | `GestorUsuarios`, `GestorSesiones`, `ClienteSesion`, `ServidorSesion`               |
| Espacio | `org::gjs::cpp::common`                                                             |
| Líneas  | 675 (246 de cabecera, 429 de fuente)                                                |
| Tests   | `GestorUsuariosTest.cpp`, `GestorSesionesTest.cpp`, `ClienteServidorSesionTest.cpp` |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Poner **identidad** sobre el diálogo de [Comandos](Comandos.md): quién está al
otro lado, si se ha autenticado, y desde cuándo.

---

## `GestorUsuarios`

El censo. Un `map` de usuario a la pareja (clave, subdirectorio).

```cpp
GestorUsuarios usuarios ( "usuarios.info" );
usuarios.Validar ( "vladimiro", "patin1" );      // true
usuarios.Subdirectorio ( "vladimiro" );          // "vladimir"
```

El fichero es **TSV**, una línea por usuario y tres campos:

```
vladimiro	patin1	vladimir
volodimir		volodimir
jarjarbinks	panagiotas	
```

El segundo campo puede ir vacío —usuario sin clave— y el tercero también, en
cuyo caso el usuario no tiene subdirectorio propio. Se carga con `FicheroTSV` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md), y una línea con
menos de dos campos invalida la carga entera.

## `GestorSesiones`

Las sesiones vivas, con dos mapas:

| Mapa          | De         | A                                      |
| ------------- | ---------- | -------------------------------------- |
| `mapSesiones` | Usuario    | (instante de inicio, última actividad) |
| `mapHilos`    | Id de hilo | Usuario                                |

El segundo es lo que hace que la API tenga **cada método por duplicado**: uno
con el usuario explícito y otro sin él, que lo deduce del hilo en curso. Como
[Servidor](ClienteServidor.md) atiende cada conexión en su propio hilo, la
versión sin argumentos «sabe» de quién está hablando.

```cpp
gestorSesiones.setUsuario ( "vladimiro" );   // asocia el hilo actual
gestorSesiones.Abrir ( "vladimiro" );
...
gestorSesiones.EstaAbierta();                // pregunta por el hilo actual
gestorSesiones.TiempoTranscurrido();
```

Hereda de `ControlConcurrencia` en privado, así que las operaciones sobre los
mapas van protegidas.

Hay tres tiempos: `TiempoInicio` (cuándo se abrió), `TiempoTranscurrido` (cuánto
lleva abierta) y `TiempoActividad` (desde la última operación). `Actividad()`
refresca el segundo sello.

## `ClienteSesion` y `ServidorSesion`

`ServidorSesion` implementa el `ProcesarComando` de
[ServidorComandos](Comandos.md) como una **máquina de dos estados**: sin sesión
y con sesión.

```
        comando entrante
              │
     ¿hace falta sesion?  ── no ──> ProcesarComandoSesion
              │ si
     ¿esta abierta?
        │             │
        no            si
        │             └── ¿es comando de fin de sesion?
        │                      si -> cerrar          no -> ProcesarComandoSesion
        │
        └── ¿es comando de inicio de sesion?
                 usuario sin clave -> "falta clave"  ( y se recuerda el usuario )
                 usuario anonimo   -> abre, si se permite
                 usuario y clave   -> valida y abre
                 nada de eso       -> "sesion no abierta"
```

Ese diálogo en dos pasos —primero el usuario, luego la clave— es el de FTP
(`USER` / `PASS`), y el que `ClienteSesion` automatiza del otro lado: guarda
usuario y clave, y en `AbrirSesion()` recorre la lista de
[`ResultadoComando`](Comandos.md) que le da el derivado, comprobando que cada
respuesta sea la esperada.

Los mensajes de cada situación son **seis métodos puros** que pone el protocolo
concreto: `MensajeSesionAbierta`, `MensajeSesionCerrada`, `MensajeFaltaClave`,
`MensajeImposibleAperturaSesion`, `MensajeUsuarioInvalido` y
`MensajeSesionNoAbierta`.

`ClienteSesion` redefine `EnviarComando` y `EnviarMensaje` para no enviar nada
mientras haga falta sesión y no esté abierta. Las cuatro son virtuales en la
base, así que la comprobación vale también por una referencia a
`ClienteComandos` o a `Cliente`. Hasta el 2026-10-12 `EnviarComando` no lo era,
y por `ClienteComandos &` el comando salía sin sesión. `AbrirSesion` y
`CerrarSesion` llaman a `ClienteComandos::EnviarComando` cualificado, que es
justo lo que necesitan para enviar el inicio y el fin de sesión.

---

## Tests

`GestorUsuariosTest.cpp` y `GestorSesionesTest.cpp` prueban los dos gestores
sueltos. `ClienteServidorSesionTest.cpp` es **la suite más larga del componente**
—1.079 líneas—: levanta un servidor con sesión y prueba el diálogo completo con
dos clientes. Comprueba también que sin sesión no sale nada, ni siquiera por
una referencia a `ClienteComandos`.

---

## Observaciones

### Defectos

- **`GestorUsuarios::Cargar` pierde memoria en cada llamada.** Reserva el lector
  con `new` y no lo libera por ninguna de las salidas:

  ```cpp
  FicheroTSV * fichero = new FicheroTSV();
  if ( fichero->Cargar( sRuta ) ) { ... }
  return( bRes );          // aqui se pierde
  ```

  No hace falta el `new`: un objeto en la pila resuelve el caso y además libera
  si salta la excepción.
- **Las claves se guardan y se comparan en claro.** `Validar` hace
  `it->second.first.compare( sClave ) == 0`, sobre el texto tal cual venía del
  fichero TSV. No hay resumen ni sal. Para un servidor de pruebas puede bastar;
  conviene que esté escrito antes de que alguien lo use de otra manera.
- **La comparación de claves no es de tiempo constante**, que en un servidor
  accesible por red es la otra mitad del problema anterior.

### Contratos

- **`GestorSesiones` no limpia nunca las sesiones viejas.** La propia cabecera
  lo dice: `// TODO: Añadir demonio limpiador de sesiones antiguas`. Los tres
  tiempos están medidos y nadie los mira: una sesión que el cliente abandona sin
  cerrar se queda en el mapa mientras viva el proceso, y con ella la entrada del
  hilo en `mapHilos`.
- **`mapHilos` crece con cada conexión.** Se indexa por `std::thread::id`, y los
  hilos de petición van con `detach` y mueren sin avisar; el identificador
  además **se reutiliza** cuando el sistema recicla el hilo. Una entrada vieja
  puede acabar contestando por un hilo nuevo que no es su dueño.
- **La API duplicada por hilo es cómoda y opaca.** `EstaAbierta()` y
  `EstaAbierta( sUsuario )` se leen igual y hacen cosas distintas; la primera
  depende de un estado —qué usuario tiene asociado este hilo— que se fijó en
  otro sitio.
- **`ServidorSesion::EsValido()` exige usuarios cargados** si la sesión es
  necesaria, y la sesión es necesaria salvo que se construya sin fichero de
  usuarios. O sea: un servidor con fichero de usuarios vacío es inválido, y uno
  sin fichero no pide sesión a nadie. Está bien pensado y no está dicho en la
  cabecera.
- **`ClienteSesion` guarda la clave en un `std::string` miembro** durante toda la
  vida del objeto, sin borrarla tras el `AbrirSesion`.
- **`ClienteSesion::ComandoInicioSesion` devuelve `std::list<ResultadoComando> &`**,
  una referencia no constante a una lista que el derivado tiene que mantener
  viva. `ClienteIETF` la guarda como miembro; cualquier otro derivado tiene que
  deducir ese contrato del código.
