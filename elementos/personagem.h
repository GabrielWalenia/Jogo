#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include "joystick.h"
typedef struct{
    unsigned char side_x;
    unsigned char side_y;
    unsigned int x;
    unsigned int y;
    //unsigned char hp; -> cenas para proximos capitulos
    joystick *js;
} personagem; 

personagem *personagem_create(unsigned char side_x, unsigned char side_y, unsigned int x, unsigned int y, unsigned int max_x, unsigned int max_y);
void personagem_move();
void personagem_destroy(personagem *element);
#endif