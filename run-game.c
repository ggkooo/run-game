#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "run-game.h"
#include "map.h"

MAP m;
POSITION hero;

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

		if (isValid(&m, option[newPosition][0], option[newPosition][1]) && isEmpty(&m, option[newPosition][0], option[newPosition][1])) {
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
	return 0;
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

	if (!isValid(&m, nextX, nextY)) return;
	if (!isEmpty(&m, nextX, nextY)) return;

	walkOnTheMap(&m, hero.x, hero.y, nextX, nextY);
	hero.x = nextX;
	hero.y = nextY;
 }

int main() {
	readMap(&m);
	findMap(&m, &hero, HERO);

	do {
		drawMap(&m);
		char command;
		scanf(" %c", &command);
		move(command);
		ghosts();
	} while(!finish());

	releaseMap(&m);
}
