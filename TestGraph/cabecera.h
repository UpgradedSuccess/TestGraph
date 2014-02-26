#include <stdio.h>
#define MAX 30

typedef struct
{
	char map[MAX][MAX];
	char desc[MAX][MAX][15];
	char text[MAX][MAX][MAX][50];
	int dest[MAX][MAX][MAX];
	int numTexto[MAX][MAX];
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

extern mapeado *mapp;
extern pos *tamMapa;
extern controls controles;
extern pos VISION;
extern pos INITPJ;
extern graphstruct graph;
extern int nummapas;

void colisiones(pos*, int*, int*);
void lectura();
void display();
void error(int);
void inicializacion();
void instrucciones();