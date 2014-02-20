#include "cabecera.h"

void display(int tamMapa[MAX][2], mapeado *mapp)
{
	int k, i, pj[2] = { 3, 3 }, mapactual = 0, cont1, cont2;
	char auxmap[MAX][MAX];

	do
	{
		cont1 = 0;
		cont2 = 0;
		k = 0;
		i = 0;
		//##Bucle usado para guardar una parte del mapa (definida por VISIONX y VISIONY) en un mapa auxiliar para poder mostrarlo correctamente.
		for (i = (pj[1] - VISIONY); i < pj[1] + (VISIONY + 1); i++)
		{
			for (k = (pj[0] - VISIONX); k < pj[0] + (VISIONX + 2); k++)
			{
				if (k == pj[0] && i == pj[1]) //Posición del personaje
				{
					auxmap[cont1][cont2] = '*';
					cont2++;
					continue;
				}
				if (k == (pj[0] + (VISIONX + 1))) //Frontera del mapa
					auxmap[cont1][cont2] = '\0';
				else
				{
					if (k >= tamMapa[mapactual][0] || k<0 || i>tamMapa[mapactual][1] || i < 0) //Exterior del mapa
						continue;
					else //Resto del mapa
						auxmap[cont1][cont2] = mapp[mapactual].map[i][k];
				}
				cont2++;
			}
			cont2 = 0;
			cont1++;
		}
		for (k = 0; k < VISIONX + 1; k++) //Bucle para mostrar el mapa
			puts(auxmap[k]);
		printf("\nMapa: %d\n%s", mapactual + 1, mapp[mapactual].desc[pj[1]][pj[0]]);
		//##Movimiento##//
		colisiones(mapp, pj, &mapactual, tamMapa); //Colision
		system("cls");
	} while (1);
}