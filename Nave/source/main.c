/*---------------------------------------------------------------------------------
Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graficos.h"
#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutservs.h"
#include "teclado.h"
#include "temporizadores.h"

//---------------------------------------------------------------------------------
// variables globales

int ESTADO = INICIO;
//double x = 128;
//double y = 176;
int x = 128;
int y = 176;
int tpartida = 0;
int money = 0;
int taime = 0;

int main() {

	/* Definir variables */	
	touchPosition pos_pantalla;

	/*  Poner en marcha el motor gráfico 2D. */
    	powerOn(POWER_ALL_2D);

	/*
     	*  Establecer la pantalla inferior como principal, inicializar el sistema gráfico
     	*  y configurar el sistema de fondos.
     	*/
    	lcdMainOnBottom();
    	initVideo();
    	initFondos();

    	/* Mostrar fondos en pantalla. */
    	SetFondo();
	//mostrarFondoSub();

	/* Inicializar memoria de sprites y guardar en ella los sprites */
	initSpriteMem();
	guardarSpritesEnMemoria();

	/* Establecer las paletas para los sprites */
	establecerPaletaPrincipal();
	establecerPaletaSecundaria();

	/* Para poder imprimir en pantalla (hacer trazas) hay que descomentar esta línea */
	 consoleDemoInit();
	/* Una vez descomentada, no se verán los gráficos de la pantalla superior. */	
// ...
	//iprintf("\x1b[2J"); limpia pantalla
	//iprintf("\x1b[10:0H fila 10 colummna 0");

	interrupciones();
	InicializarSprite();
	//iprintf("\x1b[09:1H estado: %d \n",ESTADO);
	int n=0;
while(1)
{
	//iprintf("\x1b[30:1H");
	if (ESTADO == INICIO)
	{
		iprintf("\x1b[01:1H   Bitcoin Collector: Molecule\n");
		iprintf("\x1b[04:6H                CH3 \n");
		iprintf("\x1b[05:6H                 | \n");
		iprintf("\x1b[06:6H                 N \n");
		iprintf("\x1b[07:6H                /| \n");
		iprintf("\x1b[08:6H          NH--HC C==O \n");
		iprintf("\x1b[09:6H          ||  || | \n");
		iprintf("\x1b[10:6H          ||  || | \n");
		iprintf("\x1b[11:6H          CH  CH N--CH3 \n");
		iprintf("\x1b[12:6H           |   | |  \n");
		iprintf("\x1b[13:6H           N   N-C \n");
		iprintf("\x1b[14:6H           |   | \n");
		iprintf("\x1b[15:6H           CH3 O \n");
		iprintf("\x1b[17:1H  Recolecta Bitcoins y financia\n");
		iprintf("\x1b[18:1H   los experimentos moleculares\n");
		iprintf("\x1b[19:1H   Evita minas y recoge relojes\n");
		iprintf("\x1b[20:1H    para ahumentar tu tiempo.\n");
		iprintf("\x1b[22:1H     pulsa A para comenzar!\n");

		//mostrar nave y letras en la pantalla de abajo
		MostrarNave(100,32);
		Mostrarnave1(3,120,32);
		Mostrarnave2(5,136,32);
  		MostrarMoneda(6,100,56);
		Mostrarmoneda1(7,120,56);
		Mostrarmoneda2(9,136,56);
		MostrarMina(11,100,80);
		Mostrarmina1(12,120,80);
		Mostrarmina2(14,136,80);
		MostrarReloj(16,100,104);
		Mostrarreloj1(17,120,104);
		Mostrarreloj2(19,136,104);
		
    
		if (TeclaPulsada() == A)
		{
		//borrar nave y letras en la pantalla de abajo
		BorrarNave(100,32);
		Borrarnave1(3,120,32);
		Borrarnave2(5,136,32);
		BorrarMoneda(6,100,56);
		Borrarmoneda1(7,120,56);
		Borrarmoneda2(9,136,56);
		BorrarMina(11,100,80);
		Borrarmina1(12,120,80);
		Borrarmina2(14,136,80);
		BorrarReloj(16,100,104);
		Borrarreloj1(17,120,104);
		Borrarreloj2(19,136,104);

			iprintf("\x1b[2J");
			//iprintf("\x1b[012:1H Pulsa B para salir,\n");
			//iprintf("\x1b[02:8H Partida \n");
			ESTADO = PARTIDA;
			HabilitarIntTemp();
			HabilitarIntTec();
			MostrarNave(x,y);
		}
	} if (ESTADO == FIN)
	{
		iprintf("\x1b[03:1H Pulsa B para salir,\n");
		iprintf("\x1b[04:1H Pulsa A para reiniciar.\n");
		iprintf("\x1b[06:1H Monedas recogidas: %d                           \n",money);
		iprintf("\x1b[08:1H Tiempo aguantado: %d segundos                    \n",taime);
		if (TeclaPulsada() == A) 
		{ 
			iprintf("\x1b[2J");
			//iprintf("\x1b[010:1H Pulsa B para salir");
			//iprintf("\x1b[02:8H Partida \n");
			ESTADO = PARTIDA;
			HabilitarIntTemp();
			HabilitarIntTec();
			MostrarNave(x,y);
		}
		if (TeclaPulsada() == B) 
		{
			ESTADO = INICIO;
			iprintf("\x1b[2J");
		}
	} if (ESTADO == PARTIDA)
	{
		if (TeclaPulsada() == B) tpartida = (30 * 16);
	}
}

}
