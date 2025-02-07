#ifndef _RUN_H_
#define _RUN_H_

#define TOP 'w'
#define BOTTOM 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'

int finish();
void move(char direction);
int isDirection(char direction);
void fanstasms();
void pillExplode();
void pillExplode2(int x, int y, int sumX, int sumY, int quantity);

#endif
