#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include <stdbool.h>
#include "joystick.h"
#include "arma.h"
#include "municao.h"

typedef struct{
    char side_x;
    char side_y;
    char face;		
    int x;
    int y;
    //unsigned char hp; -> cenas para proximos capitulos
    joystick *js;
    arma *gun;		
    bool falling;
} personagem; 

personagem *personagem_create(char side_x, char side_y, char face, int x, int y, int max_x, int max_y);
void personagem_move(personagem *player, int steps, char trajectory, int max_x, int max_y);
void personagem_shot(personagem *player);
void personagem_destroy(personagem *element);
void personagem_jump(personagem player, int max_x, int max_y);
#endif