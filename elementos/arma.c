#include <stdlib.h>
#include <stdio.h>
#include "personagem.h"
#include "joystick.h"
#include "arma.h"
#include "municao.h"

arma *arma_create(){

    arma *gun = (arma *) malloc(sizeof(arma));
    if(!gun) return NULL;
    gun->timer = 0;
    gun->disparos = NULL;
    return gun; 

}

municao *arma_shot(int x, int y, char trajectory, arma *gun, ALLEGRO_BITMAP *image){

    municao *shot = municao_create(x, y, trajectory, gun->disparos, image);
    if(!shot) return NULL;
    //printf("disparo");
    return shot;

}
void arma_destroy(arma *gun){
    municao *sentinel;
    for(municao *index = gun->disparos; index != NULL; index = sentinel){
        sentinel = (municao *) index->next;
        municao_destroy(index);
    }
    free(gun);
}