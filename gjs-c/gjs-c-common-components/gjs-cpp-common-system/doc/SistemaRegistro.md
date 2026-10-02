# SistemaRegistro

| Dato          | Valor                                                                |
| ------------- | -------------------------------------------------------------------- |
| Fuente        | `src/main/c++/org/gjs/cpp/common/SistemaRegistro.cpp` (1.060 líneas) |
| Cabecera      | `src/main/include/SistemaRegistro.h`, más `RegistroConstantes.h`     |
| Espacio       | `org::gjs::cpp::common`                                              |
| Prefijo       | `SisReg`                                                             |
| En la fachada | sí (`CppCommonSystem.h`)                                             |
| Test          | **—**                                                                |

[Índice](MODULOS.md) · [README](../README.md)

---

## Qué es

El acceso al **registro de Windows**: crear y borrar claves, leer y escribir
valores de cadena y numéricos.

```cpp
bool SisRegExisteClave ( const std::string & sClave, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegCrearClave ( const std::string & sClave, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegEliminarClave ( const std::string & sClave, int iClavePrinc = REG_CLV_LOCAL_MACHINE );

std::string SisRegObtValorCadena ( const std::string & sClave, const std::string & sValor, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
unsigned long SisRegObtValorNumerico ( const std::string & sClave, const std::string & sValor, int iClavePrinc = REG_CLV_LOCAL_MACHINE );

bool SisRegEstValorCadena ( const std::string & sClave, const std::string & sValor, const std::string & sDato, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegEstValorNumerico ( const std::string & sClave, const std::string & sValor, unsigned long ulDato, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
```

Son 45 funciones públicas. Es el segundo fichero más grande del componente,
detrás de `SistemaProcesos.cpp`.

---

## Qué le pasaba, y cómo quedó

**Resuelto el 2026-09-14.** El fichero no compilaba: incluía
`"SistemaRegistro.h"`, que no existía en este módulo, y además era el fuente de
la versión C copiado sin convertir —cero espacios de nombres, cero
`std::string`, 46 `char *`—. No saltaba en el build porque otros ficheros del
componente abortaban la compilación antes de que le llegara el turno.

La cabecera se recuperó de la librería original y se adaptó al idioma del
módulo, y el fuente se convirtió entero.

| Medida | Antes | Después |
| --- | --- | --- |
| Líneas | 1.861 | 1.060 |
| Espacios de nombres | 0 | 4 anidados |
| `char *` | 46 | 0 |
| Errores de compilación | 91 | 0 |

Se trajo también `RegistroConstantes.h`, que sólo estaba en el stack C y del que
el fuente usa 26 constantes.

### Lo que cambió en la API

- Las cadenas entran por `const std::string &` y salen por valor.
- El `int` de cierto/falso pasa a `bool`.
- Los pares `Xxx` / `XxxExt` de la cabecera de 2008 se funden en una sola
  función con `int iClavePrinc = REG_CLV_LOCAL_MACHINE`. La implementación ya las
  tenía fundidas desde hacía tiempo: la cabecera iba por detrás.
- `SisRegConsultarClave` y `SisRegConsultarValor` pierden el `uiMaxTamValor` y
  devuelven el dato por parámetro de salida.
- `EstaRegistradoGUID` pasa a llamarse `SisRegEstaRegistradoGUID`.
- Pasar un dato nulo a `SisRegEstValorCadena` ya no borra el valor; para eso
  está `SisRegEliminarValor`.

### El ProgId, resuelto el 2026-09-16

`SisRegRegistrarGUID` escribe el ProgId como `ficheroModulo.nombre`, pero
`SisRegDesregistrarGUID` y `SisRegEstaRegistradoGUID` lo reconstruían como
`nombre.nombre`, porque en su firma no entraba el fichero del módulo: no
encontraban nada de lo que había registrado la primera salvo que nombre y fichero
coincidieran por casualidad.

Las dos reciben ahora `sFicModulo` como último parámetro:

```cpp
void SisRegDesregistrarGUID ( const GUID & guidCodigo, const std::string & sNombre,
							  const std::string & sFicModulo );
bool SisRegEstaRegistradoGUID ( const GUID & guidCodigo, const std::string & sNombre,
								const std::string & sFicModulo );
```

El mismo cambio se aplicó al stack **C**, que tenía el defecto idéntico. Allí,
además, la cabecera declaraba `SisRegEstaRegistradoGUID` con un solo parámetro
mientras la implementación se llamaba `EstaRegistradoGUID`, sin el prefijo: ni
casaban ni había forma de llegar a ella desde fuera. Ahora sí.
que se arreglen los que van delante.

---

## Qué hacer con él

Tres salidas, de menos a más trabajo:

1. **Sacarlo del árbol de fuentes.** Si el registro de Windows no hace falta en
   el stack C++, el fichero sobra: quitarlo desbloquea la compilación sin perder
   nada que hoy funcione. Es lo que corresponde si nadie lo echaba de menos —y
   nadie puede echarlo de menos, porque no hay cabecera que lo declare.
2. **Escribir la cabecera y dejarlo como está**, en C, dentro de un
   `#if defined ( WIN )`. Compilaría, y quedaría el único módulo del componente
   fuera del espacio de nombres y con `char *` en la API pública.
3. **Convertirlo**, como se hizo con los demás: espacio de nombres,
   `std::string`, y `bool` donde hoy hay `int`. Son 1.861 líneas de llamadas a
   la API de registro de Windows; el trabajo es mecánico pero largo, y sólo
   sirve en una de las tres plataformas.

La primera es la única que no cuesta nada, y es reversible: el fichero está en
el repositorio y se puede recuperar.

---

## Observaciones

- **Nada lo declara, así que nada lo usa.** Ni la fachada, ni ningún `.cpp` del
  componente, ni ningún test. Es código muerto que además impide compilar.
- **`SisRegObtValorCadena` devuelve `const char *`** sin decir quién libera la
  cadena ni cuánto vive. Es el patrón de la versión C, y es la primera cosa que
  habría que cambiar si se decide convertirlo.
- **`SisRegClavePrincipal` es `static`** y traduce un `int` a un `HKEY`, de modo
  que la API pública no expone tipos de Windows. Ese acierto de diseño es lo
  único del fichero que sobreviviría intacto a la conversión.
