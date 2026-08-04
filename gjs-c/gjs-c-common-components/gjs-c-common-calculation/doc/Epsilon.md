# Epsilon

| Dato         | Valor                                    |
| ------------ | ---------------------------------------- |
| Cabecera     | `src/main/include/Epsilon.h` (13 líneas) |
| Fuente       | `src/main/c/org/gjs/c/common/Epsilon.c`  |
| Prefijo      | `Epsilon`                                |
| Funciones    | 1                                        |
| Incluido por | `Calculo.h`                              |
| Test         | `EpsilonTest.c` → `TestEpsilon()`        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Devuelve el **épsilon de la máquina**: el menor número que sumado a 1,0 da un
resultado distinto de 1,0 en la aritmética de coma flotante del equipo.

Es el suelo de precisión por debajo del cual comparar dos `double` no tiene
sentido, y el punto de partida para elegir la tolerancia de
[CalculoOperaciones](CalculoOperaciones.md).

## API

| Función             | Descripción                          |
| ------------------- | ------------------------------------ |
| `double Epsilon ()` | Épsilon de la máquina para `double`. |

Es el módulo más pequeño del stack C: una cabecera de 13 líneas con un único
prototipo.

```c
double dEps = Epsilon ();

if ( MatPresicion () < dEps )
{
    /* la tolerancia configurada está por debajo de lo que la máquina distingue */
}
```

## Dependencias

- `<float.h>` a través de `CalculoConfig.h`.

## Test

`EpsilonTest.c` → `TestEpsilon()`.

## Observaciones

- **El nombre no lleva prefijo de módulo.** Es la única función pública del stack
  C que se llama por su concepto a secas, sin las tres o cuatro letras de
  prefijo que usa todo lo demás (`Mat`, `Cad`, `Mem`…). `Epsilon` es un nombre
  muy genérico para un símbolo exportado por una biblioteca compartida: puede
  chocar con el del código cliente.
- Sólo cubre `double`. No hay `EpsilonReal` para `float`, pese a que la librería
  distingue en todas partes entre real y real doble.
- No está claro por qué es una función y no una constante: `DBL_EPSILON` de
  `<float.h>` da el mismo dato en tiempo de compilación. Calcularlo en ejecución
  sólo tiene sentido si se quiere medir el comportamiento real de la FPU en vez
  de creer lo que declara la cabecera del sistema.
