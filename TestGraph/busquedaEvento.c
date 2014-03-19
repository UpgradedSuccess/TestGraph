#include "cabecera.h"

short busquedaEvento(short numevento, STRUCTpersonaje personaje, STRUCTeventos *evento)
{
	short k;

	for (k = 0; k < numevento; k++)
	{
		if (personaje.pos.Y == evento[k].posEvento.Y && personaje.pos.X == evento[k].posEvento.X)
			return k;
	}
	return -1;
}