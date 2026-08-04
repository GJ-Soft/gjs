# Clases y módulos de gjs-cpp-common-types

[README](../README.md)

24 cabeceras y 22 fuentes en 4.552 líneas: 18 clases, dos plantillas y seis
conjuntos de funciones libres.

---

## El modelo de datos

| Clase             | Cabecera            | Deriva de     | Test | Documento                             |
| ----------------- | ------------------- | ------------- | ---- | ------------------------------------- |
| `Tipo`            | `Tipo.h`            | `IComparable` | ✔    | [Tipo](Tipo.md)                       |
| `Atributo`        | `Atributo.h`        | `Tipo`        | ✔    | [Atributo](Atributo.md)               |
| `Entidad`         | `Entidad.h`         | `IComparable` | ✔    | [Entidad](Entidad.md)                 |
| `Valor`           | `Valor.h`           | `IComparable` | ✔    | [Valor](Valor.md)                     |
| `ListaValores`    | `ListaValores.h`    | `IToString`   | ✔    | [ListaValores](ListaValores.md)       |
| `ConjuntoValores` | `ConjuntoValores.h` | `IToString`   | ✔    | [ConjuntoValores](ConjuntoValores.md) |

## Contenedores y plantillas

| Clase           | Cabecera       | Deriva de   | Test | Documento                   |
| --------------- | -------------- | ----------- | ---- | --------------------------- |
| `Ptr<T>`        | `Ptr.h`        | —           | ✔    | [Ptr](Ptr.md)               |
| `MapaVector<T>` | `MapaVector.h` | —           | ✔    | [MapaVector](MapaVector.md) |
| `ArbolBin`      | `ArbolBin.h`   | `IToString` | ✔    | [ArbolBin](ArbolBin.md)     |
| `NodoBin`       | `NodoBin.h`    | `IToString` | ✔    | [NodoBin](NodoBin.md)       |
| `Simbolos`      | `Simbolos.h`   | —           | ✔    | [Simbolos](Simbolos.md)     |

## Ficheros

| Clase               | Cabecera              | Deriva de           | Test | Documento                                 |
| ------------------- | --------------------- | ------------------- | ---- | ----------------------------------------- |
| `Propiedades`       | `Propiedades.h`       | —                   | ✔    | [Propiedades](Propiedades.md)             |
| `FicheroFormateado` | `FicheroFormateado.h` | —                   | ✔    | [FicheroFormateado](FicheroFormateado.md) |
| `FicheroCSV`        | `FicheroFormateado.h` | `FicheroFormateado` | ✔    | [FicheroCSV](FicheroCSV.md)               |
| `FicheroTSV`        | `FicheroFormateado.h` | `FicheroFormateado` | ✔    | [FicheroTSV](FicheroTSV.md)               |
| `FicheroDSV`        | `FicheroFormateado.h` | `FicheroFormateado` | ✔    | [FicheroDSV](FicheroDSV.md)               |

## Infraestructura

| Clase                 | Cabecera                | Deriva de             | Test | Documento                                     |
| --------------------- | ----------------------- | --------------------- | ---- | --------------------------------------------- |
| `ControlConcurrencia` | `ControlConcurrencia.h` | —                     | ✔    | [ControlConcurrencia](ControlConcurrencia.md) |
| `CaptorSalida`        | `CaptorSalida.h`        | —                     | ✔    | [CaptorSalida](CaptorSalida.md)               |
| `StringStreamOut`     | `StringStreamOut.h`     | `std::stringstream`   | ✔    | [StringStreamOut](StringStreamOut.md)         |
| `Contador`            | `Contador.h`            | `IToString` (privado) | ✔    | [Contador](Contador.md)                       |

---

## Funciones libres y enumeraciones

| Módulo            | Cabecera            | Qué aporta                            | Test | Documento                             |
| ----------------- | ------------------- | ------------------------------------- | ---- | ------------------------------------- |
| `TipoDatos`       | `TipoDatos.h`       | El `enum class` y su `ToString`       | ✔    | [TipoDatos](TipoDatos.md)             |
| `Constantes`      | `Constantes.h`      | Fecha de compilación desde `__DATE__` | ✔    | [Constantes](Constantes.md)           |
| `Calculo`         | `Calculo.h`         | Aleatorio y comparación de reales     | ✔    | [Calculo](Calculo.md)                 |
| `Secuencias`      | `Secuencias.h`      | `SonIguales` sobre arrays             | ✔    | [Secuencias](Secuencias.md)           |
| `MemoriaGlobal`   | `MemoriaGlobal.h`   | Diccionario global clave → valor      | ✔    | [MemoriaGlobal](MemoriaGlobal.md)     |
| `WinHerramientas` | `WinHerramientas.h` | `DLLEjecutar`, **sólo Windows**       | ✔    | [WinHerramientas](WinHerramientas.md) |

---

## La fachada `CppCommonTypes.h`

Trae `CppBase.h` y las 23 cabeceras del componente, y añade dos cosas propias:

```cpp
const std::string CADENA_VACIA ( "" );

template<typename Base, typename T> inline bool instanceof ( const T * ptr )
{
    return dynamic_cast<const Base *> ( ptr ) != nullptr;
}
```

`instanceof<Atributo> ( p )` es la forma corta de preguntar por el tipo real de
un puntero, y el nombre viene de Java. Como toda la jerarquía del componente es
polimórfica, funciona en cualquiera de sus clases.

> Definir una **constante y una plantilla en la cabecera fachada** es
> excepcional en el stack: el resto de fachadas sólo agrupan `#include`. Y
> `CADENA_VACIA` es un objeto con enlace interno, de modo que cada unidad de
> compilación que incluya la fachada tiene el suyo.
