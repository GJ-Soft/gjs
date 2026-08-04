# SFecha

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/SFecha.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SFecha.c` (509 líneas) |
| Prefijo      | `SFec`                                              |
| Struct       | `SFecha`                                            |
| Funciones    | 31                                                  |
| Incluido por | `Tiempo.h`                                          |
| Test         | `SFechaTest.c` → `TestSFecha()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La fecha como **objeto**. Envuelve el formato empaquetado de
[Fechas](Fechas.md) y añade ciclo de vida, construcción desde texto y
comparación con las tres representaciones.

```c
typedef struct
{
    long lValor;      /* AAAAMMDD */
} SFecha;
```

Un solo campo: el objeto no aporta almacenamiento nuevo, sino una interfaz más
cómoda y con menos posibilidades de equivocarse que las 44 funciones sueltas de
`Fechas`.

## API

### Ciclo de vida

| Función                           | Descripción                  |
| --------------------------------- | ---------------------------- |
| `SFecha * SFecCrearDef ()`        | Fecha sin valor.             |
| `SFecha * SFecCrear ( … )`        | Fecha desde componentes.     |
| `SFecha * SFecCrearLit ( … )`     | Fecha desde texto.           |
| `void SFecDestruir ( SFecha ** )` | Destruye y anula el puntero. |
| `int SFecEsValida ( SFecha * )`   | 1 si es utilizable.          |
| `int SFecTieneValor ( SFecha * )` | 1 si tiene fecha asignada.   |

La distinción entre `EsValida` y `TieneValor` permite representar el "sin fecha"
sin recurrir a valores centinela.

### Acceso

| Función                                 | Descripción                  |
| --------------------------------------- | ---------------------------- |
| `int SFecAAAA ( SFecha * )`             | Año.                         |
| `int SFecMM ( SFecha * )`               | Mes.                         |
| `int SFecDD ( SFecha * )`               | Día.                         |
| `long SFecFechaForm ( SFecha * )`       | Fecha en formato `AAAAMMDD`. |
| `SFecFecha ( SFecha * )`                | La fecha.                    |
| `SFecValor ( SFecha * )`                | Valor interno.               |
| `double SFecValorNumerico ( SFecha * )` | Valor continuo.              |

### Asignación

| Función                                     | Descripción                |
| ------------------------------------------- | -------------------------- |
| `int SFecEstablecer ( … )`                  | Fija la fecha.             |
| `int SFecEstablecerLit ( … )`               | Fija la fecha desde texto. |
| `int SFecEstablecerValorDeHoy ( SFecha * )` | Toma la fecha del sistema. |

### Comparación

Cinco operaciones por tres tipos de argumento, quince funciones:

| Operación  | Contra `SFecha *` | Contra texto         | Contra valor           |
| ---------- | ----------------- | -------------------- | ---------------------- |
| Igual      | `SFecEsIgual`     | `SFecEsIgualLit`     | `SFecEsIgualValor`     |
| Diferente  | `SFecEsDiferente` | `SFecEsDiferenteLit` | `SFecEsDiferenteValor` |
| Menor      | `SFecEsMenor`     | `SFecEsMenorLit`     | `SFecEsMenorValor`     |
| Mayor      | `SFecEsMayor`     | `SFecEsMayorLit`     | `SFecEsMayorValor`     |
| Diferencia | `SFecDiferencia`  | `SFecDiferenciaLit`  | `SFecDiferenciaValor`  |

```c
SFecha * p_fecObj = SFecCrearDef ();

SFecEstablecerValorDeHoy ( p_fecObj );
if ( SFecEsMayorLit ( p_fecObj, "01/01/2026" ) == 1 )
{
    printf ( "%04d-%02d-%02d\n", SFecAAAA ( p_fecObj ),
             SFecMM ( p_fecObj ), SFecDD ( p_fecObj ) );
}
SFecDestruir ( &p_fecObj );
```

## Dependencias

- [Fechas](Fechas.md) — toda la aritmética.
- [TiempoSistema](TiempoSistema.md) — `SFecEstablecerValorDeHoy`.
- [gjs-c-common-text](../../gjs-c-common-text/README.md) — las variantes `Lit`.

## Test

`SFechaTest.c` → `TestSFecha()`.

## Observaciones

- **No tiene aritmética.** No hay `SFecSumarDias` ni equivalente: para desplazar
  una fecha hay que sacar el formato con `SFecFechaForm`, usar
  `FecFormSumarDias` de [Fechas](Fechas.md) y volver a asignar. Es la carencia
  más notable frente a la capa de valores.
- El objeto ofrece `SFecEsDiferente`, que [Fechas](Fechas.md) no tiene, pero le
  faltan `EsMenorIgual` y `EsMayorIgual`, que la capa de valores sí ofrece. Las
  dos APIs no se cubren la una a la otra.
- `SFecCrearLit` y las variantes `Lit` **no documentan qué formato de texto
  aceptan**. Los candidatos son `FEC_FORMATO_FECHA_DEF` (`%02d/%02d/%04d`) y
  `FEC_FORMATO_FECHA_NUM` (`%04d%02d%02d`), pero esas constantes están en
  `TiempoConfig.h`, que no se publica.
- `SFecFecha` y `SFecValor` no declaran tipo de retorno en la lista de la
  cabecera; hay que mirar el fuente para saber si devuelven `long` o el objeto.
- No hay `SFecDuplicar`, presente en casi todos los objetos del stack.
