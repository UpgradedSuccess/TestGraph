#include <stdio.h>
#define MAX 30
#define VISIONX 4 // A ser posible, VISIONY será VISIONX-2. Más que nada para que el mapa sea cuadrado
#define VISIONY 2
#define INICIOPJX 3
#define INICIOPJY 3

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

extern mapeado *mapp;
extern pos *tamMapa;

void colisiones(pos*, int*, pos[]);
void lectura(pos[]);
void display(pos[]);