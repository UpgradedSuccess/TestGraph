#include "cabecera.h"

int numevento;
STRUCTpos pj;
STRUCTeventos *evento;

int busquedaEvento()
{
	int k;

	for (k = 0; k < numevento; k++)
	if (pj.Y == evento[k].posEvento.Y && pj.X == evento[k].posEvento.X)
		return k;
	return -1;
}