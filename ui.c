#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "ui.h"

char ghostDrawing[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char wallDrawing[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char heroDrawing[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char pillDrawing[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char emptyDrawing[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void drawPart(char design[4][7], int part) {
	printf("%s", design[part]);
}

void drawMap(MAP* m) {
	for (int i = 0; i < m->lines; i++) {
		for (int part = 0; part < 4; part++) {
			for (int j = 0; j < m->columns; j++) {
				switch (m->matriz[i][j]) {
					case GHOST:
						drawPart(ghostDrawing, part);
						break;
					case HERO:
						drawPart(heroDrawing, part);
						break;
					case PILL:
						drawPart(pillDrawing, part);
						break;
					case VERTICAL_WALL:
					case HORIZONTAL_WALL:
						drawPart(wallDrawing, part);
						break;
					case EMPTY:
						drawPart(emptyDrawing, part);
						break;
				}
			}
			printf("\n");
		}
	}
}
