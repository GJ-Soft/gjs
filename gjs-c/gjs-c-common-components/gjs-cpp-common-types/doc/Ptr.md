# Ptr\<T\>

| Dato     | Valor                                |
| -------- | ------------------------------------ |
| Cabecera | `src/main/include/Ptr.h` (93 líneas) |
| Fuente   | `Ptr.cpp`                            |
| Espacio  | `org::gjs::cpp::common`              |
| Tipo     | **Plantilla**, toda en línea         |
| Test     | `PtrTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un puntero que se encarga de liberar lo que apunta al salir de ámbito, **con la
opción de no hacerlo**.

```cpp
template<typename T> class Ptr
{
private:
    T *  datos;
    bool bLiberar;

public:
    Ptr ();
    explicit Ptr ( T * _datos, bool _bLiberar = true );
    explicit Ptr ( void * _datos, bool _bLiberar = true );

    Ptr ( const Ptr & ) = delete;
    Ptr & operator= ( const Ptr & ) = delete;

    virtual ~Ptr ();

    T *  getDatos ();
    void setDatos ( T * _datos );
    void setDatos ( void * _datos );
    bool EsValido ();
};
```

La bandera `bLiberar` es lo que lo distingue de un `std::unique_ptr`: permite
envolver un puntero **prestado** —a un objeto de la pila, o de otro dueño— y
tratarlo igual, sin que el destructor lo libere.

**Prohíbe la copia y la asignación** con `= delete`, que es lo correcto para un
tipo con propiedad única y lo que evita la doble liberación.

## Dependencias

`PuedeLiberarse` de
[Sistema](../../gjs-cpp-common-base/doc/Sistema.md), que el destructor consulta
antes de borrar.

## Test

`PtrTest.cpp` → `TestPtr()`.

## Observaciones

> **El destructor silencia un aviso del compilador en lugar de resolverlo:**
>
> ```cpp
> if ( bLiberar && PuedeLiberarse ( datos ) )
> {
> #pragma GCC diagnostic push
> #pragma GCC diagnostic ignored "-Wfree-nonheap-object"
>     delete datos;
> #pragma GCC diagnostic pop
> }
> ```
>
> `-Wfree-nonheap-object` avisa de que se está liberando algo que el compilador
> ve que no salió del montón. Con los constructores que tiene la clase —que
> aceptan cualquier `T *`, incluida la dirección de una variable local— el aviso
> es acertado: el caso existe, y por eso está `bLiberar`.
>
> El apaño se apoya en `PuedeLiberarse`, que
> [no puede cumplir lo que promete](../../gjs-cpp-common-base/doc/Sistema.md):
> no hay forma portable de saber si un puntero salió de `malloc`. De modo que la
> comprobación en ejecución no protege y el aviso en compilación está callado.
>
> Lo que sí protege es usar bien `bLiberar`, y eso es responsabilidad del
> llamante.

- **`setDatos` no libera el puntero anterior.** Asignar dos veces sobre el mismo
  `Ptr` pierde el primero, aunque `bLiberar` fuera cierto. Un puntero con dueño
  debería soltar lo que tenía, como hace `std::unique_ptr::reset`.
- **No hay `operator*` ni `operator->`.** Hay que escribir `p.getDatos()->campo`
  en lugar de `p->campo`, que es lo que hace cómodo a un puntero inteligente.
- **Ni `release()`, ni movimiento.** Prohibida la copia y sin constructor de
  movimiento, un `Ptr` no se puede devolver de una función ni meter en un
  `std::vector`. Queda limitado a variable local.
- **`std::unique_ptr` cubre todo esto desde C++11**, y el componente compila con
  `gnu++20`. Para el caso del puntero prestado —lo único que `unique_ptr` no
  hace— está `std::unique_ptr<T, void(*)(T*)>` con un borrador que no borra, o
  simplemente un puntero desnudo.
- **El constructor desde `void *` hace `reinterpret_cast`** sin comprobación
  posible: es la puerta por la que entra cualquier tipo. Encaja con
  [NodoBin](NodoBin.md), que guarda sus datos como `void *`, y explica por qué
  está.
- **`EsValido()` sólo comprueba que no sea nulo**, no llama a `PuedeLiberarse`
  como el destructor. Dos criterios de validez en la misma clase.
