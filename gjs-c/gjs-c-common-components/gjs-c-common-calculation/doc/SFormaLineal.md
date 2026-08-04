# SFormaLineal

| Dato         | Valor                                                     |
| ------------ | --------------------------------------------------------- |
| Cabecera     | `src/main/include/SFormaLineal.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SFormaLineal.c` (352 líneas) |
| Prefijo      | `SFrmLin`                                                 |
| Struct       | `SFormaLineal`                                            |
| Funciones    | 19                                                        |
| Incluido por | `Calculo.h`                                               |
| Test         | `SFormaLinealTest.c` → `TestSFormaLineal()`               |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **combinación lineal** de N variables: `a₁x₁ + a₂x₂ + … + aₙxₙ`. Guarda los
coeficientes y sabe evaluarse dado un vector de valores.

Es la pieza con la que se representan ecuaciones lineales, productos escalares y
funciones de coste.

```c
typedef struct
{
    int      iNumVariables;
    double * p_dCoeficientes;
} SFormaLineal;
```

## API

### Construcción

Cinco constructores: el general, el de lista variable y tres atajos para las
dimensiones habituales.

| Función                                                                        | Descripción                        |
| ------------------------------------------------------------------------------ | ---------------------------------- |
| `SFormaLineal * SFrmLinCrear ( int iNumVariables )`                            | Forma con los coeficientes a cero. |
| `SFormaLineal * SFrmLinCrearExt ( int iNumVariables, … )`                      | Con los coeficientes dados.        |
| `SFormaLineal * SFrmLinCrear1 ( double dCoef )`                                | De una variable.                   |
| `SFormaLineal * SFrmLinCrear2 ( double dCoef1, double dCoef2 )`                | De dos.                            |
| `SFormaLineal * SFrmLinCrear3 ( double dCoef1, double dCoef2, double dCoef3 )` | De tres.                           |
| `SFormaLineal * SFrmLinDuplicar ( SFormaLineal * )`                            | Copia independiente.               |
| `void SFrmLinDestruir ( SFormaLineal ** )`                                     | Destruye y anula el puntero.       |
| `int SFrmLinEsValido ( SFormaLineal * )`                                       | 1 si es utilizable.                |

### Coeficientes

| Función                                               | Descripción             |
| ----------------------------------------------------- | ----------------------- |
| `int SFrmLinNumVariables ( SFormaLineal * )`          | Número de variables.    |
| `double SFrmLinCoeficiente ( …, int iCoeficiente )`   | Coeficiente por índice. |
| `double SFrmLinCoeficiente1 ( … )`                    | Primer coeficiente.     |
| `double SFrmLinCoeficiente2 ( … )`                    | Segundo.                |
| `double SFrmLinCoeficiente3 ( … )`                    | Tercero.                |
| `int SFrmLinEstablecerCoeficiente ( …, int, double )` | Cambia un coeficiente.  |
| `double * SFrmLinVectorValores ( SFormaLineal * )`    | Vector de coeficientes. |

### Evaluación y álgebra

| Función                                                         | Descripción                        |
| --------------------------------------------------------------- | ---------------------------------- |
| `double SFrmLinEvaluar ( SFormaLineal *, double * p_dValores )` | Evalúa con un vector de valores.   |
| `double SFrmLinEvaluarExt ( SFormaLineal *, … )`                | Evalúa con los valores sueltos.    |
| `int SFrmLinMultiplicar ( SFormaLineal *, double dValor )`      | Multiplica todos los coeficientes. |
| `int SFrmLinSumar ( SFormaLineal *, SFormaLineal * )`           | Suma otra forma lineal.            |

```c
SFormaLineal * p_frmObj = SFrmLinCrear3 ( 2.0, -1.0, 0.5 );   /* 2x − y + 0,5z */

double dRes = SFrmLinEvaluarExt ( p_frmObj, 1.0, 2.0, 4.0 );  /* 2 − 2 + 2 = 2 */

SFrmLinMultiplicar ( p_frmObj, 3.0 );                          /* 6x − 3y + 1,5z */
SFrmLinDestruir ( &p_frmObj );
```

## Dependencias

- [CalculoOperaciones](CalculoOperaciones.md) — comparación con tolerancia.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`SFormaLinealTest.c` → `TestSFormaLineal()`.

## Observaciones

- **`SFrmLinVectorValores` expone el vector interno de coeficientes**, así que se
  pueden modificar sin pasar por `SFrmLinEstablecerCoeficiente`. El nombre
  además engaña: devuelve los *coeficientes*, no unos "valores".
- `SFrmLinEvaluar` recibe `double *` **sin decir cuántos elementos espera**: han
  de ser exactamente `SFrmLinNumVariables`. Pasar un vector más corto lee fuera
  y el compilador no puede avisar.
- `SFrmLinEvaluarExt` usa lista variable de argumentos **sin contador**, a
  diferencia de `SFrmLinCrearExt`, que sí recibe `iNumVariables` primero. Aquí el
  número de argumentos tiene que casar con las variables de la forma, y nada lo
  comprueba.
- `SFrmLinSumar` no dice qué ocurre si las dos formas tienen distinto número de
  variables.
- Los atajos `Coeficiente1`, `Coeficiente2` y `Coeficiente3` llegan hasta tres,
  igual que los constructores; a partir de ahí hay que usar el índice.
