# FinExcepcion

| Dato      | Valor                                              |
| --------- | -------------------------------------------------- |
| Cabecera  | `src/main/include/FinExcepcion.h`                  |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/FinExcepcion.cpp` |
| Espacio   | `org::gjs::cpp::common`                            |
| Deriva de | [`Excepcion`](Excepcion.md)                        |
| Test      | **Ninguno**                                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Convertir una **llamada a `exit()` en una excepción**, para que un proceso que
iba a terminar de golpe pueda desenrollar la pila y dar a los destructores la
oportunidad de correr.

```cpp
class FinExcepcion : public Excepcion
{
public:
    FinExcepcion ( const std::string & sModulo, const std::string & sRutina, int iCodigo );
};
```

Un solo constructor, que compone el mensaje con el código de salida:

```
[MiModulo::MiRutina] Se ha llamado exit() con codigo: 1
```

Es la pieza que le falta al stack C, donde
[`FinalizarEjecucion`](../../gjs-c-common-base/doc/Finalizacion.md) llama a
`exit()` directamente y no hay forma de interceptarlo. Aquí sí: quien capture
`FinExcepcion` decide si de verdad se termina.

Enlaza con el problema que el marco de pruebas tiene anotado en
[ControlTest](../../gjs-c-common-test/doc/ControlTest.md): distinguir un proceso
que ha terminado su trabajo de uno que se ha ido por un `exit()` no controlado.

## Dependencias

[Excepcion](Excepcion.md), `Concatenar` y `ToString`.

## Test

**Ninguno.** Es una de las tres excepciones derivadas sin suite propia.

## Observaciones

- **No guarda el código de salida.** Lo mete en el texto del mensaje y lo pierde
  como dato: quien capture la excepción para propagar ese mismo código a
  `main` tiene que volver a extraerlo del mensaje. Un `getCodigo()` con el
  `int` guardado sería lo natural, y es lo que distingue a esta clase de su
  hermana [SistemaExcepcion](SistemaExcepcion.md), que sí tiene el mismo
  problema con el `errno`.
- **Nadie la lanza dentro del componente.** No hay un envoltorio de `exit()` que
  la produzca, así que hoy es una clase que el código de usuario tendría que
  lanzar por su cuenta. Para que cumpliera su propósito haría falta la pieza que
  la lanza.
- **Sin test.** Las tres derivadas de `Excepcion` comparten la carencia; la
  base sí tiene el suyo.
- El texto está fijado en un `#define MENSAJE_EXCEPCION` dentro del `.cpp`, no en
  `BaseConfig.h` como el resto de literales del componente.
