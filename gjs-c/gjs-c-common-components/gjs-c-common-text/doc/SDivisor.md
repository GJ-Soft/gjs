# SDivisor

| Dato         | Valor                                                 |
| ------------ | ----------------------------------------------------- |
| Cabecera     | `src/main/include/SDivisor.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SDivisor.c` (336 líneas) |
| Prefijo      | `SDiv`                                                |
| Struct       | `SDivisor`                                            |
| Funciones    | 16                                                    |
| Incluido por | `Texto.h`                                             |
| Test         | `SDivisorTest.c` → `TestSDivisor()`                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Trocear un texto por un **carácter separador** y trabajar con las partes. Es el
`split` de la librería, con una vuelta de tuerca: puede producir *subdivisores*,
lo que permite recorrer estructuras jerárquicas como rutas o nombres cualificados
sin volver a trocear a mano.

## Modelo de datos

```c
typedef struct
{
    char                   cSeparador;
    char *                 p_cTexto;
    SSecuenciaLiterales *  p_secPartes;
} SDivisor;
```

Las partes se guardan en una
[SSecuenciaLiterales](../../gjs-c-common-base-types/doc/Secuencias.md).

## API

### Ciclo de vida

| Función                                                                         | Descripción                  |
| ------------------------------------------------------------------------------- | ---------------------------- |
| `SDivisor * SDivCrear ( char cSeparador )`                                      | Divisor sin texto todavía.   |
| `SDivisor * SDivCrearExt ( char cSeparador, const char * p_cTexto )`            | Divisor ya cargado.          |
| `void SDivDestruir ( SDivisor ** )`                                             | Destruye y anula el puntero. |
| `int SDivEsValido ( SDivisor * )`                                               | 1 si es utilizable.          |
| `int SDivInicializar ( SDivisor *, const char * p_cTexto )`                     | Carga un texto nuevo.        |
| `int SDivInicializarExt ( SDivisor *, char cSeparador, const char * p_cTexto )` | Cambia separador y texto.    |

### Consulta

| Función                                             | Descripción             |
| --------------------------------------------------- | ----------------------- |
| `int SDivTieneTexto ( SDivisor * )`                 | 1 si hay texto cargado. |
| `char SDivSeparador ( SDivisor * )`                 | Carácter separador.     |
| `const char * SDivTexto ( SDivisor * )`             | Texto completo.         |
| `int SDivNumPartes ( SDivisor * )`                  | Número de partes.       |
| `const char * SDivParte ( SDivisor *, int iParte )` | Parte por posición.     |
| `SSecuenciaLiterales * SDivPartes ( SDivisor * )`   | Todas las partes.       |

### Subdivisión

| Función                                                     | Descripción                                        |
| ----------------------------------------------------------- | -------------------------------------------------- |
| `char * SDivSubtexto ( SDivisor * )`                        | Texto restante tras la primera parte. **Reserva.** |
| `char * SDivSubtextoExt ( SDivisor *, int iAvances )`       | Ídem tras `iAvances` partes. **Reserva.**          |
| `SDivisor * SDivSubdivisor ( SDivisor * )`                  | Divisor sobre el subtexto.                         |
| `SDivisor * SDivSubdivisorExt ( SDivisor *, int iAvances )` | Ídem avanzando `iAvances`.                         |

```c
SDivisor * p_divObj = SDivCrearExt ( '.', "org.gjs.c.common" );

printf ( "%d partes, la primera %s\n",
         SDivNumPartes ( p_divObj ), SDivParte ( p_divObj, 0 ) );

SDivisor * p_divResto = SDivSubdivisor ( p_divObj );   /* sobre "gjs.c.common" */

SDivDestruir ( &p_divResto );
SDivDestruir ( &p_divObj );
```

## Dependencias

- [Secuencias](../../gjs-c-common-base-types/doc/Secuencias.md) —
  `SSecuenciaLiterales` guarda las partes.
- [Cadenas](Cadenas.md) — el troceado.

## Test

`SDivisorTest.c` → `TestSDivisor()`.

## Observaciones

- **El separador es un solo `char`**, no una cadena: no se puede trocear por
  `", "` ni por un separador de varios caracteres.
- La cabecera no dice **qué ocurre con las partes vacías**: un texto como
  `"a..b"` con separador `'.'` puede dar tres partes (con una vacía en medio) o
  dos. Conviene comprobarlo con `SDivNumPartes` antes de asumir.
- `SDivSubtexto` y `SDivSubtextoExt` **reservan memoria** que el llamante debe
  liberar, mientras que `SDivParte` y `SDivTexto` devuelven punteros internos
  `const char *`. La diferencia está sólo en el tipo de retorno.
- `SDivPartes` expone la secuencia interna, con el aviso habitual: se puede
  dejar el divisor en un estado incoherente con el texto que dice tener.
- Es el módulo natural para trocear texto, pero devuelve `const char *`, no
  [SToken](SToken.md): las dos piezas del análisis léxico no encajan entre sí.
