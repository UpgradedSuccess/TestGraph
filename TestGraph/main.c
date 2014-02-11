#include <stdio.h>
#include <stdlib.h>
#define MAX 30


int world(char, char[MAX][MAX], int*[2]);

int main()
{
	int numX = 0, numY = 0, pj[2] = { 3, 3 }, k, i, coll;
	char map[MAX][MAX], mov;
	FILE* db;

	db = fopen("db.txt", "rb");

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
	do
	{
		for (i = 0; i <= numY; i++)
		{
			for (k = 0; k < numX; k++)
			{
				if (k == pj[0] && i == pj[1])
				{
					printf("*");
					continue;
				}
				if (k == (numX - 1))
					printf("\n");
				else
					printf("%c", map[i][k]);
			}
		}
		switch (mov = getch())
		{
		case 'w':
			coll = world(mov, map, pj);
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
			coll = world(mov, map, pj);
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
			coll = world(mov, map, pj);
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
			coll = world(mov, map, pj);
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
		}
		system("cls");
	} while (1);
}

int world(char mov, char map[MAX][MAX], int pj[2])
{
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
	}
}