#ifndef _ORG_GJS_C_CC_CPP_CONTADOR_H
#define _ORG_GJS_C_CC_CPP_CONTADOR_H



#include <IToString.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Contador : public IToString
			{
			private:
				unsigned long	ulTotal = 0;
				unsigned long	ulCorrectos = 0;

			public:
				Contador ();
				virtual ~Contador ();

			public:
				unsigned long getTotal() const;
				unsigned long getCorrectos() const;
				unsigned long getErroneos() const;

				void Incrementar ( bool bCorrecto = true );

				virtual std::string toString () override;

			};

 			}
		}
	}
}



#endif
