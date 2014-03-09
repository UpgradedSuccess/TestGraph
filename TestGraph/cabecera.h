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

void movimiento(int, int*, int*, int*, int*, STRUCTpos*, STRUCTpos*, STRUCTpos*, STRUCTgraph*, STRUCTcontroles*, STRUCTpersonaje*, char***, STRUCTeventos**, STRUCTitem*, STRUCTlink**);
void lectura(int*, int*, int*, STRUCTpos*, char***, STRUCTeventos**, STRUCTlink**);
void display(int, int*, int*, STRUCTpos*, STRUCTpos*, STRUCTgraph*, STRUCTcontroles*, STRUCTpersonaje*, char***, STRUCTeventos**, STRUCTitem*, STRUCTlink**);
void error(int);
void inicializacion(STRUCTpos*, STRUCTgraph*, STRUCTcontroles*, STRUCTpersonaje*, STRUCTitem**);
void instrucciones();
void adminmenu(STRUCTpos*, STRUCTgraph*, STRUCTcontroles*, STRUCTpersonaje*);
int busquedaEvento(int, STRUCTpos, STRUCTeventos**);
void busquedaPuerta(int*, int*, int*, int*, STRUCTpos*, STRUCTpos*, char***, STRUCTeventos**, STRUCTlink**);
int colisiones(char);
void pjmenu(STRUCTcontroles, STRUCTpersonaje*, STRUCTitem*);
void batalla(STRUCTcontroles, STRUCTpersonaje*);
int menuFlecha(int, int, STRUCTcontroles);
void defeat();