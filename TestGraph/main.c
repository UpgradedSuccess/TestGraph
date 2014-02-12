#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 30
#define VISIONX 10
#define VISIONY 8

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

int world(int, int, char, mapeado [MAX], int[2], evento[MAX], int);
int lectura(int*, int*, mapeado**, int*, evento**);
int display(int, int, int, mapeado*, evento*);

int main()
{
	int numX = 0, numY = 0, numevent = 0;
	evento *eventos = NULL;
	mapeado *mapp = NULL;

	mapp = (mapeado*)calloc(1, sizeof(mapeado));
	eventos = (evento*)calloc(MAX, sizeof(evento));
	lectura(&numX, &numY, &mapp, &numevent, &eventos);
	display(numX, numY, numevent, mapp, eventos);
}

int world(int numX, int numY, char mov, mapeado mapp[MAX], int pj[2], evento eventos[MAX], int numevent)
{
	int k;

	switch (mov)
	{
	case 'w':
		if (mapp->map[pj[1] - 1][pj[0]] == '#')
			return 0;
		else if (mapp->map[pj[1] - 1][pj[0]] == '-')
			return 1;
		else
			return 1;
	case 'a':
		if (mapp->map[pj[1]][pj[0] - 1] == '#')
			return 0;
		else if (mapp->map[pj[1]][pj[0] - 1] == '-')
			return 1;
		else
			return 1;
	case 's':
		if (mapp->map[pj[1] + 1][pj[0]] == '#')
			return 0;
		else if (mapp->map[pj[1] + 1][pj[0]] == '-')
			return 1;
		else
			return 1;
	case 'd':
		if (mapp->map[pj[1]][pj[0] + 1] == '#')
			return 0;
		else if (mapp->map[pj[1]][pj[0] + 1] == '-')
			return 1;
		else
			return 1;
	case 'e':
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
		return 0;
	}
}

int lectura(int *numX, int *numY, mapeado **mapp, int *numevent, evento **eventos)
{
	int k, nummapas=1;
	char caracter, nombremapa[10], aux[3][5] = { { '0', '0', '0', '0', '0' }, { '.', 't', 'x', 't', '\0' }, { 'm', 'a', 'p', 'a', '\0' } };
	FILE* mapa[9];
	FILE* events;

	events = fopen("events.txt", "rt");

	do
	{
		strcpy(nombremapa, aux[2]);
		itoa(nummapas, aux[0], 10);
		strcat(nombremapa, aux[0]);
		strcat(nombremapa, aux[1]);
		mapa[nummapas - 1] = fopen(nombremapa, "rt");
		if (mapa[nummapas-1] == NULL)
			break;
		nummapas++;
	} while (1);

	for (k = 0; k < nummapas; k++)
	{
		while (feof(mapa[0]) == 0)
		{
			(*mapp)->map[(*numY)][(*numX)] = fgetc(mapa[0]);
			if ((*mapp)->map[(*numY)][(*numX)] == '-')
				strcpy((*mapp)->desc[(*numY)][(*numX)], "Llanos");
			else if ((*mapp)->map[(*numY)][(*numX)] == '#')
				strcpy((*mapp)->desc[(*numY)][(*numX)], "Muro");
			else if ((*mapp)->map[(*numY)][(*numX)] == 'E')
				strcpy((*mapp)->desc[(*numY)][(*numX)], "Puerta");
			if ((*mapp)->map[(*numY)][(*numX)] == '\n')
			{
				(*numY)++;
				(*numX) = 0;
				continue;
			}
			(*numX)++;
		}
	}
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
	for (k = 0; k < (*numevent); k++)
	{
		(*mapp)->map[(*eventos)[k].pos[1]][(*eventos)[k].pos[0]] = '!';
		strcpy((*mapp)->desc[(*eventos)[k].pos[1]][(*eventos)[k].pos[0]], (*eventos)[k].name);
		strcpy((*mapp)->text[(*eventos)[k].pos[1]][(*eventos)[k].pos[0]], (*eventos)[k].text);
	}
	fclose(mapa[0]);
	fclose(events);
	return 0;
}

int display(int numX, int numY, int numevent, mapeado *mapp, evento *eventos)
{
	int k, i, coll, pj[2] = { 3, 3 };
	char mov;

	for (k = 0; k < numX; k++)
		mapp->map[k][19] = 0;
	do
	{
		for (i = pj[1] - VISIONY; i < pj[1] + (VISIONY + 1); i++)
		{
			for (k = pj[0] - VISIONX; k < pj[0] + (VISIONX + 2); k++)
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
					if (k >= numX || k<0 || i>numY || i<0)
						continue;
					else
						printf("%c", mapp->map[i][k]);
				}
			}
		}
		printf("\n%s", mapp->desc[pj[1]][pj[0]]);
		switch (mov = getch())
		{
		case 'w':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] != 0)
					pj[1]--;
				break;
			}
		case 'a':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] != 0)
					pj[0]--;
				break;
			}
		case 's':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] != numY)
					pj[1]++;
				break;
			}
		case 'd':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] != numX - 2)
					pj[0]++;
				break;
			}
		case 'e':
			world(numX, numY, mov, mapp, pj, eventos, numevent);
			break;
		}
		system("cls");
	} while (1);
}