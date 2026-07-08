#ifndef _ORG_GJS_C_CC_CPP_PTR_H
#define _ORG_GJS_C_CC_CPP_PTR_H

#include <Sistema.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			template<typename T> class Ptr
			{
			private:
				T * 		datos;
				bool		bLiberar;


			public:
				Ptr ()
				{
					datos = NULL;
					bLiberar = true;
				}

				explicit Ptr ( T * _datos, bool _bLiberar = true )
				{
					datos = _datos;
					bLiberar = _bLiberar;
				}

				explicit Ptr ( void * _datos, bool _bLiberar = true )
				{
					datos = reinterpret_cast<T *>( _datos );
					bLiberar = _bLiberar;
				}

				virtual ~Ptr ()
				{
					if ( bLiberar && PuedeLiberarse( datos ) )
					{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfree-nonheap-object"
						delete datos;
#pragma GCC diagnostic pop
					}
				}

				T * getDatos()
				{
					return ( datos );
				}

				void setDatos( T * _datos )
				{
					datos = _datos;
				}

				void setDatos( void * _datos )
				{
					T * ptr = NULL;
					if ( _datos != NULL )
					{
						ptr = reinterpret_cast<T *>( _datos );
					}
					setDatos ( ptr );
				}

				bool EsValido ()
				{
					return ( datos != NULL );
				}

			};

 			}
		}
	}
}



#endif
