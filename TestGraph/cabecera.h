#include <stdio.h>
#define MAX 30
#define VISIONX 4
#define VISIONY 2

typedef struct
{
	char map[MAX][MAX];
	char desc[MAX][MAX][30];
	char text[MAX][MAX][MAX][100];
	int dest[MAX][MAX][3];
	int numTexto[MAX][MAX];
} mapeado;

void colisiones(mapeado[MAX], int[2], int*, int[MAX][2]);
void lectura(int[MAX][2], mapeado*, int*);
void display(int[MAX][2], mapeado*);