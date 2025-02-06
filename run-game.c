#include <stdio.h>
#include <stdlib.h>
#include "run-game.h"
#include "map.h"

MAP m;
POSITION hero;

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
	} while(!finish());

	releaseMap(&m);
}
