#include <stdio.h>
#include <stdlib.h>
#include "run-game.h"

struct map m;

void releaseMap() {
	for (int i = 0; i < m.lines; i++) {
		free(m.matriz[i]);
	}
	free(m.matriz);
}

void readMap() {
	FILE* file;
	file = fopen("map.txt", "r");
	if (file == 0) {
		printf("Erro na leitura do mapa.\n");
		exit(1);
	}

	fscanf(file, "%d %d", &m.lines, &m.columns);

	allocMap();

	for (int i = 0; i <= 4; i++) {
		fscanf(file, "%s", m.matriz[i]);
	}

	fclose(file);
}

void allocMap() {
	m.matriz = malloc(sizeof(char*) * m.lines);

	for (int i = 0; i < m.lines; i++) {
		m.matriz[i] = malloc(sizeof(char) * (m.columns + 1));
	}
}

void drawMap() {
	for (int i = 0; i <= 4; i++) {
		printf("%s\n", m.matriz[i]);
	}
}

int finish() {
	return 0;
}

void move(char direction) {
	int x;
	int y;

	for (int i = 0; i < m.lines; i++) {
		for (int j = 0; j < m.columns; j++) {
			if (m.matriz[i][j] == '@') {
				x = i;
				y = j; 
				break;
			}
		}
	}

	switch(direction) {
		case 'a': 
			m.matriz[x][y-1] = '@';
			break;
		case 'd':
			m.matriz[x][y+1] = '@';
			break;
		case 's':
			m.matriz[x+1][y] = '@';
			break;
		case 'w':
			m.matriz[x-1][y] = '@';
	}

	m.matriz[x][y] = '.';
 }

int main() {
	readMap();

	do {
		drawMap();
		char command;
		scanf(" %c", &command);
		move(command);
	} while(!finish());

	releaseMap();
}
