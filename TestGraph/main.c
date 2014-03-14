#include "cabecera.h"

int main()
{
	int numevento = 0, mapactual, numlink, numitems = 0;
	char **map;
	STRUCTpos VISION, tamMapa = { 0 };
	STRUCTgraph graph;
	STRUCTcontroles controles;
	STRUCTpersonaje personaje;
	STRUCTeventos *evento;
	STRUCTitem *items;
	STRUCTlink *puertas;

	srand(time(0));
	setlocale(LC_CTYPE, "Spanish");

	mapactual = 0;
	inicializacion(&numitems, &VISION, &graph, &controles, &personaje, &items, &mapactual);
	lectura(&numevento, &mapactual, &numlink, &tamMapa, &map, &evento, &puertas);
	instrucciones();
	display(numitems, numevento, &mapactual, &numlink, &VISION, &tamMapa, &graph, &controles, &personaje, &map, &evento, items, &puertas);
}