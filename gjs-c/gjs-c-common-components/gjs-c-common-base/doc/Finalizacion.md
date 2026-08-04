# Finalizacion

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/Finalizacion.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Finalizacion.c` |
| Prefijo      | — (`FinalizarEjecucion`)                     |
| Incluido por | `Base.h`                                     |
| Test         | — (sin test asociado)                        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Terminación forzada del programa ante un error del que no se puede volver. Es la
última salida de la librería: se invoca cuando continuar la ejecución no tiene
sentido porque el propio entorno de ejecución está comprometido.

En la práctica sólo lo usa [Memoria](Memoria.md), cuando `HeapValidate` detecta
que el *heap* del proceso está corrupto.

## API

| Función                                               | Descripción                                          |
| ----------------------------------------------------- | ---------------------------------------------------- |
| `void FinalizarEjecucion ( const char * p_cMensaje )` | Muestra el mensaje y termina el proceso. No retorna. |

## Comportamiento

El comportamiento es **el mismo en todos los modos de compilación**, sin ramas
condicionales:

1. Si `p_cMensaje` es nulo se sustituye por `ERR_GRAVE_TXT_DEFECTO`
   (`"La aplicacion no puede continuar."`).
2. El mensaje se escribe en **`stderr`**, para no mezclarlo con la salida normal
   del programa.
3. Se vacían todos los bufferes con `fflush ( NULL )`.
4. Se termina con `exit ( ERR_GRAVE_COD_SALIDA )`, es decir, **código de salida 1**.

No se usa `FatalAppExit` en Windows: abre un cuadro de diálogo modal —que
colgaría una tanda de tests desatendida— y además no permite elegir el código de
salida (su primer parámetro está documentado como reservado y debe valer cero).

## Dependencias

- [Memoria](Memoria.md) — sólo por el macro `ES_NULO`.
- `<stdlib.h>` — `exit`.

El mensaje por defecto es la constante interna `ERR_GRAVE_TXT_DEFECTO`, definida
en el propio `.c`.

## Test

No hay, y difícilmente puede haberlo en el arnés actual: la función termina el
proceso, así que un caso de prueba tendría que ejecutarse en un proceso aparte y
comprobar el código de salida.

## Observaciones

- El fuente incluye `<stdlib.h>` explícitamente: `BaseConfig.h` no lo arrastra en
  las compilaciones para `WIN`, y ahí es donde vive `exit`.
- `exit` ejecuta los manejadores registrados con `atexit` y vacía los flujos.
  Como la llamada suele venir de un *heap* corrupto, si eso llegara a dar
  problemas la alternativa sería `_Exit`, que termina sin tocar nada más.
- La función no está marcada como no-retornante (`_Noreturn` / `__attribute__((noreturn))`),
  así que el compilador no puede aprovechar esa información ni avisar de código
  inalcanzable tras la llamada.
