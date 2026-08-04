# Cadenas

| Dato         | Valor                                                  |
| ------------ | ------------------------------------------------------ |
| Cabecera     | `src/main/include/Cadenas.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/Cadenas.c` (3.709 líneas) |
| Prefijo      | `Cad`                                                  |
| Funciones    | 205                                                    |
| Incluido por | `Texto.h`                                              |
| Test         | `CadenasTest.c` → `TestCadenas()`                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo completo de operaciones sobre cadenas `char *`. Es el módulo con la
API más grande de todo el stack C, y la base sobre la que está implementado
[SCadena](SCadena.md).

Amplía —sin sustituirlas— las rutinas `Cad*` de
[CadenasBase](../../gjs-c-common-base/doc/CadenasBase.md) de la librería base,
que se queda en crear, medir, duplicar y comparar. Aquí está todo lo demás.

## El convenio `Ext`

Casi todas las rutinas vienen por duplicado:

```c
int CadCopiar    ( char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadCopiarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );

int CadBuscar    ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos );
int CadBuscarExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos, int iMax1, int iMax2 );
```

La variante `Ext` recibe **la longitud máxima de cada cadena implicada**; la
corta usa el tope global `CAD_MAX_TAM` (8191). Son las mismas operaciones, y
`Ext` es la que acota de verdad.

## La API por familias

Las 205 funciones se agrupan así:

| Familia                                   | Nº  | Qué hace                                                                                                                               |
| ----------------------------------------- | --- | -------------------------------------------------------------------------------------------------------------------------------------- |
| `Eliminar…`                               | 32  | Quitar apariciones, blancos, caracteres o tramos                                                                                       |
| `Es…`                                     | 24  | Predicados: `EsIgual`, `EsMayor`, `EsIdentificadorValido`, `EsNumerica`…                                                               |
| `Contiene…`                               | 14  | Si hay blancos, caracteres no alfanuméricos, no imprimibles…                                                                           |
| `Buscar…`                                 | 12  | Posición de subcadena o carácter, hacia delante y hacia atrás                                                                          |
| `Extraer…`                                | 10  | Subcadenas por posición, hasta un carácter o desde él                                                                                  |
| `Coherencia…`                             | 8   | Equilibrio de paréntesis, corchetes, llaves y parejas de signos                                                                        |
| `Num…`                                    | 8   | Contar caracteres y palabras, con separador o sin él                                                                                   |
| `Uni…`                                    | 8   | Las mismas operaciones sobre cadenas `unichar`                                                                                         |
| `Concatenar…`                             | 6   | Unir, con carácter o con formato                                                                                                       |
| `Convertir…`                              | 6   | A mayúsculas, minúsculas y capitales                                                                                                   |
| `Copiar…`                                 | 6   | Copia, de carácter y con formato                                                                                                       |
| `Limpiar…`                                | 6   | Vaciar entera, desde una posición o hasta ella                                                                                         |
| `Palabra…`                                | 6   | Extraer la palabra n-ésima, con separador configurable                                                                                 |
| `Comparar…`                               | 4   | Parcial y sin distinguir mayúsculas                                                                                                    |
| `Acaba…` / `Empieza…`                     | 8   | Sufijo y prefijo, por cadena o por carácter                                                                                            |
| `Contar…`                                 | 4   | Repeticiones de subcadena o carácter                                                                                                   |
| `Cumple…`                                 | 4   | Contra [patrón](Patrones.md) o [expresión regular](ExpresionesRegulares.md)                                                            |
| `Escribir…` / `Insertar…` / `Reemplazar…` | 12  | Modificación en sitio                                                                                                                  |
| `Componer…`                               | 3   | Construir a partir de partes, envolviendo o varias                                                                                     |
| `Crear…`                                  | 3   | Crear con formato                                                                                                                      |
| `Imprimir…`                               | 3   | Volcado, incluidos `ImprimirJson` e `ImprimirXml`                                                                                      |
| `Transformar` / `Aplicar…`                | 4   | Aplicar una transformación carácter a carácter                                                                                         |
| Otras                                     | 12  | `Invertir`, `Envolver`, `Equivalente`, `FormatearBlancos`, `ValorNulo`, `ValorNumerico`, `Caracter`, `EstaVacia`, `EstablecerCaracter` |

## Comportamiento

Las rutinas que **devuelven `char *` reservan memoria** con `MemReservar` y la
propiedad pasa al llamante (`CadExtraer`, `CadComponer`, `CadCrearConFormato`,
`CadPalabra`…). Las que devuelven `int` operan sobre el buffer que se les pasa.

La familia `Coherencia…` es característica del módulo: comprueba que los signos
de apertura y cierre estén equilibrados, lo que la hace útil para validar
expresiones antes de procesarlas.

`CadImprimirJson` y `CadImprimirXml` escapan la cadena según las reglas de cada
formato antes de volcarla.

## Dependencias

- [CadenasBase](../../gjs-c-common-base/doc/CadenasBase.md) y `Base.h`.
- [ASCII](ASCII.md) — clasificación de caracteres.
- [Patrones](Patrones.md) y [ExpresionesRegulares](ExpresionesRegulares.md) —
  las familias `CumpleCondCar` y `CumpleExpReg`.

## Test

`CadenasTest.c` → `TestCadenas()`.

## Observaciones

- **La cabecera lleva dos `PENDIENTE` en las líneas 33-34**: faltan las
  comparativas `EsMayor` / `EsMenor` y `EmpiezaPor` sin distinguir tipo de letra
  —sólo está `CadCompararSinDistinguirTipoLetra`— y el soporte `unichar` está a
  medias: hay 8 rutinas `CadUni…` (copiar y concatenar) frente a las 197 de
  `char *`.
- **Las formas cortas no acotan.** `CadCopiar` recorre hasta `CAD_MAX_TAM`
  (8191) buscando el terminador: si el destino es menor y el origen no está
  terminado, escribe fuera. La variante `Ext` existe precisamente para eso y es
  la que conviene usar siempre.
- Tener 205 funciones en una cabecera plana, sin secciones ni agrupación, hace
  difícil encontrar la adecuada. La tabla de arriba suple esa falta.
- El nombre `Cadenas` colisiona conceptualmente con `CadenasBase` de la
  librería base, y **ambos usan el prefijo `Cad`**: al leer una llamada `Cad…`
  no se sabe de qué módulo viene sin buscarla.
