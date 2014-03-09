#include "cabecera.h"

void busquedaPuerta(int *numevento, int *mapactual, int *numlink, int *updatemap, STRUCTpos *pj, STRUCTpos *tamMapa)
{
	int k;

	for (k = 0; k < (*numlink); k++)
	{
		if (pj->Y == puertas[k].Y[0] && pj->X == puertas[k].X[0])
		{
			(*mapactual) = puertas[k].map[1];
			pj->Y = puertas[k].Y[1];
			pj->X = puertas[k].X[1];
			lectura(numevento, mapactual, numlink, tamMapa);
			(*updatemap) = 1;
			return;
		}
		if (pj->Y == puertas[k].Y[1] && pj->X == puertas[k].X[1])
		{
			(*mapactual) = puertas[k].map[0];
			pj->Y = puertas[k].Y[0];
			pj->X = puertas[k].X[0];
			lectura(numevento, mapactual, numlink, tamMapa);
			(*updatemap) = 1;
			return;
		}
	}
	return;
}