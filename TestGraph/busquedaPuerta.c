#include "cabecera.h"

void busquedaPuerta(int *numevento, int *mapactual, int *numlink, int *updatemap, STRUCTpersonaje *personaje, STRUCTpos *tamMapa, char ***map, STRUCTeventos **evento, STRUCTlink **puertas)
{
	int k, i;

	for (k = 0; k < (*numlink); k++)
	{
		if ((*personaje).pos.Y == (*puertas)[k].Y[0] && (*personaje).pos.X == (*puertas)[k].X[0])
		{
			(*mapactual) = (*puertas)[k].map[1];
			(*personaje).pos.Y = (*puertas)[k].Y[1];
			(*personaje).pos.X = (*puertas)[k].X[1];
			for (i = 0; i <= tamMapa->Y; i++)
				free((*map)[i]);
			free(*evento);
			lectura(numevento, mapactual, numlink, tamMapa, map, evento, puertas);
			(*updatemap) = 1;
			return;
		}
		if ((*personaje).pos.Y == (*puertas)[k].Y[1] && (*personaje).pos.X == (*puertas)[k].X[1])
		{
			(*mapactual) = (*puertas)[k].map[0];
			(*personaje).pos.Y = (*puertas)[k].Y[0];
			(*personaje).pos.X = (*puertas)[k].X[0];
			for (i = 0; i < tamMapa->Y; i++)
				free((*map)[i]);
			free(*evento);
			lectura(numevento, mapactual, numlink, tamMapa, map, evento, puertas);
			(*updatemap) = 1;
			return;
		}
	}
	return;
}