# SHora

| Dato         | Valor                                              |
| ------------ | -------------------------------------------------- |
| Cabecera     | `src/main/include/SHora.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SHora.c` (499 líneas) |
| Prefijo      | `SHor`                                             |
| Struct       | `SHora`                                            |
| Funciones    | 31                                                 |
| Incluido por | `Tiempo.h`                                         |
| Test         | `SHoraTest.c` → `TestSHora()`                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La hora del día como objeto, con la misma estructura que
[SFecha](SFecha.md): un formato empaquetado envuelto en una interfaz cómoda.

```c
typedef struct
{
    long lValor;      /* HHMMSS */
} SHora;
```

## API

Es **simétrica a la de [SFecha](SFecha.md)**, cambiando año/mes/día por
hora/minuto/segundo.

### Ciclo de vida

`SHorCrearDef`, `SHorCrear`, `SHorCrearLit`, `SHorDestruir`, `SHorEsValida`,
`SHorTieneValor`.

### Acceso

| Función                                | Descripción               |
| -------------------------------------- | ------------------------- |
| `int SHorHH ( SHora * )`               | Hora.                     |
| `int SHorMI ( SHora * )`               | Minutos.                  |
| `int SHorSS ( SHora * )`               | Segundos.                 |
| `long SHorHoraForm ( SHora * )`        | Hora en formato `HHMMSS`. |
| `SHorHora ( SHora * )`                 | La hora.                  |
| `SHorValor ( SHora * )`                | Valor interno.            |
| `double SHorValorNumerico ( SHora * )` | Valor continuo.           |

### Asignación

`SHorEstablecer`, `SHorEstablecerLit`, `SHorEstablecerValorDeAhora`.

### Comparación

Las mismas quince funciones que en [SFecha](SFecha.md):

| Operación  | Contra `SHora *`  | Contra texto         | Contra valor           |
| ---------- | ----------------- | -------------------- | ---------------------- |
| Igual      | `SHorEsIgual`     | `SHorEsIgualLit`     | `SHorEsIgualValor`     |
| Diferente  | `SHorEsDiferente` | `SHorEsDiferenteLit` | `SHorEsDiferenteValor` |
| Menor      | `SHorEsMenor`     | `SHorEsMenorLit`     | `SHorEsMenorValor`     |
| Mayor      | `SHorEsMayor`     | `SHorEsMayorLit`     | `SHorEsMayorValor`     |
| Diferencia | `SHorDiferencia`  | `SHorDiferenciaLit`  | `SHorDiferenciaValor`  |

```c
SHora * p_horObj = SHorCrearDef ();

SHorEstablecerValorDeAhora ( p_horObj );
printf ( "%02d:%02d:%02d\n", SHorHH ( p_horObj ),
         SHorMI ( p_horObj ), SHorSS ( p_horObj ) );
SHorDestruir ( &p_horObj );
```

## Dependencias

- [Horas](Horas.md) — la capa de valores.
- [TiempoSistema](TiempoSistema.md) — `SHorEstablecerValorDeAhora`.
- [gjs-c-common-text](../../gjs-c-common-text/README.md) — las variantes `Lit`.

## Test

`SHoraTest.c` → `TestSHora()`.

## Observaciones

- **Aquí el objeto aporta más que en [SFecha](SFecha.md)**, porque
  [Horas](Horas.md) **no tiene comparaciones**: las quince funciones de
  comparación de `SHora` no tienen equivalente en la capa de valores. Si hay que
  comparar horas, este es el módulo.
- Como [SFecha](SFecha.md), **no tiene aritmética**: para sumar o restar hay que
  bajar a `HorFormSumar` con el formato que devuelve `SHorHoraForm`.
- Los abreviados `HH`, `MI`, `SS` para hora, minuto y segundo son consistentes
  con [SReloj](Relojes.md), que usa los mismos, pero no con
  [Horas](Horas.md), donde los parámetros son `iH`, `iM`, `iS`.
- Tampoco documenta el formato de texto que aceptan las variantes `Lit`.
- No hay `SHorDuplicar`.
