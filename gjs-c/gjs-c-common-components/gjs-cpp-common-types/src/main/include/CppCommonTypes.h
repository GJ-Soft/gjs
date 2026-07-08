#ifndef _ORG_GJS_C_CC_CPP_COMMON_TYPES_H
#define _ORG_GJS_C_CC_CPP_COMMON_TYPES_H


#include <CppBase.h>

#include <Constantes.h>
#include <Calculo.h>
#include <Secuencias.h>
#include <StringStreamOut.h>
#include <CaptorSalida.h>
#include <Simbolos.h>
#include <MemoriaGlobal.h>
#include <WinHerramientas.h>


#include <Ptr.h>
#include <Propiedades.h>
#include <ArbolBin.h>
#include <TipoDatos.h>
#include <Tipo.h>
#include <Atributo.h>
#include <Valor.h>
#include <Entidad.h>
#include <ListaValores.h>
#include <ConjuntoValores.h>
#include <Contador.h>
#include <FicheroFormateado.h>
#include <ControlConcurrencia.h>
#include <MapaVector.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			const std::string CADENA_VACIA( "" );

			template<typename Base, typename T>	inline bool instanceof(const T *ptr)
			{
				return dynamic_cast<const Base*>(ptr) != nullptr;
			}

 			}
		}
	}
}


#endif
