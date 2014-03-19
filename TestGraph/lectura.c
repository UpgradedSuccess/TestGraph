#include "cabecera.h"

void lectura(short *numevento, short *mapactual, short *numlink, STRUCTpos *tamMapa, char ***map, STRUCTeventos **evento, STRUCTlink **puertas)
{
	short k, auxnumTexto = 0;
	char nombre[20], buffer;
	FILE *FILEmapa, *FILEeventos, *FILElinks;

	sprintf(nombre, "data\\mapa%hd.txt", (*mapactual) + 1);
	FILEmapa = fopen(nombre, "rt");
	if (FILEmapa == NULL)
	{
		printf("Error al abrir el archivo 'mapa%hd.txt'\n", (*mapactual) + 1);
		exit(0);
	}
	while (feof(FILEmapa) == 0)
	{
		if (fgetc(FILEmapa) == '\n')
		{
			tamMapa->Y++;
			tamMapa->X = 0;
			continue;
		}
		tamMapa->X++;
	}
	(*map) = (char**)malloc(tamMapa->Y * sizeof(char*));
	for (k = 0; k <= tamMapa->Y; k++)
		(*map)[k] = (char*)malloc(tamMapa->X * sizeof(char));
	rewind(FILEmapa);
	tamMapa->X = 0;
	tamMapa->Y = 0;
	//##Lecura del mapa##//
	while (feof(FILEmapa) == 0)
	{
		(*map)[tamMapa->Y][tamMapa->X] = fgetc(FILEmapa);
		if ((*map)[tamMapa->Y][tamMapa->X] == '\n')
		{
			tamMapa->Y++;
			tamMapa->X = 0;
			continue;
		}
		tamMapa->X++;
	}
	fclose(FILEmapa);
	//##Lectura de eventos##//
	sprintf(nombre, "data\\events%hd.txt", (*mapactual) + 1);
	FILEeventos = fopen(nombre, "rt");
	if (FILEeventos == NULL)
	{
		printf("Error al abrir el archivo 'events%hd.txt'\n", (*mapactual) + 1);
		exit(0);
	}
	(*evento) = (STRUCTeventos*)malloc(1 * sizeof(STRUCTeventos));
	*numevento = 0;
	while (feof(FILEeventos) == 0) //Conteo y redimensión de las frases por evento
	{
		buffer = fgetc(FILEeventos);
		if (buffer == '.')
		{
			auxnumTexto++;
			(*evento)[(*numevento)- 1].text = (char**)malloc(auxnumTexto * sizeof(char*));
			for (k = 0; k < auxnumTexto;k++)
				(*evento)[(*numevento)- 1].text[k] = (char*)malloc(30 * sizeof(char));
		}
		else if (buffer == '-')
		{
			auxnumTexto = 0;
			(*evento) = (STRUCTeventos*)realloc((*evento), ((*numevento)+ 1) * sizeof(STRUCTeventos));
			(*numevento)++;
		}
	}
	rewind(FILEeventos);
	for (k = 0; k < (*numevento); k++)
		(*evento)[k].numTexto = 0;
	(*numevento)= 0;
	while (feof(FILEeventos) == 0)
	{
		if (fgetc(FILEeventos) == '-')
		{
			fscanf(FILEeventos, "%hd %hd\n", &(*evento)[(*numevento)].posEvento.Y, &(*evento)[(*numevento)].posEvento.X);
			(*map)[(*evento)[(*numevento)].posEvento.Y][(*evento)[(*numevento)].posEvento.X] = '!';
			fscanf(FILEeventos, "%[^\n]s", (*evento)[(*numevento)].nombre);
			fgetc(FILEeventos);
			(*numevento)++;
		}
		else
		{
			fscanf(FILEeventos, "%[^\n]s", (*evento)[(*numevento)-1].text[(*evento)[(*numevento)-1].numTexto]);
			fgetc(FILEeventos);
			(*evento)[(*numevento)-1].numTexto++;
			if (feof(FILEeventos) != 0)
				break;
		}
	}
	fclose(FILEeventos);
	//##Lectura de links#//
	FILElinks = fopen("data\\links.txt", "rt");
	if (FILElinks == NULL)
	{
		printf("Error al abrir archivo de links.\n"
			"Se continuará, pero no habrá puertas");
		getch();
		return;
	}
	(*numlink) = 0;
	while (feof(FILElinks) == 0) //Conteo y redimensión de links
	{
		if (fgetc(FILElinks) == '\n')
			(*numlink)++;
	}
	rewind(FILElinks);
	(*puertas) = (STRUCTlink*)malloc((*numlink) * sizeof(STRUCTlink));
	k = 0;
	while (feof(FILElinks) == 0) //Lectura de links
	{
		fscanf(FILElinks, "%hd %hd %hd\n", &(*puertas)[k].map[0], &(*puertas)[k].Y[0], &(*puertas)[k].X[0]);
		fscanf(FILElinks, "%hd %hd %hd\n", &(*puertas)[k].map[1], &(*puertas)[k].Y[1], &(*puertas)[k].X[1]);

		if ((*mapactual) == (*puertas)[k].map[0])
		{
			(*map)[(*puertas)[k].Y[0]][(*puertas)[k].X[0]] = 'E';
			k++;
		}
		else if ((*mapactual) == (*puertas)[k].map[1])
		{
			(*map)[(*puertas)[k].Y[1]][(*puertas)[k].X[1]] = 'E';
			k++;
		}
	}
	fclose(FILElinks);
	return;
}