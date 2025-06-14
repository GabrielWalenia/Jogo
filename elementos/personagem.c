#include <stdlib.h>
#include <stdio.h>
#include "personagem.h"
#include "joystick.h"

#define PLAYER_STEPS 20

personagem *personagem_create(char side_x, char side_y, int x, int y, 
  int max_x, int max_y){
    if((x-side_x/2<0) || (x+side_x/2>max_x) || (y-side_y/2<0) || (y+side_y/2>max_y)) return NULL;
        
    personagem *player = (personagem *)malloc(sizeof(personagem));

    if(!player) return NULL;

    player->js = joystick_create();

    if(!player->js){
        free(player);
        return NULL;
    }

    player->side_x = side_x;
    player->side_y = side_y;
    player->x = x;
    player->y = y;
    
    return player;

}

void personagem_move(personagem *player, int steps, char trajectory, int max_x, int max_y){
    //printf("x: %d", player->x);
    unsigned int conta = (player->x - steps*PLAYER_STEPS) - (player->side_x/2);
    printf("%d\n", conta);
    if (!trajectory){ if ((player->x - steps*PLAYER_STEPS) - (player->side_x/2) >= 0) player->x = player->x - steps*PLAYER_STEPS;}
    else if(trajectory == 1){
        if(((player->x + steps*PLAYER_STEPS)+(player->side_x)/2) <= max_x) player->x = player->x + steps*PLAYER_STEPS;
    } 
}
void personagem_destroy(personagem *player){
    joystick_destroy(player->js);	
    free(player);
}