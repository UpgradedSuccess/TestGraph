#include "cabecera.h"

void batalla(int numitems, STRUCTcontroles controles, STRUCTpersonaje *personaje, STRUCTitem *items)
{
	int k, i, j, l, m, RANDMAX, RANDMIN, numSpawn = 0, turno = 0, flecha = 1, update = 1, sel, printEnemy[4], numprintEnemy, dmgdealt, numenemigos = 0;
	char mov, mapaBatalla[5][11];
	FILE *FILEmapaBatalla, *FILEenemigos;
	STRUCTpos pjBatalla;
	STRUCTenemigos *enemigos;
	STRUCTenemigosSPAWN *enemigosSPAWN;

	system("cls");
	pjBatalla.Y = 3;
	pjBatalla.X = 4;
	for (k = 0; k < 5; k++)
	{
		for (i = 0; i < 10; i++)
		{
			printf("#");
			Sleep(15);
		}
		printf("\n");
	}
	FILEmapaBatalla = fopen("data\\mapaBatalla.txt", "rt");
	if (FILEmapaBatalla == NULL)
	{
		printf("Error al abrir el archivo 'mapaBatalla.txt'\n");
		exit(0);
	}
	for (k = 0; k < 5; k++)
		fscanf(FILEmapaBatalla, "%s", mapaBatalla[k]);
	fclose(FILEmapaBatalla);
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
		fscanf(FILEenemigos, "%d %d\n", &enemigos[k].minHP, &enemigos[k].maxHP);
		fscanf(FILEenemigos, "%d %d\n", &enemigos[k].minDmg, &enemigos[k].maxDmg);
		fscanf(FILEenemigos, "%d %d\n", &enemigos[k].minEXP, &enemigos[k].maxEXP);
		fscanf(FILEenemigos, "%[^\n]s", enemigos[k].drop);
		fscanf(FILEenemigos, "%d\n", &enemigos[k].dropChance);
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
			sprintf(enemigosSPAWN[l].nombre, "%s %d", enemigos[k].nombre, i + 1);
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
			enemigosSPAWN[l].pos.X = rand() % 8 + 1;
			enemigosSPAWN[l].pos.Y = rand() % 3 + 1;
			while (enemigosSPAWN[l].pos.X == 4 && enemigosSPAWN[l].pos.Y == 3)
			{
				enemigosSPAWN[l].pos.X = rand() % 8 + 1;
				enemigosSPAWN[l].pos.Y = rand() % 3 + 1;
			}
			for (j = 0; j <= numSpawn; j++)
			{
				if (j != l)
				{
					while (enemigosSPAWN[l].pos.X == enemigosSPAWN[j].pos.X && enemigosSPAWN[l].pos.Y == enemigosSPAWN[j].pos.Y)
					{
						enemigosSPAWN[l].pos.X = rand() % 8 + 1;
						enemigosSPAWN[l].pos.Y = rand() % 3 + 1;
					}
				}
			}
			l++;
		}
	}
	do
	{
		if (personaje->HPLEFT <= 0)
			defeat();
		system("cls");
		if (update == 1)
		{
			mapaBatalla[pjBatalla.Y][pjBatalla.X] = '*';
			for (k = 0; k < numSpawn; k++)
			{
				mapaBatalla[enemigosSPAWN[k].pos.Y][enemigosSPAWN[k].pos.X] = enemigosSPAWN[k].graph;
			}
		}
		for (k = 0; k < 5; k++)
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
			printf("\n\nHP: %d / %d\n"
				"MP: %d / %d\n"
				"EXP: %d / %d", personaje->HPLEFT, personaje->HP, personaje->MPLEFT, personaje->MP, personaje->EXP, personaje->LVL * 100);
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
					mov = getch();
					if (mov == controles.UP)
					{
						if (colisiones(mapaBatalla[pjBatalla.Y - 1][pjBatalla.X]) == 1)
						{
							mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
							pjBatalla.Y--;
							turno++;
						}
					}
					else if (mov == controles.LEFT)
					{
						if (colisiones(mapaBatalla[pjBatalla.Y][pjBatalla.X - 1]) == 1)
						{
							mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
							pjBatalla.X--;
							turno++;
						}
					}
					else if (mov == controles.DOWN)
					{
						if (colisiones(mapaBatalla[pjBatalla.Y + 1][pjBatalla.X]) == 1)
						{
							mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
							pjBatalla.Y++;
							turno++;
						}
					}
					else if (mov == controles.RIGHT)
					{
						if (colisiones(mapaBatalla[pjBatalla.Y][pjBatalla.X + 1]) == 1)
						{
							mapaBatalla[pjBatalla.Y][pjBatalla.X] = '-';
							pjBatalla.X++;
							turno++;
						}
					}
					break;
				case 2:
					system("cls");
					numprintEnemy = 0;
					for (l = 0; l < numSpawn; l++)
					{
						if (pjBatalla.X + 1 == enemigosSPAWN[l].pos.X)
						{
							if (pjBatalla.Y == enemigosSPAWN[l].pos.Y)
							{
								printEnemy[numprintEnemy] = l;
								numprintEnemy++;
							}
						}
					}
					for (l = 0; l < numSpawn; l++)
					{
						if (pjBatalla.X - 1 == enemigosSPAWN[l].pos.X)
						{
							if (pjBatalla.Y == enemigosSPAWN[l].pos.Y)
							{
								printEnemy[numprintEnemy] = l;
								numprintEnemy++;
							}
						}
					}
					for (l = 0; l < numSpawn; l++)
					{
						if (pjBatalla.Y + 1 == enemigosSPAWN[l].pos.Y)
						{
							if (pjBatalla.X == enemigosSPAWN[l].pos.X)
							{
								printEnemy[numprintEnemy] = l;
								numprintEnemy++;
							}
						}
					}
					for (l = 0; l < numSpawn; l++)
					{
						if (pjBatalla.Y - 1 == enemigosSPAWN[l].pos.Y)
						{
							if (pjBatalla.X == enemigosSPAWN[l].pos.X)
							{
								printEnemy[numprintEnemy] = l;
								numprintEnemy++;
							}
						}
					}
					m = 1;
					do
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
							printf("  %s  HP:%d\n", enemigosSPAWN[printEnemy[l - 1]].nombre, enemigosSPAWN[printEnemy[l - 1]].HP);
						}
						l = m;
						m = menuFlecha(numprintEnemy, m, controles);
						if (m == 0)
						{
							turno++;
							RANDMIN = personaje->minDmg;
							RANDMAX = personaje->maxDmg - personaje->minDmg;
							dmgdealt = rand() % RANDMAX + RANDMIN;
							enemigosSPAWN[printEnemy[l - 1]].HP = enemigosSPAWN[printEnemy[l - 1]].HP - dmgdealt;
							printf("\nHas hecho %d de daño a %s!", dmgdealt, enemigosSPAWN[printEnemy[l - 1]].nombre);
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
								printf("\n%s ha muerto!\nConseguidos %d de EXP\n\t|\n\tv", enemigosSPAWN[printEnemy[l - 1]].nombre, enemigosSPAWN[l - 1].EXP);
								getch();
								mapaBatalla[enemigosSPAWN[printEnemy[l - 1]].pos.Y][enemigosSPAWN[printEnemy[l - 1]].pos.X] = '-';
								if (personaje->EXP >= personaje->LVL * 100)
								{
									system("cls");
									printf("Has ganado 1 nivel!\n\n"
										"+%d Fuerza\n"
										"+%d HP\n", personaje->LVL, personaje->LVL * 2);
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
							m = l;
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
		}
		else
		{
			Sleep(200);
			if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X + 1] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje->HPLEFT = personaje->HPLEFT - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				if (turno == numSpawn)
					turno = 0;
				else
					turno++;
				getch();
			}
			else if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X - 1] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje->HPLEFT = personaje->HPLEFT - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				if (turno == numSpawn)
					turno = 0;
				else
					turno++;
				getch();
			}
			else if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y + 1][enemigosSPAWN[turno - 1].pos.X] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje->HPLEFT = personaje->HPLEFT - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				if (turno == numSpawn)
					turno = 0;
				else
					turno++;
				getch();
			}
			else if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y - 1][enemigosSPAWN[turno - 1].pos.X] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje->HPLEFT = personaje->HPLEFT - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				if (turno == numSpawn)
					turno = 0;
				else
					turno++;
				getch();
			}
			else
			{
				if (enemigosSPAWN[turno - 1].pos.X < pjBatalla.X)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X + 1]  == '-')
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.X++;
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
				}
				if (enemigosSPAWN[turno - 1].pos.X > pjBatalla.X)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X - 1] == '-')
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.X--;
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
				}
				if (enemigosSPAWN[turno - 1].pos.Y < pjBatalla.Y)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y + 1][enemigosSPAWN[turno - 1].pos.X] == '-')
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.Y++;
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
				}
				if (enemigosSPAWN[turno - 1].pos.Y > pjBatalla.Y)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y - 1][enemigosSPAWN[turno - 1].pos.X]  == '-')
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.Y--;
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
				}
				else
				{
					if (turno == numSpawn)
						turno = 0;
					else
						turno++;
				}
			}
		}
		if (flecha == -1 || flecha == -2)
			flecha = sel;
	} while (1);
	free(enemigosSPAWN);
	free(enemigos);
	return;
}