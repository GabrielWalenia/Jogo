#include <stdlib.h>
#include "municao.h"

municao *municao_create(int x, int y, char trajectory, municao *next){
    municao *shot = (municao *) malloc(sizeof(municao));
    shot->x = x;
    shot->y = y;
    shot->trajectory = trajectory;
    shot->next = (struct municao*) next;
    return shot;
}
void municao_move(municao *shots){
    for(municao *index = shots; index != NULL; index = (municao*)index->next){
        if(!index->trajectory){index->x = index->x - BULLET_MOVE;}
        else index->x = index->x + BULLET_MOVE;
    }
}
void municao_destroy(municao *shot){
    free(shot);
}