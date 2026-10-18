# SPtr

| Dato         | Valor                                |
| ------------ | ------------------------------------ |
| Cabecera     | `src/main/include/SPtr.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SPtr.c` |
| Prefijo      | `SPtr`                               |
| Struct       | `SPtr`                               |
| Funciones    | 9                                    |
| Incluido por | `TiposBasicos.h`                     |
| Test         | `SPtrTest.c` → `TestSPtr()`          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Envoltorio que asocia un objeto cualquiera (`void *`) con la función que sabe
destruirlo. Quien recibe un `SPtr` puede liberar el objeto con `SPtrDestruir`
sin conocer su tipo.

## Modelo de datos

```c
typedef PPRCPPV PRC_DESTRUCTOR;      /* void (*)( void ** ) */

typedef struct
{
    void *          p_vObjeto;
    PRC_DESTRUCTOR  p_fDestructor;
} SPtr;
```

`PRC_DESTRUCTOR` tiene la misma forma que los destructores del stack
(`S<Pfx>Destruir ( S<Concepto> ** )`) y que `MemLiberar`: recibe la dirección del
puntero, para poder anularlo.

## API

| Función                                                  | Descripción                                                       |
| -------------------------------------------------------- | ----------------------------------------------------------------- |
| `SPtr * SPtrCrearDef ( void * p_vObjeto )`               | Envuelve el objeto con `MemLiberar` como destructor.              |
| `SPtr * SPtrCrear ( void * p_vObjeto, PRC_DESTRUCTOR )`  | Envuelve el objeto con el destructor indicado.                    |
| `SPtr * SPtrPreparar ( PRC_DESTRUCTOR )`                 | `SPtr` vacío con el destructor indicado.                          |
| `void SPtrDestruir ( SPtr ** )`                          | Llama al destructor sobre el objeto, libera el `SPtr` y lo anula. |
| `void SPtrDestruirSinLiberar ( SPtr ** )`                | Libera el `SPtr` y lo anula **sin** destruir el objeto.           |
| `int SPtrEsValido ( SPtr * )`                            | 1 si hay `SPtr`, objeto y destructor.                             |
| `int SPtrEstaVacio ( SPtr * )`                           | 1 si no envuelve ningún objeto, o si el `SPtr` es nulo.           |
| `void * SPtrObjeto ( SPtr * )`                           | El objeto envuelto (no liberar), o `NULL`.                        |
| `int SPtrEstablecer ( SPtr *, void * p_vObjeto )`        | Destruye el objeto que hubiera y guarda el nuevo.                 |

## Comportamiento

- **El `SPtr` es dueño del objeto.** `SPtrDestruir` llama al destructor una sola
  vez, con la dirección del campo `p_vObjeto` (si hay objeto), y después libera
  la estructura y anula el puntero del llamante. Destruir un `SPtr` ya nulo, o pasar `NULL`, no
  hace nada.
- **Crear exige un destructor válido** (`ES_VALIDO`), pero **no un objeto**. Con
  objeto `NULL` se crea un `SPtr` **vacío**, que puede recibir uno después con
  `SPtrEstablecer`; `SPtrCrearDef ( NULL )` hace lo mismo con `MemLiberar`.
  `SPtrPreparar ( d )` equivale a `SPtrCrear ( NULL, d )`: deja fijado el
  destructor antes de que llegue el objeto. Sin destructor, o si falla la
  reserva de la estructura, `SPtrCrear` devuelve `NULL` y **el objeto sigue
  siendo del llamante**: no se libera.
- **`SPtrDestruirSinLiberar` sólo libera la estructura.** No llama al
  destructor: el objeto queda intacto y vuelve a ser del llamante. Es lo que hay
  que usar para deshacer un `SPtr` cuyo objeto no le llegó a pertenecer, por
  ejemplo cuando falla la operación a la que se iba a entregar.
- **`SPtrEstablecer` sustituye el objeto.** Llama al destructor sobre el
  anterior y se queda con el nuevo, que pasa a ser suyo. Devuelve 1, o 0 si el
  `SPtr` es nulo. Detalles:
  - Establecer **el mismo objeto** que ya tiene no hace nada. Si lo destruyera,
    el `SPtr` se quedaría con un puntero ya liberado.
  - Establecer `NULL` destruye el objeto y deja el `SPtr` **vacío**:
    `SPtrEstaVacio` da 1 y `SPtrEsValido` da 0, igual que recién creado sin
    objeto.
- **El destructor nunca recibe un objeto nulo.** Si el `SPtr` está vacío, ni
  `SPtrDestruir` ni `SPtrEstablecer` lo llaman: no hay nada que destruir. Un
  destructor propio no necesita contemplar el `NULL`.
- `SPtrEstaVacio ( NULL )` devuelve 1, como los `…EstaVacio` del resto de la
  librería.
- `SPtrObjeto` devuelve el puntero interno: no hay que liberarlo, y deja de ser
  válido tras `SPtrDestruir` o `SPtrEstablecer`.
- `SPtrCrearDef` sólo sirve para objetos reservados con `MemReservar` en un único
  bloque. Para una estructura del stack hay que pasar su `S<Pfx>Destruir`
  (convertido a `PRC_DESTRUCTOR`), como hace `SIdPtr` en
  [Identificadores](Identificadores.md).

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md): `MemReservar`,
  `MemLiberar`, `ES_VALIDO` y el tipo `PPRCPPV` de `Funciones.h`.

## Test

`SPtrTest.c` → `TestSPtr()`:

- creación con destructor por defecto y propio (llamado una sola vez, con el
  objeto envuelto) y destrucción doble;
- `SPtrEstablecer` con otro objeto, con el mismo y con `NULL`; sobre un `SPtr`
  vacío, y su destrucción, sin llamar al destructor; más una vuelta con el
  destructor por defecto;
- `SPtrEstaVacio` con objeto y con `NULL`;
- creación sin objeto, con destructor propio y por defecto: vacío, establecer
  después sin llamar al destructor y destruir llamándolo una vez;
- `SPtrPreparar`: vacío con el destructor indicado, que es el que se usa al
  destruir tras establecer; sin destructor devuelve `NULL`;
- `SPtrDestruirSinLiberar`: no llama al destructor, el objeto sigue intacto y
  lo libera el llamante; con argumentos nulos no rompe;
- argumentos nulos: sin destructor no se crea nada.

Con `MODO_DEPURACION`, la vuelta con el destructor por defecto, la creación sin
objeto, `SPtrPreparar` y `SPtrDestruirSinLiberar` comprueban además que no
queda memoria reservada.

## Observaciones

- La estructura es pública, como en el resto del módulo: nada impide cambiar
  `p_vObjeto` o `p_fDestructor` a mano. Si se anula el destructor,
  `SPtrDestruir` libera la estructura pero no el objeto.
- Para **soltar** el objeto sin destruirlo se recupera con `SPtrObjeto` y se
  libera el `SPtr` con `SPtrDestruirSinLiberar`: la propiedad vuelve al
  llamante. Ni `SPtrObjeto` ni `SPtrEstablecer` la transfieren por sí solos.
