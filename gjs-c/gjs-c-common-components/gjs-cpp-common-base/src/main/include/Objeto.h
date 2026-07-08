#ifndef _ORG_GJS_CC_CPP_BASE_OBJETO_H
#define _ORG_GJS_CC_CPP_BASE_OBJETO_H

#include <string>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

class Objeto
{
public:
	Objeto ();
	virtual ~Objeto ();

public:
	std::string getTipo () const;
	virtual int hash() const;
	virtual bool esValido () const ;
	size_t getTam() const;

	Objeto * clonar();

	virtual bool equals ( Objeto & objeto ) const;
	virtual bool equals ( Objeto * objeto ) const;

	virtual std::string toString ();

protected:
	virtual void assignar( Objeto & objeto );

public:
	Objeto & operator=( Objeto & objeto );
	bool operator== ( Objeto & objeto );
	bool operator!= ( Objeto & objeto );

};

 			}
		}
	}
}



#endif
