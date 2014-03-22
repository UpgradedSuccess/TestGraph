#include "cabecera.h"

int main()
{
	short numevento = 0, mapactual, numlink, numitems = 0, mov, bat, k;
	char **map;
	bool updatemap = true;
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
	intromenu(&items, controles, &personaje, &mapactual);
	lectura(&numevento, &mapactual, &numlink, &tamMapa, &map, &evento, &puertas);
	do
	{
		bat = rand() % 25;
		if (bat == 0)
		{
			batalla(numitems, controles, &personaje, items);
			updatemap = true;
		}
		display(evento, VISION, tamMapa, graph, &personaje, map, updatemap, numevento, mapactual);
		mov = movimiento(numevento, &updatemap, map, &controles, &personaje, evento);
		switch (mov)
		{
		case 1:
			if ((busquedaPuerta(&mapactual, &numlink, &personaje, puertas)) == 1)
			{
				for (k = 0; k <= tamMapa.Y; k++)
					free(map[k]);
				free(evento);
				updatemap = true;
				lectura(&numevento, &mapactual, &numlink, &tamMapa, &map, &evento, &puertas);
			}
			break;
		case 2:
			pjmenu(controles, &personaje, items, mapactual);
			break;
		case 3:
			adminmenu(&VISION, &graph, &controles, &personaje);
			break;
		default:
			break;
		}
	} while (1);
}