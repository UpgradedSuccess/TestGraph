#include "cabecera.h"
#include <windows.h>
#include <conio.h>

void colisiones(mapeado mapp[], int pj[2], int *mapactual, int tamMapa[MAX][2])
{
	int aux[3], k, i;
	char mov;

	switch (mov = getch())
	{
	case 'w':
		if (mapp[*mapactual].map[pj[1] - 1][pj[0]] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj[1] - 1][pj[0]] == '-' || mapp[*mapactual].map[pj[1] - 1][pj[0]] == 'E' || mapp[*mapactual].map[pj[1] - 1][pj[0]] == '!')
		{
			if (pj[1] != 0)
				pj[1]--;
			return; //El personaje se mueve
		}
		else
			return; //El personaje se mueve
	case 'a':
		if (mapp[*mapactual].map[pj[1]][pj[0] - 1] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj[1]][pj[0] - 1] == '-' || mapp[*mapactual].map[pj[1]][pj[0] - 1] == 'E' || mapp[*mapactual].map[pj[1]][pj[0] - 1] == '!')
		{
			if (pj[0] != 0)
				pj[0]--;
			return;
		}
		else
			return;
	case 's':
		if (mapp[*mapactual].map[pj[1] + 1][pj[0]] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj[1] + 1][pj[0]] == '-' || mapp[*mapactual].map[pj[1] + 1][pj[0]] == 'E' || mapp[*mapactual].map[pj[1] + 1][pj[0]] == '!')
		{
			if (pj[1] != tamMapa[*mapactual][1])
				pj[1]++;
			return;
		}
		else
			return;
	case 'd':
		if (mapp[*mapactual].map[pj[1]][pj[0] + 1] == '#')
		{
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj[1]][pj[0] + 1] == '-' || mapp[*mapactual].map[pj[1]][pj[0] + 1] == 'E' || mapp[*mapactual].map[pj[1]][pj[0] + 1] == '!')
		{
			if (pj[0] != tamMapa[*mapactual][0] - 2)
				pj[0]++;
			return;
		}
		else
			return;
	case 'e':
		if (mapp[*mapactual].map[pj[1]][pj[0]] == '!')
		{
			printf("\n\n\n");
			printf("%s:\n", mapp[*mapactual].desc[pj[1]][pj[0]]);
			printf("-");
			for (i = 0; i < mapp[*mapactual].numTexto[pj[1]][pj[0]]; i++)
			{
				for (k = 0; k < strlen(mapp[*mapactual].text[i][pj[1]][pj[0]]); k++)
				{
					printf("%c", mapp[*mapactual].text[i][pj[1]][pj[0]][k]);
					Sleep(50);
				}
				printf("\n ");
				getch();
			}
			return;
		}
		else if (mapp[*mapactual].map[pj[1]][pj[0]] == 'E')
		{
			aux[0] = mapp[*mapactual].dest[pj[1]][pj[0]][0];
			aux[1] = mapp[*mapactual].dest[pj[1]][pj[0]][1];
			aux[2] = mapp[*mapactual].dest[pj[1]][pj[0]][2];
			*mapactual = aux[0];
			pj[1] = aux[1];
			pj[0] = aux[2];
		}
		return;
	}
}