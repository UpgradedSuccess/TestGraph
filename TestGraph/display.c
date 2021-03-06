﻿#include "cabecera.h"

void display(STRUCTeventos *evento, STRUCTpos VISION, STRUCTpos tamMapa, STRUCTgraph graph, STRUCTpersonaje *personaje, char **map, short numevento, short mapactual)
{
	short k, i;
	char **auxmap = 0, descripcion[20];
	STRUCTpos aux = { 0 };

		system("cls");
		auxmap = (char**)malloc((VISION.X + 2) * (VISION.Y + 1) * 4);
		for (k = 0; k < tamMapa.X; k++)
			auxmap[k] = (char*)malloc(VISION.X * 2 * sizeof(char));

		/* Bucle usado para guardar una parte del mapa 
		(definida por VISION.X y VISION.Y) en un mapa auxiliar para poder mostrarlo correctamente. */
		for (i = (personaje->pos.Y - VISION.Y); i < personaje->pos.Y + (VISION.Y + 1); i++)
		{
			for (k = (personaje->pos.X - VISION.X); k < personaje->pos.X + (VISION.X + 2); k++)
			{
				if (k == personaje->pos.X && i == personaje->pos.Y) // Posición del personaje
				{
					auxmap[aux.Y][aux.X] = graph.PJ;
					aux.X++;
					continue;
				}
				else if (k >= (personaje->pos.X + (VISION.X + 1))) // Frontera del mapa
					auxmap[aux.Y][aux.X] = '\0';
				else
				{
					if (k >= tamMapa.X - 1 || i > tamMapa.Y || i < 0 || k < 0) // Exterior del mapa
						continue;
					else // Resto del mapa (Lo que interesa)
					{
						if (map[i][k] == '-')
							auxmap[aux.Y][aux.X] = graph.PLAINS;
						else if (map[i][k] == '#')
							auxmap[aux.Y][aux.X] = graph.WALL;
						else if (map[i][k] == '!')
							auxmap[aux.Y][aux.X] = graph.EVENT;
						else if (map[i][k] == 'E')
							auxmap[aux.Y][aux.X] = graph.DOOR;
					}
				}
				aux.X++;
			}
			aux.X = 0;
			aux.Y++;
		}
		for (k = 0; k < VISION.X + 1; k++) // Muestra el mapa por líneas.
			puts(auxmap[k]);

		// Descripciones.
		if (map[personaje->pos.Y][personaje->pos.X] == graph.PLAINS)
			strcpy(descripcion, "Llanos");
		else if (map[personaje->pos.Y][personaje->pos.X] == graph.DOOR)
			strcpy(descripcion, "Puerta");
		else if (map[personaje->pos.Y][personaje->pos.X] == graph.EVENT)
		{
			k = busquedaEvento(numevento, *personaje, evento); // Búsqueda del diálogo del NPC en el archivo events.txt
			if (k == -1)
				error(3, mapactual);
			strcpy(descripcion, evento[k].nombre);
		}
		printf("\nMapa: %hd\n%s", mapactual + 1, descripcion);
	return;
}