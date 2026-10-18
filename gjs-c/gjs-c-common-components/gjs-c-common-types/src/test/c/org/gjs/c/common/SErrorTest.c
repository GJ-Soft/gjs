#include "Base.h"

#include "SError.h"



static int TestSErrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrCrear 01:\n" );
	SError * p_errRes = SErrCrear ( NULL, NULL );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba invalido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba no advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			printf( "Error caso 1: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

static int TestSErrCrear02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrCrear 02:\n" );
	SError * p_errRes = SErrCrear ( "COD-001", "Descripcion 001" );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 0 ) 
		{
			printf( "Error caso 1: Se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba no advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrCodigo ( p_errRes ), "COD-001" ) != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de codigo errorneo: %s\n", SErrCodigo ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrDescripcion ( p_errRes ), "Descripcion 001" ) != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de descripcion errorneo: %s\n", SErrDescripcion ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

static int TestSErrCrearAdvertencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrCrearAdvertencia 01:\n" );
	SError * p_errRes = SErrCrearAdvertencia ( NULL, NULL );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba invalido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 0 ) 
		{
			printf( "Error caso 1: Se esperaba advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			printf( "Error caso 1: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

static int TestSErrCrearAdvertencia02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrCrearAdvertencia 02:\n" );
	SError * p_errRes = SErrCrearAdvertencia ( "COD-001", "Descripcion 001" );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 0 ) 
		{
			printf( "Error caso 1: Se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 0 ) 
		{
			printf( "Error caso 1: Se esperaba advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrCodigo ( p_errRes ), "COD-001" ) != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de codigo errorneo: %s\n", SErrCodigo ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrDescripcion ( p_errRes ), "Descripcion 001" ) != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de descripcion errorneo: %s\n", SErrDescripcion ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

static int TestSErrCrearForm01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrCrearForm 01:\n" );
	SError * p_errRes = SErrCrearForm ( NULL, NULL );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba invalido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba no advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			printf( "Error caso 1: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto 1\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	p_errRes = SErrCrearForm ( "COD-001", NULL );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 2: Se esperaba invalido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 2: Se esperaba no advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrCodigo ( p_errRes ), "COD-001" ) != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de codigo errorneo: %s\n", SErrCodigo ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			printf( "Error caso 2: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto 2\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

static int TestSErrCrearForm02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrCrearForm 02:\n" );
	SError * p_errRes = SErrCrearForm ( "COD-001", "Error valor=%d y descripcion=%s", 1, "Error" );
	if ( p_errRes != NULL )
	{
		if ( SErrEsValido ( p_errRes ) == 0 ) 
		{
			printf( "Error caso 1: Se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SErrEsAdvertencia ( p_errRes ) == 1 ) 
		{
			printf( "Error caso 1: Se esperaba no advertencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrCodigo ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrCodigo ( p_errRes ), "COD-001" ) != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de codigo errorneo: %s\n", SErrCodigo ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba codigo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SErrDescripcion ( p_errRes ) ) ) 
		{
			if ( CadComparar ( SErrDescripcion ( p_errRes ), "Error valor=1 y descripcion=Error") != COMP_IGUAL ) 
			{
				printf( "Error caso 1: Valor de descripcion errorneo: %s\n", SErrDescripcion ( p_errRes ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperaba descripcion nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_errRes );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

/* SErrPtr envuelve el objeto en un SPtr con SErrDestruir como destructor: al
   destruir el SPtr se libera tambien el SError. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSErrPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SError * p_errObj = SErrCrear ( "COD-001", "Descripcion 001" );
	SPtr * p_ptrObj = SErrPtr ( p_errObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SErrDestruir ( &p_errObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_errObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SError\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SError pasa a ser del SPtr: se libera con el, no por separado. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* Con objeto nulo, SErrPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSErrPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SErrPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SErrPtr ( NULL );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: con objeto nulo se esperaba un SPtr vacio, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: con objeto nulo el SPtr deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 3: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	ErrLimpiar ();
	return ( iRes );
}



int TestSError ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SError]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSErrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSErrCrear02 () == BOOL_VAL_CIERTO )&&
			( TestSErrCrearAdvertencia01 () == BOOL_VAL_CIERTO )&&
			( TestSErrCrearAdvertencia02 () == BOOL_VAL_CIERTO )&&
			( TestSErrCrearForm01 () == BOOL_VAL_CIERTO )&&
			( TestSErrCrearForm02 () == BOOL_VAL_CIERTO ) &&
			( TestSErrPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSErrPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
