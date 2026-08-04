# SFicEstructura

| Dato         | Valor                                           |
| ------------ | ----------------------------------------------- |
| Cabecera     | `src/main/include/SFicEstructura.h`             |
| Fuente       | `src/main/c/org/gjs/c/common/SFicEstructura.c`  |
| Prefijo      | `SFicEst`                                       |
| Struct       | `SFicEstructura`                                |
| Funciones    | 19                                              |
| Incluido por | `Ficheros.h`                                    |
| Test         | `SFicEstructuraTest.c` → `TestSFicEstructura()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Persistir **un bloque de datos de tamaño fijo** en un fichero, con una regla que
lo separa del resto del componente: **el fichero nunca queda abierto**.

Cada operación abre por debajo, hace lo suyo y cierra antes de volver. Entre
llamada y llamada sólo hay memoria. Por eso la API no tiene `Abrir`, `Cerrar` ni
`EstaAbierto`: no hay estado de apertura que consultar.

```c
typedef struct
{
    SFicBloques * p_ficDatos;
    SBloque *     p_blqBufDatos;
} SFicEstructura;
```

Un [fichero de bloques](Bloques.md) de un único bloque —el 0— y un
[SBloque](../../gjs-c-common-base-types/doc/SBloque.md) con su copia en memoria.

## API

### Constructores

Los siete devuelven `SFicEstructura *`. No son operaciones sobre un objeto ya
creado: `Abrir` construye.

| Función                                                          | Descripción                                       |
| ---------------------------------------------------------------- | ------------------------------------------------- |
| `SFicEstCrear ( const char * p_cRuta, int iTamElemento )`        | Crea el fichero. **Si existe, lo borra antes.**   |
| `SFicEstCrearExt ( p_cDir, p_cFic, iTamElemento )`               | Igual, con directorio y nombre por separado.      |
| `SFicEstCrearRuta ( SRuta * p_rutRuta, int iTamElemento )`       | Igual, desde un [SRuta](SRuta.md).                |
| `SFicEstAbrir ( const char * p_cRuta )`                          | Abre uno existente. **No recibe tamaño**: lo lee. |
| `SFicEstAbrirExt ( p_cDir, p_cFic, int * p_iTamElemento )`       | Igual, y **devuelve** el tamaño por el puntero.   |
| `SFicEstAbrirOCrear ( p_cRuta, iTamElemento )`                   | Abre si existe; si no, crea.                      |
| `SFicEstAbrirOCrearExt ( p_cDir, p_cFic, int * p_iTamElemento )` | Igual, con directorio y nombre.                   |

`AbrirOCrear` es la operación característica: para un fichero de estado o de
configuración, lo normal es cargarlo si existe y empezar de cero si no.

El tamaño del elemento se fija **al crear** y queda escrito en el fichero, así
que al abrir no hay que recordarlo. El formato se verifica con un número mágico
propio, `FIC_ESTR_NUM_MAG`.

### Destrucción

| Función                                      | Descripción                                  |
| -------------------------------------------- | -------------------------------------------- |
| `void SFicEstDestruir ( SFicEstructura ** )` | Libera y anula el puntero. El fichero queda. |
| `void SFicEstEliminar ( SFicEstructura ** )` | **Borra el fichero** y luego destruye.       |
| `int SFicEstEsValido ( SFicEstructura * )`   | 1 si es utilizable.                          |

### Contenido

| Función                                              | Descripción                                 |
| ---------------------------------------------------- | ------------------------------------------- |
| `SBloque * SFicEstContenido ( SFicEstructura * )`    | El bloque en memoria. **No es una copia.**  |
| `int SFicEstAsignar ( SFicEstructura *, SBloque * )` | Copia un bloque dentro.                     |
| `int SFicEstLimpiar ( SFicEstructura * )`            | Pone a cero la memoria. No toca el fichero. |
| `int SFicEstGuardarCambios ( SFicEstructura * )`     | **Abre, escribe el bloque y cierra.**       |

`SFicEstGuardarCambios` es la única escritura después de la construcción, y la
que deja ver el ciclo completo abrir-operar-cerrar en una sola llamada.

### Ruta

`SFicEstRuta`, `SFicEstDirectorio`, `SFicEstFichero`, `SFicEstEstablecerRuta`,
`SFicEstEstablecerRutaExt`, todas delegadas en el fichero de bloques.

```c
SFicEstructura * p_ficObj = SFicEstAbrirOCrear ( "estado.dat", sizeof ( MiEstado ) );

if ( SFicEstEsValido ( p_ficObj ) == 1 )
{
    SBloque * p_blqObj = SFicEstContenido ( p_ficObj );
    /* … trabajar sobre el bloque … */
    SFicEstGuardarCambios ( p_ficObj );
}
SFicEstDestruir ( &p_ficObj );
```

## Dependencias

- [SFicBloques](Bloques.md) — el almacenamiento.
- [SBloque](../../gjs-c-common-base-types/doc/SBloque.md) — la copia en memoria.
- [SRuta](SRuta.md) — en `SFicEstCrearRuta`.

## Test

`SFicEstructuraTest.c` → `TestSFicEstructura()`.

## Observaciones

- **El tamaño se fija al crear y no se puede cambiar.** El fichero guarda un
  único bloque, así que una estructura que crezca obliga a recrear el fichero y
  volver a volcar. No hay `Redimensionar`.
- **`SFicEstCrear` borra el fichero existente** (`SisEliminarFichero`) antes de
  crearlo, sin comprobar si el formato coincidía. Para no perder datos hay que
  usar `SFicEstAbrirOCrear`.
- **`SFicEstLimpiar` sólo vacía la memoria.** El fichero conserva el contenido
  anterior hasta que se llame a `SFicEstGuardarCambios`, cosa que el nombre no
  sugiere.
- **`SFicEstContenido` devuelve el bloque interno, no una copia**, y sin `const`:
  quien lo recibe puede modificar el objeto sin pasar por `SFicEstAsignar`. Es lo
  que hace práctico el módulo, pero significa que el bloque no debe sobrevivir al
  `SFicEstDestruir`.
- **La escritura no es transaccional**: si el proceso cae dentro de
  `SFicEstGuardarCambios`, el bloque queda a medias. Al ser una única escritura
  de tamaño fijo el riesgo es pequeño, pero para datos que importen sigue
  conviniendo escribir en otro nombre y renombrar.
- El nombre sugiere que guarda "una estructura", pero lo que persiste es un
  bloque de bytes sin forma: la interpretación queda entera del lado del
  llamante. No hay relación con
  [SDefDato](../../gjs-c-common-base-types/doc/Metadatos.md), que sí describe
  estructuras.
