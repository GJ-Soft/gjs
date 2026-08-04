# SVersion

| Dato         | Valor                                    |
| ------------ | ---------------------------------------- |
| Cabecera     | `src/main/include/SVersion.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SVersion.c` |
| Prefijo      | `SVer`                                   |
| Struct       | `SVersion`                               |
| Funciones    | 20                                       |
| Incluido por | `Aplicacion.h`                           |
| Test         | `SVersionTest.c` → `TestSVersion()`      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La versión de un programa: tres números y una fecha.

```c
typedef struct
{
    int      iVersion;
    int      iSubversion;
    int      iRevision;
    SFecha * p_fecVersion;
} SVersion;
```

Es lo que guarda [AplicacionInformacion](Aplicacion.md) al inicializarse, y lo
que se imprime en la línea de presentación de un programa.

## API

### Construcción

| Función                                                                      | Descripción                                             |
| ---------------------------------------------------------------------------- | ------------------------------------------------------- |
| `SVersion * SVerCrearDef ()`                                                 | Versión 1.0.0 con la fecha por defecto.                 |
| `SVersion * SVerCrear ( iVersion, iSubversion, iRevision, lFecVersion )`     | Con la fecha como `AAAAMMDD`.                           |
| `SVersion * SVerCrearExt ( iVersion, iSubversion, iRevision, p_fecVersion )` | Con un [SFecha](../../gjs-c-common-time/doc/SFecha.md). |
| `void SVerDestruir ( SVersion ** )`                                          | Destrucción.                                            |
| `int SVerEsValida ( SVersion * )`                                            | Estado.                                                 |

`SVerCrear` valida antes de reservar: exige `iVersion > 0`, los otros dos ≥ 0 y
una fecha que pase `FecFormEsValida`. Si algo falla devuelve `NULL` sin dejar
nada reservado.

### Consulta

| Función                                               | Descripción                |
| ----------------------------------------------------- | -------------------------- |
| `SVerVersion` / `SVerSubversion` / `SVerRevision`     | Los tres números.          |
| `SFecha * SVerFecha ( SVersion * )`                   | La fecha, como objeto.     |
| `long SVerValorFecha ( SVersion * )`                  | La fecha, como `AAAAMMDD`. |
| `char * SVerCadenaVersion ( SVersion *, int iCorta )` | `"1.0.3"` o `"1.0"`.       |
| `char * SVerCadenaFecha ( SVersion * )`               | La fecha, como texto.      |
| `void SVerImprimir ( SVersion * )`                    | `Version: 1.0.3  Fecha: …` |

### Modificación

| Función                                                                      | Descripción      |
| ---------------------------------------------------------------------------- | ---------------- |
| `SVerEstablecerVersion` / `…Subversion` / `…Revision`                        | Uno a uno.       |
| `SVerEstablecerFecha ( SVersion *, SFecha * )`                               | Con objeto.      |
| `SVerEstablecerFechaEnteroLargo ( SVersion *, long )`                        | Con `AAAAMMDD`.  |
| `SVerEstablecer ( p_verObj, iVersion, iSubversion, iRevision, lFecha )`      | Todo de golpe.   |
| `SVerEstablecerExt ( p_verObj, iVersion, iSubversion, iRevision, p_fecObj )` | Idem con objeto. |

Los formatos salen de `AplicacionConfig.h`: `"%d.%d.%d"`, `"%d.%d"` y
`"Version: %d.%d.%d  Fecha: %s"`.

## Dependencias

[SFecha](../../gjs-c-common-time/doc/SFecha.md) y
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md).

## Test

`SVersionTest.c` → `TestSVersion()`.

## Observaciones

- **No se puede representar una versión 0.x.** `SVerCrear` exige
  `iVersion > 0`, así que `0.9.1` —la numeración habitual de lo que aún no ha
  llegado a la primera versión estable— no cabe. El propio stack se numera
  `1.0.0-RC.2`, de modo que el caso no se le presenta, pero la restricción es
  arbitraria.
- **Tampoco cabe una versión sin fecha.** `SVerCrear` exige una fecha válida,
  y no hay constructor que acepte sólo los tres números. `SVerCrearDef` rellena
  con la fecha por defecto de
  [SFecha](../../gjs-c-common-time/doc/SFecha.md), que no es la de hoy.
- **`SVerEsValida` no comprueba la revisión** mientras que `SVerCrear` sí. La
  asimetría no llega a romper nada —un objeto creado por el constructor ya tiene
  la revisión validada—, pero `SVerEstablecerRevision` puede dejarla negativa y
  el objeto seguirá dándose por válido.
- **La condición `iRevision >= 0` de `SVerCadenaVersion` está muerta.** Sirve
  para caer en el formato corto cuando no hay revisión, pero ningún camino deja
  la revisión negativa salvo el `SVerEstablecerRevision` anterior. En la
  práctica la forma corta sólo se obtiene pasando `iCorta`.
- **Duplica a [Versiones](../../gjs-c-common-base/doc/Versiones.md)** de
  `gjs-c-common-base`, que compone y compara cadenas de versión con los mismos
  cuatro niveles. Aquí es un objeto con fecha; allí, funciones sobre cadenas.
  No se usan entre sí.
- **No hay comparación.** Ni `SVerComparar`, ni `SVerEsAnterior`, ni
  `SVerEsCompatible`: se puede construir e imprimir una versión, no decidir si
  una es más nueva que otra, que es la operación por la que existen los números
  de versión. `SisLibVersion` de
  [SistemaLibrerias](../../gjs-c-common-system/doc/SistemaLibrerias.md) devuelve
  los cuatro números sueltos precisamente para eso, y no hay puente entre los dos
  módulos.
- **`SVerCadenaVersion` y `SVerCadenaFecha` devuelven memoria reservada** que el
  llamante debe liberar; `SVerFecha` devuelve el objeto interno, que no.
