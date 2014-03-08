#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

typedef struct
{
	char nombre[15];
	int HP;
	int HPLEFT;
	int MP;
	int MPLEFT;
	int LVL;
	int EXP;
	int STR;
	int DEF;
	int ACC;
	int INT;
	int weapEquip;
	int armorEquip;
	int invent;
	int minDmg;
	int maxDmg;
	int inventario[4][2];
} STRUCTpersonaje;
typedef struct
{
	int X;
	int Y;
} STRUCTpos;
typedef struct
{
	char nombre[15];
	int minHP;
	int maxHP;
	int minDmg;
	int maxDmg;
	int minEXP;
	int maxEXP;
	int num;
	char graph;
} STRUCTenemigos;
typedef struct
{
	char nombre[15];
	int HP;
	int minDmg;
	int maxDmg;
	int EXP;
	char graph;
	STRUCTpos pos;
} STRUCTenemigosSPAWN;
typedef struct
{
	int map[2];
	int X[2];
	int Y[2];
} STRUCTlink;

typedef struct
{
	char UP;
	char DOWN;
	char LEFT;
	char RIGHT;
	char ACTION;
	char BACK;
	char SPECIAL;
	char MENU;
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

typedef struct
{
	char nombre[15];
	int minDmg;
	int maxDmg;
	int def;
	int tipo;
}STRUCTitem;

extern STRUCTcontroles controles;
extern STRUCTpos VISION, INITPJ, tamMapa, pj, TAMCMD;
extern STRUCTgraph graph;
extern STRUCTeventos *evento;
extern STRUCTlink *puertas;
extern STRUCTpersonaje personaje;
extern STRUCTitem *items;
extern int numevento, mapactual, numlink, updatemap, auxmalloc, numitems, numinv, numenemigos;
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
void pjmenu();
void batalla();
int menuFlecha(int, int);
void defeat();