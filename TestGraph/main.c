#include "cabecera.h"
#include <conio.h>
#include <stdlib.h>

mapeado *mapp;
pos *tamMapa;

int main()
{

	lectura(tamMapa);
	printf("Instrucciones:\n\nMovimiento: 'wasd'\nInteraccion: 'e'\n\nLeyenda:\nMuros: '#'\nPuertas: 'E'\nLlanos: '-'\n\nPulse una tecla para continuar...");
	getch();
	system("cls");
	display(tamMapa);
}