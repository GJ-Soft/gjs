# SPropiedades

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/SPropiedades.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SPropiedades.c` |
| Prefijo      | `SProp`                                      |
| Struct       | `SPropiedades`                               |
| Funciones    | 12                                           |
| Incluido por | `Aplicacion.h`                               |
| Test         | `SPropiedadesTest.c` → `TestSPropiedades()`  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un fichero de configuración `clave=valor`, con carga y guardado. Es el
`.properties` de toda la vida.

```c
typedef struct
{
    SListaLiterales * p_lislitClaves;
    SListaEntradas *  p_lisentPropiedades;
} SPropiedades;
```

Dos contenedores en paralelo: las
[entradas](../../gjs-c-common-types/doc/Entradas.md) guardan clave y valor, y la
[lista de literales](../../gjs-c-common-base-types/doc/Listas.md) mantiene las
claves **en orden de inserción**, que es lo que la lista de entradas no da.

## API

### Ciclo de vida

| Función                                              | Descripción                           |
| ---------------------------------------------------- | ------------------------------------- |
| `SPropiedades * SPropCrearDef ()`                    | Vacío.                                |
| `SPropiedades * SPropCrear ( const char * p_cRuta )` | Vacío y **cargado** desde el fichero. |
| `void SPropDestruir ( SPropiedades ** )`             | Destrucción.                          |

### Propiedades

| Función                                                                  | Descripción                       |
| ------------------------------------------------------------------------ | --------------------------------- |
| `const char * SPropObtPropiedad ( p_propObj, p_cClave )`                 | El valor, o `NULL`.               |
| `const char * SPropObtPropiedadExt ( p_propObj, p_cClave, p_cValorDef )` | Con valor por defecto.            |
| `int SPropEstPropiedad ( p_propObj, p_cClave, p_cValor )`                | Fija o crea.                      |
| `int SPropExistePropiedad ( p_propObj, p_cClave )`                       | 1 si está.                        |
| `void SPropEliminarPropiedad ( p_propObj, p_cClave )`                    | La quita de los dos contenedores. |
| `int SPropNumPropiedades ( p_propObj )`                                  | Cuántas hay.                      |
| `SListaLiterales * SPropPropiedades ( p_propObj )`                       | Las claves, en orden.             |

`SPropObtPropiedadExt` es la que se usa en la práctica: devuelve el valor por
defecto cuando la clave no está, sin obligar a comprobar antes.

### Fichero

| Función                                                | Descripción     |
| ------------------------------------------------------ | --------------- |
| `int SPropCargar ( p_propObj, const char * p_cRuta )`  | Lee el fichero. |
| `int SPropGuardar ( p_propObj, const char * p_cRuta )` | Lo reescribe.   |

## El formato

```
nombre=MiPrograma
ruta=/var/datos
margen="  "
```

- La clave es lo que hay antes del **primer** `=`; el valor, lo que hay después.
- Los blancos de los extremos se recortan en clave y valor.
- Un valor que empiece o acabe en espacio se guarda **entre comillas dobles**, y
  al cargar se le quitan. Es lo que permite conservar un valor como `"  "`.
- Una línea sin `=` se ignora.

## Dependencias

- [SListaEntradas](../../gjs-c-common-types/doc/Entradas.md) — clave y valor.
- [SListaLiterales](../../gjs-c-common-base-types/doc/Listas.md) — el orden.
- [SFicTexto](../../gjs-c-common-io/doc/FicherosBasicos.md) — el fichero.

## Test

`SPropiedadesTest.c` → `TestSPropiedades()`.

## Observaciones

> **Tres fugas de memoria.**
>
> 1. `SPropCargar` crea un `SFicTexto` con `SFicTxtCrear`, lo cierra con
>    `SFicTxtCerrar` y **nunca llama a `SFicTxtDestruir`**. El objeto y su ruta
>    se pierden en cada carga.
> 2. `SPropGuardar` hace exactamente lo mismo.
> 3. `_ParsearPropiedad`, al quitar las comillas de un valor, se pisa el puntero:
>
>    ```c
>    *p_p_cValor = CadExtraer ( *p_p_cValor, 1, CadLongitud ( *p_p_cValor ) - 2 );
>    ```
>
>    `CadExtraer` reserva una cadena nueva y el búfer anterior queda sin
>    liberar. Ocurre una vez por cada valor entrecomillado del fichero.
>
> Las tres son de las que no dan la cara: el programa funciona, sólo consume de
> más. La primera pesa en un proceso que recargue su configuración
> periódicamente.

- **No hay comentarios en el formato.** Ni `#` ni `;`: `_EsPropiedad` sólo mira
  si hay un `=` a partir de la posición 1. Una línea `# tiempo=30` se carga como
  la propiedad `# tiempo` con valor `30`, y al guardar sale sin el `#`. Una
  línea de comentario sin `=` se descarta en silencio, así que **guardar un
  fichero cargado pierde todos sus comentarios**.
- **`_EsPropiedad` y `_ParsearPropiedad` no son estáticas.** Son símbolos
  globales exportados por la librería, y además empiezan por guion bajo, que el
  estándar de C reserva para la implementación. Deberían ser `static`.
- **Las dos modifican la línea recibida** con `CadFormatearBlancos`, y
  `SPropCargar` las llama en cadena, de modo que la línea se reformatea dos
  veces. No hace daño, pero la firma `char *` en lugar de `const char *` no
  advierte de que el parámetro se toca.
- **`SPropPropiedades` devuelve la lista interna**, no una copia: quien la reciba
  puede insertar o borrar claves y dejar los dos contenedores descuadrados.
- **Los dos contenedores se mantienen a mano**, y sólo `SPropEstPropiedad` y
  `SPropEliminarPropiedad` los tocan a la vez. `SPropEliminarPropiedad` además
  no comprueba el resultado de `SLisLitBuscar` antes de pasárselo a
  `SLisLitEliminarElem`.
- **`SPropGuardar` abre en `MOD_APR_REESCRITURA`**, así que trunca el fichero
  nada más abrirlo: un fallo a media escritura deja la configuración a medias y
  sin copia. Conviene escribir a un temporal y renombrar.
- **`SPropCargar` no informa de las líneas mal formadas.** Lleva la cuenta en
  `iNumLinea` y no la usa para nada.
- `SPropCrear ( p_cRuta )` devuelve un objeto válido aunque el fichero no exista:
  ignora el resultado de `SPropCargar`. Es razonable —un fichero de
  configuración que aún no está— pero no se distingue de un fichero ilegible.
