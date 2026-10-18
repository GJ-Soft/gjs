#include "SPtr.h"



#include "TiposBasicosConfig.h"


static void _MemLiberar ( void ** p_p_vObj )
{
	MemLiberar ( p_p_vObj );
}


SPtr * SPtrCrearDef ( void * p_vObjeto )
{
	return ( SPtrCrear ( p_vObjeto, _MemLiberar ) );
}

SPtr * SPtrCrear ( void * p_vObjeto, PRC_DESTRUCTOR p_fDestructor )
{
	SPtr * p_ptrObj;
	
	if ( ES_VALIDO ( p_fDestructor ) )
	{
		p_ptrObj = (SPtr *) MemReservar ( sizeof ( SPtr ) );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			p_ptrObj->p_vObjeto = p_vObjeto;
			p_ptrObj->p_fDestructor = p_fDestructor;
		}
	}
	else
	{
		p_ptrObj = NULL;
	}
	return ( p_ptrObj );
}

SPtr * SPtrPreparar ( PRC_DESTRUCTOR p_fDestructor )
{
	return ( SPtrCrear ( NULL, p_fDestructor ) );
}

void SPtrDestruir ( SPtr ** p_p_ptrObj )
{
	SPtr * p_ptrObj;
	
	if ( ES_VALIDO ( p_p_ptrObj ) )
	{
		p_ptrObj = *p_p_ptrObj;

		if ( ES_VALIDO ( p_ptrObj ) )
		{
			if ( ES_VALIDO ( p_ptrObj->p_vObjeto ) )
			{
				if ( ES_VALIDO ( p_ptrObj->p_fDestructor ) )
				{
					p_ptrObj->p_fDestructor ( &(p_ptrObj->p_vObjeto) );
				}
			}
			MemLiberar ( (void **) p_p_ptrObj );
		}
	}
}

void SPtrDestruirSinLiberar ( SPtr ** p_p_ptrObj )
{
	SPtr * p_ptrObj;
	
	if ( ES_VALIDO ( p_p_ptrObj ) )
	{
		p_ptrObj = *p_p_ptrObj;

		if ( ES_VALIDO ( p_ptrObj ) )
		{
			MemLiberar ( (void **) p_p_ptrObj );
		}
	}
}

int SPtrEsValido ( SPtr * p_ptrObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ptrObj ) )
	{
		if ( ES_VALIDO ( p_ptrObj->p_vObjeto ) )
		{
			if ( ES_VALIDO ( p_ptrObj->p_fDestructor ) )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPtrEstaVacio ( SPtr * p_ptrObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ptrObj ) )
	{
		if ( ES_NULO ( p_ptrObj->p_vObjeto ) )
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
		iRes = 1;
	}
	return ( iRes );
}

void * SPtrObjeto ( SPtr * p_ptrObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_ptrObj ) )
	{
		p_vRes = p_ptrObj->p_vObjeto;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SPtrEstablecer ( SPtr * p_ptrObj, void * p_vObjeto )
{
	int iRes;

	if ( ES_VALIDO ( p_ptrObj ) )
	{
		if ( p_ptrObj->p_vObjeto != p_vObjeto )
		{
			if ( ES_VALIDO ( p_ptrObj->p_vObjeto ) )
			{
				if ( ES_VALIDO ( p_ptrObj->p_fDestructor ) )
				{
					p_ptrObj->p_fDestructor ( &(p_ptrObj->p_vObjeto) );
				}
			}
			p_ptrObj->p_vObjeto = p_vObjeto;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

