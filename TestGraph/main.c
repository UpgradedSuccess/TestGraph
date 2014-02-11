#include <stdio.h>
#include <stdlib.h>
#define MAX 30

typedef struct
{
	int pos[2];
	char text[MAX];
} evento;

int world(int, int, char, char[MAX][MAX], int[2], evento[MAX]);



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
	numevent = numevent / 2;
	rewind(events);
	for (k = 0; k < numevent; k++)
	{
		fscanf(events, "%d ", &eventos[k].pos[0]);
		fscanf(events, "%d\n", &eventos[k].pos[1]);
		fscanf(events, "%[^\n]s", eventos[k].text);
	}
	for (k = 0; k < numevent; k++)
		map[eventos[k].pos[1]][eventos[k].pos[0]] = '!';
	do
	{
		for (i = pj[1]-2; i < pj[1]+2; i++)
		{
			for (k = pj[0] - 6; k < pj[0] + 6; k++)
			{
				if (k == pj[0] && i == pj[1])
				{
					printf("*");
					continue;
				}
				if (k == (pj[0] + 5))
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
			coll = world(numX, numY, mov, map, pj, eventos);
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
			coll = world(numX, numY, mov, map, pj, eventos);
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
			coll = world(numX, numY, mov, map, pj, eventos);
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
			coll = world(numX, numY, mov, map, pj, eventos);
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
			world(numX, numY, mov, map, pj, eventos);
			break;
		}
		system("cls");
	} while (1);
}

int world(int numX, int numY, char mov, char map[MAX][MAX], int pj[2], evento eventos[MAX])
{
	int k;

	switch (mov)
	{
	case 'w':
		if (map[pj[1] - 1][pj[0]] == '#')
			return 0;
		else if (map[pj[1] - 1][pj[0]] == '-')
			return 1;
	case 'a':
		if (map[pj[1]][pj[0] - 1] == '#')
			return 0;
		else if (map[pj[1]][pj[0] - 1] == '-')
			return 1;
	case 's':
		if (map[pj[1] + 1][pj[0]] == '#')
			return 0;
		else if (map[pj[1] + 1][pj[0]] == '-')
			return 1;
	case 'd':
		if (map[pj[1]][pj[0] + 1] == '#')
			return 0;
		else if (map[pj[1]][pj[0] + 1] == '-')
			return 1;
	case 'e':
		for (k = 0; k < numY; k++)
		{
			if (pj[0] == eventos[k].pos[0])
			{
				if (pj[1] == eventos[k].pos[1])
				{
					system("cls");
					printf("%s", eventos[k].text);
					getch();
					return 1;
				}
			}
		}
		return 0;
	}
}