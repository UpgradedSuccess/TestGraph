#include "cabecera.h"
#include <windows.h>
#include <conio.h>

mapeado *mapp;
pos *tamMapa;
controls controles;
pos VISION;
pos INITPJ;
graphstruct graph;

void colisiones(pos *pj, int *mapactual, int *KEY)
{
	int k, i, j, sel;
	char mov;
	link aux;

	mov = getch();
	if (mov == controles.UP)
	{
		if (mapp[*mapactual].map[pj->Y - 1][pj->X] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y - 1][pj->X] == '-' || mapp[*mapactual].map[pj->Y - 1][pj->X] == 'E' || mapp[*mapactual].map[pj->Y - 1][pj->X] == '!')
		{
			if (pj->Y != 0)
			{
				pj->Y--;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.LEFT)
	{
		if (mapp[*mapactual].map[pj->Y][pj->X - 1] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X - 1] == '-' || mapp[*mapactual].map[pj->Y][pj->X - 1] == 'E' || mapp[*mapactual].map[pj->Y][pj->X - 1] == '!')
		{
			if (pj->X != 0)
			{
				pj->X--;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.DOWN)
	{
		if (mapp[*mapactual].map[pj->Y + 1][pj->X] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y + 1][pj->X] == '-' || mapp[*mapactual].map[pj->Y + 1][pj->X] == 'E' || mapp[*mapactual].map[pj->Y + 1][pj->X] == '!')
		{
			if (pj->Y != tamMapa[*mapactual].Y)
			{
				pj->Y++;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.RIGHT)
	{
		if (mapp[*mapactual].map[pj->Y][pj->X + 1] == '#')
		{
			*KEY = 0;
			printf("\a");
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X + 1] == '-' || mapp[*mapactual].map[pj->Y][pj->X + 1] == 'E' || mapp[*mapactual].map[pj->Y][pj->X + 1] == '!')
		{
			if (pj->X != tamMapa[*mapactual].X - 2)
			{
				pj->X++;
				*KEY = 1;
			}
			return;
		}
		else
			return;
	}
	else if (mov == controles.ACTION)
	{
		if (mapp[*mapactual].map[pj->Y][pj->X] == '-')
		{
			*KEY = 0;
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X] == '!')
		{
			*KEY = 1;
			printf("\n\n\n");
			printf("%s: \n", mapp[*mapactual].desc[pj->Y][pj->X]);
			printf("-");
			for (i = 0; i < mapp[*mapactual].numTexto[pj->Y][pj->X]; i++)
			{
				for (k = 0; k < strlen(mapp[*mapactual].text[pj->Y][pj->X][i]); k++)
				{
					printf("%c", mapp[*mapactual].text[pj->Y][pj->X][i][k]);
					Sleep(50);
				}
				printf("\n ");
				getch();
			}
			return;
		}
		else if (mapp[*mapactual].map[pj->Y][pj->X] == 'E')
		{
			*KEY = 1;
			aux.map = mapp[*mapactual].dest[pj->Y][pj->X][0];
			aux.Y = mapp[*mapactual].dest[pj->Y][pj->X][1];
			aux.X = mapp[*mapactual].dest[pj->Y][pj->X][2];
			*mapactual = aux.map;
			pj->Y = aux.Y;
			pj->X = aux.X;
		}
		return;
	}
	if (mov == controles.SPECIAL)
	{
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
				printf("Se recomienda que el rango en X sea Y + 2\n\n");
				printf("Introduzca el rango de vision en X: ");
				scanf("%d", &VISION.X);
				printf("\nIntroduzca el rango de vision en Y: ");
				scanf("%d", &VISION.Y);
				fflush(stdin);
				break;
			case 3:
				system("cls");
				printf("Posicion actual:\nX: %d\nY: %d\n\n", INITPJ.X, INITPJ.Y);
				printf("Introduzca la posicion inicial en X: ");
				scanf("%d", &INITPJ.X);
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
}