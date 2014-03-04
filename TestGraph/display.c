﻿#include "cabecera.h"
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char **map;
STRUCTpos VISION, INITPJ, tamMapa, pj, TAMCMD;
STRUCTgraph graph;
int mapactual, auxmalloc;

void display()
{
	int k, i, updatemap = 1;
	char **auxmap = 0, descripcion[10], cmdSize[30];
	STRUCTpos aux;

	getch();
	system("cls");
	pj.X = INITPJ.X;
	pj.Y = INITPJ.Y;
	auxmalloc = 1;
	sprintf(cmdSize, "mode con: cols=%d lines=%d", TAMCMD.X, TAMCMD.Y);
	system(cmdSize);
	do
	{
		if (updatemap == 1)
		{
			system("cls");
			if (auxmalloc != 0)
			{
				auxmap = (char**)malloc(tamMapa.X* sizeof(char*));
				for (k = 0; k < tamMapa.X; k++)
					auxmap[k] = (char*)malloc(tamMapa.Y* sizeof(char));
			}
			aux.Y = 0;
			aux.X = 0;
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
			for (k = 0; k < VISION.X + 1; k++)
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
		movimiento(&updatemap);
	} while (1);
}