# Version

| Dato     | Valor                                    |
| -------- | ---------------------------------------- |
| Cabecera | `src/main/include/Version.h` (90 líneas) |
| Fuente   | `Version.cpp` (200 líneas)               |
| Espacio  | `org::gjs::cpp::common`                  |
| Métodos  | 14                                       |
| Test     | `VersionTest.cpp` (162 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La versión de un programa: tres números y la fecha en que se publicó.

```cpp
Version ver ( 2, 3, 4, (long) 20260804 );

ver.Ver ();                    // 2
ver.Subver ();                 // 3
ver.Rev ();                    // 4
ver.CadenaVersion ();          // "2.3.4"
ver.CadenaVersion ( true );    // "2.3"     <- la corta quita la revision
```

**`bCorta` decide si sale la revisión, no la fecha**: los dos formatos son
`"{}.{}.{}"` y `"{}.{}"`, y **la fecha no aparece en ninguno**. Para mostrarla
hay que pedirla aparte con `Fecha()` y formatearla.

Es **la única clase del componente**, y la usa
[AplicacionInformacion](Aplicacion.md) para guardar la versión del programa.

## La API

| Grupo        | Métodos                         |
| ------------ | ------------------------------- |
| Lectura      | `Ver`, `Subver`, `Rev`, `Fecha` |
| Escritura    | `Establecer` (dos formas)       |
| Presentación | `CadenaVersion`, `Imprimir`     |
| Validez      | `EsValida`                      |

Los cinco `Establecer…` por campo —`EstablecerVer`, `EstablecerSubver`,
`EstablecerRev` y las dos `EstablecerFecha`— son **privados**: desde fuera sólo
se puede fijar la versión entera de una vez, que es lo razonable para un dato que
tiene que ser coherente.

## `private Fecha`

```cpp
class Version : private Fecha
```

Hereda de [`Fecha`](../../gjs-cpp-common-time/doc/Fecha.md) en privado para
guardar la fecha de publicación. La herencia privada aquí es composición
disfrazada —igual que en los sockets de
[gjs-cpp-common-io](../../gjs-cpp-common-io/doc/Sockets.md)—: `Version` no *es*
una fecha, la *tiene*.

---

## Test

`VersionTest.cpp` cubre construcción, lectura, cadena corta y larga, cambio con
`Establecer` y validez. Todas sus construcciones llevan la fecha con un molde
explícito —`Version verObj ( 2, 3, 4, (long) 0 )`—, y eso no es casualidad: ver
la primera observación.

---

## Observaciones

### Los dos constructores se pisan

```cpp
Version ( int iVersion, int iSubversion = 0, int iRevision = 0, long lFecVersion = 0 );
Version ( int iVersion, int iSubversion = 0, int iRevision = 0,
          const Fecha & fecVersion = Fecha{} );
```

Los dos aceptan los mismos tres primeros argumentos y **los dos tienen el cuarto
por defecto**, así que cualquier llamada con uno, dos o tres argumentos encaja
en ambos y el compilador no puede elegir:

```cpp
Version v1 ( 2 );              // ambiguo: no compila
Version v2 ( 2, 3 );           // ambiguo: no compila
Version v3 ( 2, 3, 4 );        // ambiguo: no compila
Version v4 ( 2, 3, 4, 0L );    // resuelve: el de long
Version v5 ( 2, 3, 4, fecha ); // resuelve: el de Fecha
```

Es decir: **el constructor cómodo —sólo el número de versión— no se puede usar**,
y los valores por defecto de `iSubversion` y `iRevision` no sirven para nada. El
test lo confirma sin decirlo: sus cuatro construcciones escriben el molde
`(long) 0` a mano, que es exactamente lo que hay que hacer para desempatar.

Lo mismo le pasa a la pareja `Establecer`, y el test también lo esquiva:
`verObj.Establecer ( 5, 6, 7, (long) 20251127 )`.

**El arreglo es quitar el valor por defecto de uno de los dos cuartos
parámetros** —el de `long`, por ejemplo—: entonces `Version ( 2 )` resuelve sin
ambigüedad al de `Fecha`, y las llamadas con `long` siguen funcionando.

### El método que tapa al tipo

```cpp
::org::gjs::cpp::common::Fecha Fecha () const;
```

Un método llamado `Fecha` que devuelve un `Fecha`. A partir de esa línea, dentro
de la clase, **`Fecha` nombra la función y no el tipo**, y por eso las otras
cuatro firmas que lo usan tienen que escribirlo entero:

```cpp
Version ( int, int, int, const ::org::gjs::cpp::common::Fecha & fecVersion = ::org::gjs::cpp::common::Fecha{} );
bool EstablecerFecha ( const ::org::gjs::cpp::common::Fecha & fecVersion );
bool Establecer ( int, int, int, const ::org::gjs::cpp::common::Fecha & fecVersion = ::org::gjs::cpp::common::Fecha{} );
```

Esa cualificación de cuarenta caracteres repetida seis veces en una cabecera de
noventa líneas **es la huella del problema**. Es el mismo defecto que
[FechaHora](../../gjs-cpp-common-time/doc/FechaHora.md), y aquí se ve el coste
sin salir del fichero. Con llamar al método `FechaVersion` —como ya se llama
`AplicFechaVersion` en [AplicacionInformacion](Aplicacion.md)— desaparecen las
seis.

### Otras

- **`CadenaVersion` no es `const`** y `Ver`, `Subver`, `Rev` y `Fecha` sí. No
  modifica nada; es una asimetría que impide formatear una `Version` constante.
- **`EsValida` tampoco es `const`.**
- **El nombre `bCorta` no dice lo que hace.** Se lee como «la versión abreviada»
  y lo que quita es **la revisión**: `2.3.4` frente a `2.3`. Además la rama larga
  exige `iRevision >= 0`, que siempre se cumple salvo que alguien haya metido un
  negativo, así que en la práctica el parámetro es lo único que decide.
- **La fecha no sale en ninguna de las dos cadenas**, pese a ser la mitad de lo
  que la clase guarda. Un tercer formato, o un parámetro más, sería lo natural.
- **`Imprimir` escribe por la salida estándar.** Es cómodo para un programa de
  consola y deja sin salida a quien quiera meter ese texto en un registro;
  `CadenaVersion` cubre ese caso.
- **`EsValida` exige `Fecha::EsValida()`**, así que una versión sin fecha no es
  válida aunque los tres números lo sean. El test no lo comprueba —su caso de
  invalidez usa `Version ( 0, 0, 0, 0 )`, y el comentario dice que falla por el
  `iVersion > 0`—, de modo que el efecto de la fecha sobre la validez está sin
  probar y sin documentar.
- **Siete caracteres perdidos** (`U+FFFD`) en los comentarios de la cabecera y
  cinco en el `.cpp`.
