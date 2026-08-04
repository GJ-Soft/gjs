# FormatoCadena

| Dato         | Valor                                         |
| ------------ | --------------------------------------------- |
| Cabecera     | `src/main/include/FormatoCadena.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/FormatoCadena.c` |
| Prefijo      | `Frm`                                         |
| Incluido por | `Base.h`                                      |
| Test         | `FormatoCadenaTest.c` → `TestFormatoCadena()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Generar cadenas formateadas a partir de un formato tipo `printf` y una lista
variable de argumentos, pero con dos garantías que `vsprintf` no da: **nunca se
escribe más allá del tamaño indicado** y **un puntero de cadena inválido no
revienta**, sino que se sustituye por un texto marcador.

Es la rutina sobre la que se apoya `ErrEstablecerConFormato`
([Errores](Errores.md)).

## API

| Función                                                                                           | Descripción                                                 |
| ------------------------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| `int FrmCadena ( char * p_cCadena, const char * p_cFormato, va_list valArgumentos, int iMaxTam )` | Formatea sobre `p_cCadena`. Devuelve 1 (éxito) o 0 (fallo). |

La rutina recibe una `va_list` ya abierta: el llamante hace `va_start` /
`va_end`. El destino `p_cCadena` lo aporta el llamante, normalmente con
`CadCrear`.

```c
static void Trazar ( const char * p_cFormato, ... )
{
    va_list  valArgs;
    char *   p_cMsj = CadCrear ( 255 );

    if ( ES_VALIDO ( p_cMsj ) )
    {
        va_start ( valArgs, p_cFormato );
        if ( FrmCadena ( p_cMsj, p_cFormato, valArgs, 255 ) == 1 )
        {
            CadImprimir ( p_cMsj );
        }
        va_end ( valArgs );
        MemLiberar ( (void **) &p_cMsj );
    }
}
```

## Formato admitido

Códigos reconocidos (constante interna `_FRM_CODIGOS`):

```
d i o x X u c s S f e E g G p n
```

| Elemento                         | Soporte                                                           |
| -------------------------------- | ----------------------------------------------------------------- |
| Anchura numérica (`%10d`)        | Sí                                                                |
| Anchura por argumento (`%*d`)    | Sí                                                                |
| Precisión (`%.3f`)               | Sí                                                                |
| Precisión por argumento (`%.*f`) | Sí                                                                |
| Modificador `l` (`%ld`)          | Sí, sólo con `d`, `f` y `u`                                       |
| `%%` literal                     | Sí                                                                |
| Bloque `(...)`                   | Reservado para una codificación de tipos que no está implementada |

## Comportamiento

La implementación es un autómata de nueve estados que recorre el formato
carácter a carácter, reconstruye cada especificador en un buffer intermedio
(`p_cFrmProc`), llama a `sprintf` con ese especificador aislado y un solo
argumento, y vuelca el resultado en el destino comprobando el límite.

Puntos relevantes:

- **El límite `iMaxTam` se respeta siempre**: el bucle de volcado corta en cuanto
  `iPosCad` lo alcanza. Se rellena hasta donde quepa.
- **Cadenas (`%s`, `%S`)**: el argumento pasa por `_EsCadenaValida`, que rechaza
  el puntero nulo y las cadenas con caracteres de control no imprimibles (código
  127, o menor de 32 fuera del rango 8-13), y también las que no terminan antes
  de `CAD_BASE_MAX_TAM`. Si la validación falla se escribe `"(nul)"`
  (`CAD_BASE_TXT_VALOR_NULO`). Si el resultado sería demasiado largo se escribe
  `"(max)"` (`CAD_BASE_TXT_DEMASIADO_LARGO`).
- **Enteros y caracteres** (`d i o x X u c`): se leen como `int`, o como `long`
  si venía el modificador `l`.
- **Reales** (`f g e E G`): se leen siempre como `double`.
- **Punteros** (`p`): se leen como `void *`.
- Tras formatear un número, el módulo hace un ajuste propio de anchura y
  precisión localizando el punto decimal en el resultado, para recortar la parte
  fraccionaria a lo pedido.
- Los cuatro buffers de trabajo se inicializan a `NULL` antes del guarda de
  entrada precisamente para que los `MemLiberar` finales sean seguros aunque el
  guarda falle.

### Casos que devuelven 0

- Cualquier parámetro nulo o `iMaxTam <= 0` (además anota `ERR_PARAMETROS`).
- Fallo al reservar alguno de los buffers internos.
- Modificador `l` repetido, o aplicado a un código distinto de `d`, `f` o `u`.
- Código de tipo no soportado.
- Especificador cuya anchura estimada supere `CAD_BASE_MAX_TAM`.
- Formato no consumido por completo.

Cuando devuelve 0 el contenido de `p_cCadena` es indeterminado (puede tener
escrito el prefijo procesado hasta el punto del fallo).

## Dependencias

- [Memoria](Memoria.md) — buffers de trabajo.
- [CadenasBase](CadenasBase.md) — `CadCrear`, `CadLongitud`, `CadInicializar`.
- [Errores](Errores.md) — `ERROR_ESTABLECER`.

## Test

`FormatoCadenaTest.c` → `TestFormatoCadena()`. Es el segundo test del arnés.

## Observaciones

- El fichero `FormatoCadena.c` está codificado en **cp1252**, no en UTF-8 como el
  resto del repositorio (se aprecia en los comentarios de cabecera). Es
  intencionado; conviene no "arreglarlo" sin comprobar el resto de la cadena de
  compilación.
- Internamente se usa `sprintf` sin límite sobre `p_cBuffer`
  (`CAD_BASE_MAX_TAM + 1` bytes). La protección es la estimación previa de
  anchura (`iMaxAncho`), no el propio `sprintf`; para `%s` la estimación real
  está comentada en el código (bloque marcado `FALTA:`) y sustituida por un
  margen fijo de 64 caracteres en el caso general.
- El bloque `(...)` que captura el estado 7 recoge una "codificación" que después
  se descarta: el código que la aplicaría está comentado.
- El código `n` figura en `_FRM_CODIGOS` pero no tiene caso en el `switch` de
  tipos, así que cae en el `default` y devuelve 0. Es lo deseable por seguridad,
  pero significa que `%n` se comporta como un error de formato, no como el `%n`
  de C.
- `CadLongitud ( p_cFormato )` se recalcula en cada vuelta del bucle principal,
  lo que hace el recorrido cuadrático respecto a la longitud del formato.
