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
	printf("Instrucciones por defecto:\n\nMovimiento: 'wasd'\nInteraccion: 'e'\nMenu de administrador: 'p'\n\nLeyenda:\nMuros: '#'\nPuertas: 'E'\nLlanos: '-'\nEventos: '!'\nPersonaje: '*'\n\nTodas las caracteristicas del juego se pueden cambiar en el menu de admin.\n\nPulse una tecla para continuar...");
	return;
}