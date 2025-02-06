#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void copyMap(MAP* destination, MAP* origin) {
	destination->lines = origin->lines;
	destination->columns = origin->columns;

	allocMap(destination);
	for (int i = 0; i < origin->lines; i++) {
		for (int j = 0; j < origin->columns; j++) {
			destination->matriz[i][j] = origin->matriz[i][j];
		}
	}
}

void walkOnTheMap(MAP* m, int originX, int originY, int newX, int newY) {
	char hero = m->matriz[originX][originY];
	m->matriz[newX][newY] = hero;
	m->matriz[originX][originY] = EMPTY;
}

int isEmpty(MAP* m, int x, int y) {
	return m->matriz[x][y] == EMPTY;
}

int isValid(MAP* m, int x, int y) {
	if (x >= m->lines) return 0;
	if (y >= m->columns) return 0;
	return 1;
}

void findMap(MAP* m, POSITION* p, char c) {
	for (int i = 0; i < m->lines; i++) {
		for (int j = 0; j < m->columns; j++) {
			if (m->matriz[i][j] == c) {
				p->x = i;
				p->y = j; 
				break;
			}
		}
	}
}

void releaseMap(MAP* m) {
	for (int i = 0; i < m->lines; i++) {
		free(m->matriz[i]);
	}
	free(m->matriz);
}

void readMap(MAP* m) {
	FILE* file;
	file = fopen("map.txt", "r");
	if (file == 0) {
		printf("Erro na leitura do mapa.\n");
		exit(1);
	}

	fscanf(file, "%d %d", &m->lines, &m->columns);

	allocMap(m);

	for (int i = 0; i <= 4; i++) {
		fscanf(file, "%s", m->matriz[i]);
	}

	fclose(file);
}

void allocMap(MAP* m) {
	m->matriz = malloc(sizeof(char*) * m->lines);

	for (int i = 0; i < m->lines; i++) {
		m->matriz[i] = malloc(sizeof(char) * (m->columns + 1));
	}
}

void drawMap(MAP* m) {
	for (int i = 0; i <= 4; i++) {
		printf("%s\n", m->matriz[i]);
	}
}