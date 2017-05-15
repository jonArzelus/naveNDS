/*temporizadores.c*/
// añadir los includes que sean necesarios
#include "defines.h"
#include "graficos.h"
#include "sprites.h"
#include "teclado.h"
#include <nds.h>
#include <stdio.h>

void HabilitarIntTemp()		//Habilita las interrupciones del temporizador
{
	//Para ello primero se deshabilitan todas las interrupciones
	//Escribir un 1 en el bit correspondiente al temporizador del REG_IE
	//Para acabar, se habilitan todas las interrupciones
	IME = 0;
	IE = (IE | 0x0008);
	IME = 1;
}		


void DeshabilitarIntTemp()		//Deshabilita las interrupciones del temporizador
{
	//Para ello primero se deshabilitan todas las interrupciones
	//Escribir un 0 en el bit correspondiente al remporizador del REG_IE
	//Para acabar, se habilitan todas las interrupciones
	IME = 0;
	IE = (IE & 0xFFFFFFF7);
	IME = 1;
}

//asigna valor a los sprites (...)

static int mon, vid, taime_sec;
int ind[6],ind_x[6],ind_y[6];
void InicializarSprite()
{
	int i,j,h;
	
		for(i = 0; i < 6; i++) {
			if(i == 0) for(j = 0; j < 6; j++) ind[j] = (rand() % 127);
			for(h = 0; h < 6; h++){
			if(i != h) while(ind[i]==ind[h]) ind[i] = (rand()%127);
			}
		}
	
	for (i=0;i<6;i++) {
		ind_x[i]=(rand()%241);
		while ((ind_x[i]<212)&&(ind_x[i]>186)) ind_x[i] = rand() % 241;
	}
	int n = 0;
	for (i=0;i<6;i++) 
	{
		ind_y[i]=n;
		n+=36;
	}
	mon = 0;
	vid = 4;
	taime_sec = 0;
}

//Rutina de atención a la interrupción del temporizador

void IntTemp()
{
	int i,h;
	for (i=0;i<6;i++)
	{
		if (ind_y[i] == 176) //moneda, mina o reloj (total: 6)
		{
			if (ind[i] < 51) BorrarMoneda(ind[i],ind_x[i],ind_y[i]);
			else if (ind[i] < 117) BorrarMina(ind[i],ind_x[i],ind_y[i]);
			else BorrarReloj(ind[i],ind_x[i],ind_y[i]);
			ind[i] = rand() % 127;
			
			for(h = 0; h < 6; h++){
				if(i != h) while(ind[i]==ind[h]) ind[i] = (rand()%127);
			}
			ind_x[i] = rand() % 241;
			while ((ind_x[i]<212)&&(ind_x[i]>186)) ind_x[i] = rand() % 241;
			ind_y[i] = 0;
			if (ind[i] < 51) MostrarMoneda(ind[i],ind_x[i],ind_y[i]);
			else if (ind[i] < 117) MostrarMina(ind[i],ind_x[i],ind_y[i]);
			else MostrarReloj(ind[i],ind_x[i],ind_y[i]);
		} else {
			ind_y[i]+=4;
			if (ind[i] < 51) MostrarMoneda(ind[i],ind_x[i],ind_y[i]);
			else if (ind[i] < 117) MostrarMina(ind[i],ind_x[i],ind_y[i]);
			else MostrarReloj(ind[i],ind_x[i],ind_y[i]);
		}
	}

	for (i=0;i<6;i++) //ver si la nave esta con una moneda/mina
	{
		if ((ind_x[i]<=(x+8)&&(ind_x[i]>=(x-8)))&&(ind_y[i]<=(y+8)&&(ind_y[i]>=(y-8)))) {
		//if (((ind_x[i]==x)&&(ind_y[i]==y))||(((ind_x[i]<x)&&((ind_x[i]+12)>=x))&&((ind_y[i]<y)&&((ind_y[i]+12)>=y)))||(((ind_x[i]>x)&&((ind_x[i]-12)<=x))&&((ind_y[i]<y)&&((ind_y[i]+12)>=y)))||(((ind_x[i]<x)&&((ind_x[i]+12)>=x))&&((ind_y[i]>y)&&((ind_y[i]-12)<=y)))||(((ind_x[i]>x)&&((ind_x[i]-12)<=x))&&((ind_y[i]>y)&&((ind_y[i]-12)<=y)))) {
			if (ind[i] < 51) 
			{
				BorrarMoneda(ind[i],ind_x[i],ind_y[i]);
				ind_y[i] = 176;
				mon++;
			} else if (ind[i] < 117) {
				BorrarMina(ind[i],ind_x[i],ind_y[i]);
				ind_y[i] = 176;
				vid--;
			} else {
				BorrarReloj(ind[i],ind_x[i],ind_y[i]);
				ind_y[i] = 176;
				tpartida -= (4*16);
			}
		}
	}
	iprintf("\x1b[05:1H Vidas: %d Monedas: %d                                    \n",vid,mon);
	iprintf("\x1b[012:1H Pulsa B para salir                                      \n");
	tpartida++;
	taime_sec++;
	iprintf("\x1b[07:1H Tiempo restante: %d                        \n", (30-(tpartida / 16)));
	if (vid < 0) tpartida = (16*30);
	if ((tpartida / 16) == 30)
	{
		iprintf("\x1b[2J");
		iprintf("\x1b[01:50H Partida acabada...\n");
		ESTADO = FIN;
		DeshabilitarIntTemp();
		DeshabilitarIntTec();
		tpartida = 0;
		BorrarNave(x,y);
		int i;
		for (i=0;i<6;i++)
		{
			if (ind[i] < 51) BorrarMoneda(ind[i],ind_x[i],ind_y[i]);
			else if (ind[i] < 117) BorrarMina(ind[i],ind_x[i],ind_y[i]);
			else BorrarReloj(ind[i],ind_x[i],ind_y[i]);
		}
		x=128; //posicion de la nave (abajo centrada)
		y=176;
		money = mon;
		taime = (taime_sec/16);
		InicializarSprite(); //inicializa las monedas/minas/relojes
	}		
}


	
	

