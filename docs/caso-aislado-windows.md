# Caso aislado en Windows

Estado: **aparcado a propósito**. Este documento guarda el prototipo que demuestra
que la vía es viable, y sobre todo la trampa que se descubrió al probarlo, para que
quien lo retome no tenga que volver a encontrarla.

Fecha de la prueba: 29/09/2026. Toolchain: MinGW `x86_64-w64-mingw32-g++ 14.4.0`,
ejecutado en Windows 11.

---

## El problema

`CasoTestAislado::Ejecutar ()` (C++) y `SCasTstaEjecutar` (C) ejecutan el caso en un
proceso aparte para que un reventón no se lleve por delante el resto del test. Lo
hacen con `fork ()`, que en Windows no existe y no tiene equivalente directo:
`CreateProcess` no clona el proceso.

**Lo que hay hoy**: en `WIN` el caso no se ejecuta, se avisa por consola y por log, y
se da por bueno (`RESULTADO_CASO_TEST_OK`). No falla el build, pero tampoco prueba
nada. Es una decisión, no un olvido.

## La vía que funciona

Relanzar el propio ejecutable de test pasándole el caso a ejecutar en una **variable
de entorno**, y no como argumento: `argv[1]` está reservado para el nombre del test,
que es lo que usa `mvn test -Dtest=<test>`, y no se puede tocar.

- Padre: `_putenv_s ( "GJS_TEST_CASO_AISLADO", <id del caso> )`, se relanza con
  `_spawnv ( _P_WAIT, ... )`, y compara el código de salida que devuelve.
- Hijo: al arrancar mira la variable; si está puesta, ejecuta ese caso y sale con su
  código.

`_spawnv` con `_P_WAIT` **devuelve directamente el código de salida del hijo**, en una
sola llamada: no hacen falta `CreateProcess` + `WaitForSingleObject` +
`GetExitCodeProcess` ni cerrar dos `HANDLE`.

### Lo que se midió

| Caso | Qué hace el hijo | Código recibido |
| ---- | ---------------- | --------------- |
| `casoBien` | devuelve `true` | `0` |
| `casoFalla` | devuelve `false` | `1` |
| `casoRevienta` | escribe fuera de rango | `0xC0000005` |
| `casoSaleCon3` | `exit ( 3 )` | `3` |

Aquí Windows sale **mejor parado que POSIX**: el código de salida es un `DWORD` de 32
bits, así que un `STATUS_ACCESS_VIOLATION` llega íntegro y se distingue solo. En POSIX
hay que mirar `WIFSIGNALED` antes de `WEXITSTATUS`, porque con un hijo señalizado
`WEXITSTATUS` vale 0 —o sea, `EXIT_SUCCESS`— y un caso muerto se cuenta como correcto.

---

## La trampa: `_spawnv` no entrecomilla nada

**`_spawnv` no le pasa el vector al hijo.** Lo pega en una línea de órdenes separando
por espacios, y no entrecomilla ningún elemento. Si la ruta del ejecutable lleva un
espacio, el `argv` del hijo sale corrido:

```
[hijo] argv[1]=PRO\AppData\...\proto.exe   argv[2]=MiTest   argv[3]=un argv[4]=argumento ...
```

Es decir: el nombre del test deja de estar en `argv[1]`, y `-Dtest=` apunta a
cualquier cosa. Y no se ve venir, porque desde `C:\GJS\Desarrollo\...` funciona
perfectamente: sólo aparece cuando alguien instala bajo `C:\Program Files\` o tiene un
perfil de usuario con espacio.

La solución es entrecomillar cada argumento antes de dárselo a `_spawnv`, con las
reglas exactas con las que el arranque de la CRT vuelve a trocear la línea:

```cpp
/* _spawnv NO pasa el vector tal cual: lo pega en una linea de ordenes separando por
   espacios y sin entrecomillar nada. Con una ruta que lleve un espacio (Program
   Files, o un perfil de usuario con espacio) el argv del hijo sale corrido, y lo que
   el padre puso en argv[1] deja de estar en argv[1].

   Estas son las reglas con las que el arranque de la CRT trocea la linea: se
   entrecomilla si hay espacio, tabulador, salto o comilla; las comillas de dentro se
   escapan con barra; y las barras que preceden a una comilla se duplican. */
static string ComillarArgumento ( const string & sArg )
{
	if ( ( ! sArg.empty () ) && ( sArg.find_first_of ( " \t\n\v\"" ) == string::npos ) )
	{
		return ( sArg );
	}

	string sRes = "\"";
	for ( size_t iPos = 0; iPos < sArg.size (); iPos = iPos + 1 )
	{
		size_t iBarras = 0;
		while ( ( iPos < sArg.size () ) && ( sArg [ iPos ] == '\\' ) )
		{
			iBarras = iBarras + 1;
			iPos = iPos + 1;
		}
		if ( iPos == sArg.size () )
		{
			sRes.append ( iBarras * 2, '\\' );
			break;
		}
		if ( sArg [ iPos ] == '"' )
		{
			sRes.append ( iBarras * 2 + 1, '\\' );
		}
		else
		{
			sRes.append ( iBarras, '\\' );
		}
		sRes.push_back ( sArg [ iPos ] );
	}
	sRes.push_back ( '"' );
	return ( sRes );
}
```

Con eso, el `argv` del hijo llega de una pieza, espacios incluidos:

```
[hijo] argc=3 argv[1]=[MiTest] argv[2]=[un argumento con espacios]
```

---

## Por qué está aparcado

Que el padre sepa lanzar al hijo es la mitad fácil. La otra mitad es que **el hijo
arranca por `main` y recorre el banco de tests entero** hasta llegar a su caso: los
ejecutaría todos por el camino, con sus efectos colaterales, y por cada caso aislado.

Para que sea utilizable hacen falta además:

1. Que `Test::Ejecutar` (y `STestEjecutar`) miren la variable y **salten todo caso que
   no sea el pedido**, dejando correr `Inicializar` y `Finalizar`, que el caso los
   necesita.
2. Decidir qué identifica al caso. Hoy el prototipo mete el id a secas, lo que obliga
   a que los ids sean únicos en todo el ejecutable y no sólo dentro de su `Test`. Lo
   correcto sería `<nombreTest>/<idCaso>`, pero `CasoTestAislado` no conoce el nombre
   de su `Test`: habría que pasárselo desde `NuevoCasoAislado`, o sea un parámetro más
   en el constructor de una librería publicada.

Eso es lo que hizo que se aparcara.

## Lo que no hay que hacer

- **Unificar y quitar el `fork ()` de POSIX.** Tiene a favor que los dos modos darían
  la misma semántica —con `fork ()` el caso hereda el proceso entero y con el relanzado
  arranca de cero, que no es lo mismo—, pero este prototipo se apoya en `__argc` y
  `__argv`, que son de la CRT de Microsoft y **en Cygwin y Linux no existen**. Allí
  habría que leer `/proc/self/cmdline` o guardar el `argv` desde `main`, que es meterse
  en el arranque de todos los tests del repo. Sale más caro que la asimetría.
- **Reutilizar `SisEjecutarComando`.** En su rama `WIN` usa `ShellExecute`, que ni
  espera al hijo ni devuelve su código de salida.

## Lo que ya está hecho y no hay que rehacer

- `SisRutaEjecutable ()` existe en los dos stacks (`SistemaProcesos.h` / `.cpp`) y da
  la ruta del ejecutable. El `GetModuleFileNameA` del prototipo sobra.
- `gjs-cpp-common-test` depende de `gjs-cpp-common`, que ya agrega
  `gjs-cpp-common-system`: no hace falta tocar ningún `pom`, basta el `#include
  <CppCommonSystem.h>` en `CppTestConfig.h`.

---

## El prototipo entero

Se compila y se ejecuta solo, sin nada del repo:

```sh
x86_64-w64-mingw32-g++ -std=gnu++20 -Wall -Wextra -DWIN \
    -static -static-libgcc -static-libstdc++ -o proto.exe proto.cpp
```

El `-static` es sólo para poder lanzarlo a mano sin arrastrar las DLL de MinGW; en el
build del repo no hace falta. Se ejecuta desde PowerShell o `cmd`, **no desde Cygwin**,
que allí se compila la rama POSIX. Con argumentos para ver que llegan:

```
proto.exe MiTest "un argumento con espacios"
```

```cpp
/* Prototipo del caso aislado en Windows: relanzarse a si mismo con el caso en una
   variable de entorno, en vez de fork ().

   Se compila con MinGW y se ejecuta en Windows puro. Prueba cuatro cosas:
     1) que la variable de entorno llega al hijo,
     2) que _spawnv ( _P_WAIT ) devuelve el codigo de salida del hijo,
     3) que un hijo que revienta se distingue de uno que sale con error,
     4) que el argv del padre llega INTACTO al hijo, incluso con espacios. */

#include <windows.h>
#include <process.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;


#define VAR_CASO_AISLADO	"GJS_TEST_CASO_AISLADO"


/* --------------------------------------------------------- los casos de prueba */

static bool CasoQueVaBien ()
{
	cout << "    [hijo] caso que va bien" << endl;
	return ( true );
}

static bool CasoQueFalla ()
{
	cout << "    [hijo] caso que devuelve false" << endl;
	return ( false );
}

static bool CasoQueRevienta ()
{
	cout << "    [hijo] caso que escribe fuera de rango" << endl;
	vector<string> vecVacio ( 0 );
	vecVacio [ 0 ] = "x";
	return ( true );
}

static bool CasoQueSaleCon3 ()
{
	cout << "    [hijo] caso que llama a exit ( 3 )" << endl;
	exit ( 3 );
	return ( true );
}


struct Caso
{
	const char *	p_cId;
	bool			( * funcion ) ();
	int				iCodigoEsperado;
};

static Caso g_casos [] =
{
	{ "casoBien",		CasoQueVaBien,		EXIT_SUCCESS },
	{ "casoFalla",		CasoQueFalla,		EXIT_FAILURE },
	{ "casoRevienta",	CasoQueRevienta,	EXIT_SUCCESS },
	{ "casoSaleCon3",	CasoQueSaleCon3,	3 },
};
static const int g_iNumCasos = sizeof ( g_casos ) / sizeof ( g_casos [ 0 ] );


/* --------------------------------------------------------------- la mecanica */

static string RutaEjecutable ()
{
	char cRuta [ MAX_PATH ] = {};
	DWORD dwTam = GetModuleFileNameA ( NULL, cRuta, MAX_PATH );
	return ( string ( cRuta, dwTam ) );
}


static string CasoSolicitado ()
{
	const char * p_cValor = getenv ( VAR_CASO_AISLADO );
	return ( ( p_cValor != NULL ) ? string ( p_cValor ) : string ( "" ) );
}


/* _spawnv NO pasa el vector tal cual: lo pega en una linea de ordenes separando por
   espacios y sin entrecomillar nada. Con una ruta que lleve un espacio (Program
   Files, o un perfil de usuario con espacio) el argv del hijo sale corrido, y lo que
   el padre puso en argv[1] deja de estar en argv[1].

   Estas son las reglas con las que el arranque de la CRT trocea la linea: se
   entrecomilla si hay espacio, tabulador, salto o comilla; las comillas de dentro se
   escapan con barra; y las barras que preceden a una comilla se duplican. */
static string ComillarArgumento ( const string & sArg )
{
	if ( ( ! sArg.empty () ) && ( sArg.find_first_of ( " \t\n\v\"" ) == string::npos ) )
	{
		return ( sArg );
	}

	string sRes = "\"";
	for ( size_t iPos = 0; iPos < sArg.size (); iPos = iPos + 1 )
	{
		size_t iBarras = 0;
		while ( ( iPos < sArg.size () ) && ( sArg [ iPos ] == '\\' ) )
		{
			iBarras = iBarras + 1;
			iPos = iPos + 1;
		}
		if ( iPos == sArg.size () )
		{
			sRes.append ( iBarras * 2, '\\' );
			break;
		}
		if ( sArg [ iPos ] == '"' )
		{
			sRes.append ( iBarras * 2 + 1, '\\' );
		}
		else
		{
			sRes.append ( iBarras, '\\' );
		}
		sRes.push_back ( sArg [ iPos ] );
	}
	sRes.push_back ( '"' );
	return ( sRes );
}


/* Relanza este mismo ejecutable con la MISMA linea de ordenes, con el caso puesto
   en la variable de entorno. Devuelve el codigo de salida del hijo, o -1. */
static int RelanzarCaso ( const string & sIdCaso )
{
	if ( _putenv_s ( VAR_CASO_AISLADO, sIdCaso.c_str () ) != 0 )
	{
		return ( -1 );
	}

	string sRuta = RutaEjecutable ();

	/* __argc / __argv son los del arranque de la CRT: asi el hijo recibe los mismos
	   argumentos que el padre, y lo que seleccione argv[1] se respeta. */
	vector < string > vecComillados;
	vecComillados.push_back ( ComillarArgumento ( sRuta ) );
	for ( int i = 1; i < __argc; i = i + 1 )
	{
		vecComillados.push_back ( ComillarArgumento ( string ( __argv [ i ] ) ) );
	}

	vector < const char * > vecArgs;
	for ( const string & sArg : vecComillados )
	{
		vecArgs.push_back ( sArg.c_str () );
	}
	vecArgs.push_back ( NULL );

	cout.flush ();
	fflush ( NULL );
	intptr_t ipRes = _spawnv ( _P_WAIT, sRuta.c_str (), (char * const *) vecArgs.data () );

	_putenv_s ( VAR_CASO_AISLADO, "" );
	return ( (int) ipRes );
}


int main ( int iNumArgs, char * p_p_cArgs [] )
{
	string sCaso = CasoSolicitado ();

	if ( ! sCaso.empty () )
	{
		/* Soy el hijo: ejecuto el caso que me han pedido y salgo con su codigo. */
		cout << "    [hijo] argc=" << iNumArgs;
		for ( int i = 1; i < iNumArgs; i = i + 1 )
		{
			cout << " argv[" << i << "]=[" << p_p_cArgs [ i ] << "]";
		}
		cout << endl;

		for ( int i = 0; i < g_iNumCasos; i = i + 1 )
		{
			if ( sCaso == g_casos [ i ].p_cId )
			{
				bool bRes = g_casos [ i ].funcion ();
				return ( bRes ? EXIT_SUCCESS : EXIT_FAILURE );
			}
		}
		cerr << "    [hijo] caso desconocido: " << sCaso << endl;
		return ( EXIT_FAILURE );
	}

	/* Soy el padre. */
	cout << "Padre: argc=" << iNumArgs << " argv[0]=[" << p_p_cArgs [ 0 ] << "]" << endl;
	int iFallos = 0;
	for ( int i = 0; i < g_iNumCasos; i = i + 1 )
	{
		cout << "--- caso " << g_casos [ i ].p_cId
			 << " (se espera codigo " << g_casos [ i ].iCodigoEsperado << ")" << endl;

		int iCodigo = RelanzarCaso ( g_casos [ i ].p_cId );

		cout << "    codigo recibido = " << iCodigo
			 << " (0x" << hex << (unsigned int) iCodigo << dec << ")";
		if ( iCodigo == g_casos [ i ].iCodigoEsperado )
		{
			cout << "  -> OK" << endl;
		}
		else
		{
			cout << "  -> KO" << endl;
			iFallos = iFallos + 1;
		}
	}
	cout << "=== fallos = " << iFallos << " de " << g_iNumCasos << endl;
	return ( iFallos == 0 ? 0 : 1 );
}
```

Salida esperada (el único fallo es el caso que revienta, que es lo que se pretende
detectar):

```
Padre: argc=3 argv[0]=[C:\...\proto.exe]
--- caso casoBien (se espera codigo 0)
    [hijo] argc=3 argv[1]=[MiTest] argv[2]=[un argumento con espacios]
    [hijo] caso que va bien
    codigo recibido = 0 (0x0)  -> OK
--- caso casoFalla (se espera codigo 1)
    codigo recibido = 1 (0x1)  -> OK
--- caso casoRevienta (se espera codigo 0)
    codigo recibido = -1073741819 (0xc0000005)  -> KO
--- caso casoSaleCon3 (se espera codigo 3)
    codigo recibido = 3 (0x3)  -> OK
=== fallos = 1 de 4
```
