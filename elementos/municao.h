#ifndef __MUNICAO__
#define __MUNICAO__
#include "arma.h"
typedef struct{
    unsigned int dano;
    char tipo;
} municao;

municao municao_create(arma *gun);
void municao_destroy(municao);
#endif