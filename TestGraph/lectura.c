#include "cabecera.h"
#include <string.h>
#include <stdlib.h>

mapeado *mapp;
pos *tamMapa;
int nummapas = 0;

void lectura()
{
	int k, i, j, cont = 0, *numevent=0;
	char nombre[12], aux[15];
	pos posEvento;
	link origen, destino;
	FILE **mapa, **events, *links;

	links = fopen("links.txt", "rt");
	mapa = (FILE**)calloc(1, sizeof(FILE*));
	events = (FILE**)calloc(1, sizeof(FILE*));
	do
	{
		strcpy(nombre, "mapa");
		strcat(nombre, itoa(nummapas + 1, aux, 10));
		strcat(nombre, ".txt");
		mapa[nummapas] = fopen(nombre, "rt");
		if (mapa[nummapas] == NULL)
			break;
		strcpy(nombre, "events");
		strcat(nombre, itoa(nummapas + 1, aux, 10));
		strcat(nombre, ".txt");
		events[nummapas] = fopen(nombre, "rt");
		if (events[nummapas] == NULL)
		{
			printf("Error al abrir el archivo 'events%d.txt'\n", nummapas + 1);
			exit(0);
		}
		nummapas++;
		mapp = (mapeado*)realloc(mapp, nummapas * sizeof(mapeado));
		tamMapa = (pos*)realloc(tamMapa, nummapas * sizeof(pos));
		numevent = (int*)realloc(numevent, nummapas * sizeof(int));
		mapa = (FILE**)realloc(mapa, (nummapas+1) * sizeof(FILE*));
		events = (FILE**)realloc(events, (nummapas+1) * sizeof(FILE*));
		if (tamMapa == NULL || numevent == NULL || mapa == NULL || events == NULL)
			error(1);
	} while (1); //Bucle de apertura de archivos de mapas.
	for (k = 0; k < nummapas; k++)
	{
		tamMapa[k].X = 0;
		tamMapa[k].Y = 0;
		while (feof(mapa[k]) == 0)
		{

			mapp[k].map[tamMapa[k].Y][tamMapa[k].X] = fgetc(mapa[k]);	//Almacenamiento del mapa.

			//###Almacenamiento de descripciones del mapa##//
			if (mapp[k].map[tamMapa[k].Y][tamMapa[k].X] == '-')
				strcpy(mapp[k].desc[tamMapa[k].Y][tamMapa[k].X], "Llanos");
			else if (mapp[k].map[tamMapa[k].Y][tamMapa[k].X] == '#')
				strcpy(mapp[k].desc[tamMapa[k].Y][tamMapa[k].X], "Muro");
			if (mapp[k].map[tamMapa[k].Y][tamMapa[k].X] == '\n')
			{
				tamMapa[k].Y++;	//El vector "tamMapa" se utiliza para ir apuntando a todos los tiles del mapa.
				tamMapa[k].X = 0;
				continue;
			}
			tamMapa[k].X++;
		}
		fclose(mapa[k]);
	}
	//##Se añade \0 al final de cada línea para que no se solapen los saltos de línea (Tú déjalo como está)##//
	for (i = 0; i < nummapas; i++)
	{
		for (k = 0; k < tamMapa[i].Y; k++)
		{
			mapp[i].map[k][tamMapa[i].X - 1] = 0;
			mapp[i].numTexto[i][k] = 0;
		}
	}
	//##Lectura y almacenamiento de los archivos de eventos##//
	for (i = 0; i < nummapas; i++)
	{
		fgetc(events[i]);
		while (feof(events[i]) == 0)
		{
			numevent[i] = 0;
			cont = 0;
			j = 0;
			fscanf(events[i], "%d %d\n", &posEvento.Y, &posEvento.X);
			mapp[i].map[posEvento.Y][posEvento.X] = '!';
			mapp[i].numTexto[posEvento.Y][posEvento.X] = 0;
			fgetc(events[i]);
			fgets(mapp[i].desc[posEvento.Y][posEvento.X], MAX, events[i]);
			strtok(mapp[i].desc[posEvento.Y][posEvento.X], "\n");
			while (fgetc(events[i]) != '-')
			{
				fgets(mapp[i].text[posEvento.Y][posEvento.X][j], MAX, events[i]);
				strtok(mapp[i].text[posEvento.Y][posEvento.X][j], "\n");
				mapp[i].numTexto[posEvento.Y][posEvento.X]++;
				if (feof(events[i]) != 0)
					break;
				j++;
			}
			numevent[i]++;
		}
		fclose(events[i]);
	}
	while (feof(links) == 0) //Lectura del archivo de links
	{
		fscanf(links, "%d %d %d ", &origen.map, &origen.Y, &origen.X);
		fscanf(links, "%d %d %d\n", &destino.map, &destino.Y, &destino.X);

		mapp[origen.map].dest[origen.Y][origen.X][0] = destino.map;
		mapp[origen.map].dest[origen.Y][origen.X][1] = destino.Y;
		mapp[origen.map].dest[origen.Y][origen.X][2] = destino.X;

		mapp[destino.map].dest[destino.Y][destino.X][0] = origen.map;
		mapp[destino.map].dest[destino.Y][destino.X][1] = origen.Y;
		mapp[destino.map].dest[destino.Y][destino.X][2] = origen.X;

		mapp[origen.map].map[origen.Y][origen.X] = 'E';
		mapp[destino.map].map[destino.Y][destino.X] = 'E';

		strcpy(mapp[origen.map].desc[origen.Y][origen.X], "Puerta");
		strcpy(mapp[destino.map].desc[destino.Y][destino.X], "Puerta");
	}
	fclose(links);
	return;
}

void error(int err)
{
	switch (err)
		case 1:
			printf("Error de memoria.\n");
			exit(0);
}