# Horas

| Dato         | Valor                                 |
| ------------ | ------------------------------------- |
| Cabecera     | `src/main/include/Horas.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Horas.c` |
| Prefijo      | `Hor`                                 |
| Funciones    | 20                                    |
| Incluido por | `Tiempo.h`                            |
| Test         | `HorasTest.c` → `TestHoras()`         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La contrapartida de [Fechas](Fechas.md) para la hora del día: validación,
descomposición y aritmética sobre horas, minutos y segundos.

Sigue el mismo esquema de tres representaciones, con el formato empaquetado
`HHMMSS` como `long`.

## API

### Construcción y descomposición

| Función                                                                      | Descripción                 |
| ---------------------------------------------------------------------------- | --------------------------- |
| `long HorFormConstruir ( int iH, int iM, int iS )`                           | Componentes → formato.      |
| `void HorFormDescomponer ( long lHora, int * p_iH, int * p_iM, int * p_iS )` | Formato → componentes.      |
| `int HorFormHoras ( long lHora )`                                            | Hora del formato.           |
| `int HorFormMinutos ( long lHora )`                                          | Minutos.                    |
| `int HorFormSegundos ( long lHora )`                                         | Segundos.                   |
| `int HorEsValida ( int iH, int iM, int iS )`                                 | Validez de los componentes. |
| `int HorFormEsValida ( long lHora )`                                         | Validez del formato.        |

### Conversión a unidades

| Función                                         | Descripción         |
| ----------------------------------------------- | ------------------- |
| `int HorNumMinutos ( int iH, int iM, int iS )`  | Total de minutos.   |
| `int HorNumSegundos ( int iH, int iM, int iS )` | Total de segundos.  |
| `int HorFormNumMinutos ( long lHora )`          | Ídem sobre formato. |
| `int HorFormNumSegundos ( long lHora )`         | Ídem.               |

Útiles para convertir una hora del día en un escalar con el que operar
directamente.

### Aritmética

| Función                                                                        | Descripción         |
| ------------------------------------------------------------------------------ | ------------------- |
| `int HorSumar ( int * p_iH, int * p_iM, int * p_iS, int iH, int iM, int iS )`  | Suma, por puntero.  |
| `int HorRestar ( int * p_iH, int * p_iM, int * p_iS, int iH, int iM, int iS )` | Resta, por puntero. |
| `long HorFormSumar ( long lHora1, long lHora2 )`                               | Suma de formatos.   |
| `long HorFormRestar ( long lHora1, long lHora2 )`                              | Resta de formatos.  |

Misma asimetría que en [Fechas](Fechas.md): la familia de componentes modifica
por puntero, la de formato devuelve el resultado.

### Valor continuo

| Función                                             | Descripción          |
| --------------------------------------------------- | -------------------- |
| `int HorValEsValido ( double dValor )`              | Validez del valor.   |
| `double HorObtenerValor ( int iH, int iM, int iS )` | Componentes → valor. |
| `double HorFormObtenerValor ( long lHora )`         | Formato → valor.     |

```c
long lHora = HorFormConstruir ( 14, 30, 5 );      /* 143005 */

int iSegs = HorFormNumSegundos ( lHora );          /* 52205  */
long lMas = HorFormSumar ( lHora, 1500 );          /* +15 min */
```

## Dependencias

- `TiempoConfig.h`.
- [gjs-c-common-calculation](../../gjs-c-common-calculation/README.md).

## Test

`HorasTest.c` → `TestHoras()`.

## Observaciones

- **La API es notablemente más pobre que la de [Fechas](Fechas.md)**: 20
  funciones frente a 44. Faltan por completo las **comparaciones**
  (`HorEsIgual`, `HorEsMenor`, `HorEsMayor` y sus variantes `Form`), que en
  fechas son diez funciones. Para comparar horas hay que hacerlo sobre el `long`
  del formato, que ordena bien, o usar [SHora](SHora.md).
- Tampoco hay `HorEstablecerValor` ni `HorFormEstablecerValor`: la conversión al
  valor continuo es **de ida y no de vuelta**, mientras que en fechas sí existen
  las dos direcciones.
- `HorFormSumar` y `HorFormRestar` reciben dos horas en formato empaquetado, lo
  que significa sumar `HHMMSS` a `HHMMSS`. No hay variante que sume una cantidad
  de segundos o de minutos sueltos.
- La cabecera no aclara qué ocurre al **desbordar las 24 horas**: si el resultado
  se normaliza al día siguiente o se deja crecer. Con `HorFormEsValida` se puede
  comprobar después.
- No contempla los segundos intercalares, que sí modela
  [Calendario](Calendario.md): `HorEsValida` presumiblemente rechaza el segundo
  60.
