#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
	short X;
	short Y;
} STRUCTpos;

typedef struct
{
	char nombre[15];
	short minDmg;
	short maxDmg;
	short def;
	short tipo;
	bool isRanged;
	short num;
}STRUCTitem;

typedef struct
{
	char nombre[15];
	short HP;
	short HPLEFT;
	short MP;
	short MPLEFT;
	short LVL;
	short EXP;
	short STR;
	short DEF;
	short ACC;
	short INT;
	short weapEquip;
	short armorEquip;
	short invent;
	short minDmg;
	short maxDmg;
	STRUCTitem *inventario;
	STRUCTpos pos;
} STRUCTpersonaje;

typedef struct
{
	char nombre[15];
	short minHP;
	short maxHP;
	short minDmg;
	short maxDmg;
	short minEXP;
	short maxEXP;
	short num;
	char graph;
	char drop[15];
	short dropChance;
} STRUCTenemigos;
typedef struct
{
	char nombre[15];
	short HP;
	short minDmg;
	short maxDmg;
	short EXP;
	char graph;
	short drop;
	short dropChance;
	STRUCTpos pos;
} STRUCTenemigosSPAWN;
typedef struct
{
	short map[2];
	short X[2];
	short Y[2];
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
	short numTexto;
} STRUCTeventos;

short movimiento(bool*, short, bool*, char**, STRUCTcontroles*, STRUCTpersonaje*, STRUCTeventos*);
void lectura(short*, short*, short*, STRUCTpos*, char***, STRUCTeventos**, STRUCTlink**);
void display(STRUCTeventos*, STRUCTpos, STRUCTpos, STRUCTgraph, STRUCTpersonaje*, char**, bool, short, short);
void error(short);
void inicializacion(short*, STRUCTpos*, STRUCTgraph*, STRUCTcontroles*, STRUCTpersonaje*, STRUCTitem**, short*);
void instrucciones();
void adminmenu(STRUCTpos*, STRUCTgraph*, STRUCTcontroles*, STRUCTpersonaje*);
short busquedaEvento(short, STRUCTpersonaje, STRUCTeventos*);
int busquedaPuerta(short*, short*, STRUCTpersonaje*, STRUCTlink*);
short colisiones(bool*, char);
void pjmenu(STRUCTcontroles, STRUCTpersonaje*, STRUCTitem*, short, STRUCTgraph, STRUCTpos);
void batalla(bool*, short, STRUCTcontroles, STRUCTpersonaje*, STRUCTitem*);
short menuFlecha(short, short, STRUCTcontroles);
void defeat();
void savegame(STRUCTcontroles, STRUCTpersonaje, short, STRUCTgraph, STRUCTpos);
short loadgame(STRUCTcontroles, STRUCTitem**, STRUCTpersonaje*, short*);
void intromenu(STRUCTitem**, STRUCTcontroles, STRUCTpersonaje*, short*);