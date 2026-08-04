# Nodos

| Dato          | Valor                                                                                               |
| ------------- | --------------------------------------------------------------------------------------------------- |
| Módulos       | 6                                                                                                   |
| Cabeceras     | `SNodo.h`, `SNodoPtr.h`, `SNodoBin.h`, `SNodoBinPtr.h`, `SNodoPorBloques.h`, `SNodoPorBloquesPtr.h` |
| Prefijos      | `SNod`, `SNodPtr`, `SNodBin`, `SNodBinPtr`, `SNodBlq`, `SNodBlqPtr`                                 |
| Incluidos por | `Tipos.h`                                                                                           |
| Tests         | Uno por módulo                                                                                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los nodos de los [árboles](Arboles.md). Un nodo guarda datos, conoce a su padre
y a sus hijos, y sabe responder preguntas sobre su posición en la jerarquía
(profundidad, número de descendientes, si tiene hermanos a un lado o a otro).

A diferencia de [SElemento](SElemento.md), que se declara con enlaces `void *`,
los nodos usan estructuras **autorreferenciales** bien formadas:

```c
typedef struct SNodo SNodo;

struct SNodo
{
    SNodo *    p_nodPadre;
    SNodo **   p_p_nodHijos;
    int        iNumHijos;
    SBloque *  p_blqDatos;
    int        iLiberar;
};
```

## Las tres formas de guardar los hijos

Es lo que distingue a las tres variantes base:

| Módulo            | Hijos                             | Pensado para               |
| ----------------- | --------------------------------- | -------------------------- |
| `SNodo`           | `SNodo **` — un array             | Nodos con pocos hijos      |
| `SNodoBin`        | Dos punteros, izquierdo y derecho | Árboles binarios           |
| `SNodoPorBloques` | `SNodoBlq ***` — array de bloques | Nodos con **muchos** hijos |

`SNodoPorBloques` reserva los hijos en bloques de `ARB_TAM_BLOQUE_HIJOS_NODO`
(256) hasta `ARB_MAX_HIJOS_NODO` (65536), en lugar de un único array que habría
que redimensionar. Las constantes están en `TiposBasicosConstantes.h`.

Cada una tiene su variante `Ptr`, que guarda un `byte *` en lugar de un
[SBloque](SBloque.md).

## API de `SNodo`

### Construcción y datos

`SNodCrear ( int iTam )` más las variantes tipadas `SNodCrearEntero`,
`SNodCrearEnteroLargo`, `SNodCrearReal`, `SNodCrearRealDoble`,
`SNodCrearCadena`, y las de encapsulado `SNodEncapsular`, `SNodEncapsularDir`.

Lectura: `SNodDatos`, `SNodEntero`, `SNodEnteroLargo`, `SNodReal`,
`SNodRealDoble`, `SNodCadena`, `SNodTieneDatos`.

Escritura: `SNodEstablecerByte`, `SNodEstablecerEntero`,
`SNodEstablecerEnteroLargo`, `SNodEstablecerReal`, `SNodEstablecerRealDoble`,
`SNodEstablecerCadena`, `SNodModificar`, `SNodModificarDir`.

### Jerarquía

| Función                            | Descripción                         |
| ---------------------------------- | ----------------------------------- |
| `SNodPadre ( SNodo * )`            | Nodo padre.                         |
| `SNodHijo ( SNodo *, int )`        | Hijo por posición.                  |
| `SNodNumHijos ( SNodo * )`         | Número de hijos.                    |
| `SNodTienePadre ( SNodo * )`       | 1 si tiene padre.                   |
| `SNodTieneHijos ( SNodo * )`       | 1 si tiene hijos.                   |
| `SNodTieneHermanos ( SNodo * )`    | 1 si tiene hermanos.                |
| `SNodTieneHermanosIzq ( SNodo * )` | 1 si tiene hermanos a la izquierda. |
| `SNodTieneHermanosDer ( SNodo * )` | 1 si tiene hermanos a la derecha.   |
| `SNodOrdenDelHijo ( … )`           | Posición de un hijo.                |

### Métricas

`SNodNodosInferiores` (total de descendientes), `SNodProfundidad` (distancia a
la raíz) y `SNodNivelesInferiores` (altura del subárbol).

### Modificación de la jerarquía

| Función                    | Descripción            |
| -------------------------- | ---------------------- |
| `SNodEmpadronar ( … )`     | Asigna un padre.       |
| `SNodDesempadronar ( … )`  | Lo saca de su padre.   |
| `SNodInsertarHijo ( … )`   | Añade un hijo.         |
| `SNodEstablecerHijo ( … )` | Sustituye un hijo.     |
| `SNodEliminarHijo ( … )`   | Quita un hijo.         |
| `SNodLimpiarHijos ( … )`   | Quita todos los hijos. |

### Diagnóstico

`SNodVerificar` comprueba la coherencia interna del nodo —que los enlaces
padre/hijo se correspondan— y `SNodDuplicar` hace una copia.

## `SNodoBin`

Cambia el vocabulario de hijos por el binario: `SNodBinHijoIzq`,
`SNodBinHijoDer`, `SNodBinTieneHijoIzq`, `SNodBinTieneHijoDer`,
`SNodBinEsHijoIzqDelPadre`, `SNodBinEsHijoDerDelPadre`,
`SNodBinTieneHermanoIzq`, `SNodBinTieneHermanoDer`, `SNodBinEstHijoIzq`,
`SNodBinEstHijoDer`, `SNodBinEliminarHijoIzq`, `SNodBinEliminarHijoDer`.

El resto (datos, métricas, `Empadronar`, `Verificar`, `Duplicar`) es igual.

## Las variantes `Ptr`

Guardan `byte *` en lugar de `SBloque *`, así que pierden toda la API tipada:
sólo quedan `SNodPtrCrear ( byte * p_byDatos, int iLiberar )`, `SNodPtrDatos` y
`SNodPtrModificar`. La parte de jerarquía y métricas es idéntica.

## Dependencias

- [SBloque](SBloque.md) — datos de las variantes base.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Tests

`SNodoTest.c`, `SNodoPtrTest.c`, `SNodoBinTest.c`, `SNodoBinPtrTest.c`,
`SNodoPorBloquesTest.c`, `SNodoPorBloquesPtrTest.c`.

## Observaciones

> **`SNodoPtr.h` declara una función que no es suya, con el tipo cambiado.** En
> la línea 32:
>
> ```c
> SNodoPtr * SNodBinCrearMem ( int iTamDatos );     /* SNodoPtr.h:32  */
> SNodoBin * SNodBinCrearMem ( int iTamDatos );     /* SNodoBin.h:29  */
> ```
>
> Es el **mismo símbolo con dos tipos de retorno distintos**. Incluir las dos
> cabeceras a la vez es un error de compilación, comprobado con el `gcc` del
> proyecto:
> *`error: conflicting types for 'SNodBinCrearMem'`*.
>
> Como `Tipos.h` incluye ambas (líneas 74 y 76), **la fachada del módulo no
> compila**. Que el módulo se construya sin problemas se debe a que ningún `.c`
> de producción incluye `Tipos.h`; ver [MODULOS.md](MODULOS.md#tiposh). La línea
> de `SNodoPtr.h` parece un resto de copia y pega y sobra.

- **`SNodoPorBloques` declara la estructura `SNodoBlq`**, no `SNodoPorBloques`:
  el nombre del fichero y el del tipo no coinciden. Lo mismo en
  `SNodoPorBloquesPtr.h`, cuya estructura es `SNodoBlqPtr`.
- Dentro de `SNodoPorBloques.h`, **una función se sale del prefijo**:
  `SNodoBlqOrdenDelHijo` en lugar de `SNodBlqOrdenDelHijo`, que es el prefijo de
  las otras 44.
- **`SNodo` escribe con `Establecer…` y `SNodoPorBloques` con `Escribir…`** para
  la misma operación (`SNodEstablecerEntero` frente a `SNodBlqEscribirEntero`),
  pese a ser variantes del mismo concepto.
- **`SNodoBin` no tiene `SNodBinCrear`**: su constructor genérico se llama
  `SNodBinCrearMem`, único caso en la librería.
- `SNodPtrDestruir ( SNodoPtr **, int iDestruirHijos )` recibe un segundo
  parámetro, como ocurre en [SPilaPtr y SColaPtr](Pilas.md). Aquí tiene más
  sentido —hay que decidir si la destrucción es recursiva— pero rompe igualmente
  el convenio de un solo argumento.
