# TiposCaracter

| Dato         | Valor                                         |
| ------------ | --------------------------------------------- |
| Cabecera     | `src/main/include/TiposCaracter.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/TiposCaracter.c` |
| Prefijo      | `TipCar`                                      |
| Funciones    | 7                                             |
| Incluido por | **Nadie** — fuera de la fachada `Texto.h`     |
| Test         | `TiposCaracterTest.c` → `TestTiposCaracter()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Define el **alfabeto de los patrones**: los siete caracteres con los que
[Patrones](Patrones.md) describe qué puede aparecer en cada posición de una
cadena.

## Los tipos

| Constante              | Carácter | Casa con              |
| ---------------------- | -------- | --------------------- |
| `TIP_CAR_DIGITO`       | `'9'`    | Un dígito             |
| `TIP_CAR_LETRA`        | `'@'`    | Una letra             |
| `TIP_CAR_SIGNO`        | `'&'`    | Un signo              |
| `TIP_CAR_ESPACIO`      | `' '`    | Un espacio            |
| `TIP_CAR_LETRADIG`     | `'#'`    | Letra o dígito        |
| `TIP_CAR_ALFANUMERICO` | `'$'`    | Carácter alfanumérico |
| `TIP_CAR_CUALQUIERA`   | `'?'`    | Cualquier carácter    |

El valor por defecto es `TIP_CAR_CUALQUIERA`, que `TextoConstantes.h` expone
como `PAT_CAR_DEFECTO`.

## API

| Función                                  | Descripción                           |
| ---------------------------------------- | ------------------------------------- |
| `int TipCarEsValido ( char cCod )`       | 1 si el carácter es uno de los siete. |
| `int TipCarEsCualquiera ( char cCod )`   | 1 si es `'?'`.                        |
| `int TipCarEsDigito ( char cCod )`       | 1 si es `'9'`.                        |
| `int TipCarEsLetra ( char cCod )`        | 1 si es `'@'`.                        |
| `int TipCarEsSigno ( char cCod )`        | 1 si es `'&'`.                        |
| `int TipCarEsLetraDigito ( char cCod )`  | 1 si es `'#'`.                        |
| `int TipCarEsAlfanumerico ( char cCod )` | 1 si es `'$'`.                        |

Obsérvese que estas funciones **no clasifican el carácter de una cadena**: dicen
qué tipo de patrón representa el símbolo. Para clasificar caracteres reales está
[ASCII](ASCII.md).

Un patrón de matrícula española se escribiría `"9999@@@"`: cuatro dígitos y tres
letras.

## Dependencias

Ninguna. La cabecera no incluye nada.

## Test

`TiposCaracterTest.c` → `TestTiposCaracter()`.

## Observaciones

- **No está en la fachada `Texto.h`**, pese a tener fuente, test y ser el
  vocabulario que necesita [Patrones](Patrones.md), que sí lo está. Un consumidor
  que incluya `Texto.h` puede usar `PatEvaluar` pero no dispone de las constantes
  para construir el patrón sin incluir `TiposCaracter.h` a mano.
- No hay constante para "espacio" en el sentido de opcional ni forma de expresar
  repeticiones: los patrones son de longitud fija, un símbolo por posición. Para
  algo más expresivo está
  [ExpresionesRegulares](ExpresionesRegulares.md).
- `TIP_CAR_ESPACIO` es el carácter espacio (`' '`), así que un patrón no puede
  distinguir "aquí va un espacio" de "aquí no hay restricción" si se construye
  rellenando con blancos.
