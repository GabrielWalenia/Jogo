#ifndef __INIMIGO__
#define __INIMIGO__

#include "arma.h"
#define ENEMY_STEPS 10

typedef struct {
    char side_x;
    char side_y;
    char face;
    int x;
    int y;
    arma *gun;
    //unsigned char hp; -> cenas para proximos capitulos

} inimigo;

inimigo *inimigo_create(char side_x, char side_y, char face, int x, int y, int max_x, int max_y);
void inimigo_move(inimigo *enemy, int steps, char trajectory, int max_x, int max_y);
void inimigo_destroy(inimigo *enemy);
void inimigo_shot(inimigo *enemy);
#endif