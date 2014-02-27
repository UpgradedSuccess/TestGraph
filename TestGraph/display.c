#include "cabecera.h"
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char **map;
STRUCTpos VISION, INITPJ, tamMapa, pj;
STRUCTgraph graph;
int mapactual;

void display()
{
	int k, i, KEY = 1;
	char **auxmap = 0, descripcion[10];
	STRUCTpos aux;

	getch();
	system("cls");
	pj.X = INITPJ.X;
	pj.Y = INITPJ.Y;
	do
	{
		auxmap = (char**)malloc(tamMapa.X* sizeof(char*));
		for (k = 0; k < tamMapa.X; k++)
			auxmap[k] = (char*)malloc(tamMapa.Y* sizeof(char));
		if (KEY == 1)
		{
			system("cls");
			aux.Y = 0;
			aux.X = 0;
			k = 0;
			i = 0;
			//##Bucle usado para guardar una parte del mapa (definida por VISION.X y VISION.Y) en un mapa auxiliar para poder mostrarlo correctamente.
			for (i = (pj.Y - VISION.Y); i < pj.Y + (VISION.Y + 1); i++)
			{
				for (k = (pj.X - VISION.X); k < pj.X + (VISION.X + 2); k++)
				{
					if (k == pj.X && i == pj.Y) //Posición del personaje
					{
						auxmap[aux.Y][aux.X] = graph.PJ;
						aux.X++;
						continue;
					}
					else if (k >= (pj.X + (VISION.X + 1))) //Frontera del mapa
						auxmap[aux.Y][aux.X] = '\0';
					else
					{
						if (k >= tamMapa.X - 1 || i > tamMapa.Y || i < 0 || k < 0) //Exterior del mapa
							continue;
						else //Resto del mapa
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
			for (k = 0; k < VISION.X + 1; k++) //Bucle para mostrar el mapa
				puts(auxmap[k]);
			if (map[pj.Y][pj.X] == graph.PLAINS)
				strcpy(descripcion, "Llanos");
			else if (map[pj.Y][pj.X] == graph.DOOR)
				strcpy(descripcion, "Puerta");
			else if (map[pj.Y][pj.X] == graph.EVENT)
			{
				k = busquedaEvento();
				strcpy(descripcion, evento[k].nombre);
			}
			printf("\nMapa: %d\n%s", mapactual + 1, descripcion);
		}
		colisiones(&KEY); //Colision
	} while (1);
}