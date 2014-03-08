#include "cabecera.h"

void batalla()
{
	int k, i, j, l, m, RANDMAX, RANDMIN, numSpawn = 0, turno = 0, flecha = 1, update = 1, sel, printEnemy[4], numprintEnemy, dmgdealt;
	char mapaBatalla[5][11], mov;
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
	numenemigos = numenemigos / 4;
	enemigos = (STRUCTenemigos*)malloc(numenemigos * sizeof(STRUCTenemigos));
	rewind(FILEenemigos);
	for (k = 0; k < numenemigos; k++)
	{
		fscanf(FILEenemigos, "%s", enemigos[k].nombre);
		fscanf(FILEenemigos, "%d %d\n", &enemigos[k].minHP, &enemigos[k].maxHP);
		fscanf(FILEenemigos, "%d %d\n", &enemigos[k].minDmg, &enemigos[k].maxDmg);
		fscanf(FILEenemigos, "%d %d\n", &enemigos[k].minEXP, &enemigos[k].maxEXP);
		if (strcmp(enemigos[k].nombre, "Goblin") == 0)
			enemigos[k].graph = 'G';
	}
	enemigosSPAWN = (STRUCTenemigosSPAWN*)malloc(10 * sizeof(STRUCTenemigosSPAWN));
	for (k = 0; k < numenemigos; k++)
	{
		enemigos[k].num = rand() % 3 + 1;
		numSpawn = numSpawn + enemigos[k].num;
		enemigosSPAWN = (STRUCTenemigosSPAWN*)realloc(enemigosSPAWN, numSpawn * sizeof(STRUCTenemigosSPAWN));
		for (i = 0; i < enemigos[k].num; i++)
		{
			sprintf(enemigosSPAWN[i].nombre, "%s %d", enemigos[k].nombre, i + 1);
			enemigosSPAWN[i].minDmg = enemigos[k].minDmg;
			enemigosSPAWN[i].maxDmg = enemigos[k].maxDmg;
			enemigosSPAWN[i].graph = enemigos[k].graph;
			RANDMIN = enemigos[k].minHP;
			RANDMAX = enemigos[k].maxHP - enemigos[k].minHP;
			enemigosSPAWN[i].HP = rand() % RANDMAX + RANDMIN;
			RANDMIN = enemigos[k].minEXP;
			RANDMAX = enemigos[k].maxEXP - enemigos[k].minEXP;
			enemigosSPAWN[i].EXP = rand() % RANDMAX + RANDMIN;
			enemigosSPAWN[i].pos.X = rand() % 8 + 1;
			enemigosSPAWN[i].pos.Y = rand() % 3 + 1;
			if (enemigosSPAWN[i].pos.X == 4 && enemigosSPAWN[i].pos.Y == 3)
			{
				enemigosSPAWN[i].pos.X = rand() % 8 + 1;
				enemigosSPAWN[i].pos.Y = rand() % 3 + 1;
			}
			for (j = 0; j < i; j++)
			{
				if (enemigosSPAWN[i].pos.X == enemigosSPAWN[j].pos.X && enemigosSPAWN[i].pos.Y == enemigosSPAWN[j].pos.Y)
				{
					enemigosSPAWN[i].pos.X = rand() % 8 + 1;
					enemigosSPAWN[i].pos.Y = rand() % 3 + 1;
				}
			}
		}
	}
	fclose(FILEenemigos);
	do
	{
		if (personaje.HP <= 0)
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
			printf("  Huir\n");
			printf("\n\nHP: %d\n"
				"MP: %d\n", personaje.HP, personaje.MP);
			sel = flecha;
			flecha = menuFlecha(3, flecha);
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
						for (l = 1; l < numprintEnemy + 1; l++)
						{
							if (l == m)
								printf("->");
							printf("  %s  HP:%d\n", enemigosSPAWN[printEnemy[l - 1]].nombre, enemigosSPAWN[printEnemy[l - 1]].HP);
						}
						l = m;
						m = menuFlecha(numprintEnemy, m);
						if (m == 0)
						{
							turno++;
							RANDMIN = personaje.minDmg;
							RANDMAX = personaje.maxDmg - personaje.minDmg;
							dmgdealt = rand() % RANDMAX + RANDMIN;
							enemigosSPAWN[printEnemy[l - 1]].HP = enemigosSPAWN[printEnemy[l - 1]].HP - dmgdealt;
							printf("\nHas hecho %d de daño a %s!", dmgdealt, enemigosSPAWN[printEnemy[l - 1]].nombre);
							if (enemigosSPAWN[printEnemy[l - 1]].HP <= 0)
							{
								printf("\n%s ha muerto!\n\t|\n\tv", enemigosSPAWN[printEnemy[l - 1]].nombre);
								getch();
								numSpawn--;
								personaje.EXP = personaje.EXP + enemigosSPAWN[l - 1].EXP;
								mapaBatalla[enemigosSPAWN[printEnemy[l - 1]].pos.Y][enemigosSPAWN[printEnemy[l - 1]].pos.X] = '-';
								if (numSpawn == 0)
								{
									if (personaje.EXP >= personaje.LVL * 150)
									{
										personaje.EXP = personaje.EXP - personaje.LVL * 150;
										personaje.LVL++;
										personaje.STR = personaje.STR + personaje.LVL;
										personaje.HP = personaje.HP + personaje.LVL * 2;
										personaje.HPLEFT = personaje.HP;
										system("cls");
										printf("Has ganado 1 nivel!");
										getch();
									}
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
						{
							break;
						}
					} while (1);
					break;
				case 3:
					if (rand() % 3 == 0)
						return;
					printf("\nNo pudiste escapar!");
					getch();
					turno++;
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
				personaje.HP = personaje.HP - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				getch();
			}
			else if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X - 1] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje.HP = personaje.HP - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				getch();
			}
			else if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y + 1][enemigosSPAWN[turno - 1].pos.X] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje.HP = personaje.HP - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				getch();
			}
			else if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y - 1][enemigosSPAWN[turno - 1].pos.X] == '*')
			{
				RANDMIN = enemigosSPAWN[turno - 1].minDmg;
				RANDMAX = enemigosSPAWN[turno - 1].maxDmg - enemigosSPAWN[turno - 1].minDmg;
				dmgdealt = rand() % RANDMAX + RANDMIN;
				personaje.HP = personaje.HP - dmgdealt;
				printf("\nHas recibido %d de daño de %s!\n\t|\n\tv", dmgdealt, enemigosSPAWN[turno - 1].nombre);
				getch();
			}
			else
			{
				if (enemigosSPAWN[turno - 1].pos.X < pjBatalla.X)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X + 1] == 'G')
					{
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
					else
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.X++;
					}
				}
				else if (enemigosSPAWN[turno - 1].pos.X > pjBatalla.X)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X - 1] == 'G')
					{
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
					else
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.X--;
					}
				}
				else if (enemigosSPAWN[turno - 1].pos.Y < pjBatalla.Y)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y + 1][enemigosSPAWN[turno - 1].pos.X] == 'G')
					{
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
					else
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.Y++;
					}
				}
				else if (enemigosSPAWN[turno - 1].pos.Y > pjBatalla.Y)
				{
					if (mapaBatalla[enemigosSPAWN[turno - 1].pos.Y - 1][enemigosSPAWN[turno - 1].pos.X] == 'G')
					{
						if (turno == numSpawn)
							turno = 0;
						else
							turno++;
						continue;
					}
					else
					{
						update = 1;
						mapaBatalla[enemigosSPAWN[turno - 1].pos.Y][enemigosSPAWN[turno - 1].pos.X] = '-';
						enemigosSPAWN[turno - 1].pos.Y--;
					}
				}
			}
			if (turno == numSpawn)
				turno = 0;
			else
				turno++;
		}
		if (flecha == -1 || flecha == -2)
			flecha = sel;
	} while (1);
	free(enemigosSPAWN);
	free(enemigos);
	return;
}