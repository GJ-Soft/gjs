#ifndef _ORG_GJS_C_CC_CPP_MAPAVECTOR_H
#define _ORG_GJS_C_CC_CPP_MAPAVECTOR_H




#include <string>
#include <unordered_map>
#include <vector>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			template <class T> class MapaVector
			{
			private:

				std::vector<std::string> 			vecOrden;
				std::unordered_map<std::string, T> 	mapObjetos;

			public:
				MapaVector();
				virtual ~MapaVector();

				size_t size() const noexcept;
				bool empty() const noexcept;
				bool isValid() const noexcept;

				bool exists( const std::string & sClave );
				T& at( size_t pos );
				T& find( const std::string & sClave );
				const std::vector<std::string> & getKeys();

				void push_back( const std::string & sClave, const T & obj );
				void push_back( const std::string & sClave, T & obj );
				void pop_back();
				void erase( size_t pos );
				void erase( const std::string & sClave );

				void clear() noexcept;

				T& operator[]( size_t pos );
				T& operator[]( const std::string & sClave );
			};

 			}
		}
	}
}

#endif
