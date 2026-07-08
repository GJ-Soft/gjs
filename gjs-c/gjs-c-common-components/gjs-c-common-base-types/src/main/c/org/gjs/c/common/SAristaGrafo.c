
#include "SAristaGrafo.h"



#include "TiposBasicosConfig.h"


static void SAriGrfInicializar ( SAristaGrafo * p_arigrfObj );



SAristaGrafo * SAriGrfCrear () 
{
   SAristaGrafo * p_arigObj;
   
   p_arigObj = (SAristaGrafo *) MemReservar ( sizeof ( SAristaGrafo ) );
   if ( ES_VALIDO ( p_arigObj ) )
   {   
		SAriGrfInicializar ( p_arigObj );
   }
   return ( p_arigObj );
}

SAristaGrafo * SAriGrfCrearExt ( SNodoGrafo * p_nodgInicial, SNodoGrafo * p_nodgFinal )
{
   SAristaGrafo * p_arigObj;
   
   p_arigObj = SAriGrfCrear ();
   if ( ES_VALIDO ( p_arigObj ) )
   {   
		SAriGrfInicializar ( p_arigObj );
		if ( ( SAriGrfConectarNodoInicial ( p_arigObj, p_nodgInicial ) == 0 ) || ( SAriGrfConectarNodoFinal ( p_arigObj, p_nodgFinal ) == 0 ) )
		{
			SAriGrfDestruir ( &p_arigObj );
		}
   }
   return ( p_arigObj );
}

void SAriGrfDestruir ( SAristaGrafo ** p_p_arigObj )
{
   SAristaGrafo * p_arigObj;
   
   if ( ES_VALIDO ( p_p_arigObj ) )
   {   
	   p_arigObj = *p_p_arigObj;
	   if ( ES_VALIDO ( p_arigObj ) )
	   {   
			SAriGrfDesconectar ( p_arigObj );
			MemLiberar ( (void **) p_p_arigObj );
		}
	}
}

SNodoGrafo * SAriGrfNodoInicial ( SAristaGrafo * p_arigObj )
{
	SNodoGrafo * p_nodgRes;
	
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_nodgRes = p_arigObj->p_nodgInicial;
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

SNodoGrafo * SAriGrfNodoFinal ( SAristaGrafo * p_arigObj )
{
	SNodoGrafo * p_nodgRes;
	
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_nodgRes = p_arigObj->p_nodgFinal;
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

int SAriGrfTieneNodoInicial ( SAristaGrafo * p_arigObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		if ( ES_VALIDO ( p_arigObj->p_nodgInicial ) )
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

int SAriGrfTieneNodoFinal ( SAristaGrafo * p_arigObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		if ( ES_VALIDO ( p_arigObj->p_nodgFinal ) )
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

int SAriGrfConectar ( SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgInicial, SNodoGrafo * p_nodgFinal )
{
	int iRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		if ( ( SAriGrfConectarNodoInicial ( p_arigObj, p_nodgInicial ) == 1 ) &&
			 ( SAriGrfConectarNodoFinal ( p_arigObj, p_nodgFinal ) == 1 ) )
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

int SAriGrfConectarNodoInicial ( SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->p_nodgInicial = p_nodgObj;
		if ( ES_VALIDO ( p_arigObj->p_nodgInicial ) )
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

int SAriGrfConectarNodoFinal ( SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->p_nodgFinal = p_nodgObj;
		if ( ES_VALIDO ( p_arigObj->p_nodgFinal ) )
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

void SAriGrfDesconectar ( SAristaGrafo * p_arigObj )
{
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->p_nodgInicial = NULL;
		p_arigObj->p_nodgFinal = NULL;
	}
}

SNodoGrafo * SAriGrfDesconectarNodoInicial ( SAristaGrafo * p_arigObj )
{
	SNodoGrafo * p_nodgRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_nodgRes = p_arigObj->p_nodgInicial;
		p_arigObj->p_nodgInicial = NULL;
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

SNodoGrafo * SAriGrfDesconectarNodoFinal ( SAristaGrafo * p_arigObj )
{
	SNodoGrafo * p_nodgRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_nodgRes = p_arigObj->p_nodgFinal;
		p_arigObj->p_nodgFinal = NULL;
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

void SAriGrfLimpiarNodoInicial ( SAristaGrafo * p_arigObj )
{
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->p_nodgInicial = NULL;
	}
}

void SAriGrfLimpiarNodoFinal ( SAristaGrafo * p_arigObj, int iLiberar )
{
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		if ( ES_VALIDO ( p_arigObj->p_nodgFinal ) )
		{
			if ( iLiberar == 1 )
			{
				SNodGrfLimpiarAristasEntrada ( p_arigObj->p_nodgFinal );
				SNodGrfLimpiarAristasSalida ( p_arigObj->p_nodgFinal, 1 );
				SNodGrfDestruir ( &(p_arigObj->p_nodgFinal) );
			}
		}
	}
}

int SAriGrfEstaRecorrida ( SAristaGrafo * p_arigObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arigObj ) )
	{   
		iRes = p_arigObj->iRecorrida;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SAriGrfMarcarComoRecorrida ( SAristaGrafo * p_arigObj )
{
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->iRecorrida = 1;
	}
}

void SAriGrfDesmarcarComoRecorrida ( SAristaGrafo * p_arigObj )
{
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->iRecorrida = 0;
	}
}

static void SAriGrfInicializar ( SAristaGrafo * p_arigObj )
{
	if ( ES_VALIDO ( p_arigObj ) )
	{   
		p_arigObj->iRecorrida = 0;
		p_arigObj->p_nodgInicial = NULL;
		p_arigObj->p_nodgFinal = NULL;
	}
}

