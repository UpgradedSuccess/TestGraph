#include "cabecera.h"

short movimiento(short numevento, char **map, STRUCTcontroles *controles, STRUCTpersonaje *personaje, STRUCTeventos *evento)
{
	short k, i, j, direccion;

	direccion = parsemov(*controles, map[personaje->pos.Y - 1][personaje->pos.X], map[personaje->pos.Y + 1][personaje->pos.X], map[personaje->pos.Y][personaje->pos.X - 1], map[personaje->pos.Y][personaje->pos.X + 1]);
	switch (direccion)
	{
	case 0:
		return 0;
	case 1:
		personaje->pos.Y--;
		break;
	case 2:
		personaje->pos.X--;
		break;
	case 3:
		personaje->pos.Y++;
		break;
	case 4:
		personaje->pos.X++;
		break;
	case 5:
		return 1;
	case 6:
		if (map[personaje->pos.Y][personaje->pos.X] == '-') // Si se pulsa la tecla de acción en un llano no sucede nada (Obvio y tal)
			return 4;
		else if (map[personaje->pos.Y][personaje->pos.X] == '!') // En caso de ser un NPC se busca dicho NPC y se muestra su diálogo.
		{
			k = busquedaEvento(numevento, *personaje, evento);
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
			return 5;
		}
		return 0;
	case 7:
		return 2;
	case 8:
		return 3;
	case 9:
		return 4;
	default:
		break;

	}
	return 6;
}

short colisiones(char comp)
{
	if (comp == '#') // Muro.
	{
		printf("\a"); // Beep!
		return 0;
	}
	else if (comp == '-' || comp == '!') // Llano o NPC.
		return 1;
	else if (comp == 'E') // Puerta.
		return 2;
	else // Error
		return 0;
}

short parsemov(STRUCTcontroles controles, char UP, char DOWN, char LEFT, char RIGHT)
{
	int col;
	char mov = getch();

	if (mov == controles.UP)
	{
		col = colisiones(UP);
		if (col == 1)
			return 1;
		else if (col == 2)
			return 5;
		else
			return 0;
	}
	else if (mov == controles.LEFT)
	{
		col = colisiones(LEFT);
		if (col == 1)
			return 2;
		else if (col == 2)
			return 5;
		else
			return 0;
	}
	else if (mov == controles.DOWN)
	{
		col = colisiones(DOWN);
		if (col == 1)
			return 3;
		else if (col == 2)
			return 5;
		else
			return 0;
	}
	else if (mov == controles.RIGHT)
	{
		col = colisiones(RIGHT);
		if (col == 1)
			return 4;
		else if (col == 2)
			return 5;
		else
			return 0;
	}
	else if (mov == controles.ACTION)
		return 6;
	else if (mov == controles.MENU)
		return 7;
	else if (mov == controles.SPECIAL)
		return 8;
	else if (mov == controles.BACK)
		return 9;
	else
		return 0;
}