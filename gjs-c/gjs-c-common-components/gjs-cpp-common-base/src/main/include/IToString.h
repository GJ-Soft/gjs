#ifndef _ORG_GJS_C_CC_CPP_ITOSTRING_H
#define _ORG_GJS_C_CC_CPP_ITOSTRING_H



#include <string>
#include <ostream>
#include <list>
#include <vector>
#include <map>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

            class IToString
			{

			public:
				IToString() {};
				virtual ~IToString() {};

				virtual std::string toString() = 0;
				virtual IToString & Base() const {
                    return ( (IToString &) *this );
				};

				friend std::ostream& operator<< ( std::ostream & strm, IToString & obj );

			};

			std::string ToString ( std::list<IToString *> & lista );
			std::string ToString ( std::list<IToString *> * lista );
			std::string ToString ( std::vector<IToString *> & vector );
			std::string ToString ( std::vector<IToString *> * vector );
			std::string ToString ( std::map<std::string, IToString *> & mapa );
			std::string ToString ( std::map<std::string, IToString *> * mapa );

			}
		}
	}
}


#endif
