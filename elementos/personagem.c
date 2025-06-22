#include <stdlib.h>
#include <stdio.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro5.h>
#include "personagem.h"
#include "joystick.h"
#include "municao.h"

#define PLAYER_STEPS 10
#define CHAO 460

personagem *personagem_create(char side_x, char side_y, char face, int x, int y, 
  int max_x, int max_y, ALLEGRO_BITMAP *sprite, char hp){
    if((x-side_x/2<0) || (x+side_x/2>max_x) || (y-side_y/2<0) || (y+side_y/2>max_y)) return NULL;
    
    if(!sprite){
        printf("Bitmap não encontrado!");
        return NULL;
    }
    personagem *player = (personagem *)malloc(sizeof(personagem));

    if(!player) return NULL;

    player->js = joystick_create();

    if(!player->js){
        free(player);
        return NULL;
    }
    player->gun = arma_create();
    if(!player->gun){
        joystick_destroy(player->js);
        free(player);
        return NULL;
    }
    player->sprite = sprite;
    player->falling = true;
    player->side_x = side_x;
    player->side_y = side_y;
    player->face = face;
    player->x = x;
    player->y = y;
    player->hp = hp;
    
    return player;

}

void personagem_move(personagem *player, int steps, char trajectory, int max_x, int max_y){

    if (!trajectory){ if ((player->x - steps*PLAYER_STEPS) - (player->side_x/2) >= 0) player->x = player->x - steps*PLAYER_STEPS;}
    else if(trajectory == 1){
        if(((player->x + steps*PLAYER_STEPS)+(player->side_x)/2) <= max_x) player->x = player->x + steps*PLAYER_STEPS;
    } 
    else if(trajectory == 2){
        if(player->y >= CHAO - 20 && player->js->up){
            player->falling = false;
            player->y -= 2;
        } else {
            player->falling = true;
        }
    }
    else if (trajectory == 3){
        if ((player->y + steps*PLAYER_STEPS) + player->side_y/2 <= max_y) player->y = player->y + steps*PLAYER_STEPS;}
}
void personagem_shot(personagem *player){																														
	municao *shot = NULL;

	if (!player->face) shot = arma_shot(player->x - player->side_x/2, player->y, player->face, player->gun, al_load_bitmap("./sprites/bullets/b_left.png"));
	else if (player->face == 1) shot = arma_shot(player->x + player->side_x/2, player->y, player->face, player->gun, al_load_bitmap("./sprites/bullets/b_right.png"));	
    else if (player->face == 2) shot = arma_shot(player->x, player->y - player->side_y/2, player->face, player->gun, al_load_bitmap("./sprites/bullets/b_up.png"));
    else if (player->face == 3) shot = arma_shot(player->x, player->y + player->side_y/2, player->face, player->gun, al_load_bitmap("./sprites/bullets/b_down.png"));						
	if (shot) player->gun->disparos = shot;
}
void personagem_destroy(personagem *player){
    joystick_destroy(player->js);	
    arma_destroy(player->gun);
    free(player);
}
