
#include "SMensaje.h"

#include "TiposDatosConfig.h"





SMensaje * SMsjCrear ( unsigned long ulId, SCadena * p_cadTexto )
{
	SMensaje *  	p_msjObj;
    SId *          	p_idMensaje;
    SDescripcion *  p_descTexto;

    p_idMensaje = SIdCrear ( ulId );
    p_descTexto = SDescCrearValor ( p_cadTexto );
    p_msjObj = SMsjEncapsular ( p_idMensaje, p_descTexto );
    if ( ES_NULO ( p_msjObj ) )
    {
        SIdDestruir ( &p_idMensaje );
        SDescDestruir ( &p_descTexto );
    }
    return ( p_msjObj );
}

SMensaje * SMsjCrearLit ( unsigned long ulId, const char * p_cTexto )
{
	SMensaje *  	p_msjObj;
    SId *          	p_idMensaje;
    SDescripcion *  p_descTexto;

    p_idMensaje = SIdCrear ( ulId );
    p_descTexto = SDescCrearValorLit ( p_cTexto );
    p_msjObj = SMsjEncapsular ( p_idMensaje, p_descTexto );
    if ( ES_NULO ( p_msjObj ) )
    {
        SIdDestruir ( &p_idMensaje );
        SDescDestruir ( &p_descTexto );
    }
    return ( p_msjObj );
}

SMensaje * SMsjEncapsular ( SId * p_idMensaje, SDescripcion * p_descTexto )
{
	SMensaje *	p_msjObj;
	
    if ( ES_VALIDO ( p_idMensaje ) )
    {
        p_msjObj = (SMensaje *) MemReservar ( sizeof ( SMensaje ) );
        if ( ES_VALIDO ( p_msjObj ) )
        {
            p_msjObj->p_entInfo = SEntEncapsular ( p_idMensaje );
            if ( ES_VALIDO ( p_msjObj->p_entInfo ) )
            {
                p_msjObj->p_descTexto = p_descTexto;
            }
            else
            {
                MemLiberar ( (void **) &p_msjObj );
            }
        }
    }
    else
    {
        p_msjObj = NULL;
    }
	return ( p_msjObj );
}

void SMsjDestruir ( SMensaje ** p_p_msjObj )
{
	SMensaje *   p_msjObj;

	if ( ES_VALIDO ( p_p_msjObj ) )
	{
		p_msjObj = *p_p_msjObj;

		if ( ES_VALIDO ( p_msjObj ) )
		{
			SEntDestruir ( &(p_msjObj->p_entInfo) );
            SDescDestruir ( &(p_msjObj->p_descTexto) );
			MemLiberar ( (void **) p_p_msjObj );
		}
	}
}

int SMsjEsValido ( SMensaje * p_msjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		if ( SEntEsValida ( p_msjObj->p_entInfo ) == 1 )
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

SId * SMsjId ( SMensaje * p_msjObj )
{
	SId * p_idRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		p_idRes = SEntId ( p_msjObj->p_entInfo );
	}
	else
	{
		p_idRes = NULL;
	}
	return ( p_idRes );
}

unsigned long SMsjValorId ( SMensaje * p_msjObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		ulRes = SEntValorId ( p_msjObj->p_entInfo );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

SDescripcion * SMsjTexto ( SMensaje * p_msjObj )
{
	SDescripcion * p_descRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		p_descRes = p_msjObj->p_descTexto;
	}
	else
	{
		p_descRes = NULL;
	}
	return ( p_descRes );
}

SCadena * SMsjValorTexto ( SMensaje * p_msjObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		p_cadRes = SDescValor ( p_msjObj->p_descTexto );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SMsjValorTextoLit ( SMensaje * p_msjObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		p_cRes = SDescValorLit ( p_msjObj->p_descTexto );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SMsjEsIgual ( SMensaje * p_msjObj, SMensaje * p_msjVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_msjVal ) )
	{
		iRes = SIdEsIgual ( SMsjId ( p_msjObj ), SMsjId ( p_msjVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMenor ( SMensaje * p_msjObj, SMensaje * p_msjVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_msjVal ) )
	{
		iRes = SIdEsMenor ( SMsjId ( p_msjObj ), SMsjId ( p_msjVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMayor ( SMensaje * p_msjObj, SMensaje * p_msjVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_msjVal ) )
	{
		iRes = SIdEsMayor ( SMsjId ( p_msjObj ), SMsjId ( p_msjVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMenorIg ( SMensaje * p_msjObj, SMensaje * p_msjVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_msjVal ) )
	{
		iRes = SIdEsMenorIg ( SMsjId ( p_msjObj ), SMsjId ( p_msjVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMayorIg ( SMensaje * p_msjObj, SMensaje * p_msjVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_msjVal ) )
	{
		iRes = SIdEsMayorIg ( SMsjId ( p_msjObj ), SMsjId ( p_msjVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsIgualId ( SMensaje * p_msjObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsIgualNum ( SMsjId ( p_msjObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMenorId ( SMensaje * p_msjObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorNum ( SMsjId ( p_msjObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMayorId ( SMensaje * p_msjObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorNum ( SMsjId ( p_msjObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMenorIgId ( SMensaje * p_msjObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorIgNum ( SMsjId ( p_msjObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMayorIgId ( SMensaje * p_msjObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorIgNum ( SMsjId ( p_msjObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsIgualNum ( SMensaje * p_msjObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) ) 
	{
		iRes = SIdEsIgualNum ( SMsjId ( p_msjObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMenorNum ( SMensaje * p_msjObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) ) 
	{
		iRes = SIdEsMenorNum ( SMsjId ( p_msjObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMayorNum ( SMensaje * p_msjObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) ) 
	{
		iRes = SIdEsMayorNum ( SMsjId ( p_msjObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMenorIgNum ( SMensaje * p_msjObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) ) 
	{
		iRes = SIdEsMenorIgNum ( SMsjId ( p_msjObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjEsMayorIgNum ( SMensaje * p_msjObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) ) 
	{
		iRes = SIdEsMayorIgNum ( SMsjId ( p_msjObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjComparar ( SMensaje * p_msjObj, SMensaje * p_msjVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) && ES_VALIDO ( p_msjVal ) )
	{
        iRes = SEntCompararId ( p_msjObj->p_entInfo, SMsjId ( p_msjVal ) );
	}
	else if  ( ES_VALIDO ( p_msjObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_msjVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SMsjCompararId ( SMensaje * p_msjObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		iRes = SIdComparar ( SMsjId ( p_msjObj ), p_idVal );
	}
	else if  ( ES_VALIDO ( p_idVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SMsjCompararNum ( SMensaje * p_msjObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_msjObj ) ) 
	{
		iRes = SIdCompararNum ( SMsjId ( p_msjObj ), ulId );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

unsigned int SMsjHash ( SMensaje * p_msjObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		uiRes = SEntHash ( p_msjObj->p_entInfo );
	}
	return ( uiRes );
}


