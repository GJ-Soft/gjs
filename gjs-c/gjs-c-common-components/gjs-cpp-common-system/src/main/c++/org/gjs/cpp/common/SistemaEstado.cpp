/******************************************************************************/
/*                             SistemaEstado.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la algunas      */
/* rutinas generales de información dinámica del sistema.                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#include "CommonSystemConfig.h"

#include "SistemaEstado.h"





using namespace std;

namespace org
{
    namespace gjs
    {
        namespace cpp
        {
            namespace common
            {


long SisFechaInicio ()
{
	long lRes;

	lRes = 0;
	return ( lRes );
}

long SisHoraInicio ()
{
	long lRes;

	lRes = 0;
	return ( lRes );
}


/*
#if ( defined ( LLONG ) )
llong SisFechaHoraInicio ()
{
	llong llRes;

	llRes = SisProcesoHoraCreacion ( 8 );
	return ( llRes );
}

#else
unsigned long SisFechaHoraInicio ()
{
	unsigned long ulRes;

	ulRes = SisProcesoHoraCreacion ( 8 );
	return ( ulRes );
}

#endif
*/

/*
Para determinar la hora del último arranque de Windows NT tenemos que ejecutar el comado:

NET STATISTICS SERVER o NET STATISTICS WORKSTATION 

Donde SERVER o WORKSTATION se refieren a los servicios que se ejecutan el máquina, no a la versión del producto.



  
EventLog:	"Se ha iniciado el servicio de Registro de sucesos."

define BUFFER_SIZE 1024*64

void DisplayEntries( )
{
    HANDLE h;
    EVENTLOGRECORD *pevlr; 
    BYTE bBuffer[BUFFER_SIZE]; 
    DWORD dwRead, dwNeeded, dwThisRecord; 
 
    // Open the Application event log. 
 
    h = OpenEventLog( NULL,    // use local computer
             "Application");   // source name
    if (h == NULL) 
    {
        printf("Could not open the Application event log."); 
        return;
    }
 
    pevlr = (EVENTLOGRECORD *) &bBuffer; 
 
    // Get the record number of the oldest event log record.

    GetOldestEventLogRecord(h, &dwThisRecord);

    // Opening the event log positions the file pointer for this 
    // handle at the beginning of the log. Read the event log records 
    // sequentially until the last record has been read. 
 
    while (ReadEventLog(h,                // event log handle 
                EVENTLOG_FORWARDS_READ |  // reads forward 
                EVENTLOG_SEQUENTIAL_READ, // sequential read 
                0,            // ignored for sequential reads 
                pevlr,        // pointer to buffer 
                BUFFER_SIZE,  // size of buffer 
                &dwRead,      // number of bytes read 
                &dwNeeded))   // bytes in next record 
    {
        while (dwRead > 0) 
        { 
            // Print the record number, event identifier, type, 
            // and source name. 
 
            printf("%03d  Event ID: 0x%08X  Event type: ", 
                dwThisRecord++, pevlr->EventID); 

            switch(pevlr->EventType)
            {
                case EVENTLOG_ERROR_TYPE:
                    printf("EVENTLOG_ERROR_TYPE\t  ");
                    break;
                case EVENTLOG_WARNING_TYPE:
                    printf("EVENTLOG_WARNING_TYPE\t  ");
                    break;
                case EVENTLOG_INFORMATION_TYPE:
                    printf("EVENTLOG_INFORMATION_TYPE  ");
                    break;
                case EVENTLOG_AUDIT_SUCCESS:
                    printf("EVENTLOG_AUDIT_SUCCESS\t  ");
                    break;
                case EVENTLOG_AUDIT_FAILURE:
                    printf("EVENTLOG_AUDIT_FAILURE\t  ");
                    break;
                default:
                    printf("Unknown ");
                    break;
            }

            printf("Event source: %s\n", 
                (LPSTR) ((LPBYTE) pevlr + sizeof(EVENTLOGRECORD))); 
 
            dwRead -= pevlr->Length; 
            pevlr = (EVENTLOGRECORD *) 
                ((LPBYTE) pevlr + pevlr->Length); 
        } 
 
        pevlr = (EVENTLOGRECORD *) &bBuffer; 
    } 
 
    CloseEventLog(h); 
}
*/


            }
        }
    }
}

