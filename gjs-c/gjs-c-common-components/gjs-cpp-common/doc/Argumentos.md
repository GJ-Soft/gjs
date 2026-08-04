# Argumentos

| Dato      | Valor                                                           |
| --------- | --------------------------------------------------------------- |
| Cabeceras | `Argumentos.h` (75 líneas), `ArgumentoInvalidoExcepcion.h` (29) |
| Fuentes   | `Argumentos.cpp` (170), `ArgumentoInvalidoExcepcion.cpp` (34)   |
| Espacio   | `org::gjs::cpp::common`                                         |
| Métodos   | 8 + 1                                                           |
| Tests     | `ArgumentosTest.cpp` (220 líneas), `ExcepcionTest.cpp` (53)     |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La línea de órdenes ya troceada, saneada y convertible a número.

```cpp
int main ( int argc, char ** argv )
{
    Argumentos args ( argc, argv );

    for ( int i = 0; i < args.NumArgumentos (); i++ )
    {
        std::cout << args.Argumento ( i ) << std::endl;
    }

    if ( args.EsArgumentoNumerico ( 0 ) )
    {
        int iValor = args.ArgumentoEntero ( 0 );
    }
}
```

## La API

| Grupo        | Métodos                                                                                                 |
| ------------ | ------------------------------------------------------------------------------------------------------- |
| Construcción | `Argumentos ( argc, argv )`, y `Argumentos ()` **sólo en Windows**                                      |
| Consulta     | `NumArgumentos`, `Argumento`                                                                            |
| Conversión   | `EsArgumentoNumerico`, `ArgumentoEntero`, `ArgumentoEnteroLargo`, `ArgumentoReal`, `ArgumentoRealDoble` |

**El índice 0 es el primer argumento de verdad, no el nombre del programa**: el
constructor arranca en `argv[1]`. Es el convenio de la versión C, y conviene
tenerlo presente porque va al revés que `argv`.

`Argumento` lanza `ArgumentoInvalidoExcepcion` si el índice se sale, en vez de
devolver una cadena vacía. Es la única clase de datos del stack que señala el
error con una excepción.

## `ArgumentoInvalidoExcepcion`

Deriva de `Excepcion` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md) y sólo añade el
constructor con módulo, rutina y el argumento que falló.

---

## Tests

`ArgumentosTest.cpp` —220 líneas, el más largo del componente— construye desde
un `argv` de mentira y prueba la cuenta, el acceso, las conversiones y la
excepción. `ExcepcionTest.cpp` prueba el mensaje.

---

## Observaciones

### El filtro es distinto en cada plataforma

Los dos constructores hacen lo mismo salvo por dos líneas, y esas dos líneas
cambian el resultado:

| Paso    | POSIX (`argc`, `argv`)         | Windows (`CommandLineToArgvW`)          |
| ------- | ------------------------------ | --------------------------------------- |
| Saneado | `EliminarCaracteresNoEstandar` | **`EliminarCaracteresNoAlfanumericos`** |
| Recorte | `EliminarBlancos`              | `Trim`                                  |

El de Windows **se queda sólo con letras y dígitos**. Eso significa que
`--verbose` llega como `verbose`, `fichero.txt` como `ficherotxt` y
`--salida=/tmp/x` como `salidatmpx`. Es decir: **las opciones no sobreviven al
constructor en Windows**, que es justo para lo que sirve una línea de órdenes.

Y el de POSIX usa `EliminarBlancos`, que quita **todos** los espacios y no sólo
los de los extremos, de modo que un argumento entrecomillado con espacios
—`"mi fichero.txt"`— llega pegado.

Los dos deberían usar el mismo par, y probablemente `EliminarCaracteresNoEstandar`
más `Trim`, que es lo mínimo que hace falta.

### El descarte de vacíos no descarta nada

```cpp
if ( ( sArg.length () >= 0 ) && ( sArg != "\\" ) )
{
    vecArgumentos [ iNumArgumentos ] = sArg;
    iNumArgumentos = iNumArgumentos + 1;
}
```

`length()` devuelve un `size_t`, que no puede ser negativo: **`>= 0` es cierto
siempre**. La intención era descartar los argumentos que quedaran vacíos tras el
saneado —es lo que hace la versión C—, y lo único que se descarta hoy es la barra
invertida suelta. Cambiar `>=` por `>` lo arregla, y está en los dos
constructores.

### Otras

- **El constructor sin argumentos sólo existe en Windows**, donde lee la línea de
  órdenes del sistema con `CommandLineToArgvW`. Es una comodidad real —y hace que
  el mismo código no compile en POSIX—. En POSIX se puede leer `/proc/self/cmdline`,
  que es el equivalente.
- **El vector se dimensiona a `iNumArgs - 1` y se rellena parcialmente.** Si
  algún argumento se descarta, quedan huecos vacíos al final que
  `NumArgumentos()` no cuenta pero el vector sigue guardando. Inofensivo y
  desordenado; con `push_back` no pasaría.
- **El comentario contradice al código.** Dice
  *«NOTA: en Unix/Linux suelen pertenecer al espacio de direcciones reservado. No
  usar ES_VALIDO»* y la línea siguiente usa `ES_VALIDO ( p_p_cArg )`. Una de las
  dos cosas hay que corregir.
- **Con `argc == 1` no se construye nada.** El constructor exige `iNumArgs > 1`,
  lo cual es correcto —no hay argumentos que guardar— y deja `iNumArgumentos` a
  cero, que es lo que se espera.
- **`EsArgumentoNumerico` y las cuatro conversiones no dicen qué hacen con un
  índice inválido.** `Argumento` lanza; si las otras cinco también lanzan, o
  devuelven cero, hay que ir al `.cpp` para saberlo, y son las que más se usan.
- **La guarda de la cabecera de la excepción tiene una errata**:
  `_ORG_GJS_C_CC_CPP_ARGUUMENTOINVALIDOEXCEPCION_H`, con dos úes. No rompe nada
  —una guarda sólo tiene que ser única— y despista al buscarla.
- **Los identificadores de las guardas dicen `CARGUMENTOS` y `CMENSAJES`**, con
  la `C` del nombre viejo de las clases (`CArgumentos`, `CMensajes`), que ya no
  llevan. Queda el rastro del renombrado.
