﻿#include "cabecera.h"
#define mapFIL 6
#define mapCOL 12

void batalla(short numitems, STRUCTcontroles controles, STRUCTpersonaje *personaje, STRUCTitem *items)
{
	short k, i, j, l, m, RANDMAX, RANDMIN, numSpawn = 0, turno = 0, flecha = 1, update = 1, sel, printEnemy[4], numprintEnemy, dmgdealt, numenemigos = 0, movIA = 0, direccion;
	char **mapaBatalla;
	FILE *FILEenemigos;
	STRUCTpos pjBatalla;
	STRUCTenemigos *enemigos;
	STRUCTenemigosSPAWN *enemigosSPAWN;

	system("cls");
	pjBatalla.X = rand() % (mapCOL - 4) + 1;
	pjBatalla.Y = rand() % (mapFIL - 2) + 1;
	for (k = 0; k < mapFIL; k++)
	{
		for (i = 0; i < mapCOL; i++)
		{
			printf("#");
			Sleep(15);
		}
		printf("\n");
	}

	mapaBatalla = (char**)malloc(mapCOL * sizeof(char*));
	for (k = 0; k < mapCOL; k++)
		mapaBatalla[k] = (char*)malloc(mapFIL * sizeof(char));

	sprintf(mapaBatalla[0], "##########");
	for (k = 1; k < mapFIL - 1; k++)
	{
		sprintf(mapaBatalla[k], "#--------#");
	}
	sprintf(mapaBatalla[mapFIL - 1], "##########");
	k = rand() % mapFIL + 1;
	for (i = 0; i < k; i++)
	{
		do 
		{
			j = rand() % (mapCOL - 4) + 1;
			l = rand() % (mapFIL - 2) + 1;
		} while (j != pjBatalla.X && l != pjBatalla.Y);
		mapaBatalla[l][j] = '#';
	}
	FILEenemigos = fopen("data\\enemigos.txt", "rt");
	if (FILEenemigos == NULL)
	{
		printf("Error al abrir el archivo 'enemigos.txt'\n");
		exit(0);
	}
	while (feof(FILEenemigos) == 0)
	{
		if (fgetc(FILEenemigos) == '\n')
			numenemigos++;
	}
	numenemigos = numenemigos / 6;
	enemigos = (STRUCTenemigos*)malloc(numenemigos * sizeof(STRUCTenemigos));
	rewind(FILEenemigos);
	for (k = 0; k < numenemigos; k++)
	{
		fscanf(FILEenemigos, "%[^\n]s", enemigos[k].nombre);
		fscanf(FILEenemigos, "%hd %hd\n", &enemigos[k].minHP, &enemigos[k].maxHP);
		fscanf(FILEenemigos, "%hd %hd\n", &enemigos[k].minDmg, &enemigos[k].maxDmg);
		fscanf(FILEenemigos, "%hd %hd\n", &enemigos[k].minEXP, &enemigos[k].maxEXP);
		fscanf(FILEenemigos, "%[^\n]s", enemigos[k].drop);
		fscanf(FILEenemigos, "%hd\n", &enemigos[k].dropChance);
		enemigos[k].graph = enemigos[k].nombre[0];
	}
	fclose(FILEenemigos);
	enemigosSPAWN = (STRUCTenemigosSPAWN*)malloc(4 * sizeof(STRUCTenemigosSPAWN));
	l = 0;
	for (k = 0; k < numenemigos; k++)
	{
		enemigos[k].num = rand() % 3 + 1;
		numSpawn = numSpawn + enemigos[k].num;
		if (numSpawn > 4)
		{
			m = numSpawn - 4;
			enemigos[k].num = enemigos[k].num - m;
			numSpawn = 4;
		}
		for (i = 0; i < enemigos[k].num; i++)
		{
			sprintf(enemigosSPAWN[l].nombre, "%s %hd", enemigos[k].nombre, i + 1);
			enemigosSPAWN[l].minDmg = enemigos[k].minDmg;
			enemigosSPAWN[l].maxDmg = enemigos[k].maxDmg;
			enemigosSPAWN[l].graph = enemigos[k].graph;
			RANDMIN = enemigos[k].minHP;
			RANDMAX = enemigos[k].maxHP - enemigos[k].minHP;
			enemigosSPAWN[l].HP = rand() % RANDMAX + RANDMIN;
			RANDMIN = enemigos[k].minEXP;
			RANDMAX = enemigos[k].maxEXP - enemigos[k].minEXP;
			enemigosSPAWN[l].EXP = rand() % RANDMAX + RANDMIN;
			for (j = 0; j < numitems; j++)
			{
				if (strcmp(enemigos[k].drop, items[j].nombre) == 0)
				{
					enemigosSPAWN[l].drop = j;
					enemigosSPAWN[l].dropChance = enemigos[k].dropChance;
				}
			}
			do
			{
				enemigosSPAWN[l].pos.X = rand() % (mapCOL - 4) + 1;
				enemigosSPAWN[l].pos.Y = rand() % (mapFIL - 2) + 1;
			} while ((enemigosSPAWN[l].pos.X != pjBatalla.X && enemigosSPAWN[l].pos.Y != pjBatalla.Y) || (mapaBatalla[enemigosSPAWN[l].pos.Y][enemigosSPAWN[l].pos.X] != '#'));
			for (j = 0; j <= l; j++)
			{
				if (j != l)
				{
					while ((enemigosSPAWN[l].pos.X == enemigosSPAWN[j].pos.X && enemigosSPAWN[l].pos.Y == enemigosSPAWN[j].pos.Y) || (enemigosSPAWN[l].pos.X == pjBatalla.X && enemigosSPAWN[l].pos.Y == pjBatalla.Y))
					{
						enemigosSPAWN[l].pos.X = rand() % (mapCOL - 4) + 1;
						enemigosSPAWN[l].pos.Y = rand() % (mapFIL - 2) + 1;
					}
				}
			}
			l++;
		}
	}
	update = 1;
	do
	{
		if (personaje->HPLEFT <= 0)
			defeat();
		if (update == 1)
		{
			system("cls");
			mapaBatalla[pjBatalla.Y][pjBatalla.X] = '*';
			for (k = 0; k < numSpawn; k++)
			{
				mapaBatalla[enemigosSPAWN[k].pos.Y][enemigosSPAWN[k].pos.X] = enemigosSPAWN[k].graph;
			}
			for (k = 0; k < mapFIL; k++)
				puts(mapaBatalla[k]);
			if (turno == 0)
			{
				printf("\n\n");
				update = 0;
				if (flecha == 1)
					printf("->");
				printf("  Mover\n");
				if (flecha == 2)
					printf("->");
				printf("  Atacar\n");
				if (flecha == 3)
					printf("->");
				printf("  Esperar\n");
				if (flecha == 4)
					printf("->");
				printf("  Huir\n");
				printf("\n\nHP: %hd / %hd\n"
					"MP: %hd / %hd\n"
					"EXP: %hd / %hd", personaje->HPLEFT, personaje->HP, personaje->MPLEFT, personaje->MP, personaje->EXP, personaje->LVL * 100);
			}
		}
		if (turno == 0)
		{
			update = 1;
			sel = flecha;
			flecha = menuFlecha(4, flecha, controles);
			if (flecha == 0)
			{
				flecha = 1;
				switch (sel)
				{
				case 1:
					update = 1;
					printf("\nElige sitio al que mover.");
					direccion = parsemov(controles, mapaBatalla[pjBatalla.Y - 1][pjBatalla.X], mapaBatalla[pjBatalla.Y + 1][pjBatalla.X], mapaBatalla[pjBatalla.Y][pjBatalla.X - 1], mapaBatalla[pjBatalla.Y][pjBatalla.X + 1]);
					switch (direccion)
					{
					case 0:
						break;
					case 1:
						mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
						pjBatalla.Y--;
						turno++;
						break;
					case 2:
						mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
						pjBatalla.X--;
						turno++;
						break;
					case 3:
						mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
						pjBatalla.Y++;
						turno++;
						break;
					case 4:
						mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
						pjBatalla.X++;
						turno++;
						break;
					default:
						break;
					}
					break;
				case 2:
					system("cls");
					numprintEnemy = 0;
					if (personaje->inventario[personaje->weapEquip].isRanged == false)
					{
						for (l = 0; l < numSpawn; l++)
						{
							if (pjBatalla.X + 1 == enemigosSPAWN[l].pos.X || pjBatalla.X - 1 == enemigosSPAWN[l].pos.X || pjBatalla.Y + 1 == enemigosSPAWN[l].pos.Y || pjBatalla.Y - 1 == enemigosSPAWN[l].pos.Y)
							{
								if (pjBatalla.Y == enemigosSPAWN[l].pos.Y || pjBatalla.X == enemigosSPAWN[l].pos.X)
								{
									printEnemy[numprintEnemy] = l;
									numprintEnemy++;
								}
							}

						}
					}
					else
					{
						for (l = 0; l < numSpawn; l++)
						{
							printEnemy[numprintEnemy] = l;
							numprintEnemy++;
						}
					}
					m = 1;
					update = 1;
					do
					{
						if (update == 1)
						{
							system("cls");
							if (numprintEnemy == 0)
							{
								printf("No hay ningún enemigo al alcance.");
								getch();
								break;
							}
							for (l = 1; l < numprintEnemy + 1; l++)
							{
								if (l == m)
									printf("->");
								printf("  %s  HP:%hd\n", enemigosSPAWN[printEnemy[l - 1]].nombre, enemigosSPAWN[printEnemy[l - 1]].HP);
							}
						}
						update = 1;
						l = m;
						m = menuFlecha(numprintEnemy, m, controles);
						if (m == 0)
						{
							turno++;
							RANDMIN = personaje->minDmg;
							RANDMAX = personaje->maxDmg - personaje->minDmg;
							dmgdealt = rand() % RANDMAX + RANDMIN;
							enemigosSPAWN[printEnemy[l - 1]].HP = enemigosSPAWN[printEnemy[l - 1]].HP - dmgdealt;
							printf("\nHas hecho %hd de daño a %s!", dmgdealt, enemigosSPAWN[printEnemy[l - 1]].nombre);
							if (enemigosSPAWN[printEnemy[l - 1]].HP <= 0)
							{
								if ((rand() % enemigosSPAWN[printEnemy[l - 1]].dropChance) == 0)
								{
									printf("\nHas conseguido: %s", items[enemigosSPAWN[printEnemy[l - 1]].drop].nombre);
									personaje->invent++;
									personaje->inventario[personaje->invent - 1] = items[enemigosSPAWN[printEnemy[l - 1]].drop];
									personaje->inventario[personaje->invent - 1].num = 1;
								}
								numSpawn--;
								personaje->EXP = personaje->EXP + enemigosSPAWN[l - 1].EXP;
								printf("\n%s ha muerto!\nConseguidos %hd de EXP\n\t|\n\tv", enemigosSPAWN[printEnemy[l - 1]].nombre, enemigosSPAWN[l - 1].EXP);
								getch();
								mapaBatalla[enemigosSPAWN[printEnemy[l - 1]].pos.Y][enemigosSPAWN[printEnemy[l - 1]].pos.X] = '-';
								if (personaje->EXP >= personaje->LVL * 100)
								{
									system("cls");
									printf("Has ganado 1 nivel!\n\n"
										"+%hd Fuerza\n"
										"+%hd HP\n", personaje->LVL, personaje->LVL * 2);
									personaje->EXP = personaje->EXP - personaje->LVL * 100;
									personaje->LVL++;
									personaje->STR = personaje->STR + personaje->LVL;
									personaje->HP = personaje->HP + personaje->LVL * 2;
									personaje->HPLEFT = personaje->HP;
									getch();
								}
								if (numSpawn == 0)
								{
									return;
								}
								enemigosSPAWN[printEnemy[l - 1]] = enemigosSPAWN[numSpawn];
								enemigosSPAWN = (STRUCTenemigosSPAWN*)realloc(enemigosSPAWN, numSpawn * sizeof(STRUCTenemigosSPAWN));
							}
							else
							{
								printf("\n\t|\n\tv");
								getch();
							}
							break;
						}
						else if (m == -1)
							break;
						else if (m == -2)
						{
							update = 0;
							m = l;
						}
					} while (1);
					break;
				case 3:
					turno++;
					break;
				case 4:
					if (rand() % 2 == 0)
						return;
					printf("\nNo pudiste escapar!");
					getch();
					turno++;
					break;
				}
			}
			else if (flecha == -1 || flecha == -2)
			{
				flecha = sel;
				update = 0;
			}
		}
		else
		{
			Sleep(200);
			movIA = ia(enemigosSPAWN[turno - 1].pos, pjBatalla, mapaBatalla[enemigosSPAWN[turno - 1].pos.Y - 1][enemigosSPAWN[turno - 1].pos.X], mapaBatalla[enemigosSPAWN[turno - 1].pos.Y + 1][enemigosSPAWN[turno - 1].pos.X], mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X + 1], mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X - 1], &enemigosSPAWN[turno - 1].last);
			switch (movIA)
			{
			case 0:
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje->HPLEFT = personaje->HPLEFT - dmgdealt;
				printf("\nHas recibido %hd de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				getch();
				break;
			case 1:
				mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
				enemigosSPAWN[turno - 1].pos.X++;
				update = 1;
				break;
			case 2:
				mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
				enemigosSPAWN[turno - 1].pos.Y++;
				update = 1;
				break;
			case 3:
				mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
				enemigosSPAWN[turno - 1].pos.X--;
				update = 1;
				break;
			case 4:
				mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
				enemigosSPAWN[turno - 1].pos.Y--;
				update = 1;
				break;
			case 5:
				if (turno == numSpawn)
					turno = 0;
				else
					turno++;
				break;
			}
			if (turno == numSpawn)
				turno = 0;
			else
				turno++;
		}
		if (flecha == -1 || flecha == -2)
		{
			flecha = sel;
			update = 0;
		}
	} while (1);
	free(enemigosSPAWN);
	free(enemigos);
	return;
}

int ia(STRUCTpos posEnemigo, STRUCTpos posPersonaje, char UP, char DOWN, char RIGHT, char LEFT, short *last)
{
	boolean flag = false, cantmove = false;

	if (RIGHT != '-' && UP != '-' && LEFT != '-' && DOWN != '-')
		return 5;
	else
	{
		do
		{
			cantmove = true;
			if ((posEnemigo.X < posPersonaje.X || flag == true) && *last != 1)
			{
				cantmove = false;
				flag = false;
				if (RIGHT == '*')
					return 0;
				else if (RIGHT == '-')
				{
					*last = 3;
					return 1;
				}
				else
				{
					cantmove = true;
					flag = true;
				}
			}
			if ((posEnemigo.Y < posPersonaje.Y || flag == true) && *last != 2)
			{
				cantmove = false;
				flag = false;
				if (DOWN == '*')
					return 0;
				else if (DOWN == '-')
				{
					*last = 4;
					return 2;
				}
				else
				{
					cantmove = true;
					flag = true;
				}
			}
			if ((posEnemigo.X > posPersonaje.X || flag == true) && *last != 3)
			{
				cantmove = false;
				flag = false;
				if (LEFT == '*')
					return 0;
				else if (LEFT == '-')
				{
					*last = 1;
					return 3;
				}
				else
				{
					cantmove = true;
					flag = true;
				}
			}
			if ((posEnemigo.Y > posPersonaje.Y || flag == true) && *last != 4)
			{
				cantmove = false;
				flag = false;
				if (UP == '*')
					return 0;
				else if (UP == '-')
				{
					*last = 2;
					return 4;
				}
				else
				{
					cantmove = true;
					flag = true;
				}
			}
			if (cantmove == true && flag == false)
			{
				*last = 0;
				return 5;
			}
		} while (1);
	}
	return 5;
}