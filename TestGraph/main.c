#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 30
#define VISIONX 4
#define VISIONY 2

typedef struct
{
	char map[MAX][MAX];
	char desc[MAX][MAX][30];
	char text[MAX][MAX][100];
	int dest[MAX][MAX][3];
} mapeado;

int world(int[9][2], char, mapeado[MAX], int[2], int[MAX], int*);
int lectura(int[9][2], mapeado*, int[MAX], int*, int[10][2][3], int*);
int display(int[9][2], int[MAX], mapeado*);

int main()
{
	int posicion[9][2], numevent[MAX], numlinks=0, nummapas=0, link[10][2][3];
	mapeado *mapp = NULL;

	mapp = (mapeado*)calloc(MAX, sizeof(mapeado));	
	lectura(posicion, mapp, numevent, &numlinks, link, &nummapas);
	mapp = (mapeado*)realloc(mapp, (nummapas+1)* sizeof(mapeado));
	display(posicion, numevent, mapp);
}

int world(int posicion[9][2], char mov, mapeado mapp[MAX], int pj[2], int numevent[MAX], int *mapactual)
{
	int aux[3];

	switch (mov)
	{
	case 'w':
		if (mapp[*mapactual].map[pj[1] - 1][pj[0]] == '#')
			return 0; //El personaje no se mueve
		else if (mapp[*mapactual].map[pj[1] - 1][pj[0]] == '-' || mapp[*mapactual].map[pj[1] - 1][pj[0]] == 'E')
			return 1; //El personaje se mueve
		else
			return 1; //El personaje se mueve
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
			printf("\n\n\n");
			printf("%s:\n", mapp[*mapactual].desc[pj[1]][pj[0]]);
			printf("-%s\n", mapp[*mapactual].text[pj[1]][pj[0]]);
			getch();
			return 1;
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
		return 0;
	}
}

int lectura(int posicion[9][2], mapeado *mapp, int numevent[MAX], int *numlinks, int link[10][2][3], int *nummapas)
{
	int k, i, posEvento[2];
	char caracter, nombremapa[10], nombrevento[15], aux1[3][5] = { { '0', '0', '0', '0', '0' }, { '.', 't', 'x', 't', '\0' }, { 'm', 'a', 'p', 'a', '\0' } }, aux2[3][7] = { { '0', '0', '0', '0', '0', '0', '0' }, { '.', 't', 'x', 't', '\0', '\0', '\0' }, { 'e', 'v', 'e', 'n', 't', 's', '\0' } };
	FILE* mapa[10];
	FILE* events[10];
	FILE* links;

	links = fopen("links.txt", "rt");

	//####Lectura del archivo de links####//
	while (feof(links) == 0)
	{
		caracter = fgetc(links);
		if (caracter == '\n')
			(*numlinks)++;
	}
	rewind(links);
	for (k = 0; k < (*numlinks); k++)
	{
		fscanf(links, "%d %d %d ", &link[k][0][0], &link[k][0][1], &link[k][0][2]);
		fscanf(links, "%d %d %d\n", &link[k][1][0], &link[k][1][1], &link[k][1][2]);
	}
	//####################################//
	do
	{
		strcpy(nombremapa, aux1[2]);
		itoa((*nummapas) + 1, aux1[0], 10);
		strcat(nombremapa, aux1[0]);
		strcat(nombremapa, aux1[1]);
		mapa[(*nummapas)] = fopen(nombremapa, "rt");
		if (mapa[(*nummapas)] == NULL)
			break;
		(*nummapas)++;
	} while (1); //Bucle de apertura de archivos de mapas.

	for (k = 0; k < (*nummapas);k++)
	{
		strcpy(nombrevento, aux2[2]);
		itoa(k+1, aux2[0], 10);
		strcat(nombrevento, aux2[0]);
		strcat(nombrevento, aux2[1]);
		events[k] = fopen(nombrevento, "rt");
	} //Bucle de apertura de archivos de eventos.
	
	for (k = 0; k < (*nummapas); k++)
	{
		posicion[k][0] = 0;
		posicion[k][1] = 0;
		while (feof(mapa[k]) == 0)
		{
			mapp[k].map[posicion[k][1]][posicion[k][0]] = fgetc(mapa[k]);	//Almacenamiento del mapa.

			//###Almacenamiento de descripciones del mapa##//
			if (mapp[k].map[posicion[k][1]][posicion[k][0]] == '-')
				strcpy(mapp[k].desc[posicion[k][1]][posicion[k][0]], "Llanos");
			else if (mapp[k].map[posicion[k][1]][posicion[k][0]] == '#')
				strcpy(mapp[k].desc[posicion[k][1]][posicion[k][0]], "Muro");
			else if (mapp[k].map[posicion[k][1]][posicion[k][0]] == 'E')
			{
				strcpy(mapp[k].desc[posicion[k][1]][posicion[k][0]], "Puerta");

				for (i = 0; i < (*numlinks); i++) //Almacenamiento de links de puertas.
				{
					//##Emparejamiento de cada link con su puerta##//
					if (link[i][0][0] == k && link[i][0][1] == posicion[k][1] && link[i][0][2] == posicion[k][0]) //Búsqueda de emparejamientos en los links de origen
					{
						mapp[k].dest[posicion[k][1]][posicion[k][0]][0] = link[i][1][0];
						mapp[k].dest[posicion[k][1]][posicion[k][0]][1] = link[i][1][1];
						mapp[k].dest[posicion[k][1]][posicion[k][0]][2] = link[i][1][2];
					}
					else if (link[i][1][0] == k && link[i][1][1] == posicion[k][1] && link[i][1][2] == posicion[k][0])	//Búsqueda de emparejamientos en los links de destino
					{
						mapp[k].dest[posicion[k][1]][posicion[k][0]][0] = link[i][0][0];
						mapp[k].dest[posicion[k][1]][posicion[k][0]][1] = link[i][0][1];
						mapp[k].dest[posicion[k][1]][posicion[k][0]][2] = link[i][0][2];
					}
				}
			}
			if (mapp[k].map[posicion[k][1]][posicion[k][0]] == '\n')
			{
				posicion[k][1]++;	//El vector "posicion" se utiliza para ir apuntando a todos los tiles del mapa.
				posicion[k][0] = 0;
				continue;
			}
			posicion[k][0]++;
		}
		fclose(mapa[k]);
	}
	//##Se añade \0 al final de cada línea para que no se solapen los saltos de línea (Tú déjalo como está)##//
	for (i = 0; i < (*nummapas); i++)
		for (k = 0; k < posicion[i][1]; k++)
			mapp[i].map[k][posicion[i][0]-1] = 0;
	//##Lectura y almacenamiento de los archivos de eventos##//
	for (i = 0; i < (*nummapas); i++)
	{
		numevent[i] = 0;
		while (feof(events[i]) == 0)
		{
			caracter = fgetc(events[i]);
			if (caracter == '\n')
					numevent[i]++;
		}
		numevent[i] = numevent[i] / 3;
		rewind(events[i]);
		for (k = 0; k < numevent[i]; k++)
		{
			fscanf(events[i], "%d %d\n", &posEvento[0], &posEvento[1]);
			fscanf(events[i], "%[^\n]s", mapp[i].desc[posEvento[1]][posEvento[0]]);
			caracter = fgetc(events[i]);
			fscanf(events[i], "%[^\n]s", mapp[i].text[posEvento[1]][posEvento[0]]);
			mapp[i].map[posEvento[1]][posEvento[0]] = '!';
		}
		fclose(events[i]);
	}
	return 0;
}

int display(int posicion[9][2], int numevent[MAX], mapeado *mapp)
{
	int k, i, coll, pj[2] = { 3, 3 }, mapactual = 0, cont1, cont2;
	char mov, auxmap[MAX][MAX];

	do
	{
		cont1 = 0;
		cont2 = 0;
		k = 0;
		i = 0;
		//##Bucle usado para guardar una parte del mapa (definida por VISIONX y VISIONY) en un mapa auxiliar para poder mostrarlo correctamente.
		for (i = (pj[1] - VISIONY); i < pj[1] + (VISIONY + 1); i++)
		{
			for (k = (pj[0] - VISIONX); k < pj[0] + (VISIONX + 2); k++)
			{
				if (k == pj[0] && i == pj[1]) //Posición del personaje
				{
					auxmap[cont1][cont2] = '*';
					cont2++;
					continue;
				}
				if (k == (pj[0] + (VISIONX + 1))) //Frontera del mapa
					auxmap[cont1][cont2] = '\0';
				else
				{
					if (k >= posicion[mapactual][0] || k<0 || i>posicion[mapactual][1] || i < 0) //Exterior del mapa
						continue;
					else //Resto del mapa
						auxmap[cont1][cont2] = mapp[mapactual].map[i][k];
				}
				cont2++;
			}
			cont2 = 0;
			cont1++;
		}
		for (k = 0; k < VISIONX+1; k++) //Bucle para mostrar el mapa
			puts(auxmap[k]);
		printf("\nMapa: %d\n%s", mapactual+1, mapp[mapactual].desc[pj[1]][pj[0]]);

		//##Movimiento##//
		switch (mov = getch())
		{
		case 'w':
			coll = world(posicion, mov, mapp, pj, numevent, &mapactual); //Colision
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] != 0)
					pj[1]--;
				break;
			}
		case 'a':
			coll = world(posicion, mov, mapp, pj, numevent, &mapactual); //Colision
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] != 0)
					pj[0]--;
				break;
			}
		case 's':
			coll = world(posicion, mov, mapp, pj, numevent, &mapactual); //Colision
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[1] != posicion[mapactual][1])
					pj[1]++;
				break;
			}
		case 'd':
			coll = world(posicion, mov, mapp, pj, numevent, &mapactual); //Colision
			if (coll == 0)
				break;
			else if (coll == 1)
			{
				if (pj[0] != posicion[mapactual][0] - 2)
					pj[0]++;
				break;
			}
		case 'e':
			world(posicion, mov, mapp, pj,numevent, &mapactual); //Colision
			break;
		}
		system("cls");
	} while (1);
}