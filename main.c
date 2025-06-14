#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "./elementos/personagem.h"
#include "./elementos/joystick.h"

#define SCREEN_X 680
#define SCREEN_Y 430

void update_position(personagem *player){
    if (player->js->left){																																										//Se o botão de movimentação para esquerda do controle do primeiro jogador está ativado... (!)
		personagem_move(player, 1, 0, SCREEN_X, SCREEN_Y);																																				//Move o quadrado do primeiro jogador para a esquerda (!)
		//if (collision_2D(player_1, player_2)) square_move(player_1, -1, 0, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
	if (player->js->right){																																										//Se o botão de movimentação para direita do controle do primeir ojogador está ativado... (!)
		personagem_move(player, 1, 1, SCREEN_X, SCREEN_Y);																																				//Move o quadrado do primeiro jogador para a direta (!)
		//if (collision_2D(player_1, player_2)) square_move(player_1, -1, 1, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
}

int main(void){
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    

    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(SCREEN_X, SCREEN_Y);
    //ALLEGRO_BITMAP *bitmap = NULL;

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    personagem *player = personagem_create(40, 70, 60, 350, SCREEN_X, SCREEN_Y);
    if(!player) return 1;
    //bitmap = al_load_bitmap("./sprites/Cowboy/Cowboy4_idle without gun_0.png");
    //assert(bitmap != NULL);
    
    //float x = 0;
    //int width = al_get_display_width(disp);
    ALLEGRO_EVENT event;

    //

    al_start_timer(timer);

    while(1){

        al_wait_for_event(queue, &event);
        
        if(event.type == ALLEGRO_EVENT_TIMER){
    
            update_position(player);	
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(player->x - player->side_x/2, player->y - player->side_y/2,
                player->x + player->side_x/2, player->y + player->side_y/2, al_map_rgb(255, 0, 0));
            al_flip_display();
        }

        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_KEY_UP)){
			if (event.keyboard.keycode == ALLEGRO_KEY_A) joystick_left(player->js);
			else if (event.keyboard.keycode == ALLEGRO_KEY_D) joystick_right(player->js);
			else if (event.keyboard.keycode == ALLEGRO_KEY_W) joystick_up(player->js);
			else if (event.keyboard.keycode == ALLEGRO_KEY_S) joystick_down(player->js);
		}

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
    }
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    //al_destroy_bitmap(bitmap);
    al_destroy_event_queue(queue);

    return 0;
}