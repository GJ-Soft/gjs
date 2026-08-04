# SAccion y TiposAccion

| Dato          | Valor                                |
| ------------- | ------------------------------------ |
| Módulos       | 2                                    |
| Cabeceras     | `SAccion.h`, `TiposAccion.h`         |
| Prefijos      | `SAcc`, `TipAcc`                     |
| Funciones     | 18 + 9                               |
| Incluidos por | `TiposDatos.h`                       |
| Tests         | `SAccionTest.c`, `TiposAccionTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **acción** es lo que hay que hacer cuando el usuario elige una opción:
devolver un código, invocar un submenú, ejecutar una función o salir.

Es la pieza con la que se construyen menús e interfaces de consola sin cablear
el flujo de control.

```c
typedef struct
{
    int      iTipo;
    int      iCodigo;
    PFUNINTI p_fAccion;    /* int (*)(int) */
} SAccion;
```

## Los tipos de acción

`TiposAccion.h` define el catálogo:

| Constante         | Valor | Qué significa                  |
| ----------------- | ----- | ------------------------------ |
| `TIP_ACC_NULO`    | 0     | No hacer nada                  |
| `TIP_ACC_CODIGO`  | 1     | Devolver un código al llamante |
| `TIP_ACC_FUNCION` | 2     | Ejecutar la función asociada   |
| `TIP_ACC_MENU`    | 3     | Entrar en un submenú           |
| `TIP_ACC_SALIR`   | 4     | Terminar                       |
| `TIP_ACC_VOLVER`  | 5     | Volver al nivel anterior       |

Y dos códigos reservados:

| Constante        | Valor |
| ---------------- | ----- |
| `COD_ACC_NULO`   | 0     |
| `COD_ACC_VOLVER` | 99    |
| `COD_ACC_SALIR`  | 100   |

Con sus predicados: `TipAccEsValido`, `TipAccEsCodigo`, `TipAccEsFuncion`,
`TipAccEsMenu`, `TipAccEsSalir`, `TipAccEsVolver`.

## API de `SAccion`

| Grupo         | Funciones                                                                                                               |
| ------------- | ----------------------------------------------------------------------------------------------------------------------- |
| Ciclo de vida | `SAccCrear ( int iTipo )`, `SAccCrearExt ( iTipo, iCodigo, p_fAccion )`, `SAccDestruir`, `SAccDuplicar`, `SAccEsValida` |
| Consulta      | `SAccTipo`, `SAccCodigo`, `SAccFuncion`                                                                                 |
| Predicados    | `SAccRetornaCodigo`, `SAccInvocaMenu`, `SAccEjecutaFuncion`, `SAccOrdenaSalir`, `SAccOrdenaVolver`                      |
| Asignación    | `SAccEstablecer`, `SAccEstablecerExt`, `SAccEstablecerCodigo`, `SAccEstablecerFuncion`                                  |
| **Ejecución** | `int SAccEjecutar ( SAccion * )`                                                                                        |

Los predicados están redactados desde el punto de vista de quien despacha la
acción —`SAccOrdenaSalir`, `SAccInvocaMenu`— en lugar de repetir los nombres del
catálogo, lo que hace el bucle de despacho legible:

```c
SAccion * p_accObj = SAccCrearExt ( TIP_ACC_FUNCION, 0, MiFuncion );

if ( SAccEjecutaFuncion ( p_accObj ) == 1 )
{
    int iRes = SAccEjecutar ( p_accObj );
}
else if ( SAccOrdenaSalir ( p_accObj ) == 1 )
{
    /* … */
}
SAccDestruir ( &p_accObj );
```

## Dependencias

- `Funciones.h` de [gjs-c-common-base](../../gjs-c-common-base/doc/MODULOS.md) —
  el tipo `PFUNINTI` (`int (*)(int)`).

## Tests

`SAccionTest.c` → `TestSAccion()`, `TiposAccionTest.c` → `TestTiposAccion()`.

## Observaciones

- **La función asociada es `PFUNINTI`: recibe un `int` y devuelve un `int`.** No
  hay forma de pasarle contexto ni un puntero a datos, así que una acción que
  necesite estado tiene que apoyarse en variables globales. Es la limitación de
  usar punteros a función C sin cierre.
- **`SAccEjecutar` devuelve `int` sin distinguir** entre el resultado de la
  función invocada y un fallo al ejecutar (acción nula, función no asignada).
- El tipo `TIP_ACC_MENU` existe, pero **`SAccion` no guarda qué menú invocar**:
  la estructura sólo tiene tipo, código y función. El identificador del submenú
  tendrá que ir en `iCodigo`, cosa que la cabecera no dice.
- `COD_ACC_VOLVER` (99) y `COD_ACC_SALIR` (100) son códigos reservados que
  colisionarían con códigos de aplicación en ese rango, sin que nada lo impida.
- No hay `SAccEstablecerTipo` suelto, aunque sí `SAccEstablecerCodigo` y
  `SAccEstablecerFuncion`: para cambiar sólo el tipo hay que usar
  `SAccEstablecer`.
