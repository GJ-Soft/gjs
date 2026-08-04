# Depurador

| Dato      | Valor                                           |
| --------- | ----------------------------------------------- |
| Cabecera  | `src/main/include/Depurador.h` (78 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Depurador.cpp` |
| Espacio   | `org::gjs::cpp::common`                         |
| Deriva de | [`Objeto`](Objeto.md)                           |
| Test      | **Ninguno**                                     |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Llevar la cuenta de los objetos vivos, su dirección y su tamaño, para perseguir
fugas de memoria. **Sólo existe en compilaciones de depuración**: casi todo su
contenido está dentro de `#if ( defined ( MODO_DEPURACION ) )`.

```cpp
class Depurador : public Objeto
{
private:
#  if ( defined ( MODO_DEPURACION ) )
    int    iObjetos;
    void * p_vDirObjeto;
    int    iTamObjeto;
    int    iEliminando;
    int    iError;
#  endif

public:
    Depurador ();
    virtual ~Depurador ();

#  if ( defined ( MODO_DEPURACION ) )
    bool   EsTipo ( const char * p_cNombre );
    bool   EsTipo ( const std::string & sNombre );
    int    NumObjetos ();
    void * DireccionObjeto ();
    int    Error ();
    void   EstablecerError ( int iError );
    void   LimpiarError ();

protected:
    void   ActualizarObjeto ( const std::string & sNombre, void * p_vDirObj, int iTamObj );
#  endif

    void GesClsImprimirEstado ();
};
```

En el modo normal la clase se queda en constructor, destructor y
`GesClsImprimirEstado`: hereda de `Objeto` y no añade ni un campo.

## La API de depuración

| Método                                  | Qué da                                                       |
| --------------------------------------- | ------------------------------------------------------------ |
| `EsTipo ( … )`                          | Si el objeto es del tipo que se le nombra.                   |
| `NumObjetos ()`                         | Cuántas instancias vivas hay.                                |
| `DireccionObjeto ()`                    | Dónde está.                                                  |
| `Error ()` / `Establecer…` / `Limpiar…` | Un código de error asociado.                                 |
| `ActualizarObjeto ( … )`                | El gancho protegido que registra nombre, dirección y tamaño. |
| `GesClsImprimirEstado ()`               | Vuelca el estado.                                            |

Va de la mano de [InfoMemoria](Memoria.md), que también vive entero bajo
`MODO_DEPURACION` y lleva la contabilidad global de bloques reservados.

## Dependencias

[Objeto](Objeto.md) y `Precompilacion.h`.

## Test

**Ninguno.**

## Observaciones

- **Es el único usuario de [Objeto](Objeto.md) en el componente**, y no
  aprovecha nada de lo que la base ofrece: no redefine `hash()`, ni `equals()`,
  ni `toString()`, ni `esValido()`. La herencia no le aporta más que el
  destructor virtual.
- **`GesClsImprimirEstado` es el único método fuera del `#if`**, y su nombre no
  se parece a nada más del stack C++: `Ges`+`Cls` viene de un *gestor de clases*
  que aquí ya no existe. En el stack C aparece la misma llamada, también
  comentada, en el `EntFinalizar` de
  [Entorno](../../gjs-c-common/doc/Entorno.md).
- **`EsTipo` compara por nombre en lugar de usar el `getTipo()` de la base**,
  que ya resuelve el tipo real por RTTI. Son dos mecanismos para lo mismo en una
  clase y su padre.
- **`iEliminando` no tiene acceso público.** Es el único de los cinco campos sin
  método que lo consulte, de modo que la protección contra destrucción reentrante
  que sugiere el nombre no se puede comprobar desde fuera.
- **Fuera de `MODO_DEPURACION` la clase es un envoltorio vacío** que sigue
  ocupando un puntero a tabla virtual por instancia. Quien la herede paga esa
  indirección en producción sin recibir nada.
- **Sin test**, como el resto de lo que depende de `MODO_DEPURACION`.
