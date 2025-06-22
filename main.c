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
#include "./elementos/background.h"
#include "./elementos/objetos.h"
#define SCREEN_X 620
#define SCREEN_Y 480

char check_kill_enemy(personagem *killer, inimigo *victim){

	municao *previous = NULL;
	for (municao *index = killer->gun->disparos; index != NULL; index = (municao*) index->next){																													//Para todos os projéteis do atirador
		if ((index->x >= victim->x - victim->side_x/2) && (index->x <= victim->x + victim->side_x/2) && //																										//Verique se houve colisão com a vítima no eixo X
		   (index->y >= victim->y - victim->side_y/2) && (index->y <= victim->y + victim->side_y/2)){																											//Verifique se houve colisão com a vítima no eixo Y
			victim->hp--;																																													//Reduz o HP da vítima em uma unidade (!)
			if (victim->hp){																																												//Verifica se a vítima ainda tem HP (!)
				if (previous){																																												//Verifica se não é o primeiro elemento da lista de projéteis (!)
					previous->next = index->next;																																							//Se não for, salva o próximo projétil (!)
					municao_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = (municao*) previous->next;																																						//Atualiza para o próximo projétil (!)
				}
				else {																																														//Se for o primeiro projétil da lista (!)
					killer->gun->disparos = (municao*) index->next;																																				//Atualiza o projétil no início da lista (!)
					municao_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = killer->gun->disparos;																																								//Atualiza para o próximo projétil (!)
				}
				return 0;																																													//A vítima sofreu dano, mas ainda não morre (!)
			}
			else return 1;																																													//A vítima sofreu dano e morreu (!)
		}
		previous = index;																																													//Atualiza a variável de controle do projétil anterior (!)
	}
	return 0;			
}


char check_kill_player(inimigo *killer, personagem *victim){

	municao *previous = NULL;
	for (municao *index = killer->gun->disparos; index != NULL; index = (municao*) index->next){																													//Para todos os projéteis do atirador
		if ((index->x >= victim->x - victim->side_x/2) && (index->x <= victim->x + victim->side_x/2) && //																										//Verique se houve colisão com a vítima no eixo X
		   (index->y >= victim->y - victim->side_y/2) && (index->y <= victim->y + victim->side_y/2)){																											//Verifique se houve colisão com a vítima no eixo Y
			victim->hp--;																																													//Reduz o HP da vítima em uma unidade (!)
			if (victim->hp){																																												//Verifica se a vítima ainda tem HP (!)
				if (previous){																																												//Verifica se não é o primeiro elemento da lista de projéteis (!)
					previous->next = index->next;																																							//Se não for, salva o próximo projétil (!)
					municao_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = (municao*) previous->next;																																						//Atualiza para o próximo projétil (!)
				}
				else {																																														//Se for o primeiro projétil da lista (!)
					killer->gun->disparos = (municao*) index->next;																																				//Atualiza o projétil no início da lista (!)
					municao_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = killer->gun->disparos;																																								//Atualiza para o próximo projétil (!)
				}
				return 0;																																													//A vítima sofreu dano, mas ainda não morre (!)
			}
			else return 1;																																													//A vítima sofreu dano e morreu (!)
		}
		previous = index;																																													//Atualiza a variável de controle do projétil anterior (!)
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
		//personagem_move(player, 1, 3, SCREEN_X, SCREEN_Y);
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
    // velocidade da gravidade;
    int gravidade = 10;

    struct objetos bloco[7][15];

    int chao_height = 48;
    //int chao_width = 95;

    int n_inimigos_eliminados = 0;
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    
    ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_DISPLAY *disp = al_create_display(SCREEN_X, SCREEN_Y);
    
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    background *back = init_background(0, -SCREEN_Y+150, 1, 0, SCREEN_X, SCREEN_Y, 1, 0, al_load_bitmap("./sprites/fundo_fase_1.jpg"));
    personagem *player = personagem_create(45, 47, 1, SCREEN_X/2, SCREEN_Y/2, SCREEN_X, SCREEN_Y-20, al_load_bitmap("./sprites/Cowboy/Cowboy4_idle with gun_0.png"), 5);
    inimigo *enemy = inimigo_create(45, 47, 0, SCREEN_X-25, SCREEN_Y/2, SCREEN_X, SCREEN_Y-20, al_load_bitmap("./sprites/Gangster/Cowboy2_idle with gun_0.png"), 5);
    
    
    if(!player) return 1;
    if(!enemy) return 1;
    
    for(int i = 0; i<7; i++){
        for(int j = 0; j<15; j++){
            bloco[i][j].y = SCREEN_Y - chao_height;
            bloco[i][j].x = j*60;
            bloco[i][j].width = 62;
            bloco[i][j].height = 48;
            bloco[i][j].wy = 390;
            bloco[i][j].image = al_load_bitmap("./sprites/chao/chao62x48.png");
        }
    }

    ALLEGRO_EVENT event;

    //
    char player_kill = 0;
    char enemy_kill = 0;
    al_start_timer(timer);

    while(1){
        al_wait_for_event(queue, &event);
        if (player_kill){								
			al_clear_to_color(al_map_rgb(0, 0, 0));	
			
			al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_X/2, SCREEN_Y/2, 0, "GAME OVER");
			
			al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_X/2 - 110, SCREEN_Y/2 + 5, 0, "PRESSIONE ESPAÇO PARA SAIR");
			al_flip_display();																																								

			if ((event.type == ALLEGRO_EVENT_KEY_DOWN) && (event.keyboard.keycode == ALLEGRO_KEY_SPACE)) break;																																
			else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break; 				

		}else if(enemy_kill){
            al_clear_to_color(al_map_rgb(0, 0, 0));	
			
			al_draw_text(font, al_map_rgb(0, 0, 255), SCREEN_X/2, SCREEN_Y/2, 0, "VICTORY");
			
			al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_X/2 - 110, SCREEN_Y/2 + 5, 0, "PRESSIONE ESPAÇO PARA SAIR");
			al_flip_display();																																								

			if ((event.type == ALLEGRO_EVENT_KEY_DOWN) && (event.keyboard.keycode == ALLEGRO_KEY_SPACE)) break;																																
			else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break; 
        }
        else{

            
        
            if(event.type == ALLEGRO_EVENT_TIMER){
                
                update_position(player, enemy);	
                player_kill = check_kill_player(enemy, player);																																						//Verifica se o primeiro jogador matou o segundo jogador
				enemy_kill = check_kill_enemy(player, enemy);
                if(enemy_kill){
                    n_inimigos_eliminados++;
                }
                if(n_inimigos_eliminados){
                        inimigo *chefe = inimigo_create(25, 35, 0, SCREEN_X-45, SCREEN_Y/2, SCREEN_X, SCREEN_Y-20,
                            al_load_bitmap("./sprites/Gangster/Cowboy2_idle with gun_0.png"), 30);
                       if(!chefe) return 1;
                }
                

                //al_clear_to_color(al_map_rgb(0, 0, 0));
                //update_background(back);
                draw_background(back);
                //al_draw_filled_rectangle(0, SCREEN_Y-20, SCREEN_X, SCREEN_Y, al_map_rgb(0,0, 255));
                for(int i = 0; i<7; i++){
                    for(int j = 0; j<15; j++){
                        al_draw_bitmap(bloco[i][j].image, bloco[i][j].x, bloco[i][j].y, 0);

                        if (collision_2D(player->x, player->y, player->side_x, player->side_y, bloco[i][j].x, bloco[i][j].y,
                            bloco[i][j].width, bloco[i][j].height)){
                            player->falling = false;
                            //   printf("retornou");
                        }

                        if (collision_2D(enemy->x, enemy->y, enemy->side_x, enemy->side_y, bloco[i][j].x, bloco[i][j].y,
                            bloco[i][j].width, bloco[i][j].height)){
                            enemy->falling = false;
                            //   printf("retornou");
                        }
                    }
                }

                // código para fazer o personagem cair
                if(player->falling){
                    player->y += gravidade;
                }
                if(enemy->falling){

                    enemy->y += gravidade;
                }

               

                al_draw_filled_rectangle(player->x - player->side_x/2, player->y - player->side_y/2,
                player->x + player->side_x/2, player->y + player->side_y/2, al_map_rgb(255, 0, 0));

                al_draw_filled_rectangle(enemy->x - enemy->side_x/2, enemy->y - enemy->side_y/2,
                enemy->x + enemy->side_x/2, enemy->y + enemy->side_y/2, al_map_rgb(0, 0, 255));

                al_draw_bitmap(player->sprite, player->x-25, player->y-47, 0);
                al_draw_bitmap(enemy->sprite, enemy->x-25, enemy->y-47, 0);
                for (municao *index = player->gun->disparos; index != NULL; index = (municao*) index->next)
                    al_draw_bitmap(index->image, index->x, index->y,0);
                if (player->gun->timer) player->gun->timer-=1;
                
                //inimigo_shot(enemy);
                for (municao *index = enemy->gun->disparos; index != NULL; index = (municao*) index->next)
                  al_draw_bitmap(index->image, index->x, index->y,0);
                if (enemy->gun->timer) enemy->gun->timer-=1;

                player->falling = true;
                enemy->falling = true;
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
    al_destroy_bitmap(player->sprite);
    al_destroy_bitmap(enemy->sprite);
    al_destroy_event_queue(queue);

    return 0;
}