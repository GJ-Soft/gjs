# Mensajes

| Dato     | Valor                                     |
| -------- | ----------------------------------------- |
| Cabecera | `src/main/include/Mensajes.h` (80 líneas) |
| Fuente   | `Mensajes.cpp` (134 líneas)               |
| Espacio  | `org::gjs::cpp::common`                   |
| Métodos  | 8                                         |
| Test     | `MensajesTest.cpp` (190 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **catálogo de textos por código**: los mensajes del programa fuera del código
fuente, en un fichero que se puede cambiar sin recompilar.

```cpp
Mensajes msj;
msj.Cargar ( "config/mensajes.txt" );

std::cout << msj.Texto ( 1001 ) << std::endl;
std::cout << msj [ 1001 ]       << std::endl;   // lo mismo

if ( msj.ExisteCodigo ( 1002 ) ) { ... }
```

## La API

| Grupo    | Métodos                                              |
| -------- | ---------------------------------------------------- |
| Carga    | `Cargar`, `Insertar`, `Limpiar`                      |
| Consulta | `Texto`, `operator[]`, `ExisteCodigo`, `NumMensajes` |

Por dentro es un `std::map<int, std::string>`. No hay estado global: **cada
instancia lleva su catálogo**, así que un programa puede tener varios —uno de
errores, otro de la interfaz— sin que se pisen.

## El formato del fichero

Una línea por mensaje, **código, coma, texto**:

```
1001,Fichero no encontrado
1002,No hay permisos para escribir en el directorio
2001,¿Desea guardar los cambios?
```

El separador es **la primera coma de la línea**, así que el texto puede llevar
todas las que quiera. Las líneas se sanean con `EliminarCaracteresNoEstandar` y
`Trim` —eso quita el retorno de carro de los ficheros con final de línea de
Windows—, y el código tiene que ser un entero.

---

## Test

`MensajesTest.cpp` —190 líneas— cubre inserción, consulta, el operador, la carga
desde fichero y el vaciado.

---

## Observaciones

### La carga no dice si cargó algo

```cpp
bool Mensajes::Cargar ( const string & sFichero )
{
    ...
    if ( fichero.is_open () )
    {
        while ( getline ( fichero, sLinea ) ) { ... }
        fichero.close ();
        bRes = true;              // <- true por haber abierto el fichero
    }
    return ( bRes );
}
```

`Cargar` devuelve **cierto si el fichero se pudo abrir**, no si contenía
mensajes. Un fichero vacío, uno con el formato equivocado o uno con todas las
líneas mal carga «con éxito» y deja el catálogo como estaba. `NumMensajes()`
está para preguntarlo después, y hay que saber que hace falta.

### Los errores de formato se tragan en silencio

Dentro del bucle hay dos filtros sin rama de error:

- **Línea sin coma** → se salta.
- **Código que no es un entero** → se salta.

Una errata en el fichero de mensajes hace que ese mensaje no exista, y el
programa lo descubre cuando `Texto ( iCodigo )` devuelve lo que devuelva para un
código ausente. Devolver la cuenta de líneas rechazadas, o un `bool` por línea,
daría el aviso donde hace falta.

### Otras

- **`Cargar` no limpia antes.** Dos cargas seguidas **acumulan**, y las
  repeticiones se sobrescriben: `mapMensajes[iCodigo] = sMensaje`. Es útil para
  montar un catálogo por partes y sorprende si se esperaba «cargar» como
  «reemplazar». `Limpiar()` está para eso, y hay que llamarla a mano.
- **Los códigos repetidos dentro del mismo fichero también se sobrescriben sin
  avisar**: gana el último.
- **`Texto` devuelve `const std::string` por valor.** El `const` de un retorno
  por valor no protege de nada e impide mover el resultado, así que cada consulta
  copia la cadena. `operator[]` devuelve `std::string` sin el `const`, o sea que
  las dos funciones se diferencian sólo en algo que no debería estar.
- **Qué devuelve `Texto` con un código que no existe no está dicho** en la
  cabecera. Presumiblemente la cadena vacía, que no se distingue de un mensaje
  vacío. `ExisteCodigo` cubre el caso, y obliga a dos consultas.
- **`operator[]` es `const`**, al contrario que el de `std::map`, que inserta. Es
  la decisión correcta para un catálogo de sólo lectura, y merece decirse porque
  va contra la costumbre.
- **No hay forma de recorrer el catálogo**: ni iteradores, ni una lista de
  códigos. Volcar todos los mensajes —para revisarlos o para traducirlos— no se
  puede desde la API.
- **Falta lo multiidioma, y la cabecera lo dice**: `// PENDIENTE: Utilizar
  CIdioma, y añadir funcionalidad multiidioma.` Es el motivo de ser de un
  catálogo de textos, y de momento lo que hay es un fichero por programa. Tal
  como está la clase, la salida más simple sería una instancia de `Mensajes` por
  idioma.
- **El fichero de mensajes no tiene codificación declarada.** `Cargar` lee bytes
  y les quita los caracteres no estándar; con acentos en UTF-8 eso depende de
  qué considere «no estándar» esa función. Es la clase de detalle que conviene
  fijar antes de que haya ficheros de mensajes de verdad.
