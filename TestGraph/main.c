#include "cabecera.h"

STRUCTitem *items;
STRUCTeventos *evento;
STRUCTlink *puertas;
char **map;

int main()
{
	int numevento = 0, mapactual, numlink;
	STRUCTpos VISION, tamMapa = { 0 };
	STRUCTgraph graph;
	STRUCTcontroles controles;
	STRUCTpersonaje personaje;

	srand(time(0));
	setlocale(LC_CTYPE, "Spanish");

	inicializacion(&VISION, &graph, &controles, &personaje);
	mapactual = 0;
	lectura(&numevento, &mapactual, &numlink, &tamMapa);
	instrucciones();
	display(numevento, &mapactual, &numlink, &VISION, &tamMapa, &graph, &controles, &personaje);
}