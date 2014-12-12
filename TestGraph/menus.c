#include "cabecera.h"

void adminmenu(STRUCTpos *VISION, STRUCTgraph *graph, STRUCTcontroles *controles, STRUCTpersonaje *personaje)
{
	short flecha = 1, sel, update = 1;

	do
	{
		if (update == 1)
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
		}
		update = 1;
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
				printf("\nIntroduzca tecla para BACK: ");
				controles->BACK = getch();
				printf("\nIntroduzca tecla para MENU: ");
				controles->MENU = getch();
				break;
			case 2:
				system("cls");
				printf("Rango actual:\nX: %hd\nY: %hd\n\n"
					"- Sólo se aceptan valores mayores que 0 y menores que X=6 e Y=4.\n- X DEBE ser mayor que Y.\n- Se recomienda que X sea Y + 2.\n\n", VISION->X, VISION->Y);
				do
				{
					printf("Introduzca el rango de visión en X: ");
					scanf("%hd", &VISION->X);
					fflush(stdin);
					printf("\nIntroduzca el rango de visión en Y: ");
					scanf("%hd", &VISION->Y);
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
		{
			update = 0;
			flecha = sel;
			continue;
		}
	} while (1);
}

void pjmenu(STRUCTcontroles controles, STRUCTpersonaje *personaje, STRUCTitem *items, short mapactual, STRUCTgraph graph, STRUCTpos VISION)
{
	short flecha = 1, k, i = 1, aux = 0, sel, update = 1;
	char salir;

	do
	{
		if (update == 1)
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
			if (flecha == 6)
				printf("->");
			printf("  Menú Principal\n");
			if (flecha == 7)
				printf("->");
			printf("  Salir\n");
		}
		update = 1;
		sel = flecha;
		flecha = menuFlecha(7, flecha, controles);
		if (flecha == 0)
		{
			switch (sel)
			{
			case 1:
				system("cls");
				printf("Nombre: %s\n\n"
					"HP: %hd / %hd\n"
					"MP: %hd / %hd\n"
					"Nivel: %hd\n"
					"Experiencia: %hd / %hd\n\n"
					"Fuerza: %hd\n"
					"Defensa: %hd + %hd\n"
					"Puntería: %hd\n"
					"Inteligencia: %hd\n\n"
					"Daño efectivo: %hd - %hd\n"
					, personaje->nombre, personaje->HPLEFT, personaje->HP, personaje->MPLEFT, personaje->MP, personaje->LVL, personaje->EXP, personaje->LVL * 100, personaje->STR, personaje->DEF, personaje->inventario[personaje->armorEquip].def, personaje->ACC, personaje->INT, personaje->minDmg, personaje->maxDmg);
				getch();
				break;
			case 2:
				system("cls");
				printf("Arma: %s (%hd - %hd daño)\n\n"
					"Armadura: %s (+%hd defensa)\n", personaje->inventario[personaje->weapEquip].nombre, personaje->inventario[personaje->weapEquip].minDmg, personaje->inventario[personaje->weapEquip].maxDmg, personaje->inventario[personaje->armorEquip].nombre, personaje->inventario[personaje->armorEquip].def);
				getch();
				break;
			case 3:
				do
				{
					if (update == 1)
					{
						system("cls");
						for (k = 1; k < personaje->invent + 1; k++)
						{
							if (k == i)
								printf("->");
							if (k == personaje->armorEquip + 1 || k == personaje->weapEquip + 1)
								printf("  -E-");
							printf("  %s  %hdx\n", personaje->inventario[k - 1].nombre, personaje->inventario[k - 1].num);
						}
					}
					update = 1;
					k = i;
					i = menuFlecha(personaje->invent, i, controles);
					if (i == 0)
					{
						i = k;
						system("cls");
						printf("Nombre: %s\n", personaje->inventario[i - 1].nombre);
						if (personaje->inventario[i - 1].tipo == 0)
							printf("Daño: %hd - %hd\n", personaje->inventario[i - 1].minDmg, personaje->inventario[i - 1].maxDmg);
						else if (personaje->inventario[i - 1].tipo == 1)
							printf("Defensa: %hd\n", personaje->inventario[i - 1].def);
						printf("Cantidad : %hd\n\n", personaje->inventario[i - 1].num);
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
						update = 0;
						continue;
					}
				} while (1);
				i = 1;
				break;
			case 5:
				savegame(controles, *personaje, mapactual, graph, VISION);
				break;
			case 6:
				system("cls");
				printf("¿Está seguro de que desea salir?\nAsegúrese de haber guardado antes.\n\n(S/N): ");
				salir = getch();
				if (salir == 's')
					main();
				else
					break;
			case 7:
				system("cls");
				printf("¿Está seguro de que desea salir?\nAsegúrese de haber guardado antes.\n\n(S/N): ");
				salir = getch();
				if (salir == 's')
					exit(0);
				else
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
			update = 0;
			continue;
		}
	} while (1);
}

short menuFlecha(short rangeMax, short flecha, STRUCTcontroles controles)
{
	char sel = 0;

	fflush(stdin);
	sel = getch();
	if (sel == controles.UP)
	{
		if (flecha == 1)
		{
			flecha = rangeMax;
			return flecha;
		}
		flecha--;
	}
	else if (sel == controles.DOWN)
	{
		if (flecha == rangeMax)
		{
			flecha = 1;
			return flecha;
		}
		flecha++;
	}
	else if (sel == controles.ACTION)
		return 0;
	else if (sel == controles.BACK)
		return -1;
	else
		return -2;
	return flecha;
}