#include "cabecera.h"
#include <string.h>
#include <stdlib.h>

void lectura(int tamMapa[][2], mapeado *mapp, int *nummapas)
{
	int k, i, j, posEvento[2], cont = 0, link[2][3], numevent[MAX];
	char nombremapa[10], nombrevento[12], aux[15];
	FILE* mapa[10];
	FILE* events[10];
	FILE* links;

	links = fopen("links.txt", "rt");
	do
	{
		strcpy(nombremapa, "mapa");
		strcat(nombremapa, itoa((*nummapas) + 1, aux, 10));
		strcat(nombremapa, ".txt");
		mapa[*nummapas] = fopen(nombremapa, "rt");
		if (mapa[*nummapas] == NULL)
			break;
		strcpy(nombrevento, "events");
		strcat(nombrevento, itoa((*nummapas) + 1, aux, 10));
		strcat(nombrevento, ".txt");
		events[*nummapas] = fopen(nombrevento, "rt");
		(*nummapas)++;
	} while (1); //Bucle de apertura de archivos de mapas.

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
			mapp[i].map[k][tamMapa[i][0] - 1] = 0;
	for (i = 0; i < MAX; i++)
		for (k = 0; k < MAX; k++)
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