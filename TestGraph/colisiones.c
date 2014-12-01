#include "cabecera.h"

short colisiones(bool *update, char comp)
{
	if (comp == '#') // Muro.
	{
		(*update) = false;
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