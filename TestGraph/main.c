#include <stdio.h>
#include <stdlib.h>
#define MAX 30
#define VISIONX 4
#define VISIONY 2

typedef struct
{
	int pos[2];
	char name[30];
	char text[100];
} evento;

int world(int, int, char, char[MAX][MAX], int[2], evento[MAX], int);

int main()
{
	int numX = 0, numY = 0, pj[2] = { 3, 3 }, k, i, coll, numevent = 0;
	char map[MAX][MAX], mov, caracter;
	evento eventos[MAX];
	FILE* db;
	FILE* events;

	db = fopen("db.txt", "rb");
	events = fopen("events.txt", "rb");
	while (feof(db) == 0)
	{
		map[numY][numX] = fgetc(db);
		if (map[numY][numX] == '\n')
		{
			numY++;
			numX = 0;
			continue;
		}
		numX++;
	}
	while (feof(events) == 0)
	{
		caracter = fgetc(events);
		if (caracter == '\n')
			numevent++;
	}
	numevent = numevent / 3;
	rewind(events);
	for (k = 0; k < numevent; k++)
	{
		fscanf(events, "%d %d\n", &eventos[k].pos[0], &eventos[k].pos[1]);
		fscanf(events, "%[^\r]s", eventos[k].name);
		caracter = fgetc(events);
		caracter = fgetc(events);
		fscanf(events, "%[^\r]s", eventos[k].text);
	}
	for (k = 0; k < numevent; k++)
		map[eventos[k].pos[1]][eventos[k].pos[0]] = '!';
	do
	{
		for (i = pj[1]-VISIONY; i < pj[1] + (VISIONY + 1); i++)
		{
			for (k = pj[0] - VISIONX; k < pj[0] + (VISIONX+2); k++)
			{
				if (k == pj[0] && i == pj[1])
				{
					printf("*");
					continue;
				}
				if (k == (pj[0] + (VISIONX+1)))
					printf("\n");
				else
				{
					if (k >= numX || k<0 || i>numY || i<0)
						continue;
					else
						printf("%c", map[i][k]);
				}
			}
		}
		switch (mov = getch())
		{
		case 'w':
			coll = world(numX, numY, mov, map, pj, eventos, numevent);
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
			coll = world(numX, numY, mov, map, pj, eventos, numevent);
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
			coll = world(numX, numY, mov, map, pj, eventos, numevent);
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
			coll = world(numX, numY, mov, map, pj, eventos, numevent);
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
			world(numX, numY, mov, map, pj, eventos, numevent);
			break;
		}
		system("cls");
	} while (1);
}

int world(int numX, int numY, char mov, char map[MAX][MAX], int pj[2], evento eventos[MAX], int numevent)
{
	int k;

	switch (mov)
	{
	case 'w':
		if (map[pj[1] - 1][pj[0]] == '#')
			return 0;
		else if (map[pj[1] - 1][pj[0]] == '-')
			return 1;
		else
			return 1;
	case 'a':
		if (map[pj[1]][pj[0] - 1] == '#')
			return 0;
		else if (map[pj[1]][pj[0] - 1] == '-')
			return 1;
		else
			return 1;
	case 's':
		if (map[pj[1] + 1][pj[0]] == '#')
			return 0;
		else if (map[pj[1] + 1][pj[0]] == '-')
			return 1;
		else
			return 1;
	case 'd':
		if (map[pj[1]][pj[0] + 1] == '#')
			return 0;
		else if (map[pj[1]][pj[0] + 1] == '-')
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