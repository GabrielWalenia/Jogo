#include <stdlib.h>
#include <stdio.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro5.h>
#include "inimigo.h"

inimigo *inimigo_create( char side_x, char side_y, char face, int x, int y, int max_x, int max_y,
    ALLEGRO_BITMAP *sprite, char hp){
    if((x-side_x/2<0) || (x+side_x/2>max_x) || (y-side_y/2<0) || (y+side_y/2>max_y)) return NULL;
    

    if(!sprite){
        printf("Bitmap não encontrado!");
        return NULL;
    }

    inimigo *enemy = (inimigo *)malloc(sizeof(inimigo));

    if(!enemy) return NULL;

    enemy->gun = arma_create();
    if(!enemy->gun){
        free(enemy);
        return NULL;
    }
    enemy->sprite = sprite;
    enemy->side_x = side_x;
    enemy->side_y = side_y;
    enemy->face = face;
    enemy->x = x;
    enemy->y = y;
    enemy->hp = hp;
    enemy->falling = true;
    
    return enemy;


}
void inimigo_move(inimigo *enemy, int steps, char trajectory, int max_x, int max_y){
    if (!trajectory){ 
        if ((enemy->x - steps*ENEMY_STEPS) - (enemy->side_x/2) >= 0) enemy->x = enemy->x - steps*ENEMY_STEPS;
        else enemy->face = 1;
    }
    else if(trajectory == 1){
        if(((enemy->x + steps*ENEMY_STEPS)+(enemy->side_x)/2) <= max_x) enemy->x = enemy->x + steps*ENEMY_STEPS;
        else enemy->face = 0;
    } 
}
void inimigo_destroy(inimigo *enemy){
    arma_destroy(enemy->gun);
    free(enemy);
}
void inimigo_shot(inimigo *enemy){
    municao *shot = NULL;

	if (!enemy->face) shot = arma_shot(enemy->x - enemy->side_x/2, enemy->y, enemy->face, enemy->gun, al_load_bitmap("./sprites/bullets/b_left.png"));										
	else if (enemy->face == 1) shot = arma_shot(enemy->x + enemy->side_x/2, enemy->y, enemy->face, enemy->gun, al_load_bitmap("./sprites/bullets/b_right.png"));	
    
	if (shot) enemy->gun->disparos = shot;
}