#include <stdio.h>

typedef struct
{
	int map[2];
	int X[2];
	int Y[2];
} STRUCTlink;

typedef struct
{
	int X;
	int Y;
} STRUCTpos;

typedef struct
{
	char UP;
	char DOWN;
	char LEFT;
	char RIGHT;
	char ACTION;
	char SPECIAL;
} STRUCTcontroles;

typedef struct
{
	char PLAINS;
	char WALL;
	char EVENT;
	char DOOR;
	char PJ;
} STRUCTgraph;

typedef struct
{
	STRUCTpos posEvento;
	char nombre[15];
	char **text;
	int numTexto;
} STRUCTeventos;

extern STRUCTcontroles controles;
extern STRUCTpos VISION, INITPJ, tamMapa, pj;
extern STRUCTgraph graph;
extern STRUCTeventos *evento;
extern STRUCTlink *puertas;
extern int numevento, mapactual, numlink, updatemap, auxmalloc;
extern char **map;

void movimiento();
void lectura();
void display();
void error(int);
void inicializacion();
void instrucciones();
void adminmenu();
int busquedaEvento();
void busquedaPuerta();
int colisiones(char);