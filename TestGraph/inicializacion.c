#include "cabecera.h"

void inicializacion(STRUCTpos *VISION, STRUCTgraph *graph, STRUCTcontroles *controles, STRUCTpersonaje *personaje)
{
	FILE *FILEitems;
	int k = 0, numitems = 0;
	char buffer, cmdSize[30];

	controles->UP = 'w';
	controles->DOWN = 's';
	controles->LEFT = 'a';
	controles->RIGHT = 'd';
	controles->ACTION = 'e';
	controles->BACK = 'q';
	controles->SPECIAL = 'p';
	controles->MENU = 'm';
	VISION->X = 4;
	VISION->Y = 2;
	sprintf(cmdSize, "mode con: cols=36 lines=20");
	system(cmdSize);
	graph->PLAINS = '-';
	graph->WALL = '#';
	graph->EVENT = '!';
	graph->DOOR = 'E';
	graph->PJ = '*';
	FILEitems = fopen("data\\items.txt", "rt");
	if (FILEitems == NULL)
	{
		printf("Error al abrir el archivo 'items.txt'\n");
		exit(0);
	}
	while (feof(FILEitems) == 0)
	{
		if (fgetc(FILEitems) == '\n')
		{
			numitems++;
			continue;
		}
	}
	numitems = numitems / 2;
	items = (STRUCTitem*)malloc(numitems * sizeof(STRUCTitem));
	if (items == NULL)
		error(1);
	rewind(FILEitems);
	for (k = 0; k < numitems; k++)
	{
		buffer = fgetc(FILEitems);
		if (buffer == '+')
		{
			fscanf(FILEitems, "%[^\n]s", items[k].nombre);
			fscanf(FILEitems, "%d %d", &items[k].minDmg, &items[k].maxDmg);
			items[k].tipo = 0;
			fgetc(FILEitems);
		}
		else if (buffer == '-')
		{
			fscanf(FILEitems, "%[^\n]s", items[k].nombre);
			fscanf(FILEitems, "%d", &items[k].def);
			items[k].tipo = 1;
			fgetc(FILEitems);
		}
	}
	fclose(FILEitems);
	strcpy(personaje->nombre, "Personaje");
	personaje->HP = 30;
	personaje->INT = 10;
	personaje->MP = 10 + (personaje->INT / 10);
	personaje->HPLEFT = personaje->HP;
	personaje->MPLEFT = personaje->MP;
	personaje->LVL = 1;
	personaje->EXP = 0;
	personaje->STR = 10;
	personaje->ACC = 10;
	personaje->DEF = 10;
	personaje->weapEquip = 0;
	personaje->armorEquip = 1;
	personaje->minDmg = items[personaje->weapEquip].minDmg + (personaje->STR / 10);
	personaje->maxDmg = items[personaje->weapEquip].maxDmg + (personaje->STR / 10);
	personaje->inventario[0][0] = 0;
	personaje->inventario[1][0] = 1;
	personaje->inventario[0][1] = 1;
	personaje->inventario[1][1] = 1;
	personaje->inventario[2][0] = 2;
	personaje->inventario[3][0] = 3;
	personaje->inventario[2][1] = 1;
	personaje->inventario[3][1] = 1;
	return;
}