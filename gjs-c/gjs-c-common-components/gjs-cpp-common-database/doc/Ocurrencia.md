# Ocurrencia

| Dato      | Valor                                       |
| --------- | ------------------------------------------- |
| Cabecera  | `src/main/include/Ocurrencia.h` (66 líneas) |
| Fuente    | `Ocurrencia.cpp` (196 líneas)               |
| Espacio   | `org::gjs::cpp::common`                     |
| Hereda de | `ListaValores`, `IComparable`               |
| Métodos   | 18                                          |
| Test      | `OcurrenciaTest.cpp` (193 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

**Una fila**: los valores de un registro, más la
[`Entidad`](../../gjs-cpp-common-types/doc/Entidad.md) que dice qué significa
cada uno.

```cpp
Ocurrencia ocur ( &entCliente );

ocur.getValor ( "nombre" )->Establecer ( "Vladimiro" );
ocur.getValor ( 2 )->Establecer ( 42 );

if ( ocur.EsValida () ) { ... }

Ocurrencia * pCopia = ocur.Clonar ();
```

Sin la entidad sería una [`ListaValores`](../../gjs-cpp-common-types/doc/ListaValores.md)
a secas; lo que añade es **saber qué es cada valor**, y por tanto poder validarse
y buscar por nombre de atributo.

## La API

| Grupo        | Métodos                                                       |
| ------------ | ------------------------------------------------------------- |
| Construcción | Desde `Entidad *`, desde `Ocurrencia *`, desde `Ocurrencia &` |
| Estructura   | `getEntidad`                                                  |
| Validez      | `EsValida`, `EsCompatible` (cuatro sobrecargas)               |
| Acceso       | `getValor ( "atributo" )`, `getValor ( indice )`              |
| Copia        | `Asignar` (dos formas), `Clonar`, `operator=`                 |
| Comparación  | `operator==`, `operator!=`, `getHash`                         |
| Salida       | `toString`                                                    |

### Acceso por nombre

Es lo que justifica la clase:

```cpp
Valor * Ocurrencia::getValor ( const string & sAtributo )
{
    return ( getValor ( entidad->getIndiceAtributo ( sAtributo ) ) );
}
```

El nombre del atributo se traduce a índice preguntándole a la entidad, y de ahí
se cae en el acceso por posición de `ListaValores`.

### Validez

`EsValida()` comprueba tres cosas, en orden: que la entidad lo sea, que la lista
lo sea, y que **el número de valores coincida con el número de atributos**. Si
todo eso pasa, recorre los valores comprobando que cada uno sea compatible con
su atributo.

Es una validación completa y cara: recorre la fila entera cada vez. Y la llaman
`EsCompatible`, `Asignar` y —por su medio— `operator=` y `Clonar`.

### El hash

```cpp
lHash = ( entidad->getHash() * 100000 ) + ListaValores::getHash();
```

Mezcla la estructura con el contenido, de modo que dos filas iguales de tablas
distintas no colisionan. Es lo que hace que `operator==` —heredado de
[`IComparable`](../../gjs-cpp-common-types/README.md)— compare fila con fila y no
sólo valores.

---

## Test

`OcurrenciaTest.cpp` cubre construcción, validez, acceso por nombre y por índice,
copia, clonado y comparación.

---

## Observaciones

### Los fallos silenciosos

- **`Asignar` no dice si asignó.** Devuelve `void` y toda su lógica está dentro
  de un `if` con tres condiciones —que el origen sea válido, que las entidades
  sean compatibles y que los tamaños coincidan—; si alguna falla, **no hace nada
  y el llamante no se entera**:

  ```cpp
  void Ocurrencia::Asignar ( Ocurrencia & obj )
  {
      if ( obj.EsValida () && ( entidad != NULL ) &&
           entidad->EsCompatible ( obj.getEntidad () ) &&
           ( NumValores () == obj.NumValores () ) )
      { ... }
      // y si no, silencio
  }
  ```
- **`operator=` hereda el problema.** `a = b` entre ocurrencias incompatibles
  compila, se ejecuta y deja `a` como estaba. Un `operator=` que puede no asignar
  es de las cosas que más cuesta depurar, porque nadie sospecha de él.
- **`Clonar` también.** Crea la copia y llama a `Asignar ( this )`; si `this` no
  es válida —una fila recién creada, con los valores todavía nulos, no lo es—,
  **devuelve una ocurrencia vacía en vez de un clon**, sin avisar. Clonar algo
  que aún no se ha rellenado es un caso normal, no un error del llamante.
- Los tres se arreglan igual: devolver `bool`. `Asignar` y `operator=`
  —devolviendo `*this`, con un `EsValida` que el llamante pueda consultar
  después— y `Clonar` devolviendo `NULL` si no pudo.

### El `try/catch` que no protege

```cpp
string Ocurrencia::toString ()
{
    try
    {
        return ( Concatenar ( "[Ocurrencia={Entidad=[", getEntidad()->toString(), ...
    }
    catch (...)
    {
        return ( "[Ocurrencia=[Object Error]]" );
    }
}
```

`getEntidad()` puede devolver `NULL` —lo devuelve si se construyó desde un
puntero nulo, cosa que los constructores admiten— y **desreferenciar un nulo no
lanza ninguna excepción**: es comportamiento indefinido, y el `catch (...)` no
lo ve. El bloque da una sensación de seguridad que no corresponde. Comprobar el
nulo antes cuesta una línea.

### Corrección constante

- **La clase pierde el `const` que sus bases sí tienen.** En
  [`Entidad`](../../gjs-cpp-common-types/doc/Entidad.md), `EsValida()` y
  `EsCompatible()` son `const`; aquí no lo son ninguna de las cinco. Tampoco
  `toString`, ni `getValor`, ni los tres operadores.
- **Sólo `getEntidad` y `getHash` son `const`.** El resultado es que una
  `const Ocurrencia &` —lo natural para un parámetro de sólo lectura— no se puede
  imprimir, ni comparar, ni consultar.
- **Los tres operadores toman `Ocurrencia &`, no `const Ocurrencia &`**, así que
  `ocur == Clonar()` o comparar contra un temporal no compila.

### Otras

- **El constructor de copia toma referencia no constante** (`Ocurrencia ( Ocurrencia & obj )`),
  con las mismas consecuencias: no se puede copiar una ocurrencia constante ni un
  temporal.
- **Hay tres constructores para dos casos.** El de `Ocurrencia *` y el de
  `Ocurrencia &` hacen lo mismo, y el primero acepta `NULL` construyendo un
  objeto con cero valores y entidad nula — que es justo el objeto que rompe
  `toString`.
- **`EsCompatible` sobre una ocurrencia recién creada devuelve falso**, porque
  empieza exigiendo `EsValida()` y una fila con los valores sin rellenar no lo
  es. Comprobar si dos filas *encajan estructuralmente* no debería depender de si
  están rellenas.
- **`getValor ( "atributo" )` con un nombre que no existe** depende de qué
  devuelva `getIndiceAtributo`: si es un índice fuera de rango, `ListaValores`
  devuelve nulo y el llamante se lleva un puntero nulo sin distinguirlo de un
  valor ausente.
- **El `100000` del hash es un número mágico** sin explicación, y con entidades de
  hash grande el producto puede desbordar el `long`.
