#include "cabecera.h"

void adminmenu(STRUCTpos *VISION, STRUCTgraph *graph, STRUCTcontroles *controles, STRUCTpersonaje *personaje)
{
	int flecha = 1, sel;

	do
	{
		system("cls");
		printf("\t-Menú de administrador-\n\n");
		if (flecha == 1)
			printf("->");
		printf("  Cambiar controles\n");
		if (flecha == 2)
			printf("->");
		printf("  Cambiar visión\n");
		if (flecha == 3)
			printf("->");
		printf("  Cambiar gráficos de terreno\n");
		if (flecha == 4)
			printf("->");
		printf("  Cambiar nombre del jugador\n");
		sel = flecha;
		flecha = menuFlecha(4, flecha, *controles);
		if (flecha == 0)
		{
			flecha = 1;
			switch (sel)
			{
			case 1:
				system("cls");
				printf("Introduzca tecla para UP: ");
				controles->UP = getch();
				printf("\nIntroduzca tecla para DOWN: ");
				controles->DOWN = getch();
				printf("\nIntroduzca tecla para LEFT: ");
				controles->LEFT = getch();
				printf("\nIntroduzca tecla para RIGHT: ");
				controles->RIGHT = getch();
				printf("\nIntroduzca tecla para ACTION: ");
				controles->ACTION = getch();
				printf("\nIntroduzca tecla para MENU: ");
				controles->MENU = getch();
				break;
			case 2:
				system("cls");
				printf("Rango actual:\nX: %d\nY: %d\n\n"
					"- Sólo se aceptan valores mayores que 0 y menores que X=6 e Y=4.\n- X DEBE ser mayor que Y.\n- Se recomienda que X sea Y + 2.\n\n", VISION->X, VISION->Y);
				do
				{
					printf("Introduzca el rango de visión en X: ");
					scanf("%d", &VISION->X);
					fflush(stdin);
					printf("\nIntroduzca el rango de visión en Y: ");
					scanf("%d", &VISION->Y);
					fflush(stdin);
					if (VISION->X <= 0 || VISION->Y <= 0 || VISION->Y > VISION->X || VISION->X > 6 || VISION->Y > 4)
					{
						printf("\nAlguno de los valores introducidos no es correcto.\n\n\n");
						getch();
						continue;
					}
					else
						return;
				} while (1);
			case 3:
				system("cls");
				printf("Caracteres actuales:\nLlanos: '%c'\nMuros: '%c'\nEventos: '%c'\nPuertas: '%c'\nPersonaje : '%c'\n\n"
					"Introduzca el nuevo carácter para Llanos: ", graph->PLAINS, graph->WALL, graph->EVENT, graph->DOOR, graph->PJ);
				scanf("%c", &graph->PLAINS);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para Muros: ");
				scanf("%c", &graph->WALL);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para Eventos: ");
				scanf("%c", &graph->EVENT);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para Puertas: ");
				scanf("%c", &graph->DOOR);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para el personaje: ");
				scanf("%c", &graph->PJ);
				fflush(stdin);
				break;
			case 4:
				system("cls");
				printf("Nombre actual del jugador: %s\n\n"
					"Introduzca nuevo nombre para el jugador (15 caracteres maximo): ", personaje->nombre);
				scanf("%[^\n]s", personaje->nombre);
				break;
			}
		}
		else if (flecha == -1)
			return;
		else if (flecha == -2)
			flecha = sel;
	} while (1);
}

void pjmenu(STRUCTcontroles controles, STRUCTpersonaje *personaje, STRUCTitem *items, int mapactual)
{
	int flecha = 1, k, i = 1, aux = 0, sel;

	do
	{
		system("cls");
		printf("\t-Menú-\n");
		if (flecha == 1)
			printf("->");
		printf("  Estado\n");
		if (flecha == 2)
			printf("->");
		printf("  Equipo\n");
		if (flecha == 3)
			printf("->");
		printf("  Inventario\n");
		if (flecha == 4)
			printf("->");
		printf("  Habilidades\n");
		if (flecha == 5)
			printf("->");
		printf("  Guardar partida\n");
		sel = flecha;
		flecha = menuFlecha(5, flecha, controles);
		if (flecha == 0)
		{
			switch (sel)
			{
			case 1:
				system("cls");
				printf("Nombre: %s\n\n"
					"HP: %d / %d\n"
					"MP: %d / %d\n"
					"Nivel: %d\n"
					"Experiencia: %d / %d\n\n"
					"Fuerza: %d\n"
					"Defensa: %d + %d\n"
					"Puntería: %d\n"
					"Inteligencia: %d\n\n"
					"Daño efectivo: %d - %d\n"
					, personaje->nombre, personaje->HPLEFT, personaje->HP, personaje->MPLEFT, personaje->MP, personaje->LVL, personaje->EXP, personaje->LVL * 100, personaje->STR, personaje->DEF, personaje->inventario[personaje->armorEquip].def, personaje->ACC, personaje->INT, personaje->minDmg, personaje->maxDmg);
				getch();
				break;
			case 2:
				system("cls");
				printf("Arma: %s (%d - %d daño)\n\n"
					"Armadura: %s (+%d defensa)\n", personaje->inventario[personaje->weapEquip].nombre, personaje->inventario[personaje->weapEquip].minDmg, personaje->inventario[personaje->weapEquip].maxDmg, personaje->inventario[personaje->armorEquip].nombre, personaje->inventario[personaje->armorEquip].def);
				getch();
				break;
			case 3:
				do
				{
					system("cls");
					for (k = 1; k < personaje->invent + 1; k++)
					{
						if (k == i)
							printf("->");
						if (k == personaje->armorEquip + 1 || k == personaje->weapEquip + 1)
							printf("  -E-");
						printf("  %s  %dx\n", personaje->inventario[k - 1].nombre, personaje->inventario[k - 1].num);
					}
					k = i;
					i = menuFlecha(personaje->invent, i, controles);
					if (i == 0)
					{
						i = k;
						system("cls");
						printf("Nombre: %s\n", personaje->inventario[i - 1].nombre);
						if (personaje->inventario[i - 1].tipo == 0)
							printf("Daño: %d - %d\n", personaje->inventario[i - 1].minDmg, personaje->inventario[i - 1].maxDmg);
						else if (personaje->inventario[i - 1].tipo == 1)
							printf("Defensa: %d\n", personaje->inventario[i - 1].def);
						printf("Cantidad : %d\n\n", personaje->inventario[i - 1].num);
						printf("¿Equipar? (s/n)");
						if (getch() == 's')
						{
							if (personaje->inventario[i - 1].tipo == 0)
								personaje->weapEquip = i - 1;
							else if (personaje->inventario[i - 1].tipo == 1)
								personaje->armorEquip = i - 1;
							personaje->minDmg = personaje->inventario[personaje->weapEquip].minDmg + (personaje->STR / 10);
							personaje->maxDmg = personaje->inventario[personaje->weapEquip].maxDmg + (personaje->STR / 10);
						}
					}
					else if (i == -1)
						break;
					else if (i == -2)
					{
						i = k;
						continue;
					}
				} while (1);
				i = 1;
				break;
			case 5:
				savegame(*personaje, mapactual);
				break;
			default:
				break;
			}
			flecha = 1;
		}
		else if (flecha == -1)
			return;
		else if (flecha == -2)
		{
			flecha = sel;
			continue;
		}
	} while (1);
}

int menuFlecha(int rangeMax, int flecha, STRUCTcontroles controles)
{
	char sel1 = 0;

	fflush(stdin);
	sel1 = getch();
	if (sel1 == controles.UP)
	{
		if (flecha == 1)
		{
			flecha = rangeMax;
			return flecha;
		}
		flecha--;
	}
	else if (sel1 == controles.DOWN)
	{
		if (flecha == rangeMax)
		{
			flecha = 1;
			return flecha;
		}
		flecha++;
	}
	else if (sel1 == controles.ACTION)
		return 0;
	else if (sel1 == controles.BACK)
		return -1;
	else
		return -2;
	return flecha;
}