#include "cabecera.h"

void adminmenu()
{
	int k = 1;
	char sel;

	do
	{
		system("cls");
		printf("\t-Menú de administrador-\n\n");
		if (k == 1)
			printf("->");
		printf("  Cambiar controles\n");
		if (k == 2)
			printf("->");
		printf("  Cambiar visión\n");
		if (k == 3)
			printf("->");
		printf("  Cambiar inicio de jugador\n");
		if (k == 4)
			printf("->");
		printf("  Cambiar gráficos de terreno\n");
		if (k == 5)
			printf("->");
		printf("  Cambiar nombre del jugador\n");
		if (k == 6)
			printf("->");
		printf("  Salir\n");
		sel = getch();
		if (sel == controles.UP)
		{
			if (k == 1)
			{
				k = 6;
				continue;
			}
			k--;
		}
		if (sel == controles.DOWN)
		{
			if (k == 6)
			{
				k = 1;
				continue;
			}
			k++;
		}
		if (sel == controles.ACTION)
		{
			switch (k)
			{
			case 1:
				system("cls");
				printf("Introduzca tecla para UP: ");
				controles.UP = getch();
				printf("\nIntroduzca tecla para DOWN: ");
				controles.DOWN = getch();
				printf("\nIntroduzca tecla para LEFT: ");
				controles.LEFT = getch();
				printf("\nIntroduzca tecla para RIGHT: ");
				controles.RIGHT = getch();
				printf("\nIntroduzca tecla para ACTION: ");
				controles.ACTION = getch();
				printf("\nIntroduzca tecla para MENU: ");
				controles.MENU = getch();
				break;
			case 2:
				system("cls");
				printf("Rango actual:\nX: %d\nY: %d\n\n"
					"- Sólo se aceptan valores mayores que 0 y menores que X=6 e Y=4.\n- X DEBE ser mayor que Y.\n- Se recomienda que X sea Y + 2.\n\n", VISION.X, VISION.Y);
				do
				{
					printf("Introduzca el rango de visión en X: ");
					scanf("%d", &VISION.X);
					fflush(stdin);
					printf("\nIntroduzca el rango de visión en Y: ");
					scanf("%d", &VISION.Y);
					fflush(stdin);
					if (VISION.X <= 0 || VISION.Y <= 0 || VISION.Y > VISION.X || VISION.X > 6 || VISION.Y > 4)
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
				printf("Posicion actual:\nX: %d\nY: %d\n\n"
					"Introduzca la posición inicial en X: ", INITPJ.X, INITPJ.Y);
				scanf("%d", &INITPJ.X);
				fflush(stdin);
				printf("\nIntroduzca la posición inicial en Y: ");
				scanf("%d", &INITPJ.Y);
				fflush(stdin);
				break;
			case 4:
				system("cls");
				printf("Caracteres actuales:\nLlanos: '%c'\nMuros: '%c'\nEventos: '%c'\nPuertas: '%c'\nPersonaje : '%c'\n\n"
					"Introduzca el nuevo carácter para Llanos: ", graph.PLAINS, graph.WALL, graph.EVENT, graph.DOOR, graph.PJ);
				scanf("%c", &graph.PLAINS);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para Muros: ");
				scanf("%c", &graph.WALL);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para Eventos: ");
				scanf("%c", &graph.EVENT);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para Puertas: ");
				scanf("%c", &graph.DOOR);
				fflush(stdin);
				printf("Introduzca el nuevo carácter para el personaje: ");
				scanf("%c", &graph.PJ);
				fflush(stdin);
				break;
			case 5:
				system("cls");
				printf("Nombre actual del jugador: %s\n\n"
					"Introduzca nuevo nombre para el jugador (15 caracteres maximo): ", personaje.nombre);
				scanf("%[^\n]s", personaje.nombre);
				break;
			case 6:
				return;
			}
		}
	} while (1);
}

void pjmenu()
{
	int k = 1, i = 1, aux = 0;
	char sel;

	do
	{
		system("cls");
		printf("\t-Menú-\n");
		if (k == 1)
			printf("->");
		printf("  Estado\n");
		if (k == 2)
			printf("->");
		printf("  Equipo\n");
		if (k == 3)
			printf("->");
		printf("  Inventario\n");
		if (k == 4)
			printf("->");
		printf("  Habilidades\n");
		if (k == 5)
			printf("->");
		printf("  Salir\n");
		sel = getch();
		if (sel == controles.UP)
		{
			if (k == 1)
			{
				k = 5;
				continue;
			}
			k--;
		}
		if (sel == controles.DOWN)
		{
			if (k == 5)
			{
				k = 1;
				continue;
			}
			k++;
		}
		if (sel == controles.ACTION)
		{
			switch (k)
			{
			case 1:
				system("cls");
				printf("Nombre: %s\n\n"
					"Fuerza: %d\n"
					"Defensa: %d + %d\n"
					"Puntería: %d\n"
					"Inteligencia: %d\n\n"
					"Daño efectivo: %d - %d\n"
					, personaje.nombre, personaje.STR, personaje.DEF, items[personaje.armorEquip].def, personaje.ACC, personaje.INT, personaje.minDmg, personaje.maxDmg);
				getch();
				break;
			case 2:
				system("cls");
				printf("Arma: %s (%d - %d)\n\n"
					"Armadura: %s (%d)\n", items[personaje.weapEquip].nombre, items[personaje.weapEquip].minDmg, items[personaje.weapEquip].maxDmg, items[personaje.armorEquip].nombre, items[personaje.armorEquip].def);
				getch();
				break;
			case 3:
				do
				{
					system("cls");
					for (k = 1; k < numinv + 1; k++)
					{
						if (k == i)
							printf("->");
						printf("  %s  %dx\n", items[personaje.inventario[k - 1][0]].nombre, personaje.inventario[k - 1][1]);
						if (k == numinv)
						{
							if (i == numinv + 1)
								printf("->");
							printf("  Salir\n");
						}
					}
					sel = getch();
					if (sel == controles.UP)
					{
						if (i == 1)
						{
							i = numinv + 1;
							continue;
						}
						i--;
					}
					else if (sel == controles.DOWN)
					{
						if (i == numinv + 1)
						{
							i = 1;
							continue;
						}
						i++;
					}
					else if (sel == controles.ACTION)
					{
						if (i == numinv + 1)
							break;
						system("cls");
						printf("Nombre: %s\n", items[personaje.inventario[i - 1][0]].nombre);
						if (items[personaje.inventario[i - 1][0]].tipo == 0)
							printf("Daño: %d - %d\n", items[personaje.inventario[i - 1][0]].minDmg, items[personaje.inventario[i - 1][0]].maxDmg);
						else if (items[personaje.inventario[i - 1][0]].tipo == 1)
							printf("Defensa: %d\n", items[personaje.inventario[i - 1][0]].def);
						printf("Cantidad : %d\n\n", personaje.inventario[i - 1][1]);
						printf("¿Equipar? (s/n)");
						if (getch() == 's')
						{
							if (items[personaje.inventario[i - 1][0]].tipo == 0)
								personaje.weapEquip = i - 1;
							else if (items[personaje.inventario[i - 1][0]].tipo == 1)
								personaje.armorEquip = i - 1;
							personaje.minDmg = items[personaje.weapEquip].minDmg + (personaje.STR / 10);
							personaje.maxDmg = items[personaje.weapEquip].maxDmg + (personaje.STR / 10);
						}
					}
				} while (1);
				k = 1;
				i = 1;
				break;
			case 5:
				return;
			default:
				break;
			}
		}
	} while (1);
}