#include "cabecera.h"
#include <stdlib.h>

void error(short err, short mapa)
{
	system("cls");
	switch (err)
	{
	case 1:
		printf("Error de memoria.\n");
		break;
	case 2:
		printf("Error al buscar la puerta. Revise el archivo links.txt\n");
		break;
	case 3:
		printf("Error al buscar el NPC. Revise el archivo events%hd.txt\n", mapa);
		break;
	case 4:
		printf("Error al abrir el archivo 'items.txt'\n");
		break;
	case 5:
		printf("Error al abrir el archivo 'mapa%hd.txt'\n", mapa);
		break;
	case 6:
		printf("Error desconocido.");
		break;
	}
	getch();
	exit(0);
}

void instrucciones()
{
	printf("Instrucciones por defecto:\n\n"
		"Movimiento: 'wasd'\n"
		"Interacción: 'e'\n"
		"Atrás : 'q'\n"
		"Menú 'm'\n"
		"Menúde administrador: 'p'\n\n"
		"Leyenda:\n"
		"Muros: '#'\n"
		"Puertas: 'E'\n"
		"Llanos: '-'\n"
		"Eventos: '!'\n"
		"Personaje: '*'\n\n"
		"Todas las características del juego se pueden cambiar en el menú de admin.\n\n"
		"Pulse una tecla para continuar...");
	return;
}

void defeat()
{
	system("cls");
	printf("\t\tHas muerto\n\n");
	getch();
	exit(0);
}