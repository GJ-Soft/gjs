#ifndef _ORG_GJS_C_CC_CPP_CONSTANTES_H
#define _ORG_GJS_C_CC_CPP_CONSTANTES_H

#include <stdio.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


const char FECHA_ANO[4+1] =
{
   __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10], '\0'
};

const char FECHA_MES[2+1] =
{
   (__DATE__[0] == 'O' || __DATE__[0] == 'N' || __DATE__[0] == 'D') ? '1' : '0',
   (__DATE__[0] == 'J') ? ( (__DATE__[1] == 'a') ? '1' :       // Jan, Jun or Jul
                            ((__DATE__[2] == 'n') ? '6' : '7') ) :
   (__DATE__[0] == 'F') ? '2' :                                // Feb
   (__DATE__[0] == 'M') ? (__DATE__[2] == 'r') ? '3' : '5' :   // Mar or May
   (__DATE__[0] == 'A') ? (__DATE__[1] == 'p') ? '4' : '8' :   // Apr or Aug
   (__DATE__[0] == 'S') ? '9' :                                // Sep
   (__DATE__[0] == 'O') ? '0' :                                // Oct
   (__DATE__[0] == 'N') ? '1' :                                // Nov
   (__DATE__[0] == 'D') ? '2' :                                // Dec
   0,
  '\0'
};

const char FECHA_DIA[2+1] =
{
   __DATE__[4]==' ' ? '0' : __DATE__[4],
   __DATE__[5],
  '\0'
};

const char FECHA[8+1] =
{
   __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10],
   (__DATE__[0] == 'O' || __DATE__[0] == 'N' || __DATE__[0] == 'D') ? '1' : '0',
   (__DATE__[0] == 'J') ? ( (__DATE__[1] == 'a') ? '1' :       // Jan, Jun or Jul
                            ((__DATE__[2] == 'n') ? '6' : '7') ) :
   (__DATE__[0] == 'F') ? '2' :                                // Feb
   (__DATE__[0] == 'M') ? (__DATE__[2] == 'r') ? '3' : '5' :   // Mar or May
   (__DATE__[0] == 'A') ? (__DATE__[1] == 'p') ? '4' : '8' :   // Apr or Aug
   (__DATE__[0] == 'S') ? '9' :                                // Sep
   (__DATE__[0] == 'O') ? '0' :                                // Oct
   (__DATE__[0] == 'N') ? '1' :                                // Nov
   (__DATE__[0] == 'D') ? '2' :                                // Dec
   0,
   __DATE__[4]==' ' ? '0' : __DATE__[4],
   __DATE__[5],
  '\0'
};


 			}
		}
	}
}

#endif
