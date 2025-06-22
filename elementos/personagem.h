#ifndef __PERSONAGEM__
#define __PERSONAGEM__

#include <stdbool.h>
#include <allegro5/bitmap.h>
#include "joystick.h"
#include "arma.h"
#include "municao.h"

typedef struct{
    char side_x;
    char side_y;
    char face;		
    int x;
    int y;
    char hp;
    joystick *js;
    arma *gun;		
    bool falling;
    ALLEGRO_BITMAP *sprite;
} personagem; 

personagem *personagem_create(char side_x, char side_y, char face, int x,
    int y, int max_x, int max_y, ALLEGRO_BITMAP *sprite, char hp);
void personagem_move(personagem *player, int steps, char trajectory, int max_x, int max_y);
void personagem_shot(personagem *player);
void personagem_destroy(personagem *element);
#endif