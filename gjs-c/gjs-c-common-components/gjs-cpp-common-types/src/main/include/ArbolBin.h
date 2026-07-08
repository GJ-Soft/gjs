#ifndef _ORG_GJS_C_CC_CPP_ARBOLBIN_H
#define _ORG_GJS_C_CC_CPP_ARBOLBIN_H

#include <NodoBin.h>
#include <IToString.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ArbolBin : public IToString
			{
			private:
				NodoBin * nodoRaiz;

			public:
				ArbolBin ();
				explicit ArbolBin ( NodoBin * nodo );
				explicit ArbolBin ( void * datos );
				virtual ~ArbolBin ();

				bool TieneRaiz ();
				int Tam ();
				int Profundidad ();

				NodoBin * getRaiz();
				void setRaiz( NodoBin * nodo );
				void setRaiz( void * datos );

				void EmpadrarPorDer( NodoBin * nodo );
				void EmpadrarPorDer( void * datos );
				void EmpadrarPorIzq( NodoBin * nodo );
				void EmpadrarPorIzq( void * datos );

				void Vaciar();

				NodoBin * PrimeroPreorden ();
				NodoBin * PrimeroPostorden ();
				NodoBin * PrimeroInorden ();

				virtual std::string toString() override;

			};

 			}
		}
	}
}

#endif
