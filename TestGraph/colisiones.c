#include "cabecera.h"
#include <windows.h>
#include <conio.h>

mapeado *mapp;
pos *tamMapa;

void colisiones(pos *pj, int *mapactual)
{
	int k, i;
	char mov;
	link aux;

	switch (mov = getch())
	{
	case 'w':
		if (mapp[*mapactual].map[pj->Y - 1][pj->X] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y - 1][pj->X] == '-' || mapp[*mapactual].map[pj->Y - 1][pj->X] == 'E' || mapp[*mapactual].map[pj->Y - 1][pj->X] == '!')
		{
			if (pj->Y != 0)
				pj->Y--;
			return;
		}
		else
			return;
	case 'a':
		if (mapp[*mapactual].map[pj->Y][pj->X - 1] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X - 1] == '-' || mapp[*mapactual].map[pj->Y][pj->X - 1] == 'E' || mapp[*mapactual].map[pj->Y][pj->X - 1] == '!')
		{
			if (pj->X != 0)
				pj->X--;
			return;
		}
		else
			return;
	case 's':
		if (mapp[*mapactual].map[pj->Y + 1][pj->X] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y + 1][pj->X] == '-' || mapp[*mapactual].map[pj->Y + 1][pj->X] == 'E' || mapp[*mapactual].map[pj->Y + 1][pj->X] == '!')
		{
			if (pj->Y != tamMapa[*mapactual].Y)
				pj->Y++;
			return;
		}
		else
			return;
	case 'd':
		if (mapp[*mapactual].map[pj->Y][pj->X + 1] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X + 1] == '-' || mapp[*mapactual].map[pj->Y][pj->X + 1] == 'E' || mapp[*mapactual].map[pj->Y][pj->X + 1] == '!')
		{
			if (pj->X != tamMapa[*mapactual].X - 2)
				pj->X++;
			return;
		}
		else
			return;
	case 'e':
		if (mapp[*mapactual].map[pj->Y][pj->X] == '!')
		{
			printf("\n\n\n");
			printf("%s:\n", mapp[*mapactual].desc[pj->Y][pj->X]);
			printf("-");
			for (i = 0; i < mapp[*mapactual].numTexto[pj->Y][pj->X]; i++)
			{
				for (k = 0; k < strlen(mapp[*mapactual].text[pj->Y][pj->X][i]); k++)
				{
					printf("%c", mapp[*mapactual].text[pj->Y][pj->X][i][k]);
					Sleep(50);
				}
				printf("\n ");
				getch();
			}
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X] == 'E')
		{
			aux.map = mapp[*mapactual].dest[pj->Y][pj->X][0];
			aux.Y = mapp[*mapactual].dest[pj->Y][pj->X][1];
			aux.X = mapp[*mapactual].dest[pj->Y][pj->X][2];
			*mapactual = aux.map;
			pj->Y = aux.Y;
			pj->X = aux.X;
		}
		return;
	}
}