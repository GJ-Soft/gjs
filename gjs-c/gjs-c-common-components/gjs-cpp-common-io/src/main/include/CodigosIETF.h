#ifndef _ORG_GJS_C_CC_CPP_CODIGOS_IETF_H
#define _ORG_GJS_C_CC_CPP_CODIGOS_IETF_H






namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			const std::string IETF_CONTINUAR = "100";
			const std::string IETF_CAMBIANDO_PROTOCOLO = "101";
			const std::string IETF_PROCESANDO = "102";
			const std::string IETF_CONSEJOS = "103";
			const std::string IETF_REINICIAR_MARCADOR = "110";  
			const std::string IETF_SERVICIO_LISTO_PROXIMAMEMTE = "120";  
 			const std::string IETF_TRANSFERENCIA_INICIADA = "125"; 
			const std::string IETF_FICHERO_PREPARADO = "150"; 
 
			const std::string IETF_OK = "200";
			const std::string IETF_CREADO = "201";
			const std::string IETF_ACEPTADO = "202";
			const std::string IETF_INFORMACION_NO_AUTORIZADA = "203";
			const std::string IETF_SIN_CONTENIDO = "204";
			const std::string IETF_CONTENIDO_INICIALIZADO = "205";
			const std::string IETF_CONTENIDO_PARCIAL = "206";

			const std::string IETF_MULTIPLES_OPCIONES = "300";
			const std::string IETF_MOVIDO_PERMANENTEMENTE = "301";
			const std::string IETF_ENCONTRADO = "302";
			const std::string IETF_PRUEBA_OTRO = "303";
			const std::string IETF_NO_MODIFICADO = "304";
			const std::string IETF_USAR_PROXY = "305";
			const std::string IETF_TEMPORALMENTE_REDIRIGIDO = "307";
			
			const std::string IETF_PETICION_ERROENA = "400";
			const std::string IETF_NO_AUTORIZADO = "401";
			const std::string IETF_PAGO_REQUERIDO = "402";
			const std::string IETF_PROHIBIDO = "403";
			const std::string IETF_NO_ENCONTRADO = "404";
			const std::string IETF_METODO_NO_PERMITIDO = "405";
			const std::string IETF_NO_ACEPTABLE = "406";
			const std::string IETF_AUTENTICACION_PROXY_REQUERIDA = "407";
			const std::string IETF_TIEMPO_EXCEDIDO = "408";			
			const std::string IETF_CONFLICTO = "409";			
			const std::string IETF_DESAPARECIDO = "410";			
			const std::string IETF_LONGITUD_REQUERIDA = "411";			
			const std::string IETF_FALLO_PRECONDICION = "412";			
			const std::string IETF_ENTIDAD_DEMASIADO_GRANDE = "413";			
			const std::string IETF_URI_DEMASIADO_GRANDE = "414";			
			const std::string IETF_TIPO_NO_SOPORTADO = "415";			
			const std::string IETF_RANGO_NO_SATISFACIBLE = "416";			
			const std::string IETF_EXPECTACION_FALLIDA = "417";			
			
			const std::string IETF_ERROR_INTERNO = "500";
			const std::string IETF_NO_IMPLEMENTADO = "501";
			const std::string IETF_ERROR_SINTACTICO = "501";
			const std::string IETF_PUERTA_ENLACE_ERRONEA = "502";
			const std::string IETF_COMANDO_NO_IMPLEMENTADO = "502";
			const std::string IETF_SERVICIO_NO_DISPONIBLE = "503";  
			const std::string IETF_SECUENCIA_ERRONEA = "503";  
			const std::string IETF_TIEMPO_PUERTA_ENLACE_EXCEDIDO = "504";
			const std::string IETF_CASO_NO_IMPLEMENTADO = "504";  
			const std::string IETF_VERSION_PROTOCOLO_NO_SOPORTADA = "505";
 
			const std::string IETF_ESTADO_SISTEMA = "211";  
			const std::string IETF_ESTADO_DIRECTORIO = "212";  
			const std::string IETF_ESTADO_FICHERO = "213";  
			const std::string IETF_AYUDA = "214";  
			const std::string IETF_INFO_SISTEMA = "215";  
                                                                         
			const std::string IETF_SERVICIO_PREPARADO = "220"; 
			const std::string IETF_SALIR = "221";  
 			const std::string IETF_SOLICITUD_MAL_DIRIGIDA = "421";  
    
 			const std::string IETF_CONEXION_ABIERTA = "225";
  			const std::string IETF_ERROR_CONEXION = "425";  
			const std::string IETF_CERRANDO_CONEXION = "226";  
 			const std::string IETF_CONEXION_CERRADA = "426";
			const std::string IETF_MODO_PASIVO = "227"; 
                                                                       
			const std::string IETF_SESION_INICIADA = "230"; 
			const std::string IETF_SESION_NO_INICIADA = "530"; 
			const std::string IETF_FALTA_CLAVE = "331";  
			const std::string IETF_NECESARIO_SESION = "332";  
			const std::string IETF_NECESARIO_SESION_PARA_OPERACION = "532";  
                                                                        
 			const std::string IETF_ACCION_COMPLETADA = "250"; 
			const std::string IETF_ACCION_PENDIENTE = "350";  
 			const std::string IETF_FICHERO_NO_DISPONIBLE = "450"; 
 			const std::string IETF_ACCION_NO_REALIZADA = "550";  
  			const std::string IETF_ACCION_ABORTADA = "451";  
 			const std::string IETF_ESPACIO_INSUFICIENTE = "452";  
 			const std::string IETF_ESPACIO_EXCEDIDO = "552";  
			const std::string IETF_ACCION_NO_PERMITIDA = "553"; 
  			const std::string IETF_INICIAR_CORREO = "354";  

  			const std::string IETF_DIRECTORIO = "257";  

		
			const std::string IETF_DESCONOCIDO = "999";
			
			
			bool EsCodigoIETF( const std::string & sCodigo );
			std::string ConstruirRespuestaIETF( const std::string & sCodigo, const std::string sMensaje = "" );
			bool ProcesarRespuestaIETF( const std::string & sRespuesta, std::string & sCodigo, std::string & sMensaje );
			std::string ConstruirMensajeIETF( const std::string sMensaje );
			std::string ProcesarMensajeIETF( const std::string & sMensaje );
		
 			}
		}
	}
}


#endif