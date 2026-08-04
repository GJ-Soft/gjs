# UtilesTest

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabecera     | `src/main/include/UtilesTest.h`                             |
| Fuente       | `src/main/c/org/gjs/c/common/test/UtilesTest.c` (94 líneas) |
| Prefijo      | **Ninguno**                                                 |
| Funciones    | 10                                                          |
| Incluido por | `CTest.h`                                                   |
| Test         | `UtilesTestTest.c` → `TestUtilesTest()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los **verificadores**: las funciones con las que un caso comprueba que lo que ha
obtenido es lo que esperaba.

Todas siguen la misma forma:

```c
void VerificarXxx ( const char * p_cInfoCaso, … resultado …, … esperado …, int * iRes );
```

Reciben una etiqueta para la traza, el valor obtenido, el esperado y **el puntero
al resultado del caso**, que ponen a 0 si la comprobación falla. Eso es lo que
permite encadenar comprobaciones sin cortar el caso:

```c
static int CasoMiModulo_01 ()
{
    int iRes = 1;

    VerificarValorEntero ( "suma",  Sumar ( 2, 3 ), 5,     &iRes );
    VerificarValorLit    ( "nombre", p_cNombre,     "Ana", &iRes );
    VerificarNoEsNulo    ( "objeto", p_objObj,             &iRes );

    return ( iRes );
}
```

El caso sigue hasta el final aunque falle la primera, y en la traza salen todas.

## API

| Función                                                                    | Comprueba                      |
| -------------------------------------------------------------------------- | ------------------------------ |
| `VerificarValorLit ( p_cInfoCaso, p_cResultado, p_cEsperado, iRes )`       | Cadenas: longitud y contenido. |
| `VerificarValorEntero ( p_cInfoCaso, iResultado, iEsperado, iRes )`        | `int`.                         |
| `VerificarValorEnteroLargo ( p_cInfoCaso, lResultado, lEsperado, iRes )`   | `long`.                        |
| `VerificarValorReal ( p_cInfoCaso, fResultado, fEsperado, iRes )`          | `float`, con épsilon.          |
| `VerificarValorRealDoble ( p_cInfoCaso, dResultado, dEsperado, iRes )`     | `double`, con épsilon.         |
| `VerificarEsCierto ( p_cInfoCaso, iResultado, iRes )`                      | Distinto de 0.                 |
| `VerificarEsFalso ( p_cInfoCaso, iResultado, iRes )`                       | Igual a 0.                     |
| `VerificarEsNulo ( p_cInfoCaso, p_vResultado, iRes )`                      | Puntero nulo.                  |
| `VerificarNoEsNulo ( p_cInfoCaso, p_vResultado, iRes )`                    | Puntero no nulo.               |
| `int LanzarEjecutable ( const char * p_cExe, const char * p_cParametros )` | Lanza un programa externo.     |

Los dos verificadores de reales comparan con
[`MatEsIgual`](../../gjs-c-common-calculation/doc/Epsilon.md), no con `==`, que
es lo correcto para coma flotante.

## La traza

Cada verificación escribe una línea por el
[log de la aplicación](../../gjs-c-common/doc/AplicacionLog.md):

```
    Caso: [suma]: Resultado: [5]
```

Y, si falla, una segunda en nivel de error con lo que se esperaba.

## Dependencias

[AplicacionLog](../../gjs-c-common/doc/AplicacionLog.md),
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md),
[Epsilon](../../gjs-c-common-calculation/doc/Epsilon.md) y
`SisEjecutarComando` de
[SistemaComandos](../../gjs-c-common-system/doc/Entorno.md).

## Test

`UtilesTestTest.c` → `TestUtilesTest()`.

## Observaciones

- **La traza recorta los valores largos.** Los verificadores escriben por
  `AplicLogAnotar` incluyendo el valor comprobado, así que un
  `VerificarValorLit` sobre una cadena que no quepa en la línea de log sale
  partido o truncado según el interruptor de partición de
  [SLog](../../gjs-c-common-log/doc/SLog.md). La comparación es exacta —eso no
  se toca—, pero lo que se lee en la traza puede no ser el valor entero.
- **`VerificarEsFalso` sólo rechaza el valor 1.** La comprobación es
  `if ( iResultado == 1 )`, de modo que un 2 o un -1 se dan por falsos. Su
  pareja `VerificarEsCierto` sí lo hace bien, con `if ( iResultado == 0 )`.
  Debería ser `!= 0`.
- **`VerificarEsNulo` y `VerificarNoEsNulo` imprimen un puntero con `%ld`.** El
  tipo no coincide, y aunque en Cygwin y Linux de 64 bits `long` y `void *`
  midan lo mismo, en Windows de 64 bits `long` son 4 bytes y la traza saldría
  truncada. El especificador de puntero es `%p`.
- **`VerificarValorLit` puede dar dos errores por un solo fallo**: comprueba
  primero la longitud y luego el contenido, sin cortar, así que una cadena
  distinta y de otro tamaño produce dos líneas de error.
- **Dos mensajes de error tienen el paréntesis sin cerrar**:
  `"(esperado [%s]"` y `"(esperado [1]"`.
- **No hay verificador de `unsigned`.** Con `VerificarValorEnteroLargo` un
  `unsigned long` grande se convierte a `long` y puede salir negativo en la
  traza y en la comparación.
- **Ni de bytes, ni de cadenas Unicode**, que sí contemplaba la versión C++ de
  [ControlTest](ControlTest.md).
- **`LanzarEjecutable` no encaja aquí.** No verifica nada: envuelve
  `SisEjecutarComando` con los mismos dos parámetros y `iSegundoPlano` a 0. Y
  arrastra el problema de aquella —la orden se pasa al intérprete sin escapar—.
- **Las funciones no llevan prefijo de módulo.** `VerificarValorEntero` y
  compañía son símbolos globales sin `Utl` ni nada que las sitúe, igual que
  [SimularEntradaConsola](../../gjs-c-common-support/doc/Pruebas.md). Como esta
  librería sólo se enlaza en ejecutables de prueba, el riesgo de colisión es
  menor.
