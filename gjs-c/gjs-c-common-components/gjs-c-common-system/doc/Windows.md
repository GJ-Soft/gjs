# Módulos sólo de Windows

| Dato          | Valor                                                                                  |
| ------------- | -------------------------------------------------------------------------------------- |
| Módulos       | 2 + 2 cabeceras                                                                        |
| Cabeceras     | `SistemaRegistro.h`, `RegistroConstantes.h`, `SistemaImpresoras.h`, `EntornoWindows.h` |
| Prefijos      | `SisReg`, `Sis`                                                                        |
| Funciones     | 54 + 2                                                                                 |
| Incluidos por | `Sistema.h` (`SistemaRegistro.h` sólo si `WIN`)                                        |
| Tests         | `SistemaImpresorasTest.c` (`SistemaRegistro` no tiene)                                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Lo que no tiene equivalente fuera de Windows y por tanto no se ha intentado
portar: el registro y la impresión.

A diferencia del resto del componente, aquí no hay rama `#else` con un
`PENDIENTE`: **el contenido entero está dentro de `#if ( defined ( WIN ) )`**, y
en el modo normal las cabeceras quedan vacías.

```c
#if ( defined ( WIN ) )
int SisImpresionPosible ();
int SisImprimir ( const char * p_cTexto );
#endif
```

Es la solución honesta: si la función no existe, que el compilador lo diga en el
`#include`, en lugar de devolver 0 y dejar al llamante creyendo que ha
funcionado.

## `SistemaRegistro` — el registro de Windows

54 funciones en 1.871 líneas, organizadas en dos niveles.

### Nivel alto: por nombre de clave

| Función                                                          | Descripción                   |
| ---------------------------------------------------------------- | ----------------------------- |
| `SisRegExisteClave` / `SisRegCrearClave` / `SisRegEliminarClave` | Sobre `HKEY_LOCAL_MACHINE`.   |
| `…ClaveExt`                                                      | Con clave principal a elegir. |
| `SisRegObtValorCadena` / `SisRegObtValorNumerico`                | Lectura.                      |
| `SisRegEstValorCadena` / `SisRegEstValorNumerico`                | Escritura.                    |
| `SisRegCrearValorCadena` / `SisRegCrearValorNumerico`            | Creación.                     |
| Las seis anteriores con sufijo `Ext`                             | Con clave principal.          |

La clave principal se elige con las constantes de `RegistroConstantes.h`:

| Constante                | Valor | Equivale a            |
| ------------------------ | ----- | --------------------- |
| `REG_CLV_CLASSES_ROOT`   | 0     | `HKEY_CLASSES_ROOT`   |
| `REG_CLV_CURRENT_CONFIG` | 1     | `HKEY_CURRENT_CONFIG` |
| `REG_CLV_CURRENT_USER`   | 2     | `HKEY_CURRENT_USER`   |
| `REG_CLV_LOCAL_MACHINE`  | 3     | `HKEY_LOCAL_MACHINE`  |
| `REG_CLV_USERS`          | 4     | `HKEY_USERS`          |

Sin sufijo `Ext` se asume `REG_CLV_LOCAL_MACHINE`.

### Nivel bajo: por `HKEY`

`SisRegCrear`, `SisRegAbrir`, `SisRegCerrar`, `SisRegEsClaveValida`,
`SisRegNumSubclaves`, `SisRegNumValores`, `SisRegExisteSubclave`,
`SisRegExisteValor`, `SisRegEliminarSubclave`, `SisRegEliminarTodasSubclaves`,
`SisRegConsultarClave`, `SisRegEstablecerClave`, `SisRegConsultarValor`,
`SisRegEstablecerValor`, `SisRegEliminarValor`, `SisRegEliminarTodosValores`,
`SisRegEliminarContenido`, y sus variantes `Ent` para valores numéricos.

Más `SisRegImportarFichero` y `SisRegExportarFichero`.

### Registro COM

Cinco funciones para dar de alta componentes COM, que es para lo que se escribió
todo lo anterior:

| Función                                                       | Descripción                     |
| ------------------------------------------------------------- | ------------------------------- |
| `SisRegistrarModulo ( guidModulo, p_cFicModulo, p_cVersion )` | Registra una librería de tipos. |
| `SisRegistrarGUID ( guidCodigo, nombre, descripcion, … )`     | Registra una clase.             |
| `SisRegDesregistrarModulo` / `SisRegDesregistrarGUID`         | Las da de baja.                 |
| `SisRegEstaRegistradoModulo` / `SisRegEstaRegistradoGUID`     | Consulta.                       |

`RegistroConstantes.h` acompaña con los nombres de las claves COM
(`CLSID`, `TypeLib`, `InprocServer32`, `ProgId`, `ThreadingModel`,
`ImplementedCategories`, `VersionIndependentProgId`, `CURVER`) y los límites:
`REG_MAX_TAM_GUID` (38), `REG_MAX_TAM_CLAVE` (63), `REG_MAX_TAM_VALOR` (1023),
`REG_MAX_NIVELES` (10).

## `SistemaImpresoras`

| Función                                     | Descripción                    |
| ------------------------------------------- | ------------------------------ |
| `int SisImpresionPosible ()`                | 1 si hay impresora disponible. |
| `int SisImprimir ( const char * p_cTexto )` | Imprime un texto.              |

93 líneas para dos funciones. Su test existe y pasa en el modo normal porque no
hay nada que probar.

## `EntornoWindows.h`

**Vacía.** Trece líneas que son sólo la cabecera de comentario del fichero: sin
guardián de inclusión, sin constantes y sin declaraciones. Ninguna otra cabecera
la incluye. Es un fichero que quedó del diseño original y nunca se rellenó.

## Dependencias

La API de Windows: `advapi32` para el registro, `winspool` para la impresión.

## Tests

`SistemaImpresorasTest.c` → `TestSistemaImpresoras()`.
`SistemaRegistro` **no tiene test**, y es el segundo módulo más grande del
componente.

## Observaciones

- **`SistemaRegistro` no tiene test.** 1.871 líneas y 54 funciones que escriben
  en el registro del sistema —incluida `SisRegEliminarTodasSubclaves`— sin una
  sola comprobación automática. Se entiende que probarlo requiere permisos y
  ensuciar la máquina, pero es el módulo donde un fallo hace más daño.
- **`SisRegObtValorCadena` devuelve `const char *`** mientras que el resto del
  stack devuelve `char *` reservado en las funciones equivalentes. Si apunta a un
  búfer estático, dos lecturas seguidas se pisan; si está reservado, no hay quien
  lo libere. La cabecera no lo aclara.
- **`SisRegConsultarValor` recibe el destino como `const char *`** y a la vez lo
  usa como búfer de salida (`p_cValor, uiMaxTamValor`). El `const` es incorrecto:
  la función escribe ahí.
- **`REG_MAX_TAM_CLAVE` vale 63**, cuando Windows permite 255 caracteres por
  nombre de clave, y `REG_MAX_NIVELES` fija 10 niveles de profundidad sin que
  Windows imponga ese límite. Son restricciones propias, no del sistema.
- **El registro COM apunta a una tecnología en retirada.** `ThreadingModel`,
  `InprocServer32` y el registro por `CLSID` siguen funcionando, pero es la parte
  del componente más atada a su época.
- **`EntornoWindows.h` debería borrarse o rellenarse.** Tal cual, es una cabecera
  publicada en el NAR `noarch` que no aporta nada, y sin guardián de inclusión.
