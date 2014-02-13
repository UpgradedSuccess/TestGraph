#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 30
#define VISIONX 4
#define VISIONY 2

typedef struct
{
	int pos[2];
	char name[30];
	char text[100];
} evento;

typedef struct
{
	char map[MAX][MAX];
	char desc[MAX][MAX][30];
	char text[MAX][MAX][100];
} mapeado;

int world(int[9][2], char, mapeado[MAX], int[2], evento[MAX], int, int*);
int lectura(int[9][2], mapeado*, int*, evento**);
int display(int[9][2], int, mapeado*, evento*);

int main()
{
	int posicion[9][2], numevent = 0;
	evento *eventos = NULL;
	mapeado *mapp = NULL;

	mapp = (mapeado*)calloc(10, sizeof(mapeado));
	eventos = (evento*)calloc(MAX, sizeof(evento));
	lectura(posicion, mapp, &numevent, &eventos);
	display(posicion, numevent, mapp, eventos);
}

int world(int posicion[2][2], char mov, mapeado mapp[MAX], int pj[2], evento eventos[MAX], int numevent, int *mapactual)
{
	int k;

	switch (mov)
	{
	case 'w':
		if (mapp[*mapactual].map[pj[1] - 1][pj[0]] == '#')
			return 0;
		else if (mapp[*mapactual].map[pj[1] - 1][pj[0]] == '-' || mapp[*mapactual].map[pj[1] - 1][pj[0]] == 'E')
			return 1;
		else
			return 1;
	case 'a':
		if (mapp[*mapactual].map[pj[1]][pj[0] - 1] == '#')
			return 0;
		else if (mapp[*mapactual].map[pj[1]][pj[0] - 1] == '-' || mapp[*mapactual].map[pj[1]][pj[0] - 1] == 'E')
			return 1;
		else
			return 1;
	case 's':
		if (mapp[*mapactual].map[pj[1] + 1][pj[0]] == '#')
			return 0;
		else if (mapp[*mapactual].map[pj[1] + 1][pj[0]] == '-' || mapp[*mapactual].map[pj[1] + 1][pj[0]] == 'E')
			return 1;
		else
			return 1;
	case 'd':
		if (mapp[*mapactual].map[pj[1]][pj[0] + 1] == '#')
			return 0;
		else if (mapp[*mapactual].map[pj[1]][pj[0] + 1] == '-' || mapp[*mapactual].map[pj[1]][pj[0] + 1] == 'E')
			return 1;
		else
			return 1;
	case 'e':
		if (mapp[*mapactual].map[pj[1]][pj[0]] == '!')
		{
			for (k = 0; k < numevent; k++)
			{
				if (pj[0] == eventos[k].pos[0])
				{
					if (pj[1] == eventos[k].pos[1])
					{
						printf("\n\n\n");
						printf("%s:\n", eventos[k].name);
						printf("-%s\n", eventos[k].text);
						getch();
						return 1;
					}
				}
			}
		}
		else if (mapp[*mapactual].map[pj[1]][pj[0]] == 'E')
		{
			if (*mapactual == 0)
			{
				*mapactual = 1;
				pj[1] = 6;
				pj[0] = 0;
				return 0;
			}
			else if(*mapactual == 1)
			{
				*mapactual = 0;
				pj[1] = 6;
				pj[0] = posicion[0][0] - 2;
				return 0;
			}
		}
		return 0;
	}
}

int lectura(int posicion[9][2], mapeado *mapp, int *numevent, evento **eventos)
{
	int k, i, nummapas=0;
	char caracter, nombremapa[10], aux[3][5] = { { '0', '0', '0', '0', '0' }, { '.', 't', 'x', 't', '\0' }, { 'm', 'a', 'p', 'a', '\0' } };
	FILE* mapa[3];
	FILE* events;

	events = fopen("events.txt", "rt");

	do
	{
		strcpy(nombremapa, aux[2]);
		itoa(nummapas+1, aux[0], 10);
		strcat(nombremapa, aux[0]);
		strcat(nombremapa, aux[1]);
		mapa[nummapas] = fopen(nombremapa, "rt");
		if (mapa[nummapas] == NULL)
			break;
		nummapas++;
	} while (1);

	for (k = 0; k < nummapas; k++)
	{
		posicion[k][0] = 0;
		posicion[k][1] = 0;
	}

	for (k = 0; k < nummapas; k++)
	{
		while (feof(mapa[k]) == 0)
		{
			mapp[k].map[posicion[k][1]][posicion[k][0]] = fgetc(mapa[k]);
			if (mapp[k].map[posicion[k][1]][posicion[k][0]] == '-')
				strcpy(mapp[k].desc[posicion[k][1]][posicion[k][0]], "Llanos");
			else if (mapp[k].map[posicion[k][1]][posicion[k][0]] == '#')
				strcpy(mapp[k].desc[posicion[k][1]][posicion[k][0]], "Muro");
			else if (mapp[k].map[posicion[k][1]][posicion[k][0]] == 'E')
				strcpy(mapp[k].desc[posicion[k][1]][posicion[k][0]], "Puerta");
			if (mapp[k].map[posicion[k][1]][posicion[k][0]] == '\n')
			{
				posicion[k][1]++;
				posicion[k][0] = 0;
				continue;
			}
			posicion[k][0]++;
		}
	}
	for (i = 0; i < nummapas; i++)
		for (k = 0; k < posicion[i][1]; k++)
			mapp[i].map[k][posicion[i][0]-1] = 0;
	for (k = 0; k < nummapas; k++)
		fclose(mapa[k]);

	while (feof(events) == 0)
	{
		caracter = fgetc(events);
		if (caracter == '\n')
			(*numevent)++;
	}
	(*numevent) = (*numevent) / 3;
	rewind(events);
	for (k = 0; k < (*numevent); k++)
	{
		fscanf(events, "%d %d\n", &(*eventos)[k].pos[0], &(*eventos)[k].pos[1]);
		fscanf(events, "%[^\n]s", (*eventos)[k].name);
		caracter = fgetc(events);
		fscanf(events, "%[^\n]s", (*eventos)[k].text);
	}
	fclose(events);
	for (k = 0; k < (*numevent); k++)
	{
		mapp[k].map[(*eventos)[k].pos[1]][(*eventos)[k].pos[0]] = '!';
		strcpy(mapp[k].desc[(*eventos)[k].pos[1]][(*eventos)[k].pos[0]], (*eventos)[k].name);
		strcpy(mapp[k].text[(*eventos)[k].pos[1]][(*eventos)[k].pos[0]], (*eventos)[k].text);
	}
	return 0;
}

int display(int posicion[9][2], int numevent, mapeado *mapp, evento *eventos)
{
	int k, i, coll, pj[2] = { 3, 3 }, mapactual=0;
	char mov;

	do
	{
		k = 0;
		i = 0;
		for (i = (pj[1] - VISIONY); i < pj[1] + (VISIONY + 1); i++)
		{
			for (k = (pj[0] - VISIONX); k < pj[0] + (VISIONX + 2); k++)
			{
				if (k == pj[0] && i == pj[1])
				{
					printf("*");
					continue;
				}
				if (k == (pj[0] + (VISIONX + 1)))
					printf("\n");
				else
				{
					if (k >= posicion[mapactual][0] || k<0 || i>posicion[mapactual][1] || i<0)
						continue;
					else
						printf("%c", mapp[mapactual].map[i][k]);
				}
			}
		}
		printf("\n%s", mapp[mapactual].desc[pj[1]][pj[0]]);
		switch (mov = getch())
		{
		case 'w':
			coll = world(posicion, mov, mapp, pj, eventos, numevent, &mapactual);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] != 0)
					pj[1]--;
				break;
			}
		case 'a':
			coll = world(posicion, mov, mapp, pj, eventos, numevent, &mapactual);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] != 0)
					pj[0]--;
				break;
			}
		case 's':
			coll = world(posicion, mov, mapp, pj, eventos, numevent, &mapactual);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] != posicion[mapactual][1])
					pj[1]++;
				break;
			}
		case 'd':
			coll = world(posicion, mov, mapp, pj, eventos, numevent, &mapactual);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] != posicion[mapactual][0] - 2)
					pj[0]++;
				break;
			}
		case 'e':
			world(posicion, mov, mapp, pj, eventos, numevent, &mapactual);
			break;
		}
		system("cls");
	} while (1);
}