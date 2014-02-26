#include "cabecera.h"
#include <stdlib.h>

mapeado *mapp;
pos *tamMapa;
pos VISION;
pos INITPJ;
graphstruct graph;

void display()
{
	int k, i, mapactual = 0, KEY = 1;
	char **auxmap = 0;
	pos pj, aux;

	getch();
	system("cls");
	pj.X = INITPJ.X;
	pj.Y = INITPJ.Y;
	do
	{
		auxmap = (char**)malloc(tamMapa[mapactual].X* sizeof(char*));
		for (k = 0; k < tamMapa[mapactual].X; k++)
			auxmap[k] = (char*)malloc(tamMapa[mapactual].Y* sizeof(char));
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
					if (k == (pj.X + (VISION.X + 1))) //Frontera del mapa
						auxmap[aux.Y][aux.X] = '\0';
					else
					{
						if (k >= tamMapa[mapactual].X - 1 || k < 0 || i > tamMapa[mapactual].Y || i < 0) //Exterior del mapa
							continue;
						else //Resto del mapa
						{
							if (mapp[mapactual].map[i][k] == '-')
								auxmap[aux.Y][aux.X] = graph.PLAINS;
							else if (mapp[mapactual].map[i][k] == '#')
								auxmap[aux.Y][aux.X] = graph.WALL;
							else if (mapp[mapactual].map[i][k] == '!')
								auxmap[aux.Y][aux.X] = graph.EVENT;
							else if (mapp[mapactual].map[i][k] == 'E')
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
			printf("\nMapa: %d\n%s", mapactual + 1, mapp[mapactual].desc[pj.Y][pj.X]);
		}
		colisiones(&pj, &mapactual, &KEY); //Colision
	} while (1);
}