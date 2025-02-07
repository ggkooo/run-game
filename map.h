#ifndef _MAP_H_
#define _MAP_H_

#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

struct map {
	char** matriz;
	int lines;
	int columns;
};

typedef struct map MAP;

struct position {
	int x;
	int y;
};

typedef struct position POSITION;

void releaseMap(MAP* m);
void readMap(MAP* m);
void allocMap(MAP* m);
int findMap(MAP* m, POSITION* p, char c);
int isEmpty(MAP* m, int x, int y);
int isValid(MAP* m, int x, int y);
void walkOnTheMap(MAP* m, int originX, int originY, int newX, int newY);
void copyMap(MAP* destination, MAP* origin);
int canWalk(MAP* m, char hero, int x, int y);
int isWall(MAP* m, int x, int y);
int isHero(MAP* m, char hero, int x, int y);

#endif
