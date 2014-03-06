#include "cabecera.h"

STRUCTcontroles controles;
STRUCTpos VISION, INITPJ, TAMCMD;
STRUCTgraph graph;
STRUCTpersonaje personaje;
STRUCTitem *items;
STRUCTpos tamMapa = { 0 };
STRUCTeventos *evento;
STRUCTlink *puertas;
char **map;
int auxmalloc, updatemap, numinv = 4, numevento = 0, mapactual, numlink, numitems = 0;

int main()
{
	setlocale(LC_CTYPE, "Spanish");

	inicializacion();
	lectura();
	instrucciones();
	display();
}