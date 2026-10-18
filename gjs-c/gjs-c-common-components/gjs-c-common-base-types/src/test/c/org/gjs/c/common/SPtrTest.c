#include "Base.h"

#include "SPtr.h"



/* Destructor de prueba: cuenta las llamadas, apunta el objeto que recibe y   */
/* lo libera como haria el destructor por defecto.                            */
static int iNumLlamadasDestructor = 0;
static void * p_vObjetoDestruido = NULL;

static void DestructorContador ( void ** p_p_vObj )
{
	iNumLlamadasDestructor = iNumLlamadasDestructor + 1;
	p_vObjetoDestruido = *p_p_vObj;
	MemLiberar ( p_p_vObj );
}

static int * CrearEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( p_iDato );
}



static int TestSPtrCrearDef01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrCrearDef 01:\n" );

	int * p_iDato = CrearEntero ( 42 );
	SPtr * p_ptrObj = SPtrCrearDef ( p_iDato );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_iDato );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el puntero deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_iDato )
		{
			printf( "Error caso 3: el objeto deberia ser el mismo puntero que se paso al crear\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SPtrObjeto ( p_ptrObj ) ) != 42 )
		{
			printf( "Error caso 4: el objeto deberia contener 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El destructor por defecto libera el objeto con MemLiberar. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}

static int TestSPtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrCrear 01:\n" );

	iNumLlamadasDestructor = 0;
	p_vObjetoDestruido = NULL;

	int * p_iDato = CrearEntero ( 7 );
	SPtr * p_ptrObj = SPtrCrear ( p_iDato, DestructorContador );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_iDato );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el puntero deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_iDato )
		{
			printf( "Error caso 3: el puntero deberia envolver el objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 0 )
		{
			printf( "Error caso 4: el destructor no deberia llamarse antes de destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
		if ( iNumLlamadasDestructor != 1 )
		{
			printf( "Error caso 5: el destructor deberia llamarse exactamente una vez (%d)\n", iNumLlamadasDestructor );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_vObjetoDestruido != p_iDato )
		{
			printf( "Error caso 6: el destructor deberia recibir el objeto envuelto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Destruir otra vez el puntero ya nulo no debe volver a llamar al destructor. */
		SPtrDestruir ( &p_ptrObj );
		if ( iNumLlamadasDestructor != 1 )
		{
			printf( "Error caso 8: destruir un nulo no deberia llamar al destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}

static int TestSPtrEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrEstablecer 01:\n" );

	iNumLlamadasDestructor = 0;
	p_vObjetoDestruido = NULL;

	int * p_iA = CrearEntero ( 1 );
	int * p_iB = CrearEntero ( 2 );
	SPtr * p_ptrObj = SPtrCrear ( p_iA, DestructorContador );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 0: no se pudo crear el puntero\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_iA );
		MemLiberar ( (void **) &p_iB );
	}
	else if ( ES_NULO ( p_iB ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
		SPtrDestruir ( &p_ptrObj );
	}
	else
	{
		/* Cambiar el objeto destruye el anterior y guarda el nuevo. */
		if ( SPtrEstablecer ( p_ptrObj, p_iB ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 1 )
		{
			printf( "Error caso 2: el destructor deberia llamarse una vez (%d)\n", iNumLlamadasDestructor );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_vObjetoDestruido != p_iA )
		{
			printf( "Error caso 3: el destructor deberia recibir el objeto anterior\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_iB )
		{
			printf( "Error caso 4: el objeto deberia ser el nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SPtrObjeto ( p_ptrObj ) ) != 2 )
		{
			printf( "Error caso 5: el objeto deberia valer 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer el mismo objeto no lo destruye: si lo hiciera, el SPtr se
		   quedaria con un puntero ya liberado. */
		if ( SPtrEstablecer ( p_ptrObj, p_iB ) != 1 )
		{
			printf( "Error caso 6: se esperaba resultado 1 al establecer el mismo objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 1 )
		{
			printf( "Error caso 7: establecer el mismo objeto no deberia destruirlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_iB )
		{
			printf( "Error caso 8: establecer el mismo objeto deberia conservarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer NULL destruye el objeto y deja el puntero vacio. */
		if ( SPtrEstablecer ( p_ptrObj, NULL ) != 1 )
		{
			printf( "Error caso 9: se esperaba resultado 1 al establecer nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 2 )
		{
			printf( "Error caso 10: el destructor deberia llamarse otra vez (%d)\n", iNumLlamadasDestructor );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_vObjetoDestruido != p_iB )
		{
			printf( "Error caso 11: el destructor deberia recibir el objeto que habia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 12: tras establecer nulo deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrEsValido ( p_ptrObj ) != 0 )
		{
			printf( "Error caso 13: tras establecer nulo no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SPtrObjeto ( p_ptrObj ) ) )
		{
			printf( "Error caso 14: tras establecer nulo el objeto deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vacio no hay nada que destruir: el destructor nunca recibe un nulo,
		   ni al establecer otro objeto ni al destruir el SPtr. */
		int * p_iC = CrearEntero ( 3 );
		if ( SPtrEstablecer ( p_ptrObj, p_iC ) != 1 )
		{
			printf( "Error caso 15: se esperaba resultado 1 al establecer sobre un vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 2 )
		{
			printf( "Error caso 16: establecer sobre un vacio no deberia llamar al destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_iC )
		{
			printf( "Error caso 17: el objeto deberia ser el establecido sobre el vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrEstablecer ( p_ptrObj, NULL );
		iNumLlamadasDestructor = 0;
		SPtrDestruir ( &p_ptrObj );
		if ( iNumLlamadasDestructor != 0 )
		{
			printf( "Error caso 18: destruir un vacio no deberia llamar al destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 19: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Sin SPtr no se establece nada. */
	if ( SPtrEstablecer ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 20: con puntero nulo se esperaba resultado 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Con el destructor por defecto: al cambiar de objeto el anterior se libera.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSPtrEstablecer02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrEstablecer 02:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	int * p_iA = CrearEntero ( 1 );
	SPtr * p_ptrObj = SPtrCrearDef ( p_iA );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 0: no se pudo crear el puntero\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_iA );
	}
	else
	{
		if ( SPtrEstablecer ( p_ptrObj, CrearEntero ( 2 ) ) != 1 )
		{
			printf( "Error caso 1: establecer deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SPtrObjeto ( p_ptrObj ) ) != 2 )
		{
			printf( "Error caso 2: el objeto deberia pasar a valer 2\n" );
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
	return ( iRes );
}

static int TestSPtrEstaVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrEstaVacio 01:\n" );

	int * p_iDato = CrearEntero ( 5 );
	SPtr * p_ptrObj = SPtrCrearDef ( p_iDato );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 0: no se pudo crear el puntero\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_iDato );
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 0 )
		{
			printf( "Error caso 1: recien creado con objeto no deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
	}
	/* Como el resto de la libreria, un puntero nulo cuenta como vacio. */
	if ( SPtrEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 2: un puntero nulo deberia contar como vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Crear sin objeto da un SPtr vacio, que puede recibir uno despues con
   SPtrEstablecer. El destructor solo se llama cuando hay objeto. Con
   MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSPtrCrearVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrCrearVacio 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumLlamadasDestructor = 0;
	p_vObjetoDestruido = NULL;

	SPtr * p_ptrObj = SPtrCrear ( NULL, DestructorContador );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: sin objeto se esperaba un SPtr vacio, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: creado sin objeto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrEsValido ( p_ptrObj ) != 0 )
		{
			printf( "Error caso 3: vacio no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SPtrObjeto ( p_ptrObj ) ) )
		{
			printf( "Error caso 4: vacio deberia devolver objeto nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int * p_iDato = CrearEntero ( 3 );
		if ( SPtrEstablecer ( p_ptrObj, p_iDato ) != 1 )
		{
			printf( "Error caso 5: establecer sobre un SPtr vacio deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 0 )
		{
			printf( "Error caso 6: establecer sobre un SPtr vacio no deberia llamar al destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 7: con objeto establecido deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
		if ( iNumLlamadasDestructor != 1 )
		{
			printf( "Error caso 8: se esperaba 1 llamada al destructor: %d\n", iNumLlamadasDestructor );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_vObjetoDestruido != p_iDato )
		{
			printf( "Error caso 9: el destructor deberia recibir el objeto establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}

	/* Igual con el destructor por defecto; destruirlo vacio no libera nada mas. */
	p_ptrObj = SPtrCrearDef ( NULL );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 10: sin objeto se esperaba un SPtr vacio por defecto, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 11: creado por defecto sin objeto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 12: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 13: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSPtrPreparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrPreparar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumLlamadasDestructor = 0;
	p_vObjetoDestruido = NULL;

	SPtr * p_ptrObj = SPtrPreparar ( DestructorContador );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: con destructor se esperaba un SPtr vacio, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: preparado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_ptrObj->p_fDestructor != DestructorContador )
		{
			printf( "Error caso 3: deberia guardar el destructor recibido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int * p_iDato = CrearEntero ( 4 );
		if ( SPtrEstablecer ( p_ptrObj, p_iDato ) != 1 )
		{
			printf( "Error caso 4: establecer sobre un SPtr preparado deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
		if ( iNumLlamadasDestructor != 1 )
		{
			printf( "Error caso 5: se esperaba 1 llamada al destructor: %d\n", iNumLlamadasDestructor );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_vObjetoDestruido != p_iDato )
		{
			printf( "Error caso 6: el destructor deberia recibir el objeto establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}

	/* Sin destructor no se prepara nada. */
	if ( ES_VALIDO ( SPtrPreparar ( NULL ) ) )
	{
		printf( "Error caso 7: se esperaba nulo al preparar sin destructor\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 8: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	ErrLimpiar ();
	return ( iRes );
}

static int TestSPtrDestruirSinLiberar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrDestruirSinLiberar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumLlamadasDestructor = 0;
	p_vObjetoDestruido = NULL;

	/* Libera el SPtr, pero el objeto sigue vivo y vuelve a ser del llamante. */
	int * p_iDato = CrearEntero ( 5 );
	SPtr * p_ptrObj = SPtrCrear ( p_iDato, DestructorContador );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se ha creado el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		SPtrDestruirSinLiberar ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 2: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumLlamadasDestructor != 0 )
		{
			printf( "Error caso 3: no deberia haberse llamado al destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *p_iDato != 5 )
		{
			printf( "Error caso 4: el objeto deberia seguir intacto: %d\n", *p_iDato );
			iRes = BOOL_VAL_FALSO;
		}
	}
	MemLiberar ( (void **) &p_iDato );

	/* Con argumentos nulos no debe romper. */
	SPtr * p_ptrNulo = NULL;
	SPtrDestruirSinLiberar ( NULL );
	SPtrDestruirSinLiberar ( &p_ptrNulo );
	if ( iNumLlamadasDestructor != 0 )
	{
		printf( "Error caso 5: no deberia haberse llamado al destructor con nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 6: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSPtrInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPtrInvalidos 01:\n" );

	iNumLlamadasDestructor = 0;

	/* Sin destructor no se crea nada; el objeto sigue siendo del llamante. */
	int * p_iDato = CrearEntero ( 1 );
	if ( ES_VALIDO ( SPtrCrear ( p_iDato, NULL ) ) )
	{
		printf( "Error caso 1: se esperaba nulo al crear sin destructor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_iDato );
	if ( ES_VALIDO ( SPtrCrear ( NULL, NULL ) ) )
	{
		printf( "Error caso 2: se esperaba nulo al crear sin objeto ni destructor\n" );
		iRes = BOOL_VAL_FALSO;
	}

	if ( SPtrEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 3: un puntero nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SPtrObjeto ( NULL ) ) )
	{
		printf( "Error caso 4: con puntero nulo se espera objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir con argumentos nulos no debe romper ni llamar al destructor. */
	SPtr * p_ptrNulo = NULL;
	SPtrDestruir ( NULL );
	SPtrDestruir ( &p_ptrNulo );
	if ( iNumLlamadasDestructor != 0 )
	{
		printf( "Error caso 5: no deberia haberse llamado al destructor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}


int TestSPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPtrCrearDef01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrEstablecer02 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrEstaVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrCrearVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrPreparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrDestruirSinLiberar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPtrInvalidos01 () == BOOL_VAL_CIERTO ) )
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
