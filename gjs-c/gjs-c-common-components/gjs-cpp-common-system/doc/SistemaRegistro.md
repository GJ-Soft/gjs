# SistemaRegistro

| Dato          | Valor                                                                |
| ------------- | -------------------------------------------------------------------- |
| Fuente        | `src/main/c++/org/gjs/cpp/common/SistemaRegistro.cpp` (1.861 líneas) |
| Cabecera      | **no existe**                                                        |
| Espacio       | **ninguno**                                                          |
| Prefijo       | `SisReg`                                                             |
| En la fachada | no                                                                   |
| Test          | **—**                                                                |

[Índice](MODULOS.md) · [README](../README.md)

---

## Qué es

El acceso al **registro de Windows**: crear y borrar claves, leer y escribir
valores de cadena y numéricos.

```c
int SisRegExisteClave ( const char * p_cClave, int iClavePrinc );
int SisRegCrearClave ( const char * p_cClave, int iClavePrinc );
int SisRegEliminarClave ( const char * p_cClave, int iClavePrinc );

const char * SisRegObtValorCadena ( const char * p_cClave, const char * p_cValor, int iClavePrinc );
unsigned long SisRegObtValorNumerico ( const char * p_cClave, const char * p_cValor, int iClavePrinc );

int SisRegEstValorCadena ( const char * p_cClave, const char * p_cValor, const char * p_cDato, int iClavePrinc );
int SisRegEstValorNumerico ( const char * p_cClave, const char * p_cValor, unsigned long ulDato, int iClavePrinc );
```

Es el fichero más grande del componente.

---

## Qué le pasa

**No puede compilar.** Su segunda línea es:

```cpp
#include "SistemaRegistro.h"
```

y esa cabecera **no existe en este módulo**. Las comillas hacen que el
preprocesador busque primero en el directorio del propio fichero
—`src/main/c++/org/gjs/cpp/common/`, donde sólo está `CommonSystemConfig.h`— y
después en las rutas de inclusión, que son `src/main/include` de este módulo y
los `include` publicados por sus cuatro dependencias. En ninguna está.

Los únicos `SistemaRegistro.h` del repositorio pertenecen al **stack C**, dentro
de árboles `target/` de los arquetipos. El módulo C++ no depende del C, así que
no llegan.

### Y además no está convertido

Tres medidas sobre el fichero dicen lo mismo:

| Medida                         | `SistemaRegistro.cpp` | El resto del componente |
| ------------------------------ | --------------------- | ----------------------- |
| Espacios de nombres declarados | **0**                 | 4 anidados              |
| Usos de `std::string`          | **0**                 | por todas partes        |
| Usos de `char *`               | **37**                | residuales              |

Es el fuente de la versión C copiado tal cual al árbol C++: mismas firmas con
`const char *`, mismo estilo de retorno con `int` como código, y sin envolver en
`org::gjs::cpp::common`.

### Por qué no salta en el build

El `output.txt` del 9 de julio **no lo menciona ni una vez**. La razón está en
las últimas líneas del log: los errores de `SistemaComandos.cpp` y
`SistemaInformacion.cpp` abortaron la compilación —«Core 0 interrupted», «Core 6
interrupted»…— antes de que le llegara el turno. El fallo sigue ahí, esperando a
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
