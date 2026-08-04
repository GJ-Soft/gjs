# Aplicación: identidad y validaciones

| Dato          | Valor                                                                           |
| ------------- | ------------------------------------------------------------------------------- |
| Cabeceras     | `Aplicacion.h` (fachada), `AplicacionInformacion.h`, `AplicacionValidaciones.h` |
| Fuentes       | `AplicacionInformacion.c`, `AplicacionValidaciones.c`                           |
| Prefijo       | `Aplic`                                                                         |
| Funciones     | 12 + 3                                                                          |
| Incluidos por | `Aplicacion.h`                                                                  |
| Tests         | `AplicacionInformacionTest.c`, `AplicacionValidacionesTest.c`                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Quién es esta aplicación: cómo se llama, qué versión tiene, con qué PID corre y
si está inicializada. Y, aparte, tres validadores de códigos de usuario.

Es el módulo que hay que llamar primero, y el que da sentido a
`AplicImprimirInfoVersion` —la línea de presentación que imprime un programa al
arrancar—.

## `AplicacionInformacion`

### Ciclo de vida

| Función                                                                                   | Descripción                    |
| ----------------------------------------------------------------------------------------- | ------------------------------ |
| `int AplicInicializar ( p_cNombre, iVersion, iSubversion, iRevision, ulFecha, iConsola )` | Registra la identidad.         |
| `void AplicFinalizar ()`                                                                  | Libera y deja sin inicializar. |
| `int AplicEstaInicializada ()`                                                            | Estado.                        |

`iConsola` a 0 cierra la consola con
[`AplicConCerrar`](AplicacionConsola.md): es la forma de declarar que el
programa es de ventanas.

### Consulta

| Función                                              | Descripción                       |
| ---------------------------------------------------- | --------------------------------- |
| `const char * AplicNombre ()`                        | El nombre registrado.             |
| `AplicVersion` / `AplicSubversion` / `AplicRevision` | Los tres números.                 |
| `const char * AplicCadenaVersion ()`                 | La versión como texto.            |
| `SFecha * AplicFechaVersion ()`                      | La fecha, como objeto.            |
| `long AplicValorFechaVersion ()`                     | La fecha, como entero `AAAAMMDD`. |
| `long AplicPID ()`                                   | El PID, cacheado al inicializar.  |
| `void AplicImprimirInfoVersion ()`                   | Imprime la línea de presentación. |

El estado vive en cuatro variables estáticas: nombre, PID, un
[SVersion](SVersion.md) y la bandera de inicialización.

## `AplicacionValidaciones`

| Función                                                   | Regla                                              |
| --------------------------------------------------------- | -------------------------------------------------- |
| `int AplicCodigoValido ( const char * p_cCod, int iTam )` | Longitud **exacta** `iTam`, letras y dígitos.      |
| `int AplicCodigoUsuarioValido ( const char * p_cCod )`    | De 4 a 30, letras, dígitos y `_`.                  |
| `int AplicClaveUsuarioValido ( const char * p_cClave )`   | Hasta 30, letras, dígitos y `_`. **Admite vacía.** |

Las tres exigen además que cada carácter pertenezca al juego principal ASCII
(`ASCIIPerteneceAlJuegoPrincipal`), lo que descarta acentos y cualquier byte por
encima de 127.

## Dependencias

- [SVersion](SVersion.md) — el objeto de versión.
- [SFecha](../../gjs-c-common-time/doc/SFecha.md) — la fecha.
- `SisPID` de
  [SistemaProcesos](../../gjs-c-common-system/doc/SistemaProcesos.md).
- [ASCIIEstandar](../../gjs-c-common-base/doc/ASCIIEstandar.md) — los
  predicados de carácter.

## Tests

`AplicacionInformacionTest.c` → `TestAplicacionInformacion()`,
`AplicacionValidacionesTest.c` → `TestAplicacionValidaciones()`.

## Observaciones

> **`AplicInicializar` intercambia subversión y revisión** en su rama de
> reinicialización:
>
> ```c
> /* la firma es SVerEstablecer ( p_verObj, iVersion, iSubversion, iRevision, lFecha ) */
> SVerEstablecer ( g_p_verAplicInfo, iVersion, iRevision, iSubversion, ulFecha )
> ```
>
> Los dos parámetros son `int`, así que el compilador no dice nada. Hoy la rama
> es inalcanzable —`AplicFinalizar` anula el `SVersion`, de modo que la
> siguiente inicialización vuelve por el `SVerCrear`—, pero el error está
> escrito y saldrá en cuanto alguien toque el ciclo de vida.

- **`AplicInicializar` devuelve 0 tanto si falla como si ya estaba
  inicializada.** No hay forma de distinguir "no había memoria" de "ya lo habías
  llamado"; para lo segundo hay que consultar `AplicEstaInicializada` antes.
- **`AplicClaveUsuarioValido` admite la clave vacía**, y el código lo deja
  anotado (`// NOTA: Se admite clave vacia`). Es una decisión, no un descuido,
  pero conviene saber que este validador no impide una cuenta sin clave.
- **La clave sólo admite letras, dígitos y guion bajo.** Un validador que
  rechaza `.`, `-`, `!` o `$` empuja hacia claves más débiles, justo al revés de
  lo que se pretende. Para el código de usuario la restricción tiene sentido;
  para la clave, no.
- **`AplicCodigoValido` exige longitud exacta**, no máxima, cosa que el nombre
  no sugiere: `AplicCodigoValido ( "AB", 4 )` devuelve 0.
- **El estado es global y no está protegido**, como el de
  [SistemaErrores](../../gjs-c-common-system/doc/SistemaErrores.md). Dos hilos
  que inicialicen a la vez se pisan.
- **`AplicNombre` devuelve el puntero interno**, que `AplicFinalizar` libera:
  guardarlo y usarlo después de finalizar apunta a memoria muerta.
- El error de memoria de `AplicInicializar` está comentado
  (`//ErrEstablecer ( ERR_MEMORIA_INSUFICIENTE, … )`), así que un fallo de
  reserva no deja rastro en
  [Errores](../../gjs-c-common-base/doc/Errores.md).
