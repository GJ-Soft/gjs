/***************************************************************************/
/*                          Conversor.h                                   */
/*-------------------------------------------------------------------------*/
/* Librería: ClasesBase                                                    */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene la definición de la clase de datos     */
/* Conversor, destinada a gestionar la conversión automática entre los    */
/* diferentes tipos de datos básicos.                                      */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CONVERSOR_H
#define _ORG_GJS_C_CC_CPP_CONVERSOR_H


#include <string>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



class Conversor
{
private:
	int				    iValor;
	long			    lValor;
	long long		    llValor;
	unsigned int	    uiValor;
	unsigned long	    ulValor;
	unsigned long long	ullValor;
	float			    fValor;
	double			    dValor;
	long double			ldValor;
	std::string			    sValor;

	bool				bConvValida;

public:
	Conversor ();
	Conversor ( int iValor );
	Conversor ( long lValor );
	Conversor ( long long llValor );
	Conversor ( unsigned int uiValor );
	Conversor ( unsigned long ulValor );
	Conversor ( unsigned long long ullValor );
	Conversor ( float fValor );
	Conversor ( double dValor );
	Conversor ( long double ldValor );
	Conversor ( std::string & sValor );
	Conversor ( const std::string & sValor );
	Conversor ( char * p_cValor );
	Conversor ( const char * p_cValor );

	~Conversor ();

	int Entero ();
	long EnteroLargo ();
	long long EnteroDobleLargo ();
	unsigned int EnteroSinSigno ();
	unsigned long EnteroLargoSinSigno ();
	unsigned long long EnteroDobleLargoSinSigno ();
	float Real ();
	double RealDoble ();
	long double RealDobleLargo ();
	const std::string & Cadena ();
	std::string CadenaHex ();

	void EstablecerValor ( int iValor );
	void EstablecerValor ( long lValor );
	void EstablecerValor ( long long llValor );
	void EstablecerValor ( unsigned int uiValor );
	void EstablecerValor ( unsigned long ulValor );
	void EstablecerValor ( unsigned long long ullValor );
	void EstablecerValor ( float fValor );
	void EstablecerValor ( double dValor );
	void EstablecerValor ( long double ldValor );
	void EstablecerValor ( std::string & sValor );
	void EstablecerValor ( const std::string & sValor );
	void EstablecerValor ( char * p_cValor );
	void EstablecerValor ( const char * p_cValor );
	void EstablecerValorHex ( std::string & sValor );
	void EstablecerValorHex ( const std::string & sValor );
	void EstablecerValorHex ( char * p_cValor );
	void EstablecerValorHex ( const char * p_cValor );

	bool EsCadenaNumerica ();
	bool EsCadenaNumericaEntera ();
	bool EsCadenaNumericaReal ();
	bool EsCadenaNumericaHexadecimal ();
	bool ConversionValida ();

private:
	void Inicializar ();
};



            }
		}
	}
}




#endif
