#include "cabecera.h"

short busquedaEvento(short numevento, STRUCTpersonaje personaje, STRUCTeventos *evento)
{
	short k;

	// Compara la posici�n actual del personaje con las posiciones del archivo events.txt
	for (k = 0; k < numevento; k++)
	{
		if (personaje.pos.Y == evento[k].posEvento.Y && personaje.pos.X == evento[k].posEvento.X)
			return k; // Posici�n que coincide.
	}
	return -1; // Error.
}