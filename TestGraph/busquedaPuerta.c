#include "cabecera.h"

int busquedaPuerta(short *mapactual, short *numlink, STRUCTpersonaje *personaje, STRUCTlink *puertas)
{

	/*
	Compara la (X, Y) del personaje con las diferentes (X, Y) del archivo links.txt
	Las coordenadas en este archivo van por parejas,
	en caso de darse una coincidencia se considera la pareja como las coordenadas de destino.

	Explicación del archivo links.txt:

	MAP X Y (Pareja 1) --- MAP X Y (Pareja 2)
	MAP X Y (Pareja 1) --- MAP X Y (Pareja 2)
	MAP X Y (Pareja 1) --- MAP X Y (Pareja 2)
	...
	*/

	short k;

	for (k = 0; k < (*numlink); k++)
	{
		if (personaje->pos.Y == puertas[k].Y[0] && personaje->pos.X == puertas[k].X[0]) // Comparación con la pareja 1 del archivo.
		{
			(*mapactual) = puertas[k].map[1];
			personaje->pos.Y = puertas[k].Y[1];
			personaje->pos.X = puertas[k].X[1];
			return 1;
		}
		else if (personaje->pos.Y == puertas[k].Y[1] && personaje->pos.X == puertas[k].X[1]) // Comparación con la pareja 2 del archivo.
		{
			(*mapactual) = puertas[k].map[0];
			personaje->pos.Y = puertas[k].Y[0];
			personaje->pos.X = puertas[k].X[0];
			return 1;
		}
	}
	return 0;
}