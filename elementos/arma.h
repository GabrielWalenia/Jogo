#ifndef __ARMA__
#define __ARMA__
#include "municao.h"
typedef struct{
    void *portador;
    //unsigned int dano;
    municao *municao;
    
} arma;

arma *arma_create(void *portador);
void arma_destroy(arma *gun);
#endif