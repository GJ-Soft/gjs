# Cajas de mensaje

| Dato      | Valor                                                  |
| --------- | ------------------------------------------------------ |
| Cabeceras | `CajaMensajes.h` (63), `TiposCajaMensajes.h` (97)      |
| Fuentes   | `CajaMensajes.cpp` (166), `TiposCajaMensajes.cpp` (71) |
| Espacio   | `org::gjs::cpp::common`                                |
| Prefijos  | `CajMsj`, `TipCajMsj`                                  |
| Declara   | 3 + 2                                                  |
| Tests     | `CajaMensajesTest.cpp`, `TiposCajaMensajesTest.cpp`    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Preguntar algo al usuario y recoger la respuesta, **con la misma llamada en
Windows y en consola**.

```cpp
RespuestaCajaMensajes resp = CajMsjMostrar ( TipoCajaMensajes::PreguntaSiNoCan,
                                             "Salir",
                                             "¿Guardar los cambios?" );
if ( resp == RespuestaCajaMensajes::Aceptar ) { ... }

CajMsjMostrarConFormato ( TipoCajaMensajes::Error, "Fallo",
                          "No se pudo abrir {} ( codigo {} )", sFichero, iErr );
```

## Los dos catálogos

`TiposCajaMensajes.h` define **dos `enum class`**, que es lo que distingue a este
módulo del resto del stack:

### El tipo de caja

Trece valores, combinando el icono con los botones:

| Icono       | Sólo Aceptar  | Aceptar/Cancelar | Reintentar/Cancelar | Abortar/Reintentar/Ignorar | Sí/No/Cancelar    |
| ----------- | ------------- | ---------------- | ------------------- | -------------------------- | ----------------- |
| Información | `Informacion` | —                | —                   | —                          | —                 |
| Pregunta    | `Pregunta`    | `PreguntaOkCan`  | `PreguntaReinCan`   | —                          | `PreguntaSiNoCan` |
| Aviso       | `Aviso`       | `AvisoOkCan`     | `AvisoReinCan`      | `AvisoAbrReinIgn`          | —                 |
| Error       | `Error`       | `ErrorOkCan`     | `ErrorReinCan`      | `ErrorAbrReinIgn`          | —                 |

### La respuesta

```cpp
enum class RespuestaCajaMensajes
{
    Ninguna = 0,    // no mostrada / tipo invalido
    Aceptar,        // OK / Si
    Cancelar,
    Reintentar,
    No,
    Abortar,
    Ignorar
};
```

Los comentarios de la cabecera documentan lo importante: `Ninguna` es el caso de
error, y **en consola POSIX la respuesta siempre es `Aceptar`**, porque el
diálogo es bloqueante hasta el retorno y no hay botones.

Los valores del `enum class` de tipos **coinciden con los `#define
TIP_CAJ_MSJ_*` antiguos**, que se conservan encima en el mismo fichero por
compatibilidad, y hay un comentario que lo dice. `TipCajMsjEsValido` está
sobrecargado para los dos: el `int` viejo y el enumerado nuevo.

## Cómo se pinta

| Plataforma | Qué hace                                                                          |
| ---------- | --------------------------------------------------------------------------------- |
| Windows    | `MessageBox`, con los indicadores derivados del tipo                              |
| POSIX      | **Dibuja un recuadro en la consola** con caracteres de línea, y espera al retorno |

La versión de consola es un rectángulo con esquinas, una línea separadora entre
el título y el mensaje, y salida por `cout`. Es la misma familia de dibujo que
[AplicacionConsola](Consola.md).

## La variante con formato

```cpp
template<typename... Args>
RespuestaCajaMensajes CajMsjMostrarConFormato ( TipoCajaMensajes tipo, const std::string & sTitulo,
                                                const std::string & sFormato, Args&&... argumentos )
{
    return ( CajMsjMostrar ( tipo, sTitulo,
             std::vformat ( sFormato, std::make_format_args ( argumentos... ) ) ) );
}
```

**Definida en la cabecera**, con el comentario que explica por qué. Ver
[Consola](Consola.md) para el contraste con
[gjs-cpp-common-log](../../gjs-cpp-common-log/doc/Log.md#las-plantillas-no-funcionan).

---

## Tests

`TiposCajaMensajesTest.cpp` prueba las dos sobrecargas de `TipCajMsjEsValido` y
la correspondencia entre los enumerados y las macros antiguas.
`CajaMensajesTest.cpp` —189 líneas— prueba la caja en consola, que es la que se
puede probar sin que aparezca una ventana.

---

## Observaciones

### Lo que está bien

- **Es el único catálogo del stack con `enum class`.** Todos los demás
  —`TiposSistema`, `Procesadores`, `SistemaSignals`, `CodigosIETF`— son macros o
  constantes sueltas, con lo que un `int` de una familia se puede pasar donde se
  espera otra. Aquí el compilador lo impide.
- **La compatibilidad está resuelta sin duplicar.** Los `#define` viejos siguen
  ahí y los valores del enumerado se definen **a partir de ellos**, de modo que no
  pueden desincronizarse.
- **El enumerado de respuesta documenta su propio caso degradado**, que es lo que
  hace usable la API en las dos plataformas.

### Lo que no

- **`Ninguna` mezcla dos situaciones**: «no se mostró» y «el tipo era inválido».
  Son fallos distintos —uno del entorno y otro del programador— y dan la misma
  respuesta.
- **En consola, la respuesta no depende del tipo.** Una `PreguntaSiNoCan` y una
  `Informacion` devuelven las dos `Aceptar`, así que **el código que decida según
  la respuesta no funciona fuera de Windows**. Está documentado en la cabecera, y
  es una limitación de fondo: la caja de consola pinta los botones que
  correspondan pero no los lee. Leer un carácter y traducirlo sería la mitad del
  problema resuelto.
- **`std::vformat` lanza si el formato no concuerda** con los argumentos, y la
  plantilla no lo captura: un mensaje de error mal escrito tumba el programa
  justo cuando iba a avisar de otro error. Es el peor momento posible para esa
  excepción.
- **No hay caja de entrada de texto**, sólo de botones. Para pedir una cadena hay
  que ir a `AplicConLeerCadena` de [AplicacionConsola](Consola.md), que es de
  consola y no tiene equivalente en ventana.
- **Trece tipos y una cuadrícula con huecos**: no hay `InformacionOkCan`, ni
  `PreguntaAbrReinIgn`, ni `AvisoSiNoCan`. Las combinaciones que faltan no son un
  descuido —son las que Windows no ofrece con ese icono— y la cabecera no lo
  dice, así que parece arbitrario.
- **Cinco caracteres perdidos** (`U+FFFD`) en `TiposCajaMensajes.h` y siete en
  `CajaMensajes.h`.
