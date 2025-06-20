#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include "./elementos/personagem.h"
#include "./elementos/joystick.h"
#include "./elementos/arma.h"
#include "./elementos/municao.h"
#include "./elementos/inimigo.h"

#define SCREEN_X 620
#define SCREEN_Y 480

unsigned char check_kill(personagem *killer, personagem *victim){

    for(municao *index = killer->gun->disparos; index != NULL; index = (municao*) index->next){

        if((index->x >= victim->x - victim->side_x/2) &&(index->x<=index->x + victim->side_x/2) && 
          (index->y >= victim->y-victim->side_y/2) && (index->y<= victim->y+victim->side_y/2)){
            return 1;
        }
    }
    return 0;

}


char collision_2D(int Ax, int Ay, int A_side_x, int A_side_y,
    int Bx, int By, int B_side_x, int B_side_y){
    if ((((By-B_side_y/2 >= Ay-A_side_y/2) && (Ay+A_side_y/2 >= By-B_side_y/2)) ||
		((Ay-A_side_y/2 >= By-B_side_y/2) && (By+B_side_y/2 >= Ay-A_side_y/2))) && 	
		(((Bx-B_side_x/2 >= Ax-A_side_x/2) && (Ax+A_side_x/2 >= Bx-B_side_x/2)) || 	
		((Ax-A_side_x/2 >= Bx-B_side_x/2) && (Bx+B_side_x/2 >= Ax-A_side_x/2)))) {
            //printf("COLISAO");
            return 1;
        }	
	else return 0;
}

void update_bullets(personagem *player, inimigo *enemy){

    municao *previous = NULL;
    for(municao *index = player->gun->disparos; index != NULL;){

        if(!index->trajectory) index->x -= BULLET_MOVE;
        else if(index->trajectory == 1) index->x += BULLET_MOVE;
        else if(index->trajectory == 2) index->y -= BULLET_MOVE;
        else if(index->trajectory == 3) index->y += BULLET_MOVE;

        if((index->x<0)||(index->x>SCREEN_X)){
            if(previous){

                previous->next = index->next;
                municao_destroy(index);
                index = (municao *) previous->next;

            } else {

                player->gun->disparos = (municao *) index->next;
                municao_destroy(index);
                index = player->gun->disparos;

            }
        } else {
            previous = index;
            index = (municao *) index->next;
        }
    }

}
void update_position(personagem *player, inimigo *inimigo1){
    inimigo_move(inimigo1, 1, inimigo1->face, SCREEN_X, SCREEN_Y);
    //inimigo_shot(inimigo1);
    if (player->js->left){																																										
		personagem_move(player, 1, 0, SCREEN_X, SCREEN_Y);
        //personagem_sprite = al_load_bitmap("./sprites/Cowboy/Cowboy4_idle with gun_0.png");
        //al_draw_bitmap(personagem_sprite, player->x, player->y, 0);
        player->face = 0;																																				
		//if (collision_2D(player_1, player_2)) square_move(player_1, -1, 0, X_SCREEN, Y_SCREEN);																											
	}
	if (player->js->right){																																										
		personagem_move(player, 1, 1, SCREEN_X, SCREEN_Y);
        player->face = 1;																																				
		//if (collision_2D(player_1, player_2)) square_move(player_1, -1, 1, X_SCREEN, Y_SCREEN);																											
	}
    if (player->js->up){																																										
		personagem_move(player, 1, 2, SCREEN_X, SCREEN_Y);		
        player->face = 2;																																			
		//if (collision_2D(player_1, player_2)) square_move(player_1, -1, 1, X_SCREEN, Y_SCREEN);																											
	}
    if (player->js->down){																																									
		personagem_move(player, 1, 3, SCREEN_X, SCREEN_Y);
        player->face = 3;																												
		//if (collision_2D(player_1, player_2)) square_move(player_1, -1, 1, X_SCREEN, Y_SCREEN);																		
	}
    if (player->js->fire){																																							
		if (!player->gun->timer){	
            //printf("disparo");																																		
			personagem_shot(player); 																																					
			player->gun->timer = PISTOL_COOLDOWN;																																							
		} 
	}
    update_bullets(player,inimigo1);				
}

int main(void){
    // velocidade do personagem na posicao y
    int vly = 0;
    // velocidade da gravidade;
    int gravidade = 4;

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    
    //int frameWidth = 128;
    //int frameHeight = 128;

    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(SCREEN_X, SCREEN_Y);
    
    ALLEGRO_BITMAP *personagem_sprite;
    personagem_sprite = al_load_bitmap("./sprites/Cowboy/Cowboy4_idle with gun_0.png");

    if(!personagem_sprite){
        printf("Bitmap não encontrado!");
        return 1;
    }

    ALLEGRO_BITMAP *inimigo_sprite;
    inimigo_sprite = al_load_bitmap("./sprites/Gangster/Cowboy2_idle with gun_0.png");

    if(!inimigo_sprite){
        printf("Bitmap não encontrado!");
        return 1;
    }

    //al_set_window_title(disp, "fase 1");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    personagem *player = personagem_create(25, 35, 1, SCREEN_X/2, SCREEN_Y/2, SCREEN_X, SCREEN_Y-20);
    inimigo *enemy = inimigo_create(25, 35, 0, SCREEN_X-25, SCREEN_Y/2, SCREEN_X, SCREEN_Y-20);
    
    if(!player) return 1;
    
    ALLEGRO_EVENT event;

    //
    char pk = 0;
    al_start_timer(timer);

    while(1){

        if (pk){								
			al_clear_to_color(al_map_rgb(0, 0, 0));	
			
			if (pk) al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_X/2, SCREEN_Y/2, 0, "GAME OVER");
			
			al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_X/2 - 110, SCREEN_Y/2 + 5, 0, "PRESSIONE ESPAÇO PARA SAIR");
			al_flip_display();																																								

			if ((event.type == 10) && (event.keyboard.keycode == 75)) break;																																
			else if (event.type == 42) break; 				

		}else{

            al_wait_for_event(queue, &event);
        
            if(event.type == ALLEGRO_EVENT_TIMER){
    
                update_position(player, enemy);	
                // código para fazer o personagem cair
                if(player->falling){
                    vly += gravidade;
                    player->y += vly;
                }

                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(0, SCREEN_Y-20, SCREEN_X, SCREEN_Y, al_map_rgb(0,0, 255));

                if (collision_2D(player->x, player->y, player->side_x, player->side_y, SCREEN_X/2, SCREEN_Y-10, SCREEN_X, 20)){
                    player->falling = false;
                //   printf("retornou");
                } else{
                    player->falling = true;
                }

                al_draw_filled_rectangle(player->x - player->side_x/2, player->y - player->side_y/2,
                player->x + player->side_x/2, player->y + player->side_y/2, al_map_rgb(255, 0, 0));

                al_draw_filled_rectangle(enemy->x - enemy->side_x/2, enemy->y - enemy->side_y/2,
                enemy->x + enemy->side_x/2, enemy->y + enemy->side_y/2, al_map_rgb(0, 0, 255));

                al_draw_bitmap(personagem_sprite, player->x-14, player->y-37, 0);
                al_draw_bitmap(inimigo_sprite, enemy->x-14, enemy->y-37, 0);
                for (municao *index = player->gun->disparos; index != NULL; index = (municao*) index->next)
                  al_draw_filled_circle(index->x, index->y, 2, al_map_rgb(255, 0, 0));
                if (player->gun->timer) player->gun->timer-=1;

                for (municao *index = enemy->gun->disparos; index != NULL; index = (municao*) index->next)
                  al_draw_filled_circle(index->x, index->y, 2, al_map_rgb(255, 0, 0));
                if (enemy->gun->timer) enemy->gun->timer-=1;

                al_flip_display();
                
            }

            else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_KEY_UP)){
			    if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) joystick_left(player->js);
			    else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) joystick_right(player->js);
			    else if (event.keyboard.keycode == ALLEGRO_KEY_UP) joystick_up(player->js);
			    else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) joystick_down(player->js);
                else if (event.keyboard.keycode == ALLEGRO_KEY_X) joystick_fire(player->js);
		    }

            else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                break;
            }
        }
    }
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_bitmap(personagem_sprite);
    al_destroy_event_queue(queue);

    return 0;
}