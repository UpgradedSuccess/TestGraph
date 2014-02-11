#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 30
#define VISIONX 6
#define VISIONY 3

typedef struct
{
	int pos[2];
	char name[30];
	char text[100];
} evento;

typedef struct
{
	char map[MAX];
	char desc[MAX][30];
	char text[MAX][100];
} mapeado;

int world(int, int, char, mapeado [MAX], int[2], evento[MAX], int);
int lectura(int*, int*, mapeado**, int*, evento**);
int display(int, int, int, mapeado*, evento*);

int main()
{
	int numX = 0, numY = 0, numevent = 0;
	evento *eventos = NULL;
	mapeado *mapp = NULL;

	mapp = (mapeado*)calloc(MAX, sizeof(mapeado));
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
		if (mapp[pj[1] - 1].map[pj[0]] == '#')
			return 0;
		else if (mapp[pj[1] - 1].map[pj[0]] == '-')
			return 1;
		else
			return 1;
	case 'a':
		if (mapp[pj[1]].map[pj[0] - 1] == '#')
			return 0;
		else if (mapp[pj[1]].map[pj[0] - 1] == '-')
			return 1;
		else
			return 1;
	case 's':
		if (mapp[pj[1] + 1].map[pj[0]] == '#')
			return 0;
		else if (mapp[pj[1] + 1].map[pj[0]] == '-')
			return 1;
		else
			return 1;
	case 'd':
		if (mapp[pj[1]].map[pj[0] + 1] == '#')
			return 0;
		else if (mapp[pj[1]].map[pj[0] + 1] == '-')
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
	int k;
	char caracter;
	FILE* db;
	FILE* events;

	db = fopen("db.txt", "rt");
	events = fopen("events.txt", "rt");
	while (feof(db) == 0)
	{
		(*mapp)[(*numY)].map[(*numX)] = fgetc(db);
		if ((*mapp)[(*numY)].map[(*numX)] == '-')
			strcpy((*mapp)[(*numY)].desc[(*numX)], "Llanos");
		else if ((*mapp)[(*numY)].map[(*numX)] == '#')
			strcpy((*mapp)[(*numY)].desc[(*numX)], "Muro");
		if ((*mapp)[(*numY)].map[(*numX)] == '\n')
		{
			(*numY)++;
			(*numX) = 0;
			continue;
		}
		(*numX)++;
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
		(*mapp)[(*eventos)[k].pos[1]].map[(*eventos)[k].pos[0]] = '!';
		strcpy((*mapp)[(*eventos)[k].pos[1]].desc[(*eventos)[k].pos[0]], (*eventos)[k].name);
		strcpy((*mapp)[(*eventos)[k].pos[1]].text[(*eventos)[k].pos[0]], (*eventos)[k].text);
	}
	fclose(db);
	fclose(events);
	return 0;
}

int display(int numX, int numY, int numevent, mapeado *mapp, evento *eventos)
{
	int k, i, coll, pj[2] = { 3, 3 };
	char mov;

	for (k = 0; k < numX; k++)
		mapp[k].map[19] = 0;
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
						printf("%c", mapp[i].map[k]);
				}
			}
		}
		printf("\n%s", mapp[pj[1]].desc[pj[0]]);
		switch (mov = getch())
		{
		case 'w':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] == 0)
					pj[1] = numY;
				else
					pj[1]--;
				break;
			}
		case 'a':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] == 0)
					pj[0] = numX - 2;
				else
					pj[0]--;
				break;
			}
		case 's':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] == numY)
					pj[1] = 0;
				else
					pj[1]++;
				break;
			}
		case 'd':
			coll = world(numX, numY, mov, mapp, pj, eventos, numevent);
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] == numX - 2)
					pj[0] = 0;
				else
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