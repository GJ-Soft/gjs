# Consola

| Dato      | Valor                                                                                              |
| --------- | -------------------------------------------------------------------------------------------------- |
| Cabeceras | `AplicacionConsola.h` (67), `ConsolaDepuracion.h` (58), `SimulacionUsuarioConsola.h` (52)          |
| Fuentes   | `AplicacionConsola.cpp` (432), `ConsolaDepuracion.cpp` (102), `SimulacionUsuarioConsola.cpp` (111) |
| Espacio   | `org::gjs::cpp::common`                                                                            |
| Prefijos  | `AplicCon`, `ConDep`                                                                               |
| Funciones | 15 + 7 + 2                                                                                         |
| Tests     | `AplicacionConsolaTest.cpp`, `ConsolaDepuracionTest.cpp` · `SimulacionUsuarioConsola` **sin test** |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Tres módulos alrededor del terminal: **la consola del programa**, **una segunda
consola para trazas de depuración** y **una forma de simular al usuario** para
poder probar las dos primeras.

```cpp
AplicConAbrir ();

AplicConDibujarLineaDoble ();
int iOpcion = AplicConLeerNumeroEntre ( 1, 5 );
AplicConEsperarRetorno ();

AplicConCerrar ();
```

---

## `AplicacionConsola`

| Grupo         | Funciones                                                                                       |
| ------------- | ----------------------------------------------------------------------------------------------- |
| Ciclo de vida | `AplicConAbrir`, `AplicConCerrar`, `AplicConEstaAbierta`                                        |
| Consulta      | `AplicConAncho`                                                                                 |
| Limpieza      | `AplicConLimpiar`                                                                               |
| Entrada       | `AplicConLeerNumero`, `AplicConLeerNumeroEntre`, `AplicConLeerCadena`, `AplicConEsperarRetorno` |
| Dibujo        | `AplicConDibujarLinea`, `…Ext`, `…Simple`, `…Doble`, `AplicConDibujarRectangulo`, `…Doble`      |

Las seis de dibujo son la mitad del módulo: líneas simples y dobles del ancho de
la consola, y rectángulos con esquinas. Es lo que hace falta para un menú de
texto.

## `ConsolaDepuracion`

Un canal aparte para trazas, con el mismo ciclo de vida —`ConDepAbrir`,
`ConDepCerrar`, `ConDepEstaAbierta`— y dos escritores:

```cpp
bool ConDepEscribir ( const std::string & sTexto );
bool ConDepEscribirLinea ( const std::string & sTexto );

template<typename... Args> bool ConDepEscribir ( const std::string & sFormato, Args&&... argumentos );
template<typename... Args> bool ConDepEscribirLinea ( const std::string & sFormato, Args&&... argumentos );
```

**Las plantillas están definidas en la cabecera**, con un comentario que dice por
qué: *«una plantilla debe ser visible en el punto de instanciación»*. Delegan en
`std::vformat` y en el escritor base. Es la forma correcta, y el contraste con
[gjs-cpp-common-log](../../gjs-cpp-common-log/doc/Log.md#las-plantillas-no-funcionan)
—donde las mismas plantillas están en el `.cpp` y no enlazan— es directo: aquí
alguien se dio cuenta y allí no.

## `SimulacionUsuarioConsola`

Dos funciones para probar lo anterior sin nadie tecleando:

```cpp
bool SimularEntradaConsola ( const std::string & sEntrada );
void RestaurarEntradaConsola ();
```

La primera engancha la entrada estándar a una tubería precargada con el texto
más un retorno, y **cierra el extremo de escritura**, de modo que el lector ve la
entrada y después el fin de fichero: nunca se queda bloqueado aunque lea de más.
La segunda deshace la redirección.

El comentario de la cabecera lo explica entero, incluido el caso en que no
aplica: en Windows, `getche` y `kbhit` no pasan por la entrada estándar, así que
la simulación devuelve `false`.

---

## Tests

`AplicacionConsolaTest.cpp` prueba la lectura **usando la simulación**: precarga
la entrada, llama a `AplicConLeerNumero` y comprueba el resultado. Sin ese
módulo, esa suite no existiría.

`ConsolaDepuracionTest.cpp` prueba el ciclo de vida y los dos escritores.

---

## Observaciones

### Una herramienta de pruebas dentro de la biblioteca

- **`SimulacionUsuarioConsola` está en la fachada.** Es código de andamiaje
  —redirige la entrada estándar del proceso— publicado como API de una biblioteca
  de producción. Su pareja simétrica, `CaptorSalida` —que intercepta la salida en
  vez de la entrada—, vive en
  [gjs-cpp-common-types](../../gjs-cpp-common-types/README.md); las dos juntas en
  `gjs-cpp-common-test` tendrían más sentido que repartidas en dos bibliotecas
  que no son de pruebas.
- **Y no tiene test**, lo cual es coherente: es con lo que se prueban los demás.
  El precio es que si la simulación se rompe, el fallo aparece en
  `AplicacionConsolaTest` como si fuera de la consola.
- **No hay forma de preguntar si la simulación está activa.** Los otros tres
  módulos con estado del componente tienen su `…EstaAbierta`; éste no. Llamar a
  `RestaurarEntradaConsola` sin haber simulado es inocuo —lo dice el comentario—,
  así que el hueco es menor, y sigue siendo una asimetría.

### `AplicacionConsola`

- **`AplicConLeerCadena` devuelve `std::string *`**, puntero desnudo sin contrato
  de propiedad, en un componente donde `AplicNombre` y `CadenaVersion` devuelven
  por valor. Es la única función del componente que lo hace en la entrada.
- **Cuatro marcas `PENDIENTE`**, y las dos primeras están en la cabecera del
  fichero y dicen lo esencial:

  ```
  // PENDIENTE: Como determinar si es WIN en modo consola o no?
  //  PENDIENTE: Refinar para el caso GNU/UNIX y completar para el caso VC
  ```

  O sea: **el módulo no sabe distinguir un programa de consola de uno de ventana
  en Windows**, que es justo lo que decide si `AplicConAbrir` tiene que crear una
  consola o aprovechar la que hay.
- **`AplicConAncho` es lo que usan las seis funciones de dibujo**, y si la
  consola no está abierta o no se puede consultar, el valor que devuelva decide
  cómo salen las líneas. Qué devuelve en ese caso no está escrito.
- **`AplicConLeerNumeroEntre ( iMin, iMax )` no dice qué hace si el usuario
  escribe otra cosa**: si vuelve a preguntar, si devuelve `iMin`, o si devuelve
  un centinela. Es la función más usada de las de entrada y la que más falta le
  hace.
- **`AplicConDibujarLineaExt ( iAncho, iColIni, cCar )` tiene los parámetros en
  otro orden** que su hermana `AplicConDibujarLinea ( cCar )`: el carácter pasa
  de primero a último. Al lado, `AplicConDibujarRectangulo ( iAlto, iAncho,
  iColIni )` no acepta carácter.

### `ConsolaDepuracion`

- **Las dos plantillas se llaman igual que los dos escritores base.** Es
  deliberado y funciona —con un solo argumento gana la sobrecarga no plantilla—,
  y significa que una llamada con un texto que contenga llaves, como
  `ConDepEscribir ( "{contador}" )`, va a la versión sin formato y sale tal cual,
  mientras que `ConDepEscribir ( "{}", i )` formatea. La diferencia depende del
  número de argumentos, no de la cadena.
- **`std::vformat` lanza `std::format_error` si la cadena de formato no
  concuerda** con los argumentos, y ninguna de las dos plantillas lo captura: una
  traza de depuración mal escrita tumba el programa que se estaba depurando.
- **No es una consola aparte: es la misma.** El nombre y el ciclo de vida propio
  sugieren un segundo canal, y lo que hace `ConDepAbrir` es comprobar si la
  consola de la aplicación ya está abierta y, si no, abrirla con
  `AplicConAbrir`; los escritores mandan a `cout` como todo lo demás. Lo único
  que aporta sobre escribir directamente es **el interruptor**: con la consola de
  depuración cerrada, `ConDepEscribir` no imprime nada y devuelve `false`. Eso es
  útil —permite dejar las trazas puestas y apagarlas—, y no es lo que el nombre
  promete.
- **Recuerda si la abrió él.** `g_bConsolaDepuracionAbierta` distingue «la
  consola ya estaba» de «la abrí yo», y `ConDepCerrar` sólo cierra en el segundo
  caso. Es el detalle bien resuelto del módulo.
- **Cada escritura consulta el ancho y trunca.** `ConDepEscribir` llama a
  `AplicConAncho()` en cada llamada y corta el texto a esa longitud, así que
  **una traza más ancha que la consola se pierde por la derecha en silencio**, y
  `ConDepEscribirLinea` mete el salto de línea igual. Para trazas de depuración
  —que suelen ser largas— es justo lo contrario de lo que interesa.
