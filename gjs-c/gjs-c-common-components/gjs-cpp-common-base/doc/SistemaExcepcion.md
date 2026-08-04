# SistemaExcepcion

| Dato      | Valor                                                  |
| --------- | ------------------------------------------------------ |
| Cabecera  | `src/main/include/SistemaExcepcion.h`                  |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/SistemaExcepcion.cpp` |
| Espacio   | `org::gjs::cpp::common`                                |
| Deriva de | [`Excepcion`](Excepcion.md)                            |
| Test      | **Ninguno**                                            |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Convertir un **`errno` en una excepción con texto legible**. Es el puente entre
las llamadas al sistema, que informan con un número, y el manejo de errores del
stack C++, que es por excepción.

```cpp
class SistemaExcepcion : public Excepcion
{
public:
    SistemaExcepcion ( const std::string & sModulo, const std::string & sRutina, int iErrno );
};
```

El constructor traduce el número con `strerror` y se lo pasa a la base:

```cpp
if ( open ( sRuta.c_str (), O_RDONLY ) == -1 )
{
    throw SistemaExcepcion ( "Ficheros", "Leer", errno );
}
```

```
[Ficheros::Leer] No such file or directory
```

Es el equivalente C++ de
[SistemaErrores](../../gjs-c-common-system/doc/SistemaErrores.md) del stack C,
con la diferencia de que allí hay que consultar el error y aquí llega solo.

## Dependencias

[Excepcion](Excepcion.md) y `<cstring>` para `strerror`.

## Test

**Ninguno.**

## Observaciones

- **El mensaje sale en inglés.** `strerror` devuelve el texto del sistema, que
  en una máquina con la configuración regional por defecto es
  *"No such file or directory"*, mientras que el resto de mensajes del stack
  están en castellano. Una excepción de este componente puede llevar las dos
  lenguas en la misma línea.
- **No guarda el `errno`.** Igual que sus dos hermanas, lo convierte a texto y
  lo pierde: quien capture no puede distinguir `ENOENT` de `EACCES` sin
  comparar cadenas. Un `getErrno()` con el `int` guardado costaría una línea y
  es lo que hace falta para reaccionar según el error.
- **`strerror` no es reentrante.** Puede devolver un puntero a un búfer estático
  compartido; en un programa con hilos, dos excepciones simultáneas pueden
  pisarse el texto. La versión segura es `strerror_r`, con la complicación de
  que su firma difiere entre POSIX y GNU.
- **No valida el `errno` recibido.** Con un valor fuera de rango `strerror`
  devuelve algo como *"Unknown error 999"*, que es aceptable, pero tampoco hay
  nada que impida construir la excepción con 0 —es decir, "no ha habido
  error"—.
- **Sin test.**
