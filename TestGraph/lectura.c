#include "cabecera.h"
#include <string.h>
#include <stdlib.h>

mapeado mapp;
pos tamMapa;
eventstruct *evento;
link *puertas;
int numevent, mapactual, numlink;

void lectura()
{
	int k, auxnumTexto;
	char nombre[12], aux[15], buffer;
	FILE *mapa, *events, *links;

	links = fopen("links.txt", "rt");
	strcpy(nombre, "mapa");
	strcat(nombre, itoa(mapactual + 1, aux, 10));
	strcat(nombre, ".txt");
	mapa = fopen(nombre, "rt");
	strcpy(nombre, "events");
	strcat(nombre, itoa(mapactual + 1, aux, 10));
	strcat(nombre, ".txt");
	events = fopen(nombre, "rt");
	if (events == NULL)
	{
		printf("Error al abrir el archivo 'events%d.txt'\n", mapactual + 1);
		exit(0);
	}
	tamMapa.X = 0;
	tamMapa.Y = 0;
	while (feof(mapa) == 0)
	{
		if (fgetc(mapa) == '\n')
		{
			tamMapa.Y++;
			tamMapa.X = 0;
			continue;
		}
		tamMapa.X++;
	}
	mapp.map = (char**)malloc(tamMapa.Y * sizeof(char*));
	for (k = 0; k <= tamMapa.Y; k++)
		mapp.map[k] = (char*)malloc(tamMapa.X * sizeof(char));
	rewind(mapa);

	tamMapa.X = 0;
	tamMapa.Y = 0;
	while (feof(mapa) == 0)
	{
		mapp.map[tamMapa.Y][tamMapa.X] = fgetc(mapa);	//Almacenamiento del mapa.
		if (mapp.map[tamMapa.Y][tamMapa.X] == '\n')
		{
			tamMapa.Y++;	//El vector "tamMapa" se utiliza para ir apuntando a todos los tiles del mapa.
			tamMapa.X = 0;
			continue;
		}
		tamMapa.X++;
	}
	fclose(mapa);
	//##Se añade \0 al final de cada línea para que no se solapen los saltos de línea (Tú déjalo como está)##//
	for (k = 0; k < tamMapa.Y; k++)
	{
		mapp.map[k][tamMapa.X - 1] = 0;
	}
	//##Lectura y almacenamiento de los archivos de eventos##//
	numevent = 0;
	auxnumTexto = 0;
	while (feof(events) == 0)
	{
		buffer = fgetc(events);
		if (buffer == '.')
		{
			auxnumTexto++;
			evento[numevent - 1].text = (char**)malloc(auxnumTexto * sizeof(char*));
			for (k = 0; k < auxnumTexto;k++)
				evento[numevent - 1].text[k] = (char*)malloc(30 * sizeof(char));
		}
		else if (buffer == '-')
		{
			auxnumTexto = 0;
			evento = (eventstruct*)realloc(evento, (numevent + 1) * sizeof(eventstruct));
			numevent++;
		}
		
	}
	rewind(events);
	for (k = 0; k < numevent; k++)
		evento[k].numTexto = 0;
	numevent = 0;
	while (feof(events) == 0)
	{
		if (fgetc(events) == '-')
		{
			fscanf(events, "%d %d\n", &evento[numevent].posEvento.Y, &evento[numevent].posEvento.X);
			mapp.map[evento[numevent].posEvento.Y][evento[numevent].posEvento.X] = '!';
			fscanf(events, "%[^\n]s", evento[numevent].nombre);
			fgetc(events);
			numevent++;
		}
		else
		{
			fscanf(events, "%[^\n]s", evento[numevent-1].text[evento[numevent-1].numTexto]);
			fgetc(events);
			evento[numevent-1].numTexto++;
			if (feof(events) != 0)
				break;
		}
	}
	fclose(events);
	while (feof(links) == 0) //Lectura del archivo de links
	{
		if (fgetc(links) == '\n')
			numlink++;
	}
	rewind(links);
	puertas = (link*)malloc(numlink * sizeof(link));
	k = 0;
	while (feof(links) == 0) //Lectura del archivo de links
	{
		fscanf(links, "%d %d %d\n", &puertas[k].map[0], &puertas[k].Y[0], &puertas[k].X[0]);
		fscanf(links, "%d %d %d\n", &puertas[k].map[1], &puertas[k].Y[1], &puertas[k].X[1]);

		if (mapactual == puertas[k].map[0])
		{
			mapp.map[puertas[k].Y[0]][puertas[k].X[0]] = 'E';
			k++;
		}
		if (mapactual == puertas[k].map[1])
		{
			mapp.map[puertas[k].Y[1]][puertas[k].X[1]] = 'E';
			k++;
		}
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