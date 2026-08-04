# Versiones

| Dato         | Valor                                     |
| ------------ | ----------------------------------------- |
| Cabecera     | `src/main/include/Versiones.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Versiones.c` |
| Prefijo      | `Vers`, `VERS_`                           |
| Incluido por | `Base.h`                                  |
| Test         | `VersionesTest.c` → `TestVersiones()`     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Construir e interpretar cadenas de versión con hasta cuatro niveles:
**versión.subversión.revisión.corrección**.

## API

### Patrones

| Constante    | Valor           |
| ------------ | --------------- |
| `VERS_PAT_1` | `"%d"`          |
| `VERS_PAT_2` | `"%d.%d"`       |
| `VERS_PAT_3` | `"%d.%d.%d"`    |
| `VERS_PAT_4` | `"%d.%d.%d.%d"` |

### Funciones

| Función                                                                                                                      | Descripción                             |
| ---------------------------------------------------------------------------------------------------------------------------- | --------------------------------------- |
| `char * VersCadena ( int iVersion, int iSubversion, int iRevision, int iCorreccion )`                                        | Compone la cadena. **Reserva memoria.** |
| `int VersProcesar ( const char * p_cCadena, int * p_iVersion, int * p_iSubversion, int * p_iRevision, int * p_iCorreccion )` | Descompone la cadena. Devuelve 1/0.     |

## Comportamiento

### `VersCadena`

El número de niveles que se emiten lo decide el **primer argumento negativo**: se
recorren en orden y se corta ahí.

```c
VersCadena ( 1,  0,  0,  2 );   /* "1.0.0.2" */
VersCadena ( 1,  0,  0, -1 );   /* "1.0.0"   */
VersCadena ( 1,  0, -1, -1 );   /* "1.0"     */
VersCadena ( 1, -1, -1, -1 );   /* "1"       */
VersCadena ( -1, 0,  0,  0 );   /* NULL + ERR_PARAMETROS */
```

Un `iVersion` negativo es error: devuelve `NULL` y anota `ERR_PARAMETROS`.

Obsérvese que el corte es posicional: `VersCadena ( 1, -1, 3, 4 )` produce
`"1"`, no `"1.?.3.4"`.

La cadena devuelta se **reserva con `MemReservar`** (vía `CadCrear` +
`CadDuplicar`) y es propiedad del llamante: hay que liberarla con
`MemLiberar` / `MemLiberarCadena`.

### `VersProcesar`

Usa `sscanf` con `VERS_PAT_4` y cuenta cuántos campos ha logrado leer. Sólo
escribe en los punteros de salida correspondientes a campos realmente leídos, y
además sólo si el puntero es válido: se puede pasar `NULL` en los que no
interesen.

```c
int iMayor = 0;
int iMenor = 0;

if ( VersProcesar ( "1.4.2", &iMayor, &iMenor, NULL, NULL ) == 1 )
{
    /* iMayor = 1, iMenor = 4 */
}
```

Devuelve `1` si leyó al menos un campo, y `0` con `ERR_PARAMETROS` si el puntero
de entrada es nulo o no se pudo leer ninguno.

**Los campos ausentes no se tocan**: conservan el valor que tuvieran antes de la
llamada, así que conviene inicializarlos.

## Dependencias

- [Memoria](Memoria.md) — reserva de la cadena.
- [CadenasBase](CadenasBase.md) — `CadCrear`, `CadDuplicar`.
- [Errores](Errores.md) — `ERROR_ESTABLECER`.

## Test

`VersionesTest.c` → `TestVersiones()`.

## Observaciones

- `VersCadena` reserva un buffer auxiliar con `CadCrear`, escribe con `sprintf` y
  después **duplica** el resultado con `CadDuplicar` para ajustar el tamaño. El
  buffer auxiliar se libera al terminar. El dimensionado (11 caracteres para el
  primer nivel y 12 por cada nivel adicional) cubre el peor caso de un `int`.
- Se llama a `sprintf` pasando siempre los cuatro enteros aunque el patrón
  consuma menos. Es legal en C (los argumentos sobrantes se ignoran), pero es
  frágil.
- `VersProcesar` no valida el formato: acepta cualquier cadena que empiece por un
  número. `"1.4.2-RC.2"` se lee como versión 1, subversión 4, revisión 2, e
  ignora el resto sin avisar. Para las versiones tipo semver del propio proyecto
  (`1.0.0-RC.2`) eso significa que el sufijo se pierde.
- No hay rutina de comparación de versiones.
