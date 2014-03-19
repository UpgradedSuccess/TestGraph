#include "cabecera.h"

int busquedaPuerta(short *mapactual, short *numlink, STRUCTpersonaje *personaje, STRUCTlink *puertas)
{
	short k;

	for (k = 0; k < (*numlink); k++)
	{
		if (personaje->pos.Y == puertas[k].Y[0] && personaje->pos.X == puertas[k].X[0])
		{
			(*mapactual) = puertas[k].map[1];
			personaje->pos.Y = puertas[k].Y[1];
			personaje->pos.X = puertas[k].X[1];
			return 1;
		}
		else if (personaje->pos.Y == puertas[k].Y[1] && personaje->pos.X == puertas[k].X[1])
		{
			(*mapactual) = puertas[k].map[0];
			personaje->pos.Y = puertas[k].Y[0];
			personaje->pos.X = puertas[k].X[0];
			return 1;
		}
	}
	return 0;
}