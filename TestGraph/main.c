#include "cabecera.h"
#include <conio.h>
#include <stdlib.h>

int main()
{
	int tamMapa[MAX][2], nummapas=0;
	mapeado *mapp = NULL;

	mapp = (mapeado*)calloc(MAX, sizeof(mapeado));
	lectura(tamMapa, mapp, &nummapas);
	mapp = (mapeado*)realloc(mapp, (nummapas+1)* sizeof(mapeado));
	printf("Instrucciones:\n\nMovimiento: 'wasd'\nInteraccion: 'e'\n\nLeyenda:\nMuros: '#'\nPuertas: 'E'\nLlanos: '-'\n\nPulse una tecla para continuar...");
	getch();
	system("cls");
	display(tamMapa, mapp);
}