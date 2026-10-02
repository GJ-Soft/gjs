# SRuta

| Dato         | Valor                                                |
| ------------ | ---------------------------------------------------- |
| Cabecera     | `src/main/include/SRuta.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/SRuta.c` (1.261 líneas) |
| Prefijo      | `SRut`                                               |
| Struct       | `SRuta`                                              |
| Funciones    | 59                                                   |
| Incluido por | `Ficheros.h`                                         |
| Test         | `SRutaTest.c` → `TestSRuta()`                        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una ruta como **objeto con dos partes**: directorio y fichero.

```c
typedef struct
{
    SCadena * p_cadDirectorio;
    SCadena * p_cadFichero;
} SRuta;
```

Guardar las dos partes por separado es lo que evita la aritmética de cadenas
—buscar la última barra, cuidar el separador según el sistema— que es la fuente
habitual de errores al manejar rutas.

## API

### Construcción

| Función                        | Descripción                     |
| ------------------------------ | ------------------------------- |
| `SRutCrearDirectorio ( … )`    | Ruta que es sólo un directorio. |
| `SRutCrearDirectorioActual ()` | El directorio de trabajo.       |
| `SRutCrearDirectorioLit ( … )` | Ídem desde literal.             |
| `SRutCrearFichero ( … )`       | Ruta a un fichero.              |
| `SRutCrearFicheroLit ( … )`    | Ídem desde literal.             |

Más `SRutDestruir` y `SRutEsValida`.

### Acceso

| Función                                    | Devuelve                    |
| ------------------------------------------ | --------------------------- |
| `SRutDirectorio` / `SRutDirectorioLit`     | La parte de directorio      |
| `SRutFichero` / `SRutFicheroLit`           | El nombre del fichero       |
| `SRutFicheroSinExtension` / `…Lit`         | El nombre sin extensión     |
| `SRutRuta` / `SRutRutaLit`                 | La ruta completa            |
| `SRutRutaAbsoluta` / `SRutRutaAbsolutaLit` | La ruta resuelta a absoluta |

El sufijo `Lit` devuelve `const char *` en lugar de
[SCadena](../../gjs-c-common-text/doc/SCadena.md).

### Asignación

Nueve funciones `SRutEstablecer…`: `SRutEstablecer`,
`SRutEstablecerDirectorio`, `SRutEstablecerDirectorioActual`,
`SRutEstablecerDirectorioLit`, `SRutEstablecerFichero` y sus variantes.

### Extensión

| Función                         | Descripción          |
| ------------------------------- | -------------------- |
| `SRutAgregarExtension` / `…Lit` | Añade una extensión. |
| `SRutEliminarExtension`         | Quita la extensión.  |

### Consultas

Catorce predicados `SRutEs…`, entre ellos `SRutEsAbsoluta`,
`SRutEsDirectorio`, `SRutEsDirectorioValido`, `SRutEsAccesible`,
`SRutEsDeSoloLectura` y `SRutEsDelSistema`.

Y tres de existencia: `SRutExiste`, `SRutExisteDirectorio`,
`SRutExisteFichero`.

`SRutEsEstiloUNIX` y `SRutEsEstiloDOS` miran **sólo el directorio**:

| Directorio                  | UNIX | DOS |
| --------------------------- | ---- | --- |
| `/tmp`, `/`, `./a`, `../a`  | 1    | 0   |
| `C:\Temp`, `C:`, `\\srv\sh` | 0    | 1   |
| `tmp` (sin separadores)     | 1    | 1   |
| `C:/dir`, `a/b\c` (mezcla)  | 0    | 0   |
| vacío                       | 0    | 0   |

Usan los patrones `SF_PATRON_DIR_UNIX` (`"(/)?*(/?*)"`) y
`SF_PATRON_DIR_DOS` (`"(\\)?*(\\?*)"`) de `FicherosConfig.h`. Como el motor de
[expresiones](../../gjs-c-common-text/doc/ExpresionesRegulares.md) no puede
excluir caracteres, el separador del otro estilo y la unidad (`C:`) se
descartan aparte. Hasta el 2026-10-01 usaban expresiones de estilo PCRE
(`^…$`, `[^/]`, `+`) que ese motor no entiende, y devolvían siempre `0`.
Lo cubre `TestSRutEstilo01`.

```c
SRuta * p_rutObj = SRutCrearFicheroLit ( "datos/informe.txt" );

if ( SRutExisteFichero ( p_rutObj ) == 1 )
{
    printf ( "%s\n", SRutFicheroSinExtensionLit ( p_rutObj ) );  /* informe */
}
SRutAgregarExtensionLit ( p_rutObj, "bak" );
SRutDestruir ( &p_rutObj );
```

## Dependencias

- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — las dos partes.
- [SistemaFicheros](SistemaFicheros.md) — existencia y atributos.

## Test

`SRutaTest.c` → `TestSRuta()`.

## Observaciones

- **Los predicados de existencia y atributos duplican los de
  [SistemaFicheros](SistemaFicheros.md).** `SRutExisteFichero` y
  `SisExisteFichero` responden a lo mismo con distinto envoltorio; hay 14
  predicados `SRutEs…` y 15 `SisEs…` con solapamiento evidente. La diferencia
  práctica es que el objeto ya lleva la ruta dentro.
- **La estructura no puede representar una ruta con sólo nombre de fichero y sin
  directorio de forma distinguible** de una con directorio vacío: ambos casos
  dejan `p_cadDirectorio` sin contenido.
- `SRutRutaAbsoluta` resuelve la ruta contra el directorio actual, lo que hace
  que su resultado **dependa del estado del proceso** en el momento de la
  llamada.
- No hay operaciones de composición entre rutas: no existe `SRutUnir` para
  concatenar un subdirectorio, aunque
  [SistemaFicheros](SistemaFicheros.md) sí tiene `SisComponerRuta`.
- Con 59 funciones y 1.261 líneas es el segundo módulo más grande del componente,
  pero la mitad de su API son variantes `Lit` de la otra mitad.
