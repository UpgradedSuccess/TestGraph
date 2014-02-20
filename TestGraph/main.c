#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define MAX 30
#define VISIONX 4
#define VISIONY 2

typedef struct
{
	char map[MAX][MAX];
	char desc[MAX][MAX][30];
	char text[MAX][MAX][MAX][100];
	int dest[MAX][MAX][3];
	int numTexto[MAX][MAX];
} mapeado;

void world(mapeado[MAX], int[2], int*, int[MAX][2]);
void lectura(int[MAX][2], mapeado*, int*);
void display(int[MAX][2], mapeado*);

int main()
{
	int tamMapa[MAX][2], nummapas=0;
	mapeado *mapp = NULL;
	mapp = (mapeado*)calloc(MAX, sizeof(mapeado));	
	lectura(tamMapa, mapp, &nummapas);
	mapp = (mapeado*)realloc(mapp, (nummapas+1)* sizeof(mapeado));
	printf("Instrucciones:\n\nMovimiento: 'wasd'\nInteraccion: 'e'\n\nLeyenda:\nMuros: '#'\nPuertas: 'E'\nLlanos: '-'\n\nPulse una tecla para continuar...");
	getch();
	system("cls");
	display(tamMapa, mapp);
}

void world(mapeado mapp[MAX], int pj[2], int *mapactual, int tamMapa[MAX][2])
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

void lectura(int tamMapa[MAX][2], mapeado *mapp, int *nummapas)
{
	int k, i, j, posEvento[2], cont = 0, link[2][3], numevent[MAX];
	char nombremapa[10], nombrevento[15], aux[15];
	FILE* mapa[10];
	FILE* events[10];
	FILE* links;

	links = fopen("links.txt", "rt");	
	do
	{
		strcpy(nombremapa, "mapa");
		itoa((*nummapas) + 1, aux, 10);
		strcat(nombremapa, aux);
		strcpy(aux, ".txt");
		strcat(nombremapa, aux);
		mapa[(*nummapas)] = fopen(nombremapa, "rt");
		if (mapa[(*nummapas)] == NULL)
			break;
		(*nummapas)++;
	} while (1); //Bucle de apertura de archivos de mapas.

	for (k = 0; k < (*nummapas);k++)
	{
		strcpy(nombrevento, "events");
		itoa(k + 1, aux, 10);
		strcat(nombrevento, aux);
		strcpy(aux, ".txt");
		strcat(nombrevento, aux);
		events[k] = fopen(nombrevento, "rt");
	} //Bucle de apertura de archivos de eventos.
	
	for (k = 0; k < (*nummapas); k++)
	{
		tamMapa[k][0] = 0;
		tamMapa[k][1] = 0;
		while (feof(mapa[k]) == 0)
		{
			mapp[k].map[tamMapa[k][1]][tamMapa[k][0]] = fgetc(mapa[k]);	//Almacenamiento del mapa.

			//###Almacenamiento de descripciones del mapa##//
			if (mapp[k].map[tamMapa[k][1]][tamMapa[k][0]] == '-')
				strcpy(mapp[k].desc[tamMapa[k][1]][tamMapa[k][0]], "Llanos");
			else if (mapp[k].map[tamMapa[k][1]][tamMapa[k][0]] == '#')
				strcpy(mapp[k].desc[tamMapa[k][1]][tamMapa[k][0]], "Muro");
			if (mapp[k].map[tamMapa[k][1]][tamMapa[k][0]] == '\n')
			{
				tamMapa[k][1]++;	//El vector "tamMapa" se utiliza para ir apuntando a todos los tiles del mapa.
				tamMapa[k][0] = 0;
				continue;
			}
			tamMapa[k][0]++;
		}
		fclose(mapa[k]);
	}
	//##Se añade \0 al final de cada línea para que no se solapen los saltos de línea (Tú déjalo como está)##//
	for (i = 0; i < (*nummapas); i++)
		for (k = 0; k < tamMapa[i][1]; k++)
			mapp[i].map[k][tamMapa[i][0]-1] = 0;
	for (i = 0; i < MAX; i++)
		for (k = 0; k < MAX;k++)
			mapp[i].numTexto[i][k] = 0;
	//##Lectura y almacenamiento de los archivos de eventos##//
	for (i = 0; i < (*nummapas); i++)
	{
		numevent[i] = 0;
		cont = 0;
		while (feof(events[i]) == 0)
		{
			if (fgetc(events[i]) == '\n')
				numevent[i]++;
		}
		numevent[i] = numevent[i] / 3;
		rewind(events[i]);
		for (k = 0; k < numevent[i]; k++)
		{
			fflush(stdin);
			fscanf(events[i], "%d %d\n", &posEvento[0], &posEvento[1]);
			mapp[i].map[posEvento[1]][posEvento[0]] = '!';
			fscanf(events[i], "%[^\n]s", mapp[i].desc[posEvento[1]][posEvento[0]]);
			fseek(events[i], 2, SEEK_CUR);
			for (j = 0; j < MAX; j++)
			{
				fscanf(events[i], "%[^.]s", mapp[i].text[j][posEvento[1]][posEvento[0]]);
				if (fgetc(events[i]) == '.')
				{
					mapp[i].numTexto[posEvento[1]][posEvento[0]]++;
					if (fgetc(events[i]) == '\n')
						break;
				}
				else
					break;
			}
		}
		fclose(events[i]);
	}
	while (feof(links) == 0) //Lectura del archivo de links
	{
		fscanf(links, "%d %d %d ", &link[0][0], &link[0][1], &link[0][2]);
		fscanf(links, "%d %d %d\n", &link[1][0], &link[1][1], &link[1][2]);
		mapp[link[0][0]].dest[link[0][1]][link[0][2]][0] = link[1][0];
		mapp[link[0][0]].dest[link[0][1]][link[0][2]][1] = link[1][1];
		mapp[link[0][0]].dest[link[0][1]][link[0][2]][2] = link[1][2];
		mapp[link[1][0]].dest[link[1][1]][link[1][2]][0] = link[0][0];
		mapp[link[1][0]].dest[link[1][1]][link[1][2]][1] = link[0][1];
		mapp[link[1][0]].dest[link[1][1]][link[1][2]][2] = link[0][2];
		mapp[link[0][0]].map[link[0][1]][link[0][2]] = 'E';
		mapp[link[1][0]].map[link[1][1]][link[1][2]] = 'E';
		strcpy(mapp[link[0][0]].desc[link[0][1]][link[0][2]], "Puerta");
		strcpy(mapp[link[1][0]].desc[link[1][1]][link[1][2]], "Puerta");
	}
	fclose(links);
	return;
}

void display(int tamMapa[MAX][2], mapeado *mapp)
{
	int k, i, pj[2] = { 3, 3 }, mapactual = 0, cont1, cont2;
	char auxmap[MAX][MAX];

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
					if (k >= tamMapa[mapactual][0] || k<0 || i>tamMapa[mapactual][1] || i < 0) //Exterior del mapa
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
		world(mapp, pj, &mapactual, tamMapa); //Colision
		system("cls");
	} while (1);
}