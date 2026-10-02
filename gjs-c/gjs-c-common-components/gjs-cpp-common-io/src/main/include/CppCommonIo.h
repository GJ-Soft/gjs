#ifndef _ORG_GJS_C_CC_CPP_COMMON_IO_H
#define _ORG_GJS_C_CC_CPP_COMMON_IO_H

#include <Precompilacion.h>

/* winsock2.h debe incluirse antes de cualquier cabecera que arrastre
   sys/types.h (que define fd_set en Cygwin); si no, w32api avisa de conflicto
   de fd_set con los sockets W32. Va aqui: tras Precompilacion.h (que define WIN
   y solo trae stdint.h) y antes de SocketExcepcion.h (que arrastra sys/types.h
   via CppBase). Solo winsock2.h, igual que Socket.h, para no meter windows.h
   (macros min/max) en la compilacion de los test. */
#if ( defined ( WIN ) )
#	include <winsock2.h>
#endif

#include <ESExcepcion.h>
#include <SocketExcepcion.h>
#include <Socket.h>

#include <ExtensionesFicheros.h>
#include <SistemaFicheros.h>

#include <SocketServidor.h>
#include <SocketCliente.h>
#include <SocketAtencion.h>

#include <GestorUsuarios.h>
#include <GestorSesiones.h>
#include <Cliente.h>
#include <Servidor.h>

#include <PuertosIETF.h>
#include <CodigosIETF.h>
#include <ComandosIETF.h>

#include <Comando.h>
#include <ComandoIETF.h>
#include <ResultadoComando.h>
#include <ClienteComandos.h>
#include <ServidorComandos.h>

#include <ClienteSesion.h>
#include <ServidorSesion.h>

#include <ClienteIETF.h>
#include <ServidorIETF.h>
#include <ClienteFTP.h>
#include <ServidorFTP.h>

#include <HTTPConstantes.h>
#include <URI.h>
#include <ClienteHTTP.h>
#include <ServidorHTTP.h>

#endif
