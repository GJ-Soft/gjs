
#ifndef _ORG_GJS_C_CC_SIMULACIONUSUARIOCONSOLA_H
#define _ORG_GJS_C_CC_SIMULACIONUSUARIOCONSOLA_H







/* Simula una entrada de usuario por consola para los tests cuyo codigo bajo
   prueba lee de stdin de forma bloqueante (p. ej. el getchar() de CajMsjMostrar
   en POSIX). Engancha stdin a una tuberia precargada con p_cEntrada + retorno
   ("" simula pulsar solo <retorno>). El extremo de escritura se cierra tras
   escribir, de modo que el lector ve la entrada y despues EOF: nunca se queda
   bloqueado, aunque lea de mas. Hay que llamar a RestaurarEntradaConsola tras
   la lectura para devolver stdin a su estado original. Devuelve 1 si prepara la
   entrada, 0 en caso de error o si no aplica (WIN: getche/kbhit no pasan por
   stdin). */
int SimularEntradaConsola ( const char * p_cEntrada );
void RestaurarEntradaConsola ();







#endif
