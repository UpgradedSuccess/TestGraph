#include "cabecera.h"
#include <string.h>
#include <stdlib.h>

mapeado *mapp;
pos *tamMapa;
eventstruct *evento;
int nummapas = 0;
int numevent;

void lectura()
{
	int k, i, j, cont = 0, numlinks = 0;
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
			if (fgetc(mapa[k]) == '\n')
			{
				tamMapa[k].Y++;
				tamMapa[k].X = 0;
				continue;
			}
			tamMapa[k].X++;
		}
		mapp[k].map = (char**)malloc(tamMapa[k].Y * sizeof(char*));
		mapp[k].dest = (int***)malloc(tamMapa[k].Y * sizeof(int**));
		for (i = 0; i <= tamMapa[k].Y; i++)
		{
			mapp[k].map[i] = (char*)malloc(tamMapa[k].X * sizeof(char));
			mapp[k].dest[i] = (int**)malloc(tamMapa[k].X * sizeof(int*));
			for (j = 0; j <= tamMapa[k].X; j++)
			{
				mapp[k].dest[i][j] = (int*)malloc(3 * sizeof(int));
			}
		}
		rewind(mapa[k]);
	}
	for (k = 0; k < nummapas; k++)
	{
		tamMapa[k].X = 0;
		tamMapa[k].Y = 0;
		while (feof(mapa[k]) == 0)
		{
			mapp[k].map[tamMapa[k].Y][tamMapa[k].X] = fgetc(mapa[k]);	//Almacenamiento del mapa.
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
		}
	}
	//##Lectura y almacenamiento de los archivos de eventos##//
	numevent = 0;
	for (i = 0; i < nummapas; i++)
	{
		while (feof(events[i]) == 0)
		{
			if (fgetc(events[i]) == '-')
				numevent++;
		}
		rewind(events[i]);
	}
	evento = (eventstruct*)malloc(numevent * sizeof(eventstruct));
	for (k = 0; k < numevent; k++)
		evento[k].numTexto = 0;
	numevent = 0;
	for (i = 0; i < nummapas; i++)
	{
		while (feof(events[i]) == 0)
		{
			if (fgetc(events[i]) == '-')
			{
				fscanf(events[i], "%d %d\n", &evento[numevent].posEvento.Y, &evento[numevent].posEvento.X);
				evento[numevent].posEvento.map = i;
				mapp[i].map[evento[numevent].posEvento.Y][evento[numevent].posEvento.X] = '!';
				fscanf(events[i], "%[^\n]s", evento[numevent].nombre);
				fgetc(events[i]);
				numevent++;
			}
			else
			{
				fscanf(events[i], "%[^\n]s", evento[numevent-1].text[evento[numevent-1].numTexto]);
				fgetc(events[i]);
				evento[numevent-1].numTexto++;
				if (feof(events[i]) != 0)
					break;
			}
		}
		fclose(events[i]);
	}
	while (feof(links) == 0) //Lectura del archivo de links
	{
		fscanf(links, "%d %d %d\n", &origen.map, &origen.Y, &origen.X);
		fscanf(links, "%d %d %d\n", &destino.map, &destino.Y, &destino.X);

		mapp[origen.map].dest[origen.Y][origen.X][0] = destino.map;
		mapp[origen.map].dest[origen.Y][origen.X][1] = destino.Y;
		mapp[origen.map].dest[origen.Y][origen.X][2] = destino.X;

		mapp[destino.map].dest[destino.Y][destino.X][0] = origen.map;
		mapp[destino.map].dest[destino.Y][destino.X][1] = origen.Y;
		mapp[destino.map].dest[destino.Y][destino.X][2] = origen.X;

		mapp[origen.map].map[origen.Y][origen.X] = 'E';
		mapp[destino.map].map[destino.Y][destino.X] = 'E';
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