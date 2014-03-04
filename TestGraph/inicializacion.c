#include "cabecera.h"

STRUCTcontroles controles;
STRUCTpos VISION, INITPJ, TAMCMD;
STRUCTgraph graph;

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
	TAMCMD.X = 35;
	TAMCMD.Y = 15;
	graph.PLAINS = '-';
	graph.WALL = '#';
	graph.EVENT = '!';
	graph.DOOR = 'E';
	graph.PJ = '*';
	return;
}