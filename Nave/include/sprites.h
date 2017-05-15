extern u16* gfxNave;
extern u16* gfxMoneda;
extern u16* gfxMina;
extern u16* gfxReloj;

/* Inicializar la memoria de Sprites. */
extern void initSpriteMem();

/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaPrincipal();

/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaSecundaria();

/* Para guardar los sprites en memoria y luego poder usarlos.*/

extern void guardarSpritesEnMemoria();
extern void MostrarMoneda(int indice, int x, int y);
extern void BorrarMoneda(int indice, int x, int y);

extern void MostrarReloj(int indice, int x, int y);
extern void BorrarReloj(int indice, int x, int y);

extern void MostrarMina(int indice, int x, int y);
extern void BorrarMina(int indice, int x, int y);

extern void Mostrarmina1(int indice, int x, int y);
extern void Borrarmina1(int indice, int x, int y);
extern void Mostrarmina2(int indice, int x, int y);
extern void Borrarmina2(int indice, int x, int y);

extern void Mostrarmoneda1(int indice, int x, int y);
extern void Borrarmoneda1(int indice, int x, int y);
extern void Mostrarmoneda2(int indice, int x, int y);
extern void Borrarmoneda2(int indice, int x, int y);

extern void Mostrarnave1(int indice, int x, int y);
extern void Borrarnave1(int indice, int x, int y);
extern void Mostrarnave2(int indice, int x, int y);
extern void Borrarnave2(int indice, int x, int y);

extern void Mostrarreloj1(int indice, int x, int y);
extern void Borrarreloj1(int indice, int x, int y);
extern void Mostrarreloj2(int indice, int x, int y);
extern void Borrarreloj2(int indice, int x, int y);

extern void MostrarNave (int x, int y);
extern void BorrarNave (int x, int y);





