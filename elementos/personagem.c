#include <stdlib.h>
#include "personagem.h"

void *personagem_destroy(personagem *elemento){
    free(elemento);
}