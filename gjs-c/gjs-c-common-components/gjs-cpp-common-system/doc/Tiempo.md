# Tiempo

| Dato      | Valor                                                                          |
| --------- | ------------------------------------------------------------------------------ |
| Cabeceras | `SistemaTiempo.h` (52), `CTemporizador.h` (66), `CContadorCiclos.h` (68)       |
| Fuentes   | `SistemaTiempo.cpp` (85), `CTemporizador.cpp` (93), `CContadorCiclos.cpp` (99) |
| Espacio   | `org::gjs::cpp::common`                                                        |
| Declara   | 2 funciones + 8 métodos                                                        |
| Tests     | `SistemaTiempoTest.cpp`, `CTemporizadorTest.cpp`, `CContadorCiclosTest.cpp`    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Dos cosas distintas que comparten familia: **esperar** y **contar ciclos de
procesador**.

```cpp
SisEsperar ( 250 );                    // milisegundos

CContadorCiclos contador;
contador.Iniciar ();
// ... lo que se quiera medir ...
uint64_t ui64Ciclos = contador.Parar ();
```

No hay aquí nada de fechas ni de horas: eso es
[gjs-cpp-common-time](../../gjs-cpp-common-time/README.md), que es otro
componente. Éste sólo tiene lo que depende del sistema operativo.

## Las tres piezas

| Pieza             | Qué es                               | Debajo                  |
| ----------------- | ------------------------------------ | ----------------------- |
| `SisEsperar`      | Detener el hilo un rato              | `Sleep` / `sleep`       |
| `SisCiclosCPU`    | El contador de ciclos del procesador | `rdtsc`, en ensamblador |
| `CTemporizador`   | Una espera con el intervalo guardado | `SisEsperar`            |
| `CContadorCiclos` | Medir en ciclos entre dos puntos     | `SisCiclosCPU`          |

`CTemporizador` guarda un intervalo y lo reutiliza:

```cpp
CTemporizador temp ( 100 );
for ( int i = 0; i < 10; i++ ) { temp.Esperar (); }   // 100 ms cada vuelta
```

`CContadorCiclos` es un cronómetro en ciclos, con `Iniciar`, `Valor` —lo que
lleva sin parar—, `Parar` y `EstaContando`.

---

## Tests

Los tres son de coherencia: que esperar tarde algo, que el contador crezca, que
`EstaContando` diga la verdad antes y después de `Parar`.

---

## Observaciones

### `SisEsperar` no espera en POSIX

Es el defecto de peso del módulo:

```cpp
#  if ( defined ( WIN ) )
    Sleep ( (DWORD) iMiliSegs );
#  else
    if ( iMiliSegs > 500 )
    {
        sleep ( iMiliSegs / 1000 + 1 );
    }
    else
    {

    }
#  endif
```

En POSIX —**el modo de compilación por defecto**— la rama de menos de medio
segundo está **vacía**: no espera nada. Y la otra usa `sleep`, que trabaja en
segundos:

| Llamada               | Windows | POSIX    |
| --------------------- | ------- | -------- |
| `SisEsperar ( 100 )`  | 100 ms  | **0 ms** |
| `SisEsperar ( 500 )`  | 500 ms  | **0 ms** |
| `SisEsperar ( 600 )`  | 600 ms  | **1 s**  |
| `SisEsperar ( 1500 )` | 1,5 s   | **2 s**  |
| `SisEsperar ( 2000 )` | 2 s     | **3 s**  |

O sea: por debajo de 500 ms no hace nada, y por encima redondea **hacia arriba
al segundo siguiente**, siempre de más. `CTemporizador` delega en ella, así que
arrastra lo mismo.

Debajo, comentadas, están las tres líneas que lo resolvían con `select` y un
`timeval`. Hoy la respuesta es una línea:
`std::this_thread::sleep_for ( std::chrono::milliseconds ( iMiliSegs ) )`, que
además es portable y quitaría las dos ramas.

**Ningún test lo detecta**, porque comprueban que la espera tarde «algo», no
cuánto.

### `SisCiclosCPU`

- **Es ensamblador x86 en línea.** `cpuid` seguido de `rdtsc`, con `%rbx` y
  `%rcx` en la lista de registros machacados — nombres de 64 bits, así que la
  función **no compila en x86 de 32 bits** ni en ninguna otra arquitectura.
- **`cpuid` antes de `rdtsc`** es la receta clásica para impedir que el
  procesador reordene la lectura, y está bien puesta. El precio es que `cpuid`
  es una instrucción cara y serializante: medir algo muy corto mide sobre todo
  el `cpuid`.
- **El contador de ciclos no es un reloj.** Con frecuencia variable y varios
  núcleos, dos lecturas seguidas pueden venir de núcleos distintos y dar una
  diferencia negativa. Los procesadores modernos tienen TSC invariante, que lo
  mitiga; nada de esto está dicho en la cabecera, y `CContadorCiclos` presenta el
  valor como si fuera una medida fiable.
- **No hay conversión a tiempo.** Para pasar de ciclos a segundos hace falta la
  frecuencia, que está en `SisVelocidadCPU` de
  [SistemaInformacion](Informacion.md) — otro módulo, y sin unidades declaradas.

### Las clases

- **La cabecera de `CContadorCiclos` describe a `CTemporizador`.** Palabra por
  palabra: *«implementa un temporizador basado en las primitivas de temporización
  del sistema operativo»*. Es un copiar y pegar: la clase cuenta ciclos de
  procesador, que no es temporizar.
- **`CTemporizador` no aporta casi nada sobre `SisEsperar`**: guarda un `int` y
  lo pasa. Su valor está en poder cambiar el intervalo en un sitio; su coste, una
  clase más en la fachada.
- **`Valor()` y `Parar()` devuelven lo mismo si ya se paró**, y la cabecera no
  dice qué pasa si se llama a `Parar` dos veces, ni a `Valor` sin haber
  iniciado.
- **`EstIntervalo` en vez de `setIntervalo`**, como el resto de las clases de
  este componente. Ver [MODULOS](MODULOS.md#las-cuatro-clases).
