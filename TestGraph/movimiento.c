#include "cabecera.h"

void movimiento()
{
	int k, i, j;
	char mov;

	mov = getch();
	if (mov == controles.UP)
	{
		auxmalloc = 0;
		updatemap = colisiones(map[pj.Y - 1][pj.X]);
		if (updatemap == 1)
			pj.Y--;
		else if (updatemap == 2)
		{
			pj.Y--;
			busquedaPuerta();
		}
	}
	else if (mov == controles.LEFT)
	{
		auxmalloc = 0;
		updatemap = colisiones(map[pj.Y][pj.X - 1]);
		if (updatemap == 1)
			pj.X--;
		else if (updatemap == 2)
		{
			pj.X--;
			busquedaPuerta();
		}
	}
	else if (mov == controles.DOWN)
	{
		auxmalloc = 0;
		updatemap = colisiones(map[pj.Y + 1][pj.X]);
		if (updatemap == 1)
			pj.Y++;
		else if (updatemap == 2)
		{
			pj.Y++;
			busquedaPuerta();
		}
	}
	else if (mov == controles.RIGHT)
	{
		auxmalloc = 0;
		updatemap = colisiones(map[pj.Y][pj.X + 1]);
		if (updatemap == 1)
			pj.X++;
		else if (updatemap == 2)
		{
			pj.X++;
			busquedaPuerta();
		}
	}
	else if (mov == controles.ACTION)
	{
		auxmalloc = 0;
		if (map[pj.Y][pj.X] == '-')
		{
			updatemap = 0;
			return;
		}
		else if (map[pj.Y][pj.X] == '!')
		{
			updatemap = 1;
			k = busquedaEvento();
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
			return;
		}
		return;
	}
	else if (mov == controles.MENU)
		pjmenu();
	else if (mov == controles.SPECIAL)
	{
		auxmalloc = 1;
		adminmenu();
	}
}