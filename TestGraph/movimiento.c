#include "cabecera.h"

short movimiento(bool *update, short numevento, bool *updatemap, char **map, STRUCTcontroles *controles, STRUCTpersonaje *personaje, STRUCTeventos *evento)
{
	short k, i, j;
	char mov;

	mov = getch();
	if (mov == controles->UP)
	{
		k = colisiones(update, map[personaje->pos.Y - 1][personaje->pos.X]); // La función colisiones determina si el movimiento se puede realizar.
		if (k == 1) // Movimiento posible.
			personaje->pos.Y--;
		else if (k == 2) // Puerta.
		{
			personaje->pos.Y--;
			return 1;
		}
	}
	else if (mov == controles->LEFT)
	{
		k = colisiones(update, map[personaje->pos.Y][personaje->pos.X - 1]);
		if (k == 1)
			personaje->pos.X--;
		else if (k == 2)
		{
			personaje->pos.X--;
			return 1;
		}
	}
	else if (mov == controles->DOWN)
	{
		k = colisiones(update, map[personaje->pos.Y + 1][personaje->pos.X]);
		if (k == 1)
			personaje->pos.Y++;
		else if (k == 2)
		{
			personaje->pos.Y++;
			return 1;
		}
	}
	else if (mov == controles->RIGHT)
	{
		k = colisiones(update, map[personaje->pos.Y][personaje->pos.X + 1]);
		if (k == 1)
			personaje->pos.X++;
		else if (k == 2)
		{
			personaje->pos.X++;
			return 1;
		}
	}
	else if (mov == controles->ACTION)
	{
		if (map[personaje->pos.Y][personaje->pos.X] == '-') // Si se pulsa la tecla de acción en un llano no sucede nada (Obvio y tal)
		{
			(*updatemap) = false;
			return 0;
		}
		else if (map[personaje->pos.Y][personaje->pos.X] == '!') // En caso de ser un NPC se busca dicho NPC y se muestra su diálogo.
		{
			(*updatemap) = true;
			k = busquedaEvento(numevento, *personaje, evento);
			printf("\n\n\n");
			printf("%s: \n", evento[k].nombre);
			printf("-");
			for (i = 0; i < evento[k].numTexto; i++)
			{
				for (j = 0; j < strlen(evento[k].text[i]); j++)
				{
					printf("%c", evento[k].text[i][j]);
					Sleep(50);
				}
				printf("\n ");
				getch();
			}
			return 0;
		}
		return 0;
	}
	else if (mov == controles->MENU)
		return 2;
	else if (mov == controles->SPECIAL)
		return 3;
	return 0;
}