#include <stdio.h>
#include <stdlib.h>

int main() {
	char map[5][10+1];

	FILE* file;
	file = fopen("map.txt", "r");
	if (file == 0) {
		printf("Erro na leitura do mapa.\n");
		exit(1);
	}

	for (int i = 0; i <= 4; i++) {
		fscanf(file, "%s", map[i]);
	}

	for (int i = 0; i <= 4; i++) {
		printf("%s\n", map[i]);
	}

	fclose(file);
}
