
#include "Epsilon.h"

#include "CommonCalculationConfig.h"


static double g_dCalcEpsilon = -0.1;





double Epsilon ()
{
	double	dEps;
	double	dEps1;
	int		iFinal;

	if ( g_dCalcEpsilon < 0.0 )
	{
		dEps = 1.0;
		iFinal = 0;
		while ( iFinal == 0 )
		{
			dEps = dEps * 0.5;
			dEps1 = 1.0 + dEps;
			if ( dEps1 <= 1.0 )
			{
				iFinal = 1;
				g_dCalcEpsilon = dEps;
			}
		}
	}
	return ( g_dCalcEpsilon );
}


