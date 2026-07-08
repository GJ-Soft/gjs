
#include "SRelojProgramable.h"
#include "SistemaProcesos.h"
#include "SistemaTiempo.h"

#include "SistemaConfig.h"







typedef struct
{
	PPRCV 			fAlarma;
	long			lHoraAlarma;
	SReloj *		p_rljObj;
	int volatile *	p_iParar;
	int 			iSaltado;
	
} TSRelojProgramableParamHilo;






static void SRljPrgInicializar ( SRelojProgramable * p_rljprgObj );
#if ( defined ( WIN ) )
static int SRelojProgramableCuerpoHilo ( void * p_vDatos );
#else
static void * SRelojProgramableCuerpoHilo ( void * p_vDatos );
#endif



SRelojProgramable * SRljPrgCrear ( long lHora )
{
	SRelojProgramable * p_rljprgObj;
	
	p_rljprgObj = (SRelojProgramable *) MemReservar ( sizeof ( SRelojProgramable ) );
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		p_rljprgObj->p_rljObj = SRljCrear ( lHora );
		SRljPrgInicializar ( p_rljprgObj ); 
	}
	return ( p_rljprgObj );
}

SRelojProgramable * SRljPrgCrearExt ( long lHora, long lHoraAlarma, PPRCV fAlarma )
{
	SRelojProgramable * p_rljprgObj;
	
	p_rljprgObj = SRljPrgCrear ( lHora );
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		SRljPrgEstablecerAlarma ( p_rljprgObj, lHoraAlarma, fAlarma ); 
	}
	return ( p_rljprgObj );
}

void SRljPrgDestruir ( SRelojProgramable ** p_p_rljprgObj )
{
	SRelojProgramable * p_rljprgObj;
	
	if ( ES_VALIDO ( p_p_rljprgObj ) )
	{
		p_rljprgObj = *p_p_rljprgObj;
		if ( ES_VALIDO ( p_rljprgObj ) )
		{
			SRljPrgDesactivarAlarma ( p_rljprgObj );
			SRljDestruir ( &(p_rljprgObj->p_rljObj) );
			MemLiberar ( (void **) p_p_rljprgObj );
		}
	}
}

long SRljPrgHoraAlarma ( SRelojProgramable * p_rljprgObj )
{
	long lRes;
	
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		lRes = p_rljprgObj->lHoraAlarma;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

PPRCV SRljPrgProcedimientoAlarma ( SRelojProgramable * p_rljprgObj )
{
	PPRCV fRes;
	
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		fRes = p_rljprgObj->fAlarma;
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

void SRljPrgEstablecerAlarma ( SRelojProgramable * p_rljprgObj, long lHoraAlarma, PPRCV fAlarma )
{
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		if ( p_rljprgObj->iAlarma == 0 )
		{
			if ( ( HorFormEsValida ( lHoraAlarma ) == 1 ) && ES_VALIDO ( fAlarma ) )
			{
				p_rljprgObj->lHoraAlarma = lHoraAlarma;
				p_rljprgObj->fAlarma = fAlarma;
				p_rljprgObj->iParar = 0;
			}
		}
	}
}

int SRljPrgAlarmaActivada ( SRelojProgramable * p_rljprgObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		iRes = p_rljprgObj->iAlarma;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRljPrgActivarAlarma ( SRelojProgramable * p_rljprgObj )
{
	int								iRes;
	TSRelojProgramableParamHilo *	p_parhInfo;

	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		if ( ( p_rljprgObj->iAlarma == 0 ) && ( HorFormEsValida ( p_rljprgObj->lHoraAlarma ) == 1 ) && ES_VALIDO ( p_rljprgObj->fAlarma ) &&
			 ( p_rljprgObj->thTID == 0 ) ) 
		{
			p_rljprgObj->iParar = 0;
			p_parhInfo = (TSRelojProgramableParamHilo *) MemReservar ( sizeof ( TSRelojProgramableParamHilo ) );
			if ( ES_VALIDO ( p_parhInfo ) )
			{
				p_parhInfo->fAlarma = p_rljprgObj->fAlarma;
				p_parhInfo->lHoraAlarma = p_rljprgObj->lHoraAlarma;
				p_parhInfo->p_rljObj = p_rljprgObj->p_rljObj;
				p_parhInfo->p_iParar = &(p_rljprgObj->iParar);
				p_parhInfo->iSaltado = 0;
				p_rljprgObj->p_vParams = (void *) p_parhInfo;

				p_rljprgObj->thTID = SisCrearHilo ( SRelojProgramableCuerpoHilo, (void *) p_parhInfo, 0 );
				if ( p_rljprgObj->thTID > 0 )
				{
					iRes = 1;
					p_rljprgObj->iAlarma = 1;
				}
				else
				{
					iRes = 0;
					MemLiberar ( (void **) &p_parhInfo );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SRljPrgDesactivarAlarma ( SRelojProgramable * p_rljprgObj )
{
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		if ( p_rljprgObj->iAlarma == 1 )
		{
			if ( ES_VALIDO ( p_rljprgObj->p_vParams ) )
			{
				p_rljprgObj->iParar = 1;
			}
			while ( p_rljprgObj->iParar == 1 )
			{
				SisEsperar ( 5 );
			}
			p_rljprgObj->iAlarma = 0;
			p_rljprgObj->thTID = 0;
			MemLiberar ( (void **) &(p_rljprgObj->p_vParams) );
		}
	}
}

void SRljPrgInicializar ( SRelojProgramable * p_rljprgObj )
{
	if ( ES_VALIDO ( p_rljprgObj ) )
	{
		p_rljprgObj->lHoraAlarma = -1;
		p_rljprgObj->fAlarma = NULL;
		p_rljprgObj->thTID = 0;
		p_rljprgObj->iAlarma = 0;
		p_rljprgObj->p_vParams = NULL;
		p_rljprgObj->iParar = 0;
	}
}


#if ( defined ( WIN ) )
static int SRelojProgramableCuerpoHilo ( void * p_vDatos )
#else
static void * SRelojProgramableCuerpoHilo ( void * p_vDatos )
#endif
{
	long							lHora;
	int								iRes;
	int								iSaltar;
#  if ( !defined ( WIN ) )
	void *							p_vRes;
#  endif
	TSRelojProgramableParamHilo *	p_parhInfo;

	if ( ES_VALIDO ( p_vDatos ) )
	{
		p_parhInfo = (TSRelojProgramableParamHilo *) p_vDatos;
		if ( ES_VALIDO ( p_parhInfo->p_rljObj  ) && ( HorFormEsValida ( p_parhInfo->lHoraAlarma ) == 1 ) &&
			 ES_VALIDO ( p_parhInfo->fAlarma ) && ( *p_parhInfo->p_iParar == 0 ) )
		{
			iRes = 1;
			
			while ( ( iRes == 1 ) && ( *p_parhInfo->p_iParar == 0 ) )
			{
				iSaltar = 0;
				lHora = SRljHora ( p_parhInfo->p_rljObj );
				if ( p_parhInfo->iSaltado == 1 )
				{
					if ( lHora <= p_parhInfo->lHoraAlarma )
					{
						p_parhInfo->iSaltado = 0;
					}
				}
				if ( p_parhInfo->iSaltado == 0 ) 
				{
					if ( lHora >= p_parhInfo->lHoraAlarma )
					{ 
						iSaltar = 1;
					}
				}

				if ( ( iSaltar == 1) && ( iRes == 1 ) && ( *p_parhInfo->p_iParar == 0 ) )
				{
					if ( ES_VALIDO ( p_parhInfo->fAlarma ) )
					{
						p_parhInfo->iSaltado = 1;
						p_parhInfo->fAlarma ();
					}
					else
					{
						iRes = 0;
					}
				}

				if ( ( *p_parhInfo->p_iParar == 0 ) && ( iRes == 1 ) )
				{
					SisEsperar ( 200 );
				}
			}

			if ( *p_parhInfo->p_iParar == 1 )
			{
				*p_parhInfo->p_iParar = 0;
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
#  if ( !defined ( WIN ) )
	p_vRes = NULL;
#  endif

#  if ( defined ( WIN ) )
	return ( iRes );
#  else
	pthread_exit ( p_vRes );
#  endif
}



