/*-------------------------------------
defines.h
-------------------------------------*/

#include <nds.h>
#include <stdio.h>

//Aquí se definen los registros del gestor de interrupciones

#define IME		(*(vuint16*)0x04000208) //Interrupt Master Enable -- Habilita o deshabilita todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable -- Activa o desactiva las interrupciones una a una
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag -- Guarda las peticiones de interrupción

// Aquí se definen algunas funciones para el tratamiento de las interrupciones
#define EnableInts() IME=1 //habilita todas las interrupciones
#define DisableInts() IME=0 //deshabilita todas las interrupciones

// Aquí se definen los registros del teclado 
#define TECLAS_DAT	(*(vuint16*)0x4000130) //registro de datos del teclado
#define TECLAS_CNT	(*(vuint16*)0x4000132) //registro de control del teclado

// Aquí se definen los registros del temporizador
#define TIMER0_CNT   (*(vuint16*)0x04000102) //registro de control del temporizador
// El temporizador se activa poniendo un 1 en el 7º bit.
// El temporizador interrumpirá al desbordarse el contador, si hay un 1 en el 6º bit.
// Los dos bits de menos peso indican lo siguiente:
//			00 frecuencia 33554432 hz
//			01 frecuencia 33554432/64 hz
//			10 frecuencia 33554432/256 hz
//			11 frecuencia 33554432/1024 hz

#define TIMER0_DAT    (*(vuint16*)0x04000100) //registro de datos del temporizador
// Se utiliza para indicar a partir de qué valor tiene que empezar a contar

// Para no liarse con los números a cada teclas se le ha asignado un nombre

#define A			0 
#define B			1
#define SELECT			2 
#define START			3
#define DCHA			4
#define IZDA			5
#define ARRIBA			6 
#define ABAJO			7
#define R			8 
#define L			9

// Asignar un nombre a cada estado
#define INICIO		0
#define PARTIDA		1
//#define ESPERA		2
#define FIN		2
//...

// variables globales

extern int ESTADO;
extern int tpartida;
extern int money, taime;
//extern double x,y;
extern int x,y;






