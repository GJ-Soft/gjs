# SFicEncabezado

| Dato         | Valor                                                         |
| ------------ | ------------------------------------------------------------- |
| Cabecera     | `src/main/include/SFicEncabezado.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/SFicEncabezado.c` (1.045 líneas) |
| Prefijo      | `SFicEnc`                                                     |
| Struct       | `SFicEncabezado`                                              |
| Funciones    | 41                                                            |
| Incluido por | `Ficheros.h`                                                  |
| Test         | `SFicEncabezadoTest.c` → `TestSFicEncabezado()`               |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un fichero de acceso aleatorio con **cabecera de tamaño fijo y número mágico**.
Es el primer formato propio del componente: separa el fichero en dos zonas, una
de metadatos y otra de datos, y usa el número mágico para verificar que el
fichero es del tipo esperado antes de leerlo.

```c
typedef struct
{
    int              iNumMagico;
    unsigned long    ulTamCabecera;
    SFicAleatorio *  p_ficObj;
} SFicEncabezado;
```

Sobre él se construyen [SFicBloques](Bloques.md) y, a través de éste, el resto
de formatos estructurados.

## API

### Cabecera

| Función                                                 | Descripción                                 |
| ------------------------------------------------------- | ------------------------------------------- |
| `SFicEncTamCabecera` / `SFicEncEstablecerTamCabecera`   | Tamaño de la zona de cabecera.              |
| `SFicEncLeerCabecera` / `SFicEncEscribirCabecera`       | Lee y escribe la cabecera entera.           |
| `SFicEncCrearBufferCabecera`                            | Reserva un búfer del tamaño de la cabecera. |
| `SFicEncNumeroMagico` / `SFicEncEstablecerNumeroMagico` | La marca de formato.                        |
| `SFicEncTieneNumeroMagico`                              | 1 si el fichero lleva la marca esperada.    |

`SFicEncTieneNumeroMagico` es la comprobación que hay que hacer nada más abrir:
distingue un fichero del formato correcto de uno cualquiera con la extensión
adecuada.

### Datos

| Función                                           | Descripción                                         |
| ------------------------------------------------- | --------------------------------------------------- |
| `SFicEncTamDatos`                                 | Tamaño de la zona de datos, sin contar la cabecera. |
| `SFicEncTam`                                      | Tamaño total del fichero.                           |
| `SFicEncLeer` / `SFicEncEscribir`                 | En la posición actual.                              |
| `SFicEncLeerEn` / `SFicEncEscribirEn`             | En una posición dada.                               |
| `SFicEncLeerBuffer` / `SFicEncEscribirBuffer`     | Bloques.                                            |
| `SFicEncLeerBufferEn` / `SFicEncEscribirBufferEn` | Bloques en una posición.                            |
| `SFicEncPos` / `SFicEncPosicionar`                | Posición.                                           |
| `SFicEncMoverAInicio` / `SFicEncMoverAFinal`      | Extremos.                                           |
| `SFicEncEstaVacio` / `SFicEncEstaEnFinal`         | Estado.                                             |

La distinción entre `SFicEncTam` y `SFicEncTamDatos` es la clave del módulo: las
posiciones de la zona de datos son **relativas al final de la cabecera**, así
que el llamante no tiene que sumar el desplazamiento.

### Ciclo de vida

`SFicEncCrear`, `SFicEncCrearExt`, `SFicEncCrearRuta`, `SFicEncDestruir`,
`SFicEncEsValido`, `SFicEncAbrir`, `SFicEncAbrirExt`, `SFicEncCerrar`,
`SFicEncEstaAbierto`, `SFicEncRuta`, `SFicEncEstablecerRuta`,
`SFicEncEstablecerRutaExt`, `SFicEncDirectorio`, `SFicEncFichero`,
`SFicEncEliminar`, `SFicEncAsignar`, `SFicEncAsignarExt`.

## Dependencias

- [SFicAleatorio](FicherosBasicos.md) — el acceso por posición.
- [SBuffer](../../gjs-c-common-base-types/doc/SBuffer.md) — el búfer de cabecera.

## Test

`SFicEncabezadoTest.c` → `TestSFicEncabezado()`.

## Observaciones

- **El número mágico es un `int`**, sin que la cabecera diga cómo se serializa.
  Al escribirlo tal cual, el fichero **depende del orden de bytes de la
  máquina**: uno creado en una arquitectura big endian no pasaría
  `SFicEncTieneNumeroMagico` en una little endian. El stack tiene
  [OrdenBytes](../../gjs-c-common-base/doc/OrdenBytes.md) precisamente para esto.
- **El tamaño de cabecera se puede cambiar con el fichero ya escrito.**
  `SFicEncEstablecerTamCabecera` no dice qué ocurre con los datos existentes: si
  se desplazan, se pierden o el fichero queda incoherente.
- `SFicEncCrearBufferCabecera` reserva memoria que el llamante debe liberar, pero
  el nombre no lo sugiere tanto como un `Duplicar…`.
- El número mágico aparece también en
  [SFicAleatorio](FicherosBasicos.md) (`SFicAlNumeroMagico`), pese a que la
  estructura de éste no tiene campo para guardarlo. Los dos módulos exponen el
  mismo concepto con distinta base.
- `SFicEncAsignar` y `SFicEncAsignarExt` no aparecen en el resto de la jerarquía
  de ficheros; la cabecera no aclara qué asignan.
