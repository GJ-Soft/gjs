# Apoyo a las pruebas

| Dato          | Valor                                                |
| ------------- | ---------------------------------------------------- |
| Módulos       | 2                                                    |
| Cabeceras     | `SimulacionUsuarioConsola.h`, `UtilidadesFicheros.h` |
| Prefijos      | — , `FicTxt`                                         |
| Funciones     | 2 + 1                                                |
| Incluidos por | `Aplicacion.h`                                       |
| Tests         | **Ninguno**                                          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Las dos piezas que hacen falta para poder probar el resto del componente: una
que simula al usuario tecleando y otra que comprueba el contenido de un fichero
de texto.

Están en `src/main`, no en `src/test`, y entran por la fachada.

## `SimulacionUsuarioConsola`

| Función                                                 | Descripción                    |
| ------------------------------------------------------- | ------------------------------ |
| `int SimularEntradaConsola ( const char * p_cEntrada )` | Precarga `stdin` con un texto. |
| `void RestaurarEntradaConsola ()`                       | Devuelve `stdin` a su estado.  |

El problema que resuelve: [CajMsjMostrar](CajaMensajes.md) hace un `getchar` en
consola, así que sin esto un test que lo llame se queda bloqueado esperando al
usuario.

La solución está bien pensada:

1. Crea una tubería y escribe en ella `p_cEntrada` seguido de un retorno —una
   cadena vacía simula pulsar sólo `<retorno>`—.
2. **Cierra el extremo de escritura**, de modo que el lector ve la entrada y
   después `EOF`: nunca se queda colgado, aunque lea de más.
3. Guarda el `stdin` original con `dup`, engancha la tubería con `dup2` y
   devuelve 1.

`RestaurarEntradaConsola` deshace los `dup2` y es inocuo si no había simulación
activa. No se puede anidar: una segunda llamada mientras hay una simulación en
curso devuelve 0.

En Windows devuelve 0 sin hacer nada, y con razón: allí la lectura va por
`kbhit` y `getche`, que no pasan por `stdin`.

## `UtilidadesFicheros`

```c
int FicTxtContenidoCoincide ( const char * p_cRuta, const char ** p_p_cLineas, int iNumLineas );
```

Compara un fichero de texto, línea a línea, con un vector de cadenas. Devuelve
cierto sólo si coinciden todas **y** el número de líneas es exacto.

Ignora las líneas vacías, que es lo que hace la comprobación robusta frente al
terminador de línea: un fichero con `CRLF` y otro con `LF` dan el mismo
resultado. Es lo que se usa para verificar lo que escribe
[SPropGuardar](SPropiedades.md).

## Dependencias

[SFicTexto](../../gjs-c-common-io/doc/FicherosBasicos.md) y
[Cadenas](../../gjs-c-common-text/doc/Cadenas.md).

## Tests

**Ninguno.** Son los dos únicos módulos del componente sin suite, lo cual tiene
su lógica: son la herramienta con la que se prueban los demás.

## Observaciones

> **Son utilidades de prueba publicadas en la librería de producción.** Están en
> `src/main/include`, se publican en el NAR `noarch` y entran por la fachada
> `Aplicacion.h`, así que cualquier programa que incluya `<Aplicacion.h>` se
> lleva `SimularEntradaConsola` en su espacio de nombres.
>
> Y no es una función inocua: **redirige el `stdin` del proceso**. Un programa
> que la llame por descuido —el nombre no lleva prefijo de módulo, a diferencia
> de todo lo demás en el stack— se queda leyendo de una tubería cerrada.
>
> El sitio natural sería `src/test`, o un componente aparte como
> `gjs-c-common-test`.

- **`SimularEntradaConsola` y `RestaurarEntradaConsola` no llevan prefijo.** Son
  las dos únicas funciones públicas del stack C sin él, lo que las deja
  expuestas a colisionar con cualquier símbolo del programa que enlace.
- **No comprueba el resultado de `write`.** Si la tubería se llena —una entrada
  mayor que el búfer del sistema, típicamente 64 KB— la escritura se trunca en
  silencio y el test lee menos de lo que creía haber preparado.
- **`RestaurarEntradaConsola` hace `fflush ( stdin )`**, que es comportamiento
  indefinido en C estándar sobre un flujo de entrada. En glibc y en Cygwin
  funciona como descarte del búfer, pero no es portable.
- **`FicTxtContenidoCoincide` ignora las líneas vacías del fichero pero no las
  del vector**: si `p_p_cLineas` contiene una cadena vacía, la comparación
  fallará siempre porque esa posición nunca se consume.
- **Recorre el fichero entero aunque ya haya fallado.** Pone `iRes` a falso y
  sigue leyendo hasta el final en lugar de cortar, que en un fichero grande es
  trabajo perdido.
- El prefijo `FicTxt` de `FicTxtContenidoCoincide` es el de
  [SFicTexto](../../gjs-c-common-io/doc/FicherosBasicos.md) —`SFicTxt`— sin la
  `S`, lo que sugiere una relación con ese módulo que no existe.
