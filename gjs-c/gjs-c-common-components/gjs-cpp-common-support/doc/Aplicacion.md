# La aplicación

| Dato      | Valor                                                                |
| --------- | -------------------------------------------------------------------- |
| Cabeceras | `AplicacionInformacion.h` (72), `AplicacionValidaciones.h` (37)      |
| Fuentes   | `AplicacionInformacion.cpp` (208), `AplicacionValidaciones.cpp` (94) |
| Espacio   | `org::gjs::cpp::common`                                              |
| Prefijo   | `Aplic`                                                              |
| Funciones | 12 + 3                                                               |
| Tests     | `AplicacionInformacionTest.cpp`, `AplicacionValidacionesTest.cpp`    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La identidad del programa: cómo se llama, qué versión es, desde cuándo corre. Y,
sin mucha relación, tres validaciones de códigos de usuario.

```cpp
AplicInicializar ( "MiPrograma", 2, 3, 4, 20260804, true );

AplicNombre ();              // "MiPrograma"
AplicCadenaVersion ();       // "2.3.4"
AplicPID ();                 // el identificador de proceso
AplicImprimirInfoVersion (); // lo saca por consola

AplicFinalizar ();
```

## `AplicacionInformacion`

Es **estado global del proceso**: hay una aplicación y una sola, con su nombre y
su [Version](Version.md) dentro.

| Grupo         | Funciones                                                                |
| ------------- | ------------------------------------------------------------------------ |
| Ciclo de vida | `AplicInicializar`, `AplicFinalizar`, `AplicEstaInicializada`            |
| Identidad     | `AplicNombre`, `AplicPID`                                                |
| Versión       | `AplicVersion`, `AplicSubversion`, `AplicRevision`, `AplicCadenaVersion` |
| Fecha         | `AplicFechaVersion`, `AplicValorFechaVersion`                            |
| Salida        | `AplicImprimirInfoVersion`                                               |

`AplicInicializar` recibe el nombre, los tres números de versión, la fecha como
`long` en formato `AAAAMMDD` y una bandera que dice si hay que abrir la consola.
El último argumento es lo que engancha este módulo con
[AplicacionConsola](Consola.md).

La fecha se ofrece de las dos maneras: `AplicFechaVersion` devuelve un
[`Fecha`](../../gjs-cpp-common-time/doc/Fecha.md) y `AplicValorFechaVersion` el
`long` crudo. Es la misma pareja que el resto del stack ofrece para los datos de
tiempo.

## `AplicacionValidaciones`

Tres funciones sueltas:

```cpp
bool AplicCodigoValido ( const std::string & sCod, int iTam );
bool AplicCodigoUsuarioValido ( const std::string & sCod );
bool AplicClaveUsuarioValido ( const std::string & sClave );
```

La primera es la general —un código de una longitud dada— y las otras dos la
aplican a los dos casos concretos con la longitud ya puesta.

---

## Tests

`AplicacionInformacionTest.cpp` prueba el ciclo entero: que antes de inicializar
no esté inicializada, que después los datos coincidan con los que se pasaron, y
que `AplicFinalizar` lo deshaga. `AplicacionValidacionesTest.cpp` es más largo
—156 líneas— y recorre los casos de borde de las tres validaciones.

---

## Observaciones

### `AplicacionInformacion`

- **`AplicNombre` devuelve `std::string` por valor y `AplicCadenaVersion`
  también**, lo cual está bien y contrasta con `AplicConLeerCadena` de
  [AplicacionConsola](Consola.md), que devuelve puntero. Dentro del mismo
  componente conviven los dos criterios.
- **`AplicPID` devuelve `long`**, y por debajo llama a `SisPID` de
  [gjs-cpp-common-system](../../gjs-cpp-common-system/doc/Procesos.md), que
  arrastra el `PENDIENTE` de pasarlo a `unsigned long` para UNIX. El problema se
  hereda entero.
- **No se puede cambiar nada después de inicializar.** No hay
  `AplicEstablecerNombre` ni equivalente: lo que se pasa a `AplicInicializar` es
  definitivo hasta `AplicFinalizar`. Es defendible para la identidad de un
  programa, y significa que un programa que quiera reetiquetarse tiene que
  finalizar y volver a inicializar.
- **Qué pasa al leer sin inicializar no está dicho.** `AplicNombre()` antes de
  `AplicInicializar` devuelve algo —presumiblemente la cadena vacía—, y la
  cabecera no lo declara; `AplicEstaInicializada` está para preguntarlo antes.
- **La cabecera lleva una nota con dos erratas**: `// Pendeitne a?adir cadena
  fecha y info del nombre` —«Pendeitne» por «Pendiente», y un carácter perdido en
  «añadir»—. Dice lo que falta: una forma de obtener la fecha ya formateada.
- **Diez caracteres perdidos** (`U+FFFD`) en el `.cpp` y siete en la cabecera.

### `AplicacionValidaciones`

- **No pinta nada en este componente.** Validar un código de usuario no tiene que
  ver con la consola, la versión ni el portapapeles; encaja mucho mejor en
  [gjs-cpp-common-io](../../gjs-cpp-common-io/doc/Sesiones.md), junto a
  `GestorUsuarios`, que es quien valida usuarios de verdad. Hoy son dos sitios
  distintos con la misma responsabilidad.
- **`AplicClaveUsuarioValido` no comprueba fortaleza**, sólo forma. El nombre se
  presta a esperar más de lo que hace, y en un componente que también tiene
  `GestorUsuarios` guardando claves en claro conviene tenerlo claro.
- **`AplicCodigoValido ( sCod, iTam )` toma la longitud como argumento** y las
  otras dos la fijan dentro. Los dos valores concretos están en el `.cpp`, no en
  la cabecera, así que quien quiera saber cuánto mide un código de usuario tiene
  que ir a buscarlo.
- **El nombre `AplicClaveUsuarioValido` no concuerda en género** con lo que
  valida —una clave—; `AplicClaveUsuarioValida` sería lo correcto. Es una errata
  en API pública, del mismo tipo que las de
  [gjs-cpp-common-calculation](../../gjs-cpp-common-calculation/doc/CalculoOperaciones.md#observaciones).
