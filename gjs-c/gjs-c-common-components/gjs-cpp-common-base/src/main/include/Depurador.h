
#ifndef _ORG_GJS_CC_CPP_BASE_DEPURADOR_H
#define _ORG_GJS_CC_CPP_BASE_DEPURADOR_H




#include <Precompilacion.h>



#include <string>
#include <Objeto.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



class Depurador : public Objeto
{
private:
#  if ( defined ( MODO_DEPURACION ) )
	int		iObjetos;
	void *	p_vDirObjeto;
	int		iTamObjeto;
	int		iEliminando;

	int		iError;
#  endif

public:
	Depurador ();

	virtual ~Depurador ();

#  if ( defined ( MODO_DEPURACION ) )
	bool EsTipo ( const char * p_cNombre );
	bool EsTipo ( const std::string & sNombre );

	int NumObjetos ();
	void * DireccionObjeto ();

	int Error ();
	void EstablecerError ( int iError );
	void LimpiarError ();

protected:
	void ActualizarObjeto ( const std::string & sNombre, void * p_vDirObj, int iTamObj );

#  endif
};




void GesClsImprimirEstado ();




 			}
		}
	}
}



#endif
