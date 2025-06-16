#ifndef __MUNICAO__
#define __MUNICAO__


#define BULLET_MOVE 5
typedef struct{
    int dano;
    //char tipo;
    int x;																															//Local, no eixo x, onde se localiza a bala (!)
	int y;																															//Local, no eixo y, onde se localiza a bala (!)
	char trajectory;																													//Trajetória da bala
	struct municao *next; 			
} municao;

municao *municao_create(int x, int y, char trajectory, municao *next);
void municao_move(municao *shot);
void municao_destroy(municao *shot);
#endif