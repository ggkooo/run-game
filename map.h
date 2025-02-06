#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '_'

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
void drawMap(MAP* m);
void findMap(MAP* m, POSITION* p, char c);
int isEmpty(MAP* m, int x, int y);
int isValid(MAP* m, int x, int y);
void walkOnTheMap(MAP* m, int originX, int originY, int newX, int newY);
void copyMap(MAP* destination, MAP* origin);