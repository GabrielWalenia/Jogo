#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include "joystick.h"
typedef struct{
    char side_x;
    char side_y;
    int x;
    int y;
    //unsigned char hp; -> cenas para proximos capitulos
    joystick *js;
} personagem; 

personagem *personagem_create(char side_x, char side_y, int x, int y, int max_x, int max_y);
void personagem_move(personagem *player, int steps, char trajectory, int max_x, int max_y);
void personagem_destroy(personagem *element);
#endif