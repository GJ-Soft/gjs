# Excepcion

| Dato      | Valor                                                       |
| --------- | ----------------------------------------------------------- |
| Cabecera  | `src/main/include/Excepcion.h`                              |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Excepcion.cpp`             |
| Espacio   | `org::gjs::cpp::common`                                     |
| Deriva de | `std::runtime_error`                                        |
| Derivadas | `FinExcepcion`, `NoEncontradoExcepcion`, `SistemaExcepcion` |
| Test      | `ExcepcionTest.cpp`                                         |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una excepción que dice **de dónde viene**. Es la diferencia de fondo con el
stack C, que señala los fallos con `ERROR_ESTABLECER` y valores de retorno que
el llamante puede ignorar.

```cpp
class Excepcion : public std::runtime_error
{
private:
    std::string sModulo;
    std::string sRutina;
    std::string sMensaje;
    std::string sWhat;

public:
    Excepcion ( const std::string & sModulo, const std::string & sRutina, const std::string & sMensaje );
    Excepcion ( const std::string & sModulo, const std::string & sRutina, const std::string & sMensaje, const std::exception & ex );
    Excepcion ( const std::string & sModulo, const std::string & sRutina, const std::exception & ex );

    std::string getModulo () const;
    std::string getRutina () const;
    std::string getMensaje () const;
    const char * what () const noexcept;
    std::string  whatExt () const;
    std::exception & toException ();
};
```

## Los tres constructores

| Forma                             | Para qué                                     |
| --------------------------------- | -------------------------------------------- |
| `( módulo, rutina, mensaje )`     | Un fallo detectado aquí.                     |
| `( módulo, rutina, mensaje, ex )` | Un fallo de más abajo, con contexto añadido. |
| `( módulo, rutina, ex )`          | Un fallo de más abajo, tal cual.             |

Los dos últimos **encadenan**: toman el `what()` de la excepción original y lo
incorporan al mensaje, de modo que al subir por las capas se va acumulando el
rastro. Es lo que en otros lenguajes se llama excepción con causa.

El mensaje final se compone siempre igual:

```
[MiModulo::MiRutina] No se pudo abrir el fichero [datos.txt]
```

```cpp
try
{
    LeerFichero ( sRuta );
}
catch ( std::exception & ex )
{
    throw Excepcion ( "MiModulo", "Cargar", "No se pudo leer la configuracion", ex );
}
```

## Dependencias

`<stdexcept>` y `Concatenar` del propio componente.

## Test

`ExcepcionTest.cpp` → `TestExcepcion()`.

## Observaciones

- **`what()` está redefinida y no es `virtual` en la cabecera.** Lo es de
  hecho, por heredarla de `std::exception`, pero declararla sin `virtual` ni
  `override` hace que el lector no sepa si está redefiniendo o tapando. Con
  `override` el compilador además avisaría de cualquier desajuste de firma.
- **`whatExt()` y `what()` devuelven lo mismo.** El cuerpo de las dos es
  `sWhat`, una en `std::string` y otra en `const char *`. El nombre `Ext`
  sugiere información añadida que no hay: la diferencia real es sólo el tipo de
  retorno, y evitar el `c_str()` en el llamante.
- **`sMensaje` y el mensaje de `runtime_error` divergen** en el segundo
  constructor: a la base se le pasa `_sMensaje` a secas y a `sMensaje` se le
  añade el `what()` de la excepción original. Quien capture por
  `std::runtime_error &` en vez de por `Excepcion &` ve un mensaje distinto —y
  sin el `[modulo::rutina]`—, que es justo el caso de código ajeno al stack.
- **Los cuatro campos se asignan en el cuerpo del constructor**, no en la lista
  de inicialización. Con `std::string` eso construye vacío y después asigna;
  no es incorrecto, pero es trabajo de más en el camino de una excepción.
- **No hay constructor de copia declarado** y sí hay estado propio. Funciona por
  el implícito, pero lanzar y capturar excepciones copia el objeto, y el
  contrato conviene dejarlo escrito.
- **No hay `Excepcion` para argumentos inválidos** aquí, pese a ser el caso más
  común; sí existe `ArgumentoInvalidoExcepcion`, pero en
  [gjs-cpp-common](../../gjs-cpp-common/README.md), cinco componentes más
  arriba. Las cuatro clases de esta familia estarían mejor juntas.
- **`toException()` devuelve `std::exception &` a partir del propio objeto**, lo
  que no añade nada que no dé una conversión implícita a la base, y en cambio
  invita a guardar la referencia más allá del `catch`.
