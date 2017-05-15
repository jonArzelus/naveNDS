/*-------------------------------------
rutsers.c
-------------------------------------*/
// añadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "teclado.h"
#include "defines.h"
#include "temporizadores.h"
//Este procedimiento inicializa la tabla de interrupciones para que el gestor de interrupciones sepa
//qué rutina de atención tiene que ejecutar cuando le llega una petición de interrupción. 
//Además es aquí donde se configuran los registros de control de los periféricos.
void interrupciones()
{
	irqSet (IRQ_TIMER0,IntTemp);
	irqSet (IRQ_KEYS,IntTec);
	//activa interrupcion del teclado y start
	TECLAS_CNT = 0x43FF; //teclas (todas) y interrupciones
	//interrupciones timer0
	TIMER0_DAT = 0x8000; //52429, Genera 16 interrupciones por segundo
	TIMER0_CNT = 0x00C1; //activar la interrupcion y dividir por 2		
}
