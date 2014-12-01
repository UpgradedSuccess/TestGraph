#include "cabecera.h"

int main()
{
	short numevento = 0, mapactual, numlink, numitems = 0, mov, bat;
	char **map;
	bool updatemap = true; // Usado para determinar cuándo hay que refrescar la pantalla.
	bool update = false; // Usado para determinar cuándo hay que buscar una batalla.
	STRUCTpos VISION, tamMapa = { 0 };
	STRUCTgraph graph;
	STRUCTcontroles controles;
	STRUCTpersonaje personaje;
	STRUCTeventos *evento;
	STRUCTitem *items;
	STRUCTlink *puertas;

	srand(time(0));
	setlocale(LC_CTYPE, "Spanish");
	mapactual = 0; // Mapa a cargar por defecto.
	inicializacion(&numitems, &VISION, &graph, &controles, &personaje, &items, &mapactual); //Inicialización de variables.
	intromenu(&items, controles, &personaje, &mapactual); // Menú de introducción (Nuevo juego, Cargar partida...).
	lectura(&numevento, &mapactual, &numlink, &tamMapa, &map, &evento, &puertas); // Primera lectura del mapa.

	do // Bucle principal.
	{
		bat = rand() % 25;
		if (bat == 0 && update == true)
		{
			batalla(numitems, controles, &personaje, items);
			updatemap = true;
		}
		if (updatemap == true)
			display(evento, VISION, tamMapa, graph, &personaje, map, numevento, mapactual);
		mov = movimiento(numevento, map, &controles, &personaje, evento);
		switch (mov) // El valor devuelto por la función movimiento determina si el personaje se ha movido a un terreno normal, a una puerta o se ha pulsado el menú.
		{
		case 1: // El personaje se ha movido a una puerta.
			if ((busquedaPuerta(&mapactual, &numlink, &personaje, puertas)) == 1) // Se busca la puerta de enlace y se asigna como actual el mapa de destino.
			{
				free(evento);
				updatemap = true;
				lectura(&numevento, &mapactual, &numlink, &tamMapa, &map, &evento, &puertas); // Se lee el mapa al que lleva la puerta.
			}
			else
				error(2, mapactual);
			break;
		case 2: // El personaje ha abierto el menú
			update = false;
			updatemap = true;
			pjmenu(controles, &personaje, items, mapactual, graph, VISION);
			break;
		case 3: // El personaje ha abierto el menú de administrador.
			update = false;
			updatemap = true;
			adminmenu(&VISION, &graph, &controles, &personaje);
			break;
		case 4:
			update = false;
			updatemap = false;
			break;
		case 5:
			update = false;
			updatemap = true;
			break;
		default: // El personaje se ha movido a un terreno normal.
			break;
		}
	} while (1);
}