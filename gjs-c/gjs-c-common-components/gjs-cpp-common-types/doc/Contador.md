# Contador

| Dato      | Valor                                     |
| --------- | ----------------------------------------- |
| Cabecera  | `src/main/include/Contador.h` (48 líneas) |
| Fuente    | `Contador.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                   |
| Deriva de | `IToString` — **en privado**              |
| Test      | `ContadorTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Contar intentos y aciertos. Tres números —total, correctos y erróneos— de los
que sólo se guardan dos.

```cpp
class Contador : IToString
{
private:
    unsigned long ulTotal     = 0;
    unsigned long ulCorrectos = 0;

public:
    Contador ();
    virtual ~Contador ();

    unsigned long getTotal () const;
    unsigned long getCorrectos () const;
    unsigned long getErroneos () const;

    void Incrementar ( bool bCorrecto = true );

    virtual std::string toString () override;
};
```

`getErroneos()` es la resta, de modo que no hay forma de que los tres números se
descuadren. Y `Incrementar` con el parámetro por defecto a `true` hace que el
caso frecuente —contar un acierto— se escriba sin argumentos.

Es el recuento que lleva a mano el marco de pruebas del stack C en
[STest](../../gjs-c-common-test/doc/STest.md), con sus campos `iEjecutados`,
`iCorrectos`, `iErroneos` y `iFallidos`.

## Dependencias

`IToString` de [gjs-cpp-common-base](../../gjs-cpp-common-base/doc/IToString.md).

## Test

`ContadorTest.cpp` → `TestContador()`.

## Observaciones

> **La herencia es privada por descuido.** En C++, `class` sin especificador de
> acceso hereda **en privado**:
>
> ```cpp
> class Contador : IToString        // <- falta el public
> ```
>
> Todas las demás clases del componente escriben `: public IToString`. La
> consecuencia es que `Contador` **no es un `IToString` para nadie de fuera**:
>
> - No se puede pasar a `ToString ( IToString & )`.
> - No entra en las colecciones volcables de
>   [IToString](../../gjs-cpp-common-base/doc/IToString.md).
> - No funciona el `operator<<` que la interfaz declara amigo.
> - `instanceof<IToString> ( p )` sobre un `Contador *` devuelve falso.
>
> El `toString()` sí se puede llamar directamente sobre el objeto, porque está
> declarado público, de modo que el fallo no salta a la vista: sólo aparece
> cuando se intenta tratar el contador como lo que dice ser.
>
> Se arregla con una palabra.

- **No hay forma de reiniciarlo.** Ni `Limpiar()` ni `Reiniciar()`: un contador
  sólo sube. Para volver a cero hay que construir otro.
- **`Incrementar` no admite un incremento distinto de uno.** Sumar un lote de
  resultados obliga a un bucle.
- **`getErroneos()` es una resta sin protección.** Con `unsigned long`, si
  alguna vez `ulCorrectos` superase a `ulTotal` el resultado no sería negativo
  sino enorme. Hoy no puede pasar porque los dos campos son privados y sólo los
  toca `Incrementar`, pero conviene saber por qué es seguro.
- **Falta el tercer estado.** El marco de pruebas del stack distingue *correcto*,
  *erróneo* y *fallido* —el caso que no se pudo ni ejecutar—, y este contador
  sólo tiene dos. Con `bool` como parámetro no hay sitio para el tercero.
