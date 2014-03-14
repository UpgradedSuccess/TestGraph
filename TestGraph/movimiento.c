#include "cabecera.h"

void movimiento(int numevento, int *mapactual, int *numlink, int *updatemap, int *auxmalloc, STRUCTpos *VISION, STRUCTpos *tamMapa, STRUCTgraph *graph, STRUCTcontroles *controles, STRUCTpersonaje *personaje, char ***map, STRUCTeventos **evento, STRUCTitem *items, STRUCTlink **puertas)
{
	int k, i, j;
	char mov;

	mov = getch();
	if (mov == controles->UP)
	{
		(*auxmalloc) = 0;
		(*updatemap) = colisiones((*map)[personaje->pos.Y - 1][personaje->pos.X]);
		if ((*updatemap) == 1)
			personaje->pos.Y--;
		else if ((*updatemap) == 2)
		{
			personaje->pos.Y--;
			(*auxmalloc) = 1;
			busquedaPuerta(&numevento, mapactual, numlink, updatemap, personaje, tamMapa, map, evento, puertas);
		}
	}
	else if (mov == controles->LEFT)
	{
		(*auxmalloc) = 0;
		(*updatemap) = colisiones((*map)[personaje->pos.Y][personaje->pos.X - 1]);
		if ((*updatemap) == 1)
			personaje->pos.X--;
		else if ((*updatemap) == 2)
		{
			personaje->pos.X--;
			(*auxmalloc) = 1;
			busquedaPuerta(&numevento, mapactual, numlink, updatemap, personaje, tamMapa, map, evento, puertas);
		}
	}
	else if (mov == controles->DOWN)
	{
		(*auxmalloc) = 0;
		(*updatemap) = colisiones((*map)[personaje->pos.Y + 1][personaje->pos.X]);
		if ((*updatemap) == 1)
			personaje->pos.Y++;
		else if ((*updatemap) == 2)
		{
			personaje->pos.Y++;
			(*auxmalloc) = 1;
			busquedaPuerta(&numevento, mapactual, numlink, updatemap, personaje, tamMapa, map, evento, puertas);
		}
	}
	else if (mov == controles->RIGHT)
	{
		(*auxmalloc) = 0;
		(*updatemap) = colisiones((*map)[personaje->pos.Y][personaje->pos.X + 1]);
		if ((*updatemap) == 1)
			personaje->pos.X++;
		else if ((*updatemap) == 2)
		{
			personaje->pos.X++;
			(*auxmalloc) = 1;
			busquedaPuerta(&numevento, mapactual, numlink, updatemap, personaje, tamMapa, map, evento, puertas);
		}
	}
	else if (mov == controles->ACTION)
	{
		(*auxmalloc) = 0;
		if ((*map)[personaje->pos.Y][personaje->pos.X] == '-')
		{
			(*updatemap) = 0;
			return;
		}
		else if ((*map)[personaje->pos.Y][personaje->pos.X] == '!')
		{
			(*updatemap) = 1;
			k = busquedaEvento(numevento, *personaje, evento);
			printf("\n\n\n");
			printf("%s: \n", (*evento)[k].nombre);
			printf("-");
			for (i = 0; i < (*evento)[k].numTexto; i++)
			{
				for (j = 0; j < strlen((*evento)[k].text[i]); j++)
				{
					printf("%c", (*evento)[k].text[i][j]);
					Sleep(50);
				}
				printf("\n ");
				getch();
			}
			return;
		}
		return;
	}
	else if (mov == controles->MENU)
		pjmenu(*controles, personaje, items, *mapactual);
	else if (mov == controles->SPECIAL)
	{
		(*auxmalloc) = 1;
		adminmenu(VISION, graph, controles, personaje);
	}
}