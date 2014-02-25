#include "cabecera.h"

mapeado *mapp;
pos *tamMapa;

void display()
{
	int k, i, mapactual = 0, KEY = 1;
	char auxmap[MAX][MAX];
	pos pj, aux;

	pj.X = INICIOPJX;
	pj.Y = INICIOPJY;
	do
	{
		if (KEY == 1)
		{
			system("cls");
			aux.Y = 0;
			aux.X = 0;
			k = 0;
			i = 0;
			//##Bucle usado para guardar una parte del mapa (definida por VISIONX y VISIONY) en un mapa auxiliar para poder mostrarlo correctamente.
			for (i = (pj.Y - VISIONY); i < pj.Y + (VISIONY + 1); i++)
			{
				for (k = (pj.X - VISIONX); k < pj.X + (VISIONX + 2); k++)
				{
					if (k == pj.X && i == pj.Y) //Posición del personaje
					{
						auxmap[aux.Y][aux.X] = '*';
						aux.X++;
						continue;
					}
					if (k == (pj.X + (VISIONX + 1))) //Frontera del mapa
						auxmap[aux.Y][aux.X] = '\0';
					else
					{
						if (k >= tamMapa[mapactual].X || k<0 || i>tamMapa[mapactual].Y || i < 0) //Exterior del mapa
							continue;
						else //Resto del mapa
							auxmap[aux.Y][aux.X] = mapp[mapactual].map[i][k];
					}
					aux.X++;
				}
				aux.X = 0;
				aux.Y++;
			}
			for (k = 0; k < VISIONX + 1; k++) //Bucle para mostrar el mapa
				puts(auxmap[k]);
			printf("\nMapa: %d\n%s", mapactual + 1, mapp[mapactual].desc[pj.Y][pj.X]);
		}
		colisiones(&pj, &mapactual, &KEY); //Colision
	} while (1);
}