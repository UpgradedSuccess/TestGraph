#include "cabecera.h"

void inicializacion(short *numitems, STRUCTpos *VISION, STRUCTgraph *graph, STRUCTcontroles *controles, STRUCTpersonaje *personaje, STRUCTitem **items, short *mapactual)
{
	FILE *FILEitems;
	short k = 0;
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
			fscanf(FILEitems, "%hd %hd", &(*items)[k].minDmg, &(*items)[k].maxDmg);
			fscanf(FILEitems, "%hd", &(*items)[k].isRanged);
			(*items)[k].num = 0;
			(*items)[k].tipo = 0;
			fgetc(FILEitems);
		}
		else if (buffer == '-')
		{
			fscanf(FILEitems, "%[^\n]s", (*items)[k].nombre);
			fscanf(FILEitems, "%hd", &(*items)[k].def);
			(*items)[k].num = 0;
			(*items)[k].tipo = 1;
			fgetc(FILEitems);
		}
	}
	fclose(FILEitems);
	return;
}

void savegame(STRUCTcontroles controles, STRUCTpersonaje personaje, short mapactual)
{
	char nombre[20], nombresave[3][20];
	short k, numsave = 0, flecha = 1;
	FILE *FILEsave;

	system("cls");
	for (k = 0; k < 3; k++)
	{
		sprintf(nombre, "data\\save%hd.txt", k + 1);
		FILEsave = fopen(nombre, "rt");
		if (FILEsave == NULL)
			break;
		fscanf(FILEsave, "%[^\n]s", nombresave[k]);
		numsave++;
		fclose(FILEsave);
	}
	do
	{
		for (k = 0; k < numsave; k++)
		{
			system("cls");
			for (k = 1; k < 4; k++)
			{
				if (k == flecha)
					printf("->");
				if (k < numsave + 1)
					printf("  %s\n", nombresave[k - 1]);
				else
					printf("  -Nueva Partida-\n");
			}
			k = flecha;
			flecha = menuFlecha(3, flecha, controles);
			if (flecha == 0)
			{
				flecha = 1;
				sprintf(nombre, "data\\save%hd.txt", k);
				FILEsave = fopen(nombre, "wt");
				fprintf(FILEsave, "%s\n", personaje.nombre);
				fprintf(FILEsave, "%hd %hd\n", personaje.HP, personaje.HPLEFT);
				fprintf(FILEsave, "%hd %hd\n", personaje.MP, personaje.MPLEFT);
				fprintf(FILEsave, "%hd\n", personaje.LVL);
				fprintf(FILEsave, "%hd\n", personaje.EXP);
				fprintf(FILEsave, "%hd\n", personaje.STR);
				fprintf(FILEsave, "%hd\n", personaje.DEF);
				fprintf(FILEsave, "%hd\n", personaje.ACC);
				fprintf(FILEsave, "%hd\n", personaje.INT);
				fprintf(FILEsave, "%hd\n", personaje.weapEquip);
				fprintf(FILEsave, "%hd\n", personaje.armorEquip);
				fprintf(FILEsave, "%hd\n", personaje.invent);
				for (k = 0; k < personaje.invent; k++)
				{
					fprintf(FILEsave, "%s\n", personaje.inventario[k].nombre);
					fprintf(FILEsave, "%hd\n", personaje.inventario[k].tipo);
					fprintf(FILEsave, "%hd\n", personaje.inventario[k].num);
					if (personaje.inventario[k].tipo == 0)
					{
						fprintf(FILEsave, "%hd\n", personaje.inventario[k].minDmg);
						fprintf(FILEsave, "%hd\n", personaje.inventario[k].maxDmg);
						fprintf(FILEsave, "%hd\n", personaje.inventario[k].isRanged);
					}
					else if (personaje.inventario[k].tipo == 1)
						fprintf(FILEsave, "%hd\n", personaje.inventario[k].def);
				}
				fprintf(FILEsave, "%hd %hd\n", personaje.pos.X, personaje.pos.Y);
				fprintf(FILEsave, "%hd\n", mapactual);
				printf("\nPartida guardada.\n");
				getch();
				fclose(FILEsave);
				return;
			}
			else if (flecha == -1)
				return;
			else if (flecha == -2)
			{
				flecha = k;
				continue;
			}
		}
	} while (1);
	return;
}

short loadgame(STRUCTcontroles controles, STRUCTitem **items, STRUCTpersonaje *personaje, short *mapactual)
{
	short numsave = 0, k, flecha = 1;
	char nombre[20], nombresave[3][20];
	FILE *FILEsave;

	system("cls");
	for (k = 0; k < 3; k++)
	{
		sprintf(nombre, "data\\save%hd.txt", k + 1);
		FILEsave = fopen(nombre, "rt");
		if (FILEsave == NULL)
			break;
		fscanf(FILEsave, "%[^\n]s", nombresave[k]);
		numsave++;
		fclose(FILEsave);
	}
	if (numsave == 0)
	{
		printf("No hay partidas guardadas\n");
		getch();
		return 0;
	}
	do
	{
		for (k = 0; k < numsave; k++)
		{
			system("cls");
			printf("Seleccione partida guardada:\n\n");
			for (k = 1; k < numsave + 1; k++)
			{
				if (k == flecha)
					printf("->");
				printf("  %s\n", nombresave[k - 1]);
			}
			k = flecha;
			flecha = menuFlecha(numsave, flecha, controles);
			if (flecha == 0)
			{
				flecha = 1;
				sprintf(nombre, "data\\save%hd.txt", k);
				FILEsave = fopen(nombre, "rt");
				personaje->inventario = (STRUCTitem*)malloc(15 * sizeof(STRUCTitem));
				fscanf(FILEsave, "%[^\n]s", personaje->nombre);
				fscanf(FILEsave, "%hd %hd\n", &personaje->HP, &personaje->HPLEFT);
				fscanf(FILEsave, "%hd %hd\n", &personaje->MP, &personaje->MPLEFT);
				fscanf(FILEsave, "%hd\n", &personaje->LVL);
				fscanf(FILEsave, "%hd\n", &personaje->EXP);
				fscanf(FILEsave, "%hd\n", &personaje->STR);
				fscanf(FILEsave, "%hd\n", &personaje->DEF);
				fscanf(FILEsave, "%hd\n", &personaje->ACC);
				fscanf(FILEsave, "%hd\n", &personaje->INT);
				fscanf(FILEsave, "%hd\n", &personaje->weapEquip);
				fscanf(FILEsave, "%hd\n", &personaje->armorEquip);
				fscanf(FILEsave, "%hd\n", &personaje->invent);
				for (k = 0; k < personaje->invent; k++)
				{
					fscanf(FILEsave, "%[^\n]s\n", personaje->inventario[k].nombre);
					fscanf(FILEsave, "%hd\n", &personaje->inventario[k].tipo);
					fscanf(FILEsave, "%hd\n", &personaje->inventario[k].num);
					if (personaje->inventario[k].tipo == 0)
					{
						fscanf(FILEsave, "%hd\n", &personaje->inventario[k].minDmg);
						fscanf(FILEsave, "%hd\n", &personaje->inventario[k].maxDmg);
						fscanf(FILEsave, "%hd\n", &personaje->inventario[k].isRanged);
					}
					else if (personaje->inventario[k].tipo == 1)
						fscanf(FILEsave, "%hd\n", &personaje->inventario[k].def);
				}
				fscanf(FILEsave, "%hd %hd\n", &personaje->pos.X, &personaje->pos.Y);
				fscanf(FILEsave, "%hd\n", &(*mapactual));
				personaje->minDmg = (*items)[personaje->weapEquip].minDmg + (personaje->STR / 10);
				personaje->maxDmg = (*items)[personaje->weapEquip].maxDmg + (personaje->STR / 10);
				return 1;
			}
			else if (flecha == -1)
				return 0;
			else if (flecha == -2)
			{
				flecha = k;
				continue;
			}
		}
	} while (1);
}

void intromenu(STRUCTitem **items, STRUCTcontroles controles, STRUCTpersonaje *personaje, short *mapactual)
{
	short flecha = 1, sel;

	do
	{
		system("cls");
		printf("     --Bienvenido a TestGraph!--\n\n");
		if (flecha == 1)
			printf("->");
		printf("  Nuevo juego\n");
		if (flecha == 2)
			printf("->");
		printf("  Cargar juego\n");
		if (flecha == 3)
			printf("->");
		printf("  Salir\n");
		sel = flecha;
		flecha = menuFlecha(3, flecha, controles);
		if (flecha == 0)
		{
			flecha = 1;
			switch (sel)
			{
			case 1:
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
				personaje->invent = 3;
				personaje->minDmg = (*items)[personaje->weapEquip].minDmg + (personaje->STR / 10);
				personaje->maxDmg = (*items)[personaje->weapEquip].maxDmg + (personaje->STR / 10);
				personaje->inventario = (STRUCTitem*)malloc(15 * sizeof(STRUCTitem));
				personaje->inventario[0] = (*items)[0];
				personaje->inventario[1] = (*items)[1];
				personaje->inventario[2] = (*items)[4];
				personaje->inventario[0].num = 1;
				personaje->inventario[1].num = 1;
				personaje->inventario[2].num = 1;
				personaje->pos.X = 3;
				personaje->pos.Y = 3;
				return;
			case 2:
				if ((loadgame(controles, items, personaje, mapactual)) == 1)
					return;
				else
					break;
			case 3:
				exit(0);
			}
		}
		else if (flecha == -1)
			flecha = sel;
		else if (flecha == -2)
			flecha = sel;
	} while (1);

}