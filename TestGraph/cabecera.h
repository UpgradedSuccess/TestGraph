#include <stdio.h>
#define MAX 30
#define VISIONX 4
#define VISIONY 2

typedef struct
{
	char map[MAX][MAX];
	char desc[MAX][MAX][30];
	char text[MAX][MAX][MAX][50];
	int dest[MAX][MAX][3];
	int numTexto[MAX][MAX];
} mapeado;

void colisiones(mapeado[], int[2], int*, int[][2]);
void lectura(int[][2], mapeado*, int*);
void display(int[][2], mapeado*);