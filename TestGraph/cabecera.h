#include <stdio.h>
#define MAX 30

typedef struct
{
	char **map;
	int ***dest;
} mapeado;

typedef struct
{
	int map;
	int X;
	int Y;
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
	link posEvento;
	char nombre[15];
	char text[MAX][30];
	int numTexto;
}eventstruct;

extern mapeado *mapp;
extern controls controles;
extern pos VISION;
extern pos INITPJ;
extern pos *tamMapa;
extern graphstruct graph;
extern eventstruct *evento;
extern pos pj;
extern int nummapas;
extern int numevent;

void colisiones(int*, int*);
void lectura();
void display();
void error(int);
void inicializacion();
void instrucciones();
void adminmenu();
int busquedaEvento();