#include "Base.h"

#include "SistemaUsuario.h"



static int TestSisUsrNombre01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisUsrNombre 01:\n" );
	/* Los nombres son copias que libera el llamante, en todas las plataformas. */
	char * p_cUsuario = SisUsrObtenerNombre ( 0 );
	char * p_cGrupo = SisUsrObtenerNombreGrupo ( 0 );
	if ( ES_NULO ( p_cUsuario ) )
	{
		printf( "Error caso 1: se esperaba nombre de usuario no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( p_cGrupo ) )
	{
		printf( "Error caso 2: se esperaba nombre de grupo no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cUsuario );
	MemLiberar ( (void **) &p_cGrupo );
#if ( defined ( WIN ) )
	char * p_cNombre = SisUsrObtenerNombre ( 0 );
	if ( ( ES_NULO ( p_cNombre ) ) || ( strcmp ( p_cNombre, "user" ) != 0 ) )
	{
		printf( "Error caso 3: en WIN se esperaba \"user\" para id 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cNombre );
	p_cNombre = SisUsrObtenerNombre ( 7777 );
	if ( ( ES_NULO ( p_cNombre ) ) || ( strcmp ( p_cNombre, "<none>" ) != 0 ) )
	{
		printf( "Error caso 4: en WIN se esperaba \"<none>\" para id desconocido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cNombre );
	if ( SisUsrActivarRoot () != 0 )
	{
		printf( "Error caso 5: en WIN SisUsrActivarRoot debe devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisUsrDesactivarRoot () != 0 )
	{
		printf( "Error caso 6: en WIN SisUsrDesactivarRoot debe devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}

/* El nombre es del llamante y no depende de las consultas que vengan despues.
   Antes salia de una cache de 10 entradas que liberaba la mas antigua al
   llenarse: tras consultar diez uid distintos, el primer nombre quedaba
   liberado. Y dos llamadas con el mismo uid devolvian el mismo puntero, que es
   lo que el caso 1 comprueba de forma determinista. */
static int TestSisUsrNombre02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisUsrNombre 02:\n" );
	char * p_cPrimero = SisUsrObtenerNombre ( 0 );
	char * p_cSegundo = SisUsrObtenerNombre ( 0 );

	if ( ( ES_VALIDO ( p_cPrimero ) ) && ( p_cPrimero == p_cSegundo ) )
	{
		printf( "Error caso 1: dos llamadas devolvieron el mismo puntero; se esperaban copias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	for ( unsigned int uiId = 7000; uiId < 7020; uiId = uiId + 1 )
	{
		char * p_cOtro = SisUsrObtenerNombre ( uiId );
		MemLiberar ( (void **) &p_cOtro );
	}
	if ( ( ES_NULO ( p_cPrimero ) ) || ( ES_NULO ( p_cSegundo ) ) ||
		 ( strcmp ( p_cPrimero, p_cSegundo ) != 0 ) )
	{
		printf( "Error caso 2: el nombre cambio tras otras veinte consultas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cPrimero );
	MemLiberar ( (void **) &p_cSegundo );
	return ( iRes );
}

static int TestSisUsrLogin01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisUsrLogin 01:\n" );
	char * p_cLogin = SisUsrObtenerUsuarioLogin ();
	if ( ES_NULO ( p_cLogin ) )
	{
		printf( "Error caso 1: se esperaba nombre de login no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cLogin );
	return ( iRes );
}



int TestSistemaUsuario ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaUsuario]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisUsrNombre01 () == BOOL_VAL_CIERTO ) &&
			( TestSisUsrNombre02 () == BOOL_VAL_CIERTO ) &&
			( TestSisUsrLogin01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
