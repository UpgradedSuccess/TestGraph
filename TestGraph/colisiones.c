#include "cabecera.h"

short colisiones(char comp)
{
	if (comp == '#')
	{
		printf("\a");
		return 0;
	}
	else if (comp == '-' || comp == '!')
		return 1;
	else if (comp == 'E')
		return 2;
	else
		return 0;
}