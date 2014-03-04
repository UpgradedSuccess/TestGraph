#include "cabecera.h"
#include <string.h>
#include <stdlib.h>

char **map;
STRUCTpos tamMapa = { 0 };
STRUCTeventos *evento;
STRUCTlink *puertas;
int numevento = 0, mapactual, numlink;

void lectura()
{
	int k, auxnumTexto = 0;
	char nombre[20], aux[3], buffer;
	FILE *FILEmapa, *FILEeventos, *FILElinks;

	FILElinks = fopen("data\\links.txt", "rt");
	strcpy(nombre, "data\\mapa");
	strcat(nombre, itoa(mapactual + 1, aux, 10));
	strcat(nombre, ".txt");
	FILEmapa = fopen(nombre, "rt");
	if (FILEmapa == NULL)
	{
		printf("Error al abrir el archivo 'mapa%d.txt'\n", mapactual + 1);
		exit(0);
	}
	strcpy(nombre, "data\\events");
	strcat(nombre, itoa(mapactual + 1, aux, 10));
	strcat(nombre, ".txt");
	FILEeventos = fopen(nombre, "rt");
	if (FILEeventos == NULL)
	{
		printf("Error al abrir el archivo 'eventos%d.txt'\n", mapactual + 1);
		exit(0);
	}
	while (feof(FILEmapa) == 0)
	{
		if (fgetc(FILEmapa) == '\n')
		{
			tamMapa.Y++;
			tamMapa.X = 0;
			continue;
		}
		tamMapa.X++;
	}
	map = (char**)malloc(tamMapa.Y * sizeof(char*));
	for (k = 0; k <= tamMapa.Y; k++)
		map[k] = (char*)malloc(tamMapa.X * sizeof(char));
	rewind(FILEmapa);
	tamMapa.X = 0;
	tamMapa.Y = 0;
	//##Lecura del mapa##//
	while (feof(FILEmapa) == 0)
	{
		map[tamMapa.Y][tamMapa.X] = fgetc(FILEmapa);
		if (map[tamMapa.Y][tamMapa.X] == '\n')
		{
			tamMapa.Y++;
			tamMapa.X = 0;
			continue;
		}
		tamMapa.X++;
	}
	fclose(FILEmapa);
	//##Lectura de eventos##//
	while (feof(FILEeventos) == 0) //Conteo y redimensión de las frases por evento
	{
		buffer = fgetc(FILEeventos);
		if (buffer == '.')
		{
			auxnumTexto++;
			evento[numevento- 1].text = (char**)malloc(auxnumTexto * sizeof(char*));
			for (k = 0; k < auxnumTexto;k++)
				evento[numevento- 1].text[k] = (char*)malloc(30 * sizeof(char));
		}
		else if (buffer == '-')
		{
			auxnumTexto = 0;
			evento = (STRUCTeventos*)realloc(evento, (numevento+ 1) * sizeof(STRUCTeventos));
			numevento++;
		}
		
	}
	rewind(FILEeventos);
	for (k = 0; k < numevento; k++)
		evento[k].numTexto = 0;
	numevento= 0;
	while (feof(FILEeventos) == 0)
	{
		if (fgetc(FILEeventos) == '-')
		{
			fscanf(FILEeventos, "%d %d\n", &evento[numevento].posEvento.Y, &evento[numevento].posEvento.X);
			map[evento[numevento].posEvento.Y][evento[numevento].posEvento.X] = '!';
			fscanf(FILEeventos, "%[^\n]s", evento[numevento].nombre);
			fgetc(FILEeventos);
			numevento++;
		}
		else
		{
			fscanf(FILEeventos, "%[^\n]s", evento[numevento-1].text[evento[numevento-1].numTexto]);
			fgetc(FILEeventos);
			evento[numevento-1].numTexto++;
			if (feof(FILEeventos) != 0)
				break;
		}
	}
	fclose(FILEeventos);
	//##Lectura de links#//
	while (feof(FILElinks) == 0) //Conteo y redimensión de links
	{
		if (fgetc(FILElinks) == '\n')
			numlink++;
	}
	rewind(FILElinks);
	puertas = (STRUCTlink*)malloc(numlink * sizeof(STRUCTlink));
	k = 0;
	while (feof(FILElinks) == 0) //Lectura de links
	{
		fscanf(FILElinks, "%d %d %d\n", &puertas[k].map[0], &puertas[k].Y[0], &puertas[k].X[0]);
		fscanf(FILElinks, "%d %d %d\n", &puertas[k].map[1], &puertas[k].Y[1], &puertas[k].X[1]);

		if (mapactual == puertas[k].map[0])
		{
			map[puertas[k].Y[0]][puertas[k].X[0]] = 'E';
			k++;
		}
		else if (mapactual == puertas[k].map[1])
		{
			map[puertas[k].Y[1]][puertas[k].X[1]] = 'E';
			k++;
		}
	}
	fclose(FILElinks);
	return;
}