# Cronometro

| Dato     | Valor                                       |
| -------- | ------------------------------------------- |
| Cabecera | `src/main/include/Cronometro.h` (66 líneas) |
| Fuente   | `Cronometro.cpp`                            |
| Espacio  | `org::gjs::cpp::common`                     |
| Test     | `CronometroTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Medir cuánto tarda algo.

```cpp
class Cronometro
{
private:
    std::chrono::system_clock::time_point * p_tpTiempoIni;

public:
    Cronometro ();
    ~Cronometro ();

    void      Iniciar ();
    long long Parar ();
    long long Computo ();
};
```

Tres métodos: arrancar, parar —que devuelve lo transcurrido— y `Computo()`, que
lo consulta sin detener la cuenta.

```cpp
Cronometro cro;

cro.Iniciar ();
ProcesarFichero ( sRuta );
long long llTardado = cro.Parar ();
```

Es la contraparte de [SContadorCiclos](../../gjs-c-common-system/doc/Tiempo.md)
del stack C, con la diferencia de que aquél cuenta ciclos de CPU con `rdtsc` y
éste mide tiempo de reloj.

## Dependencias

`<chrono>`.

## Test

`CronometroTest.cpp` → `TestCronometro()`.

## Observaciones

- **El `time_point` se guarda por puntero, con reserva dinámica.** Son 8 o 16
  bytes que caben de sobra en el objeto:

  ```cpp
  std::chrono::system_clock::time_point * p_tpTiempoIni;
  ```

  Guardarlo por valor quitaría el `new`, el `delete` y la posibilidad de que el
  puntero esté nulo. Con puntero, además, la clase necesita constructor de copia
  y asignación —no declarados—, de modo que copiar un `Cronometro` deja dos
  objetos apuntando al mismo instante y dos destructores liberándolo.

  El campo se puede declarar `std::chrono::system_clock::time_point tpTiempoIni;`
  y desaparece todo el problema.
- **Usa `system_clock`, que no es monótono.** Es el reloj de pared: si alguien
  cambia la hora del sistema —o la ajusta el servicio de sincronización— en medio
  de una medición, el resultado sale desplazado, y puede salir **negativo**. Para
  medir duraciones, `std::chrono::steady_clock` es el que garantiza que nunca
  retrocede, y es lo que la biblioteca estándar recomienda expresamente para
  esto.

  `system_clock` es el correcto para [FechaHora](FechaHora.md), que representa un
  instante del calendario; aquí no.
- **No se dice en qué unidad devuelve.** `Parar()` y `Computo()` devuelven
  `long long` sin más: milisegundos, microsegundos o nanosegundos, hay que
  averiguarlo leyendo el fuente. `std::chrono` está hecho justamente para que la
  unidad viaje en el tipo —`std::chrono::milliseconds`— y aquí se pierde en la
  frontera.
- **Ni `EstaContando()` ni reinicio.** No se puede preguntar si está en marcha, y
  `Parar()` sobre un cronómetro que no se inició no tiene contrato: con el puntero
  a nulo, lo previsible es que caiga.
- **No es una guarda RAII.** El destructor libera el puntero y no informa de nada;
  un `Cronometro` que midiera al salir de ámbito —y lo anotara— es lo que se
  querría para instrumentar una función.
