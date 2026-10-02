# Hash

| Dato         | Valor                                |
| ------------ | ------------------------------------ |
| Cabecera     | `src/main/include/Hash.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Hash.c` |
| Prefijo      | `Hash`                               |
| Incluido por | `Base.h`                             |
| Test         | `HashTest.c` → `TestHash()`          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Función hash de propósito general para los tipos básicos de la librería,
pensada para indexar tablas asociativas en las capas superiores. Devuelve
siempre un `unsigned int`.

## API

| Función                                                                   | Entrada                  |
| ------------------------------------------------------------------------- | ------------------------ |
| `unsigned int HashByte ( byte byVal )`                                    | un byte                  |
| `unsigned int HashCaracter ( char cVal )`                                 | un carácter              |
| `unsigned int HashBinario ( byte * p_byVal, int iTam )`                   | bloque de memoria        |
| `unsigned int HashEntero ( int iVal )`                                    | `int`                    |
| `unsigned int HashEnteroLargo ( long lVal )`                              | `long`                   |
| `unsigned int HashEnteroSinSigno ( unsigned int uiVal )`                  | `unsigned int`           |
| `unsigned int HashEnteroLargoSinSigno ( unsigned long ulVal )`            | `unsigned long`          |
| `unsigned int HashEnteroDobleLargo ( long long llVal )`                   | `long long`              |
| `unsigned int HashEnteroDobleLargoSinSigno ( unsigned long long ullVal )` | `unsigned long long`     |
| `unsigned int HashReal ( float fVal )`                                    | `float`                  |
| `unsigned int HashRealDoble ( double dVal )`                              | `double`                 |
| `unsigned int HashCadena ( const char * p_cVal )`                         | cadena terminada en cero |

### El tipo `PFUNHASH`

La cabecera define además `PFUNHASH`, alias de `PFUNUINTPV`
([Funciones.h](MODULOS.md#funcionesh)), es decir `unsigned int (*)(void *)`: el
mismo retorno que toda la familia `Hash*`. Es el tipo del *callback* con el que
una capa superior encargaría el hash de un contenido opaco. Como el argumento es
genérico, asignarle una función que tome un puntero concreto —`HashCadena`, con
su `const char *`— exige un cast en el punto de asignación.

**Hoy no lo usa nadie.** Lo usaban los `SEnt*Hash` de `gjs-c-common-types`, que
recibían uno para meter el contenido en el reparto; el parámetro se quitó porque
el hash tiene que mirar lo mismo que `EsIgual`, y el contenido no forma parte de
la identidad. El `typedef` se mantiene por si vuelve a hacer falta.

## Comportamiento

### El núcleo: `HashBinario`

Todas las variantes salvo `HashByte` y `HashCaracter` reinterpretan su argumento
como un bloque de bytes y delegan en `HashBinario`. Es una variante del esquema
**Pearson** con cuatro carriles:

1. Una tabla estática `_hash_table` de 256 bytes, permutación fija de 0-255.
2. Se mantiene un acumulador `h` de `sizeof ( unsigned int )` bytes (4 carriles).
3. El primer byte inicializa el carril 0 a través de la tabla.
4. Cada byte siguiente entra en el carril `i % 4`: se combina por XOR con el
   valor actual del carril y, si no es el carril 0, también con el carril
   anterior (difusión entre carriles), y el resultado indexa la tabla.
5. El hash final es la concatenación de los cuatro carriles en un
   `unsigned int`, con el carril 0 en el byte bajo.

`HashByte` no pasa por ahí: es la consulta directa a la tabla, así que devuelve
siempre un valor entre 0 y 255.

### Casos límite

- Puntero nulo o `iTam <= 0` → devuelve **0**, sin anotar error.
- `HashCadena` usa `CadLongitud`, así que hereda el tope `CAD_BASE_MAX_TAM`
  (8191): sólo se consideran los primeros 8191 caracteres. Además **no incluye el
  terminador** en el hash.

### Advertencias de uso

- El hash de los tipos numéricos se calcula sobre su **representación en
  memoria**, no sobre su valor. Es decir: depende del *endianness* y del tamaño
  del tipo en la plataforma. Un mismo `long` no da el mismo hash en 32 y en 64
  bits, y `HashEntero ( 1 )` y `HashEnteroLargo ( 1 )` tampoco coinciden. **No
  sirve para persistir ni para intercambiar entre máquinas.**
- `HashReal` sufre además la ambigüedad del punto flotante: `+0.0` y `-0.0` tienen
  representaciones distintas, y cualquier `NaN` da resultados arbitrarios.
- No es una función hash criptográfica.

## Dependencias

- [Memoria](Memoria.md) — sólo por `ES_VALIDO`.
- [CadenasBase](CadenasBase.md) — `CadLongitud` en `HashCadena`.
- `Funciones.h` — incluida por la cabecera, para `PFUNUINTPV`.

## Test

`HashTest.c` → `TestHash()`.

## Observaciones

- `HashBinario` usa un array de longitud variable (`byte h[ iTamHash ]`) cuyo
  tamaño es en realidad una constante de compilación; podría declararse como tal.
- El valor 0 tiene doble significado: es tanto el hash de una entrada inválida
  como un hash legítimo posible.
