#include "cabecera.h"

STRUCTcontroles controles;
STRUCTpos VISION, INITPJ;
STRUCTgraph graph;

int main()
{
	inicializacion();
	lectura();
	instrucciones();
	display();
}

void inicializacion()
{
	controles.UP = 'w';
	controles.DOWN = 's';
	controles.LEFT = 'a';
	controles.RIGHT = 'd';
	controles.ACTION = 'e';
	controles.SPECIAL = 'p';
	VISION.X = 4;
	VISION.Y = 2;
	INITPJ.X = 3;
	INITPJ.Y = 3;
	graph.PLAINS = '-';
	graph.WALL = '#';
	graph.EVENT = '!';
	graph.DOOR = 'E';
	graph.PJ = '*';
	return;
}

void instrucciones()
{
	printf("Instrucciones por defecto:\n\nMovimiento: 'wasd'\nInteraccion: 'e'\nMenu de administrador: 'p'\n\nLeyenda:\nMuros: '#'\nPuertas: 'E'\nLlanos: '-'\nEventos: '!'\nPersonaje: '*'\n\nTodas las caracteristicas del juego se pueden cambiar en el menu de admin.\n\nPulse una tecla para continuar...");
	return;
}