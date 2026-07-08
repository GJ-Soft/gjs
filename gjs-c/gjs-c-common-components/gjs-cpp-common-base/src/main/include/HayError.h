#ifndef _ORG_GJS_C_CC_CPP_HAYERROR_H
#define _ORG_GJS_C_CC_CPP_HAYERROR_H






namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class HayError
			{
			private:
				bool bError = false;

			public:
				HayError();
				virtual ~HayError();

				bool isError();
				void setError( bool bValor );
			};

            }
		}
	}
}

#endif
