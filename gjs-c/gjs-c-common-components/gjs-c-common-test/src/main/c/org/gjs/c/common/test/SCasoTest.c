#include "SCasoTest.h"
#include "CTestConfig.h"



SCasoTest * SCasTstCrearSimple ( const char * p_cId, PFUNINTV p_fTest )
{
	return ( SCasTstEncapsularSimple ( SCasTstsCrear ( p_cId, p_fTest ) ) );
}

SCasoTest * SCasTstCrearAislado ( const char * p_cId, PFUNINTV p_fTest, int iCodigoEsperado )
{
	return ( SCasTstEncapsularAislado ( SCasTstaCrear ( p_cId, p_fTest, iCodigoEsperado ) ) );
}

SCasoTest * SCasTstEncapsularSimple ( SCasoTestSimple * p_caststsObj )
{
	SCasoTest * p_caststObj;

	if ( ES_VALIDO ( p_caststsObj ) )
	{
		p_caststObj = ( SCasoTest * ) MemReservar ( sizeof ( SCasoTest ) );
		if ( ES_VALIDO ( p_caststObj ) )
		{
			p_caststObj->iTipo = 0;
			p_caststObj->p_caststsObj = p_caststsObj;
		}
	}
	else
	{
		p_caststObj = NULL;
	}
	return ( p_caststObj );
}

SCasoTest * SCasTstEncapsularAislado ( SCasoTestAislado * p_caststaObj )
{
	SCasoTest * p_caststObj;

	if ( ES_VALIDO ( p_caststaObj ) )
	{
		p_caststObj = ( SCasoTest * ) MemReservar ( sizeof ( SCasoTest ) );
		if ( ES_VALIDO ( p_caststObj ) )
		{
			p_caststObj->iTipo = 1;
			p_caststObj->p_caststaObj = p_caststaObj;
		}
	}
	else
	{
		p_caststObj = NULL;
	}
	return ( p_caststObj );
}

void SCasTstDestruir ( SCasoTest ** p_p_caststObj )
{
	SCasoTest * p_caststObj;

	if ( ES_VALIDO ( p_p_caststObj ) )
	{
		p_caststObj = *p_p_caststObj;
		if ( ES_VALIDO ( p_caststObj ) )
		{
			if ( p_caststObj->iTipo == 0 )
			{
				SCasTstsDestruir ( &(p_caststObj->p_caststsObj) );
			}
			else if ( p_caststObj->iTipo == 1 )
			{
				SCasTstaDestruir ( &(p_caststObj->p_caststaObj) );
			}
			MemLiberar ( (void **) p_p_caststObj );
		}
	}
}

const char * SCasTstObtenerId ( SCasoTest * p_caststObj ) 
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_caststObj ) )
	{
		if ( p_caststObj->iTipo == 0 )
		{
			p_cRes = SCasTstsObtenerId ( p_caststObj->p_caststsObj );
		}
		else if ( p_caststObj->iTipo == 1 )
		{
			p_cRes = SCasTstaObtenerId ( p_caststObj->p_caststaObj );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCasTstEjecutar ( SCasoTest * p_caststObj )
{
	int iRes;

	if ( ES_VALIDO ( p_caststObj ) )
	{
		if ( p_caststObj->iTipo == 0 )
		{
			iRes = SCasTstsEjecutar ( p_caststObj->p_caststsObj );
		}
		else if ( p_caststObj->iTipo == 1 )
		{
			iRes = SCasTstaEjecutar ( p_caststObj->p_caststaObj );
		}
		else
		{
			iRes = RESULTADO_CASO_TEST_KO;
			printf ("%s    Caso mal definido%s\n", ANSI_ROJO, ANSI_RESETEAR );
		}
	}
	else
	{
		iRes = RESULTADO_CASO_TEST_FAIL;
	}
	return ( iRes );
}		

int SCasTstEsCasoSimple ( SCasoTest * p_caststObj )
{
	int iRes;

	if ( ES_VALIDO ( p_caststObj ) )
	{
		if ( p_caststObj->iTipo == 0 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}		

int SCasTstEsCasoAislado ( SCasoTest * p_caststObj )
{
	int iRes;

	if ( ES_VALIDO ( p_caststObj ) )
	{
		if ( p_caststObj->iTipo == 1 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}		

SCasoTestSimple * SCasTstCasoSimple ( SCasoTest * p_caststObj )
{
	SCasoTestSimple * p_caststsRes;

	if ( ES_VALIDO ( p_caststObj ) )
	{
		if ( p_caststObj->iTipo == 0 )
		{
			p_caststsRes = p_caststObj->p_caststsObj;
		}
		else
		{
			p_caststsRes = NULL;
		}
	}
	else
	{
		p_caststsRes = NULL;
	}
	return ( p_caststsRes );
}		

SCasoTestAislado * SCasTstCasoAislado ( SCasoTest * p_caststObj )
{
	SCasoTestAislado * p_caststaRes;

	if ( ES_VALIDO ( p_caststObj ) )
	{
		if ( p_caststObj->iTipo == 1 )
		{
			p_caststaRes = p_caststObj->p_caststaObj;
		}
		else
		{
			p_caststaRes = NULL;
		}
	}
	else
	{
		p_caststaRes = NULL;
	}
	return ( p_caststaRes );
}		


