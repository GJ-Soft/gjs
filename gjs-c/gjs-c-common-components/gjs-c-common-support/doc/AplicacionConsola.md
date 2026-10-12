# AplicacionConsola

| Dato         | Valor                                                 |
| ------------ | ----------------------------------------------------- |
| Cabecera     | `src/main/include/AplicacionConsola.h`                |
| Fuente       | `src/main/c/org/gjs/c/common/AplicacionConsola.c`     |
| Prefijo      | `AplicCon`                                            |
| Funciones    | 19                                                    |
| Incluido por | `Aplicacion.h`                                        |
| Test         | `AplicacionConsolaTest.c` → `TestAplicacionConsola()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La consola como superficie de dibujo: abrirla, medirla, limpiarla, leer del
usuario y trazar líneas y rectángulos con caracteres de marco.

Es lo que usa [CajaMensajes](CajaMensajes.md) para dibujar sus cuadros cuando no
hay ventanas.

## API

### Estado

| Función                      | Descripción               |
| ---------------------------- | ------------------------- |
| `int AplicConAbrir ()`       | Abre o reabre la consola. |
| `void AplicConCerrar ()`     | La cierra.                |
| `int AplicConEstaAbierta ()` | Estado.                   |
| `int AplicConAncho ()`       | Ancho en columnas.        |
| `void AplicConLimpiar ()`    | Borra la pantalla.        |

`AplicConAncho` es la función mejor resuelta del módulo:

| Modo    | Cómo                                                                                                        |
| ------- | ----------------------------------------------------------------------------------------------------------- |
| Windows | `GetConsoleScreenBufferInfo`, usando `srWindow` —la ventana visible— y no el búfer, que puede ser más ancho |
| POSIX   | `isatty` + `ioctl ( TIOCGWINSZ )`                                                                           |

Si no hay terminal —salida redirigida a un fichero— devuelve
`CON_ANCHO_DEFECTO`, 80. Eso hace que los marcos salgan bien también en un log.

### Lectura

| Función                                              | Descripción                      |
| ---------------------------------------------------- | -------------------------------- |
| `int AplicConLeerNumero ()`                          | Un dígito, o -1.                 |
| `int AplicConLeerNumeroEntre ( int iMin, int iMax )` | Repite hasta que caiga en rango. |
| `char * AplicConLeerCadena ()`                       | Una línea, hasta 255.            |
| `void AplicConEsperarRetorno ()`                     | Espera a que se pulse retorno.   |

### Dibujo

| Función                                                    | Descripción                    |
| ---------------------------------------------------------- | ------------------------------ |
| `int AplicConDibujarLinea ( char cCar )`                   | Línea de ancho completo.       |
| `AplicConDibujarLineaDiscontinua` / `…Simple` / `…Doble`   | Con los tres estilos de marco. |
| `AplicConDibujarLineaExt ( iAncho, iColIni, cCar )`        | Con ancho y columna inicial.   |
| `…DiscontinuaExt` / `…SimpleExt` / `…DobleExt`             | Idem por estilo.               |
| `int AplicConDibujarRectangulo ( iAlto, iAncho, iColIni )` | Rectángulo simple.             |
| `int AplicConDibujarRectanguloDoble ( … )`                 | Rectángulo doble.              |

Los caracteres salen de `AplicacionConfig.h`, que define dos juegos completos
—esquinas, horizontales, verticales y uniones en T— en Unicode
(`┌ ─ ┐ ├ ┤ └ ┘` y `╔ ═ ╗ ╠ ╣ ╚ ╝`) o en página 850, según esté definido
`CON_BORDES_UNICODE`.

## Dependencias

[Cadenas](../../gjs-c-common-text/doc/Cadenas.md) y, en POSIX, `termios` y
`sys/ioctl.h`.

## Test

`AplicacionConsolaTest.c` → `TestAplicacionConsola()`. Cubre apertura, cierre,
ancho y las siete funciones de dibujo, incluidos los casos de ancho o alto 0.
**No cubre ninguna de las cuatro funciones de lectura.**

## Observaciones

> **`AplicConLeerCadena` es un bucle infinito fuera de Visual C.** El cuerpo del
> bucle está dentro de `#if defined ( VC )`, y la rama `#else` es un
> `// PENDIENTE:` vacío:
>
> ```c
> while ( ( iFinal == 0 ) && ( iCar < CON_MAX_TAM_CADENA ) )
> {
> #   if ( defined ( VC ) )
>         ... lee con kbhit / getche ...
> #   else
>         // PENDIENTE:
> #   endif
> }
> ```
>
> Ni `iFinal` ni `iCar` cambian, así que la condición nunca deja de cumplirse.
> En el modo de compilación normal la llamada **cuelga el proceso**. El test no
> la toca, que es por lo que la suite pasa.

> **`AplicConLeerNumeroEntre` puede colgarse también**, por dos motivos
> distintos:
>
> - `AplicConLeerNumero` lee **un solo carácter** con `getchar` y devuelve 0…9 o
>   -1. No lee números, lee dígitos: `AplicConLeerNumeroEntre ( 10, 20 )` no
>   puede terminar nunca porque el valor devuelto jamás llega a 10.
> - El resultado se guarda en un `char`, no en un `int`, así que el `EOF` de
>   `getchar` se confunde con un carácter. Con la entrada agotada —una tubería
>   cerrada, un fichero redirigido— el bucle gira indefinidamente.
>
> Es el mismo patrón que se corrigió en `gjs-bnf-lib`: un bucle de lectura sin
> salida por fin de entrada.

- **`AplicConAbrir` devuelve 0 si no hay terminal** (desde 2026-10-11). Hasta
  entonces hacía `open ( "/dev/tty", O_RDWR )` y encadenaba `tcgetattr`, tres
  `dup2` y `tcsetattr` sin comprobar el descriptor: sin terminal (un servicio,
  una tubería, la integración continua) `open` devolvía -1, todo fallaba en
  silencio y la consola se daba por disponible. Ahora no toca nada y devuelve 0.
  Y si `open` devuelve 0, 1 o 2 —porque ese descriptor estándar estaba
  cerrado— ya no se cierra después, que lo dejaba cerrado otra vez. La versión
  C++ es igual, y además cierra el descriptor, que antes no cerraba.
- **Y redirige los tres descriptores estándar del proceso.** Es una operación
  agresiva para una función que se llama "abrir la consola": un programa que la
  invoque pierde la redirección que le hubiera puesto quien lo lanzó.
- **La rama GNU lleva un `PENDIENTE: Verificar que sobra de todo esto`** sobre el
  bloque de `termios`, que hace `tcgetattr` y `tcsetattr` con la misma
  estructura sin modificarla: efectivamente no hace nada.
- **`AplicConLeerNumeroEntre` señala el error imprimiendo `\b`**, un retroceso,
  en lugar de un mensaje. En una salida redirigida eso es un byte de control
  suelto en medio del fichero.
- El módulo distingue `VC` de `GNU` dentro de la rama no Windows, un eje que el
  resto del stack no usa: en los demás componentes la partición es
  `WIN` / `POSIX`.
