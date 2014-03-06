#include "cabecera.h"
#include <stdlib.h>

void error(int err)
{
	switch (err)
		case 1:
			printf("Error de memoria.\n");
			exit(0);
}

void instrucciones()
{
	system("title TestGraph");
	printf("Instrucciones por defecto:\n\n"
		"Movimiento: 'wasd'\n"
		"Interacción: 'e'\n"
		"Menú: 'm'\n"
		"Menú de administrador: 'p'\n\n"
		"Leyenda:\n"
		"Muros: '#'\n"
		"Puertas: 'E'\n"
		"Llanos: '-'\n"
		"Eventos: '!'\n"
		"Personaje: '*'\n\n"
		"Todas las características del juego se pueden cambiar en el menu de admin.\n\n"
		"Pulse una tecla para continuar...");
	return;
}