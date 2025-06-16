#ifndef __ARMA__
#define __ARMA__
#include "municao.h"

#define PISTOL_COOLDOWN 10

typedef struct{
    char timer;	
    //void *portador;
    municao *disparos;
    
} arma;

arma *arma_create();
municao *arma_shot(int x, int y, char trajectory, arma *gun);
void arma_destroy(arma *gun);
#endif