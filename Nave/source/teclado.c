/*-------------------------------------
teclado.c
-------------------------------------*/

// añadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "graficos.h"
#include "sprites.h"

// int tecla; // variable para guardar el valor de la tecla pulsada

//Esta función tiene que devolver el valor 1 sii se pulsa una tecla
int DetectarTecla()
{
	if ((TECLAS_DAT & 0x03FF) != 0x03FF) {
		return 1;
	} else { return 0;
	}
}

//Esta funci�n tiene que devolver el valor de la tecla pulsada
int  TeclaPulsada() 
{
	//devuelve el valor asociado a la tecla pulsada: A=0;B=1;Select=2;Start=3;Der=4;Izq=5;
	//Arriba=6;Abajo=7;R=8;L=9;
	// -1 en otros casos

	if ((TECLAS_DAT & 0x0001) == 0) return A;
	if ((TECLAS_DAT & 0x0002) == 0) return B;
	if ((TECLAS_DAT & 0x0004) == 0) return SELECT;
	if ((TECLAS_DAT & 0x0008) == 0) return START;
	if ((TECLAS_DAT & 0x0010) == 0) return DCHA;
	if ((TECLAS_DAT & 0x0020) == 0) return IZDA;
	if ((TECLAS_DAT & 0x0040) == 0) return ARRIBA;
	if ((TECLAS_DAT & 0x0080) == 0) return ABAJO;
	if ((TECLAS_DAT & 0x0100) == 0) return R;
	if ((TECLAS_DAT & 0x0200) == 0) return L;
	return (-1);
}

void HabilitarIntTec()		//Habilitar interrupciones del teclado
{
	//Para ello primero se deshabilitan todas las interrupciones
	//Escribir un 1 en el bit correspondiente al teclado del REG_IE
	//Para acabar, se habilitan todas las interrupciones

IME = 0;
IE = (IE | 0x1000);
IME = 1;
	
}


void DeshabilitarIntTec()	//Deshabilitar interrupciones del teclado
{
//Para ello primero se deshabilitan todas las interrupciones
//Escribir un 0 en el bit correspondiente al teclado del REG_IE
//Para acabar, se habilitan todas las interrupciones

IME = 0;
IE = (IE & 0xFFFFEFFF);
IME = 1;
		
}


//Rutina de atenci�n a la interrupci�n del teclado

void IntTec()
{
	//if (TeclaPulsada() == A) iprintf("\x1b[01:1H Se ha pulsado A     \n");
	//if (TeclaPulsada() == B) iprintf("\x1b[01:1H Se ha pulsado B     \n");
	if (ESTADO == PARTIDA)
	{
		if (TeclaPulsada() == DCHA) {
			//iprintf("\x1b[01:1H Se ha pulsado DCHA  \n");
			if (x < 240) x+=16;
			else x = 0;
		} if (TeclaPulsada() == IZDA) {
			//iprintf("\x1b[01:1H Se ha pulsado IZDA  \n");
			if (x > 0) x-=16;
			else x = 240;
		} if (TeclaPulsada() == ARRIBA) {
			//iprintf("\x1b[01:1H Se ha pulsado ARRIBA\n");
			if (y > 6) y-=16;
		} if (TeclaPulsada() == ABAJO) {
			//iprintf("\x1b[01:1H Se ha pulsado ABAJO \n");
			if (y < 176) y+=16;
		}
		
		MostrarNave(x,y);
		iprintf("\x1b[09:1H Posicion X:%d Y:%d                           \n",x,y);
	}	
}
		
