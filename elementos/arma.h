#ifndef __ARMA__
#define __ARMA__

#include <allegro5/bitmap.h>
#include "municao.h"

#define PISTOL_COOLDOWN 10

typedef struct{
    char timer;	
    //void *portador;
    municao *disparos;
    
} arma;

arma *arma_create();
municao *arma_shot(int x, int y, char trajectory, arma *gun, ALLEGRO_BITMAP* image);
void arma_destroy(arma *gun);
#endif