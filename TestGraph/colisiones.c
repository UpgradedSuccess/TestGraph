#include "cabecera.h"
#include <windows.h>
#include <conio.h>

mapeado mapp;
controls controles;
pos VISION, INITPJ, pj;
graphstruct graph;
link *puertas;
int numevent, mapactual, numlink;

void colisiones(int *KEY)
{
	int k, i, j;
	char mov;
	pos aux;

	mov = getch();
	if (mov == controles.UP)
	{
		if (mapp.map[pj.Y - 1][pj.X] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp.map[pj.Y - 1][pj.X] == '-' || mapp.map[pj.Y - 1][pj.X] == 'E' || mapp.map[pj.Y - 1][pj.X] == '!')
		{
			if (pj.Y != 0)
			{
				pj.Y--;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.LEFT)
	{
		if (mapp.map[pj.Y][pj.X - 1] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp.map[pj.Y][pj.X - 1] == '-' || mapp.map[pj.Y][pj.X - 1] == 'E' || mapp.map[pj.Y][pj.X - 1] == '!')
		{
			if (pj.X != 0)
			{
				pj.X--;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.DOWN)
	{
		if (mapp.map[pj.Y + 1][pj.X] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp.map[pj.Y + 1][pj.X] == '-' || mapp.map[pj.Y + 1][pj.X] == 'E' || mapp.map[pj.Y + 1][pj.X] == '!')
		{
			if (pj.Y != tamMapa.Y)
			{
				pj.Y++;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.RIGHT)
	{
		if (mapp.map[pj.Y][pj.X + 1] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp.map[pj.Y][pj.X + 1] == '-' || mapp.map[pj.Y][pj.X + 1] == 'E' || mapp.map[pj.Y][pj.X + 1] == '!')
		{
			if (pj.X != tamMapa.X - 2)
			{
				pj.X++;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.ACTION)
	{
		if (mapp.map[pj.Y][pj.X] == '-')
		{
			*KEY = 0;
			return;
		}
		else if (mapp.map[pj.Y][pj.X] == '!')
		{
			*KEY = 1;
			k = busquedaEvento();
			printf("\n\n\n");
			printf("%s: \n", evento[k].nombre);
			printf("-");
			for (i = 0; i < evento[k].numTexto; i++)
			{
				for (j = 0; j < strlen(evento[k].text[i]); j++)
				{
					printf("%c", evento[k].text[i][j]);
					Sleep(50);
				}
				printf("\n ");
				getch();
			}
			return;
		}
		else if (mapp.map[pj.Y][pj.X] == 'E')
		{
			*KEY = 1;
			busquedaPuerta();
			lectura();
		}
		return;
	}
	if (mov == controles.SPECIAL)
		adminmenu();
}

void adminmenu()
{
	int sel;

	do
	{
		system("cls");
		printf("\t-Menu de administrador-\n");
		printf("1-Cambiar controles\n");
		printf("2-Cambiar vision\n");
		printf("3-Cambiar inicio de jugador\n");
		printf("4-Cambiar graficos de terreno\n");
		printf("5-Salir\n");
		printf("Seleccion: ");
		scanf("%d", &sel);
		fflush(stdin);
		switch (sel)
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
			break;
		case 2:
			system("cls");
			printf("Rango actual:\nX: %d\nY: %d\n\n", VISION.X, VISION.Y);
			printf("- Solo se aceptan valores mayores que 0 y menores que X=6 e Y=4.\n- X DEBE ser mayor que Y.\n- Se recomienda que X sea Y + 2.\n\n");
			do
			{
				printf("Introduzca el rango de vision en X: ");
				scanf("%d", &VISION.X);
				fflush(stdin);
				printf("\nIntroduzca el rango de vision en Y: ");
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
			printf("Posicion actual:\nX: %d\nY: %d\n\n", INITPJ.X, INITPJ.Y);
			printf("Introduzca la posicion inicial en X: ");
			scanf("%d", &INITPJ.X);
			fflush(stdin);
			printf("\nIntroduzca la posicion inicial en Y: ");
			scanf("%d", &INITPJ.Y);
			fflush(stdin);
			break;
		case 4:
			system("cls");
			printf("Caracteres actuales:\nLlanos: '%c'\nMuros: '%c'\nEventos: '%c'\nPuertas: '%c'\nPersonaje : '%c'\n\n", graph.PLAINS, graph.WALL, graph.EVENT, graph.DOOR, graph.PJ);
			printf("Introduzca el nuevo caracter para Llanos: ");
			scanf("%c", &graph.PLAINS);
			fflush(stdin);
			printf("Introduzca el nuevo caracter para Muros: ");
			scanf("%c", &graph.WALL);
			fflush(stdin);
			printf("Introduzca el nuevo caracter para Eventos: ");
			scanf("%c", &graph.EVENT);
			fflush(stdin);
			printf("Introduzca el nuevo caracter para Puertas: ");
			scanf("%c", &graph.DOOR);
			fflush(stdin);
			printf("Introduzca el nuevo caracter para el personaje: ");
			scanf("%c", &graph.PJ);
			fflush(stdin);
			break;
		case 5:
			return;
		}
	} while (1);
}

int busquedaEvento()
{
	int k;

	for (k = 0; k < numevent; k++)
		if (pj.Y == evento[k].posEvento.Y && pj.X == evento[k].posEvento.X)
			return k;
	return -1;
}

void busquedaPuerta()
{
	int k;

	for (k = 0; k < numlink; k++)
	{
		if (pj.Y == puertas[k].Y[0] && pj.X == puertas[k].X[0])
		{
			mapactual = puertas[k].map[1];
			pj.Y = puertas[k].Y[1];
			pj.X = puertas[k].X[1];
			return;
		}
		if (pj.Y == puertas[k].Y[1] && pj.X == puertas[k].X[1])
		{
			mapactual = puertas[k].map[0];
			pj.Y = puertas[k].Y[0];
			pj.X = puertas[k].X[0];
			return;
		}
	}
	return;
}