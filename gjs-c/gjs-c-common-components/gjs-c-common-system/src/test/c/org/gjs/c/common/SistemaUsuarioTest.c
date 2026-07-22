#include "Base.h"

#include "SistemaUsuario.h"



static int TestSisUsrNombre01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisUsrNombre 01:\n" );
	/* Los nombres devueltos por estas rutinas son estaticos/cacheados: NO se
	   liberan. */
	if ( ES_NULO ( SisUsrObtenerNombre ( 0 ) ) )
	{
		printf( "Error caso 1: se esperaba nombre de usuario no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SisUsrObtenerNombreGrupo ( 0 ) ) )
	{
		printf( "Error caso 2: se esperaba nombre de grupo no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
#if ( defined ( WIN ) )
	if ( strcmp ( SisUsrObtenerNombre ( 0 ), "user" ) != 0 )
	{
		printf( "Error caso 3: en WIN se esperaba \"user\" para id 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( strcmp ( SisUsrObtenerNombre ( 7777 ), "<none>" ) != 0 )
	{
		printf( "Error caso 4: en WIN se esperaba \"<none>\" para id desconocido\n" );
		iRes = BOOL_VAL_FALSO;
	}
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
