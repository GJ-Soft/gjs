#include "SCasoTestSimple.h"
#include "CTestConfig.h"



SCasoTestSimple * SCasTstsCrear ( const char * p_cId, PFUNINTV p_fTest )
{
	SCasoTestSimple * p_caststsObj;

	if ( CadEsToken ( p_cId ) && ES_VALIDO ( p_fTest ) )
	{
		p_caststsObj = (SCasoTestSimple *) MemReservar ( sizeof ( SCasoTestSimple ) );
		if ( ES_VALIDO ( p_caststsObj ) )
		{
			p_caststsObj->p_cIdCaso = CadDuplicar ( p_cId );
			if ( ES_VALIDO ( p_caststsObj->p_cIdCaso ) )
			{
				p_caststsObj->p_fTestCaso = p_fTest;
			}
			else
			{
				MemLiberar ( (void **) &p_caststsObj );
			}
		}
	}
	else
	{
		p_caststsObj = NULL;
	}
	return ( p_caststsObj );
}


void SCasTstsDestruir ( SCasoTestSimple ** p_p_caststsObj )
{
	SCasoTestSimple * p_caststsObj;

	if ( ES_VALIDO ( p_p_caststsObj ) )
	{
		p_caststsObj = *p_p_caststsObj;
		if ( ES_VALIDO ( p_caststsObj ) )
		{
			MemLiberar ( (void **) &( p_caststsObj->p_cIdCaso ) );
			MemLiberar ( (void **) p_p_caststsObj );
		}
	}
}

const char * SCasTstsObtenerId ( SCasoTestSimple * p_caststsObj ) 
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_caststsObj ) )
	{
		p_cRes = (const char *) p_caststsObj->p_cIdCaso;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCasTstsEjecutar ( SCasoTestSimple * p_caststsObj )
{
	int iRes;

	if ( ES_VALIDO ( p_caststsObj ) )
	{
		iRes = RESULTADO_CASO_TEST_OK;
		//AplicLogAnotar( "" );
		//AplicLogAnotar ( "-Caso %s:", p_caststsObj->p_cIdCaso );
		printf ( "  [Caso %s]\n", p_caststsObj->p_cIdCaso );
		if ( ES_VALIDO ( p_caststsObj->p_fTestCaso ) )
		{
			if ( p_caststsObj->p_fTestCaso() == 1 ) 
			{
				printf ("%s   Resultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
			}
			else
			{
				iRes = RESULTADO_CASO_TEST_KO;
				printf ("%s    Resultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
			}
		}
		else
		{
			//AplicLogAnotarError ( "Funcion no definida para el caso" );
			iRes = RESULTADO_CASO_TEST_FAIL;
		}
		printf ("  [Fin %s]\n", p_caststsObj->p_cIdCaso );
	}
	else
	{
		iRes = RESULTADO_CASO_TEST_FAIL;
	}
	return ( iRes );
}		
