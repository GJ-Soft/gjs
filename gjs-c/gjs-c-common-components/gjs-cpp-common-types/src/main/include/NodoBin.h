#ifndef _ORG_GJS_C_CC_CPP_NODOBIN_H
#define _ORG_GJS_C_CC_CPP_NODOBIN_H

#include <string>
#include <vector>
#include <list>
#include <initializer_list>
#include <ostream>

#include <IToString.h>


using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ArbolBin;

			class NodoBin : public IToString
			{
			private:
				void * 		datos;
				ArbolBin *	arbolDer;
				ArbolBin *	arbolIzq;
				NodoBin *	nodoPadre;

			public:
				NodoBin ();
				explicit NodoBin ( void * _datos );
				virtual ~NodoBin ();

				void * getDatos();
				void setDatos( void * _datos );

				bool EsValido ();
				bool TieneHijoDer ();
				bool TieneHijoIzq ();
				bool TieneHijos ();
				bool TienePadre ();
				bool EsHijoDer ();
				bool EsHijoIzq ();

				ArbolBin * getHijoDer ();
				ArbolBin * getHijoIzq ();
				NodoBin * getPadre ();
				void setHijoDer ( ArbolBin * arbol, bool bLiberar = true );
				void setHijoIzq ( ArbolBin * arbol, bool bLiberar = true );
				void setHijoDer ( NodoBin * nodo, bool bLiberar = true );
				void setHijoIzq ( NodoBin * nodo, bool bLiberar = true );
				void setPadre ( NodoBin * nodo, bool bLiberar = true );

				NodoBin * SigPreorden ();
				NodoBin * SigPostorden ();
				NodoBin * SigInorden ();

				virtual std::string toString() override;

			private:
				virtual void LiberarDatos( void * _datos );
				virtual std::string DatosToString( void * _datos );
			};

 			}
		}
	}
}


#endif
