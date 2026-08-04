# Portapapeles

| Dato      | Valor                                     |
| --------- | ----------------------------------------- |
| Cabecera  | `AplicacionPortapapeles.h` (55 líneas)    |
| Fuente    | `AplicacionPortapapeles.cpp` (112 líneas) |
| Espacio   | `org::gjs::cpp::common`                   |
| Prefijo   | `AplicPples`                              |
| Funciones | 3 — **sólo en Windows**                   |
| Test      | **—**                                     |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Leer y escribir el portapapeles del sistema.

```cpp
#if ( defined ( WIN ) )
AplicPplesCopiar ( "texto que va al portapapeles" );

std::string * pTexto = AplicPplesContenido ();   // y ademas lo limpia
...
delete pTexto;
#endif
```

## La API

```cpp
#if ( defined ( WIN ) )

void AplicPplesLimpiar ();
void AplicPplesCopiar ( const std::string & sTexto );
std::string * AplicPplesContenido ( bool bLimpiar = true );

#endif
```

Tres funciones, y **las tres dentro de un `#if defined ( WIN )`**: el módulo
entero desaparece fuera de Windows.

---

## Observaciones

- **No existe fuera de Windows, y la fachada lo incluye igual.** `CppCommonSupport.h`
  trae la cabecera sin condición, así que en modo POSIX entra, no declara nada, y
  el error aparece donde alguien llame a `AplicPplesCopiar`, no donde se incluye.
  Es el mismo patrón que
  [CGestorSignals](../../gjs-cpp-common-system/doc/Senales.md) y
  [SistemaRegistro](../../gjs-cpp-common-system/doc/SistemaRegistro.md): tres
  módulos del stack que sólo existen en una plataforma, sin que nada lo avise
  antes de compilar.
- **En POSIX habría por dónde**, aunque no sea trivial: no hay portapapeles del
  sistema como tal, sino el de X11 o el de Wayland, que se manejan con
  herramientas externas —`xclip`, `wl-copy`— o con la biblioteca del servidor
  gráfico. Es trabajo de verdad, y por eso está sin hacer; lo que falta es que la
  cabecera lo diga.
- **No tiene test.** Es defendible: probarlo tocaría el portapapeles real de
  quien lance la compilación, y machacar lo que el usuario tuviera copiado no es
  aceptable en una suite automática. Un test que guardase el contenido, lo
  restaurase al final y se saltase el caso en POSIX sí sería posible.
- **`AplicPplesContenido` devuelve `std::string *`**, puntero desnudo sin decir
  quién libera. Es el tercero del componente, con `AplicConLeerCadena`.
- **`AplicPplesContenido` limpia el portapapeles por defecto.** El parámetro
  `bLimpiar = true` hace que la operación de *leer* sea destructiva salvo que se
  pida lo contrario, que es lo contrario de lo que se espera de una función
  llamada «contenido». `AplicPplesContenido ( false )` es la lectura no
  destructiva, y es la que debería ser el caso por defecto.
- **`AplicPplesCopiar` no devuelve nada.** Abrir el portapapeles puede fallar
  —otro proceso lo tiene tomado, que en Windows pasa—, y el llamante no se
  entera. `AplicPplesLimpiar` lo mismo. La tercera sí devuelve algo, aunque sea
  un puntero.
- **Cuatro caracteres perdidos** (`U+FFFD`) en el `.cpp` y otros cuatro en la
  cabecera.
