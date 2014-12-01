#include "cabecera.h"

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
		error(6, 0);
}