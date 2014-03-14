#include "cabecera.h"

int busquedaEvento(int numevento, STRUCTpersonaje personaje, STRUCTeventos **evento)
{
	int k;

	for (k = 0; k < numevento; k++)
	{
		if (personaje.pos.Y == (*evento)[k].posEvento.Y && personaje.pos.X == (*evento)[k].posEvento.X)
			return k;
	}
	return -1;
}