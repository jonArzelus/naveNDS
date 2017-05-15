/*---------------------------------------------------------------------------------
Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sprites.h"
#include "defines.h"

u16* gfxNave;
u16* gfxMoneda;
u16* gfxMina;
u16* gfxReloj;
u16* gfxmina1;
u16* gfxmina2;
u16* gfxmoneda1;
u16* gfxmoneda2;
u16* gfxnave1;
u16* gfxnave2;
u16* gfxreloj1;
u16* gfxreloj2;


/* Inicializar la memoria de Sprites. */
void initSpriteMem() {

	//int i;
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfxNave= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxMoneda= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxMina= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxReloj= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxmina1= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxmina2= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxmoneda1= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxmoneda2= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxnave1= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxnave2= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxreloj1= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxreloj2= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
}
void establecerPaletaPrincipal() {

//	SPRITE_PALETTE[1] = RGB15(31,0,0); // los pixels a 1 se mostrarán rojos
	SPRITE_PALETTE[1] = RGB15(40,4,220); // los pixels a 1 se mostrarán azul
//	SPRITE_PALETTE[1] = RGB15(31,31,0); // los pixels a 1 se mostrarán verdes mas oscuros
	SPRITE_PALETTE[3] = RGB15(0,0,0); // los pixels a 2 se mostrarán negro
	SPRITE_PALETTE[4] = RGB15(102,255,255); // los pixels a 4 seran azules
	SPRITE_PALETTE[5] = RGB15(255,255,255); // los pixels a 5 seran blancos
	SPRITE_PALETTE[6] = RGB15(255,0,0); // los pixels a 6 seran rojos
//	SPRITE_PALETTE[2] = RGB15(255,216,0); // los pixels a 2 se mostrarán amarillo dorado?
	SPRITE_PALETTE[2] = RGB15(255,255,0); // los pixels a 2 se mostrarán amarillo claro?
}

/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */
void establecerPaletaSecundaria() {

	SPRITE_PALETTE_SUB[1] = RGB15(0,31,0); // los pixels a 1 se mostrarán verdes
}

/* Dibujado de un Sprite de 16x16 pixels */
/* Debido al funcionamiento de los bancos de memoria, las primeras cuatro filas 
 * forman el cuadrante superior izquiero, las siguientes, el cuadrante superior 
 * derecho, las siguientes el cuadrante inferior izquierdo y las últimas cuatro
 * filas, el cuadrante inferior derecho, como se muestra al lado.
 */

u8 Mina[256] = 
{
	0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,	//	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,6,0,6,0,0,0,3,3,6,6,6,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	6,0,3,3,6,6,6,3,0,6,3,6,3,3,6,3,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	0,0,6,3,6,6,3,2,0,0,0,6,6,3,2,2,	//	0,0,0,3,0,0,0,3,3,0,0,0,3,0,0,0,

	0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,	//	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	6,0,6,0,0,0,0,0,6,6,6,3,3,0,0,0,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	3,6,6,6,3,3,0,6,3,6,3,3,6,3,6,0,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	2,3,6,6,3,6,0,0,2,2,3,6,6,0,0,0,	//	0,0,0,0,3,0,3,3,3,3,0,3,0,0,0,0,

	0,0,0,6,6,3,2,2,0,0,6,3,6,6,3,2,	//	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,6,3,6,3,3,6,3,6,0,3,3,6,6,6,3,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	0,0,0,3,3,6,6,6,0,0,0,0,0,6,0,6,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,	//	0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,

	2,2,3,6,6,0,0,0,2,3,3,6,3,6,0,0,	//	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	3,6,3,3,6,3,6,0,3,6,6,6,3,3,0,6,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	6,6,6,3,3,0,0,0,6,0,6,0,0,0,0,0,	//	0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,
	0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,	//	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
u8 Nave[256]=
{
	0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,	//	0,0,0,0,0,0,0,5, 5,0,0,0,0,0,0,0,
	0,0,0,0,0,0,5,5,0,0,0,0,0,5,3,5,	//	0,0,0,0,0,0,0,5, 5,0,0,0,0,0,0,0,
	5,0,5,0,0,5,5,5,5,5,5,0,0,0,0,5,	//	0,0,0,0,0,0,5,5, 5,5,0,0,0,0,0,0,
	0,5,0,0,0,0,0,5,5,5,5,0,0,0,5,5,	//	0,0,0,0,0,5,3,5, 5,3,5,0,0,0,0,0,
	
	5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,	//	5,0,5,0,0,5,5,5, 5,5,5,0,0,5,0,5,
	5,5,0,0,0,0,0,0,5,3,5,0,0,0,0,0,	//	5,5,5,0,0,0,0,5, 5,0,0,0,0,5,5,5,
	5,5,5,0,0,5,0,5,5,0,0,0,0,5,5,5,	//	0,5,0,0,0,0,0,5, 5,0,0,0,0,0,5,0,
	5,0,0,0,0,0,5,0,5,5,0,0,0,5,5,5,	//	5,5,5,0,0,0,5,5, 5,5,0,0,0,5,5,5,
	
	5,3,5,5,5,5,5,3,5,3,5,0,0,0,5,3,	//	5,3,5,5,5,5,5,3, 3,5,5,5,5,5,3,5,
	5,3,5,5,5,5,5,3,5,5,5,0,5,0,5,5,	//	5,3,5,0,0,0,5,3, 3,5,0,0,0,5,3,5,
	0,5,0,0,5,0,0,5,0,0,5,5,0,0,5,5,	//	5,3,5,5,5,5,5,3, 3,5,5,5,5,5,3,5,
	0,0,0,0,0,5,5,0,0,0,0,0,0,5,0,0,	//	5,5,5,0,5,0,5,5, 5,5,0,5,0,5,5,5,
	
	3,5,5,5,5,5,3,5,3,5,0,0,0,5,3,5,	//	0,5,0,0,5,0,0,5, 5,0,0,5,0,0,5,0,
	3,5,5,5,5,5,3,5,5,5,0,5,0,5,5,5,	//	0,0,5,5,0,0,5,5, 5,5,0,0,5,5,0,0,
	5,0,0,5,0,0,5,0,5,5,0,0,5,5,0,0,	//	0,0,0,0,0,5,5,0, 0,5,5,0,0,0,0,0,
	0,5,5,0,0,0,0,0,0,0,5,0,0,0,0,0,	//	0,0,0,0,0,3,0,0, 0,0,3,0,0,0,0,0,
};
u8 Moneda[256] = 
{
	0,0,0,0,0,0,3,3,0,0,0,0,3,3,3,3,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,3,3,2,2,2,0,0,3,3,2,2,3,2,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,3,3,2,2,2,3,2,0,3,2,2,2,3,3,3,	//	0,0,0,0,0,0,0,2, 2,0,0,0,0,0,0,0,
	3,3,2,2,2,2,3,2,3,3,2,2,2,2,3,3,	//	0,0,0,0,0,2,2,2, 2,2,2,0,0,0,0,0,

	3,3,0,0,0,0,0,0,3,3,3,3,0,0,0,0,	//	0,0,0,0,2,2,2,2, 2,2,2,2,0,0,0,0,
	2,2,2,3,3,0,0,0,3,2,2,2,3,3,0,0,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,
	3,2,2,2,2,3,3,0,3,3,2,2,2,2,3,0,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,
	2,2,3,2,2,2,3,3,3,3,2,2,2,2,3,3,	//	0,0,2,2,2,2,2,2, 2,2,2,2,2,2,0,0,

	3,3,2,2,2,2,3,2,3,3,2,2,2,2,3,2,	//	0,0,2,2,2,2,2,2, 2,2,2,2,2,2,0,0,
	0,3,2,2,2,3,3,3,0,3,3,2,2,2,3,2,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,
	0,0,3,3,2,2,3,2,0,0,0,3,3,2,2,2,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,
	0,0,0,0,3,3,3,3,0,0,0,0,0,0,3,3,	//	0,0,0,0,2,2,2,2, 2,2,2,2,0,0,0,0,

	2,2,3,2,2,2,3,3,2,2,3,2,2,2,3,3,	//	0,0,0,0,0,2,2,2, 2,2,2,0,0,0,0,0,
	3,3,2,2,2,2,3,0,3,2,2,2,2,3,3,0,	//	0,0,0,0,0,0,0,2, 2,0,0,0,0,0,0,0,
	3,2,2,2,3,3,0,0,2,2,2,3,3,0,0,0,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	3,3,3,3,0,0,0,0,3,3,0,0,0,0,0,0,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 Reloj[256] = 
{
	0,0,0,0,0,0,3,3,0,0,0,0,3,3,3,3,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,3,3,4,4,4,0,0,3,3,4,4,4,4,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,3,3,4,4,4,4,4,0,3,4,4,4,4,3,3,	//	0,0,0,0,0,0,0,4, 4,0,0,0,0,0,0,0,
	3,3,4,4,4,4,3,3,3,3,4,4,4,4,4,3,	//	0,0,0,0,0,4,4,4, 4,4,4,0,0,0,0,0,

	3,3,0,0,0,0,0,0,3,3,3,3,0,0,0,0,	//	0,0,0,0,4,4,4,4, 4,4,4,4,0,0,0,0,
	4,4,4,3,3,0,0,0,4,4,4,4,3,3,0,0,	//	0,0,0,4,4,4,4,4, 4,4,4,4,4,0,0,0,
	4,4,4,4,4,3,3,0,4,4,4,4,4,4,3,0,	//	0,0,0,4,4,4,4,4, 4,4,4,4,4,0,0,0,
	3,4,4,4,4,4,3,3,3,4,4,4,4,4,3,3,	//	0,0,4,4,4,4,4,4, 4,4,4,4,4,4,0,0,

	3,3,4,4,4,4,4,3,3,3,4,4,4,4,4,4,	//	0,0,4,4,4,4,4,4, 4,4,4,4,4,4,0,0,
	0,3,4,4,4,4,4,4,0,3,3,4,4,4,4,4,	//	0,0,0,4,4,4,4,4, 4,4,4,4,4,0,0,0,
	0,0,3,3,4,4,4,4,0,0,0,3,3,4,4,4,	//	0,0,0,4,4,4,4,4, 4,4,4,4,4,0,0,0,
	0,0,0,0,3,3,3,3,0,0,0,0,0,0,3,3,	//	0,0,0,0,4,4,4,4, 4,4,4,4,0,0,0,0,

	3,3,4,4,4,4,3,3,3,3,3,4,4,4,3,3,	//	0,0,0,0,0,4,4,4, 4,4,4,0,0,0,0,0,
	4,3,3,4,4,4,3,0,4,4,4,4,4,3,3,0,	//	0,0,0,0,0,0,0,4, 4,0,0,0,0,0,0,0,
	4,4,4,4,3,3,0,0,4,4,4,3,3,0,0,0,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	3,3,3,3,0,0,0,0,3,3,0,0,0,0,0,0,	//	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 mina1[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,5,0,0,0,5,0,
0,5,3,5,0,5,3,5, 0,5,3,3,5,3,3,5,
0,5,3,5,3,5,3,5, 0,5,3,5,5,5,3,5,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 5,0,5,0,0,5,0,0,
3,5,3,5,5,3,5,5, 5,5,3,3,5,3,5,3,
3,5,3,5,3,3,5,3, 3,5,3,5,5,3,5,3,

0,5,3,5,5,5,3,5, 0,5,3,5,5,5,3,5,
0,5,3,5,5,5,3,5, 0,0,5,0,0,0,5,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

3,5,3,5,5,3,5,3, 3,5,3,5,5,3,5,3,
3,5,3,5,5,3,5,3, 5,0,5,0,0,5,0,5,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 mina2[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 5,5,0,0,0,0,0,0,
3,3,5,0,0,0,0,0, 5,5,3,5,0,0,0,0, 
5,5,3,5,0,0,0,0, 3,3,3,5,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

5,5,3,5,0,0,0,0, 5,5,3,5,0,0,0,0,
5,5,3,5,0,0,0,0, 0,0,5,0,0,0,0,0, 
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 moneda1[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,5,0,0,0,5,0,0,
5,3,5,0,5,3,5,5, 5,3,3,5,3,3,5,3,
5,3,5,3,5,3,5,3, 5,3,5,5,5,3,5,3,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 5,5,0,0,5,0,0,5,
3,3,5,5,3,5,5,3, 5,5,3,5,3,3,5,3,
5,5,3,5,3,5,3,3, 5,5,3,5,3,5,5,3,

5,3,5,5,5,3,5,3, 5,3,5,5,5,3,5,3,
5,3,5,5,5,3,5,5, 0,5,0,0,0,5,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

5,5,3,5,3,5,5,3, 5,5,3,5,3,5,5,3, 
3,3,5,5,3,5,5,3, 5,5,0,0,5,0,0,5,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 moneda2[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,5,5,5,0,5,5,
5,5,3,3,3,5,3,3, 5,3,5,5,5,5,3,5,
5,3,5,5,5,5,3,5, 5,3,3,3,5,5,3,5,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,5,5,0,0,
5,0,0,5,3,3,5,0, 3,5,5,3,5,5,3,5,
5,3,5,3,5,5,3,5, 5,3,5,3,3,3,3,5,

5,3,5,5,5,5,3,5, 5,3,5,5,5,5,3,5,
5,5,3,3,3,5,3,3, 0,0,5,5,5,0,5,5,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

5,3,5,3,5,5,3,5, 3,5,5,3,5,5,3,5, 
5,0,5,3,5,5,3,5, 0,0,0,5,0,0,5,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 nave1[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,5,0,0,5,0,0, 0,5,3,5,5,3,5,5,
0,5,3,3,5,3,5,3, 0,5,3,5,3,3,5,3,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
5,5,0,0,5,0,5,0, 3,3,5,5,3,5,3,5,
5,5,3,5,3,5,3,5, 5,5,3,5,3,5,3,5,

0,5,3,5,5,3,5,3, 0,5,3,5,5,3,5,3,
0,5,3,5,5,3,5,3, 0,0,5,0,0,5,0,5,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

3,3,3,5,3,5,3,5, 5,5,3,5,3,5,3,5,
5,5,3,5,3,5,3,5, 5,5,3,5,5,3,5,0,
0,0,5,0,0,5,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 nave2[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,5,5,5,0,0,0,0, 5,3,3,3,5,0,0,0, 
3,5,5,5,0,0,0,0, 3,5,5,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

3,3,3,5,0,0,0,0, 3,5,5,0,0,0,0,0, 
3,5,5,5,0,0,0,0, 5,3,3,3,5,0,0,0,
0,5,5,5,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 reloj1[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,5,5,5,0,0,0, 0,5,3,3,3,5,0,5,
0,5,3,5,5,3,5,3, 0,5,3,5,5,3,5,3,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
5,5,5,0,5,0,0,0, 3,3,3,5,3,5,0,0,
5,5,5,5,3,5,0,5, 5,5,5,5,3,5,0,5,

0,5,3,3,3,5,5,3, 0,5,3,5,5,3,5,3,
0,5,3,5,5,3,5,3, 0,5,3,5,5,3,5,5,
0,0,5,0,0,5,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

3,3,5,5,3,5,0,5, 5,5,5,5,3,5,0,5,
5,5,5,5,3,5,5,5, 3,3,3,5,5,3,3,5,
5,5,5,0,0,5,5,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};
u8 reloj2[256] = 
{
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,5,5,0,0,0,0,0, 5,3,3,5,0,0,0,5,
3,5,5,3,5,0,0,5, 3,5,5,3,5,0,0,5,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
5,0,0,0,0,0,0,0, 3,5,0,0,0,0,0,0,
3,5,0,0,0,0,0,0, 3,5,0,0,0,0,0,0,

3,5,5,3,5,5,0,5, 3,5,5,3,5,3,5,5,
3,5,5,3,5,3,5,5, 5,3,3,5,0,5,3,3,
0,5,5,0,0,0,5,5, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

3,5,0,0,0,0,0,0, 3,5,0,0,0,0,0,0,
3,5,0,0,0,0,0,0, 5,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
};

void BorrarMoneda(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxMoneda,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void MostrarMoneda (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxMoneda,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void BorrarReloj(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxReloj,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void MostrarReloj (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxReloj,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void BorrarMina(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxMina,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void MostrarMina (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxMina,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}

void MostrarNave (int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		127,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxNave,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		);   
oamUpdate(&oamMain); 
}
void BorrarNave(int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			127,           //oam index (0 to 127)
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite
			SpriteSize_16x16,
			SpriteColorFormat_256Color,
			gfxNave,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			);
oamUpdate(&oamMain);
}



//letras -----------------------------------------------------------------------------------------------------------



void Borrarmina1(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmina1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarmina1 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmina1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarmina2(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmina2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarmina2 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmina2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarmoneda1(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmoneda1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarmoneda1 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmoneda1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarmoneda2(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmoneda2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarmoneda2 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxmoneda2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarnave1(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxnave1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarnave1 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxnave1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarnave2(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxnave2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarnave2 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxnave2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarreloj1(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxreloj1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarreloj1 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxreloj1,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}
void Borrarreloj2(int indice, int x, int y)
{

			oamSet(&oamMain, //main graphics engine context
			indice,           //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxreloj2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			true,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 
oamUpdate(&oamMain); 

}

void Mostrarreloj2 (int indice, int x, int y)
{
 
			oamSet(&oamMain, //main graphics engine context
			indice,          //oam index (0 to 127)  
			x, y,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,		 //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfxreloj2,//+16*16/2,                  //pointer to the loaded graphics
			-1,                  //sprite rotation data  
			false,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			); 

	oamUpdate(&oamMain);  
}


/* Para cada Sprite que se quiera llevar a pantalla hay que hacer una de estas funciones. */

void guardarSpritesEnMemoria(){ 
	int i;

		for(i = 0; i < 16 * 16 / 2; i++) //muestra un cuadrado en la memoria de la pantalla principal
		{				
				gfxMoneda[i] = Moneda[i*2] | (Moneda[(i*2)+1]<<8);
				gfxReloj[i] = Reloj[i*2] | (Reloj[(i*2)+1]<<8);
				gfxMina[i] = Mina[i*2] | (Mina[(i*2)+1]<<8);	
				gfxNave[i] = Nave[i*2] | (Nave[(i*2)+1]<<8);
				gfxmina1[i] = mina1[i*2] | (mina1[(i*2)+1]<<8);
				gfxmina2[i] = mina2[i*2] | (mina2[(i*2)+1]<<8);
				gfxmoneda1[i] = moneda1[i*2] | (moneda1[(i*2)+1]<<8);
				gfxmoneda2[i] = moneda2[i*2] | (moneda2[(i*2)+1]<<8);
				gfxnave1[i] = nave1[i*2] | (nave1[(i*2)+1]<<8);
				gfxnave2[i] = nave2[i*2] | (nave2[(i*2)+1]<<8);
				gfxreloj1[i] = reloj1[i*2] | (reloj1[(i*2)+1]<<8);
				gfxreloj2[i] = reloj2[i*2] | (reloj2[(i*2)+1]<<8);	
		}
}




