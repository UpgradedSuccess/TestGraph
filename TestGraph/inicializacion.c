#include "cabecera.h"

void inicializacion(int *numitems, STRUCTpos *VISION, STRUCTgraph *graph, STRUCTcontroles *controles, STRUCTpersonaje *personaje, STRUCTitem **items, int *mapactual)
{
	FILE *FILEitems, *FILEsave;
	int k = 0;
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
		buffer = fgetc(FILEitems);
		if (buffer == '+' || buffer == '-')
		{
			(*numitems)++;
			continue;
		}
	}
	(*items) = (STRUCTitem*)malloc((*numitems) * sizeof(STRUCTitem));
	if ((*items) == NULL)
		error(1);
	rewind(FILEitems);
	for (k = 0; k < (*numitems); k++)
	{
		buffer = fgetc(FILEitems);
		if (buffer == '+')
		{
			fscanf(FILEitems, "%[^\n]s", (*items)[k].nombre);
			fscanf(FILEitems, "%d %d", &(*items)[k].minDmg, &(*items)[k].maxDmg);
			fscanf(FILEitems, "%d", &(*items)[k].isRanged);
			(*items)[k].num = 0;
			(*items)[k].tipo = 0;
			fgetc(FILEitems);
		}
		else if (buffer == '-')
		{
			fscanf(FILEitems, "%[^\n]s", (*items)[k].nombre);
			fscanf(FILEitems, "%d", &(*items)[k].def);
			(*items)[k].num = 0;
			(*items)[k].tipo = 1;
			fgetc(FILEitems);
		}
	}
	fclose(FILEitems);
	if ((FILEsave = fopen("data\\save.txt", "rt")) == NULL)
	{
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
		personaje->invent = 2;
		personaje->minDmg = (*items)[personaje->weapEquip].minDmg + (personaje->STR / 10);
		personaje->maxDmg = (*items)[personaje->weapEquip].maxDmg + (personaje->STR / 10);
		personaje->inventario = (STRUCTitem*)malloc(15 * sizeof(STRUCTitem));
		personaje->inventario[0] = (*items)[0];
		personaje->inventario[1] = (*items)[1];
		personaje->inventario[0].num = 1;
		personaje->inventario[1].num = 1;
		personaje->pos.X = 3;
		personaje->pos.Y = 3;
	}
	else
	{
		personaje->inventario = (STRUCTitem*)malloc(15 * sizeof(STRUCTitem));
		fscanf(FILEsave, "%[^\n]s", personaje->nombre);
		fscanf(FILEsave, "%d %d\n", &personaje->HP, &personaje->HPLEFT);
		fscanf(FILEsave, "%d %d\n", &personaje->MP, &personaje->MPLEFT);
		fscanf(FILEsave, "%d\n", &personaje->LVL);
		fscanf(FILEsave, "%d\n", &personaje->EXP);
		fscanf(FILEsave, "%d\n", &personaje->STR);
		fscanf(FILEsave, "%d\n", &personaje->DEF);
		fscanf(FILEsave, "%d\n", &personaje->ACC);
		fscanf(FILEsave, "%d\n", &personaje->INT);
		fscanf(FILEsave, "%d\n", &personaje->weapEquip);
		fscanf(FILEsave, "%d\n", &personaje->armorEquip);
		fscanf(FILEsave, "%d\n", &personaje->invent);
		for (k = 0; k < personaje->invent; k++)
		{
			fscanf(FILEsave, "%[^\n]s\n", personaje->inventario[k].nombre);
			fscanf(FILEsave, "%d\n", &personaje->inventario[k].tipo);
			fscanf(FILEsave, "%d\n", &personaje->inventario[k].num);
			if (personaje->inventario[k].tipo == 0)
			{
				fscanf(FILEsave, "%d\n", &personaje->inventario[k].minDmg);
				fscanf(FILEsave, "%d\n", &personaje->inventario[k].maxDmg);
				fscanf(FILEsave, "%d\n", &personaje->inventario[k].isRanged);
			}
			else if (personaje->inventario[k].tipo == 1)
				fscanf(FILEsave, "%d\n", &personaje->inventario[k].def);
		}
		fscanf(FILEsave, "%d %d\n", &personaje->pos.X, &personaje->pos.Y);
		fscanf(FILEsave, "%d\n", &(*mapactual));
		personaje->minDmg = (*items)[personaje->weapEquip].minDmg + (personaje->STR / 10);
		personaje->maxDmg = (*items)[personaje->weapEquip].maxDmg + (personaje->STR / 10);
	}
	return;
}

void savegame(STRUCTpersonaje personaje, int mapactual)
{
	int k;
	FILE *FILEsave;

	system("cls");
	FILEsave = fopen("data\\save.txt", "wt");
	if (FILEsave == NULL)
	{
		printf("\nError al guardar.\n");
		return;
	}
	fprintf(FILEsave, "%s\n", personaje.nombre);
	fprintf(FILEsave, "%d %d\n", personaje.HP, personaje.HPLEFT);
	fprintf(FILEsave, "%d %d\n", personaje.MP, personaje.MPLEFT);
	fprintf(FILEsave, "%d\n", personaje.LVL);
	fprintf(FILEsave, "%d\n", personaje.EXP);
	fprintf(FILEsave, "%d\n", personaje.STR);
	fprintf(FILEsave, "%d\n", personaje.DEF);
	fprintf(FILEsave, "%d\n", personaje.ACC);
	fprintf(FILEsave, "%d\n", personaje.INT);
	fprintf(FILEsave, "%d\n", personaje.weapEquip);
	fprintf(FILEsave, "%d\n", personaje.armorEquip);
	fprintf(FILEsave, "%d\n", personaje.invent);
	for (k = 0; k < personaje.invent; k++)
	{
		fprintf(FILEsave, "%s\n", personaje.inventario[k].nombre);
		fprintf(FILEsave, "%d\n", personaje.inventario[k].tipo);
		fprintf(FILEsave, "%d\n", personaje.inventario[k].num);
		if (personaje.inventario[k].tipo == 0)
		{
			fprintf(FILEsave, "%d\n", personaje.inventario[k].minDmg);
			fprintf(FILEsave, "%d\n", personaje.inventario[k].maxDmg);
			fprintf(FILEsave, "%d\n", personaje.inventario[k].isRanged);
		}
		else if (personaje.inventario[k].tipo == 1)
			fprintf(FILEsave, "%d\n", personaje.inventario[k].def);
	}
	fprintf(FILEsave, "%d %d\n", personaje.pos.X, personaje.pos.Y);
	fprintf(FILEsave, "%d\n", mapactual);
	printf("Partida guardada.\n");
	getch();
	fclose(FILEsave);
	return;
}