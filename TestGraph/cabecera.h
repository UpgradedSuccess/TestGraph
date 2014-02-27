#include <stdio.h>
#define MAX 30

typedef struct
{
	char **map;
} mapeado;

typedef struct
{
	int map[2];
	int X[2];
	int Y[2];
}link;

typedef struct
{
	int X;
	int Y;
}pos;

typedef struct
{
	char UP;
	char DOWN;
	char LEFT;
	char RIGHT;
	char ACTION;
	char SPECIAL;
}controls;

typedef struct
{
	char PLAINS;
	char WALL;
	char EVENT;
	char DOOR;
	char PJ;
}graphstruct;

typedef struct
{
	pos posEvento;
	char nombre[15];
	char **text;
	int numTexto;
}eventstruct;

extern mapeado mapp;
extern controls controles;
extern pos VISION, INITPJ, tamMapa, pj;
extern graphstruct graph;
extern eventstruct *evento;
extern link *puertas;
extern int numevent, mapactual, numlink;

void colisiones(int*);
void lectura();
void display();
void error(int);
void inicializacion();
void instrucciones();
void adminmenu();
int busquedaEvento();
void busquedaPuerta();