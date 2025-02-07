#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "run-game.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int hasPill = 0; 

int whereTheGhostGo(int originX, int originY, int* newX, int* newY) {
	int option[4][2] = {
		{originX, originY + 1},
		{originX + 1, originY},
		{originX, originY - 1},
		{originX - 1, originY}
	};

	srand(time(0));
	for (int i = 0; i < 10; i++) {
		int newPosition = rand() % 4;

		if (canWalk(&m, GHOST, option[newPosition][0], option[newPosition][1])) {
			*newX = option[newPosition][0];
			*newY = option[newPosition][1];
			return 1;
		}
	}

	return 0;
}

void ghosts() {
	MAP copy;
	copyMap(&copy, &m);

	for (int i = 0; i < m.lines; i++) {
		for (int j = 0; j < m.columns; j++) {
			if (copy.matriz[i][j] == GHOST) {
				int newX;
				int newY;

				int find = whereTheGhostGo(i, j, &newX, &newY);

				if (find) {
					walkOnTheMap(&m, i, j, newX, newY);
				}
			}
		}
	}

	releaseMap(&copy);
}

int finish() {
	POSITION position;
	int find = findMap(&m, &position, HERO);
	return !find;
}

int isDirection(char direction) {
	return direction != 'a' || direction != 's' || direction != 'd' || direction != 'w';
}

void move(char direction) {
	if (!isDirection(direction)) return;

	int nextX = hero.x;
	int nextY = hero.y;

	switch(direction) {
		case LEFT: 
			nextY--;
			break;
		case RIGHT:
			nextY++;
			break;
		case BOTTOM:
			nextX++;
			break;
		case TOP:
			nextX--;
			break;
	}

	if (!canWalk(&m, HERO, nextX, nextY)) return;

	if (isHero(&m, PILL, nextX, nextY)) {
		hasPill = 1;
	}

	walkOnTheMap(&m, hero.x, hero.y, nextX, nextY);
	hero.x = nextX;
	hero.y = nextY;
}

void pillExplode() {
	if(!hasPill) return;

	pillExplode2(hero.x, hero.y, 0, 1, 3);
	pillExplode2(hero.x, hero.y, 0, -1, 3);
	pillExplode2(hero.x, hero.y, 1, 0, 3);
	pillExplode2(hero.x, hero.y, -1, 0, 3);

	hasPill	= 0;
}

void pillExplode2(int x, int y, int sumX, int sumY, int quantity) {
	if (quantity == 0) return;

	int newX = x + sumX;
	int newY = y + sumY;

	if (!isValid(&m, newX, newY)) return;
	if (isWall(&m, newX, newY)) return;

	m.matriz[newX][newY] = EMPTY;
	pillExplode2(newX, newY, sumX, sumY, (quantity - 1));
}

int main() {
	readMap(&m);
	findMap(&m, &hero, HERO);

	do {
		printf("Tem pilula: %s\n", (hasPill ? "Sim" : "Nao"));
		drawMap(&m);

		char command;
		scanf(" %c", &command);
		move(command);

		if (command == BOMB) pillExplode();

		ghosts();
		system("cls");
	} while(!finish());

	releaseMap(&m);
}
