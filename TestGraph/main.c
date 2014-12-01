#include "cabecera.h"

int main()
{
	short numevento = 0, mapactual, numlink, numitems = 0, mov, bat;
	char **map;
	bool updatemap = true; // Usado para determinar cuándo hay que refrescar la pantalla.
	bool update = true; // Usado para determinar cuándo hay que buscar una batalla.
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
		if (update == true) // Únicamente puede haber batallas al moverse por terreno válido, no al salir del menú (Actualmente no rula).
		{
			bat = rand() % 25;
			if (bat == 0)
			{
				batalla(&update, numitems, controles, &personaje, items);
				updatemap = true;
			}
			display(evento, VISION, tamMapa, graph, &personaje, map, updatemap, numevento, mapactual);
		}
		else
			update = true;
		mov = movimiento(&update, numevento, &updatemap, map, &controles, &personaje, evento);
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
				error(2);
			break;
		case 2: // El personaje ha abierto el menú
			pjmenu(controles, &personaje, items, mapactual, graph, VISION);
			break;
		case 3: // El personaje ha abierto el menú de administrador.
			adminmenu(&VISION, &graph, &controles, &personaje);
			break;
		default: // El personaje se ha movido a un terreno normal.
			break;
		}
	} while (1);
}