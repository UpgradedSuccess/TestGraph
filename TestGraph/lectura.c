#include "cabecera.h"
#include <string.h>
#include <stdlib.h>

char **map;
STRUCTpos tamMapa;
STRUCTeventos *evento;
STRUCTlink *puertas;
int numevento, mapactual, numlink;

void lectura()
{
	int k, auxnumTexto;
	char nombre[12], aux[15], buffer;
	FILE *FILEmapa, *FILEeventos, *FILElinks;

	FILElinks = fopen("links.txt", "rt");
	strcpy(nombre, "mapa");
	strcat(nombre, itoa(mapactual + 1, aux, 10));
	strcat(nombre, ".txt");
	FILEmapa = fopen(nombre, "rt");
	strcpy(nombre, "events");
	strcat(nombre, itoa(mapactual + 1, aux, 10));
	strcat(nombre, ".txt");
	FILEeventos = fopen(nombre, "rt");
	if (FILEeventos == NULL)
	{
		printf("Error al abrir el archivo 'FILEeventos%d.txt'\n", mapactual + 1);
		exit(0);
	}
	tamMapa.X = 0;
	tamMapa.Y = 0;
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
	while (feof(FILEmapa) == 0)
	{
		map[tamMapa.Y][tamMapa.X] = fgetc(FILEmapa);	//Almacenamiento del mapa.
		if (map[tamMapa.Y][tamMapa.X] == '\n')
		{
			tamMapa.Y++;	//El vector "tamMapa" se utiliza para ir apuntando a todos los tiles del mapa.
			tamMapa.X = 0;
			continue;
		}
		tamMapa.X++;
	}
	fclose(FILEmapa);
	//##Se añade \0 al final de cada línea para que no se solapen los saltos de línea (Tú déjalo como está)##//
	for (k = 0; k < tamMapa.Y; k++)
	{
		map[k][tamMapa.X - 1] = 0;
	}
	//##Lectura y almacenamiento de los archivos de eventos##//
	numevento = 0;
	auxnumTexto = 0;
	while (feof(FILEeventos) == 0)
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
	while (feof(FILElinks) == 0) //Lectura del archivo de links
	{
		if (fgetc(FILElinks) == '\n')
			numlink++;
	}
	rewind(FILElinks);
	puertas = (STRUCTlink*)malloc(numlink * sizeof(STRUCTlink));
	k = 0;
	while (feof(FILElinks) == 0) //Lectura del archivo de links
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

void error(int err)
{
	switch (err)
		case 1:
			printf("Error de memoria.\n");
			exit(0);
}