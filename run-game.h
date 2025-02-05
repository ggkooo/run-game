void releaseMap();
void readMap();
void allocMap();
void drawMap();
int finish();
void move(char direction);

struct map {
	char** matriz;
	int lines;
	int columns;
};
