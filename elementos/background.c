#include <stdlib.h>
#include "background.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>

background *init_background(int x, int y, float vlx, float vly, int width, int height,
    int dirx, int diry, ALLEGRO_BITMAP *image){
        background *new_background = (background *) malloc(sizeof(background));
        
        if(!new_background){
            return NULL;
        }

        new_background->x = x;
        new_background->y = y;
        new_background->vlx = vlx;
        new_background->vly = vly;
        new_background->dirx = dirx;
        new_background->diry = diry;
        new_background->image = image;

        return new_background;
    }
void update_background(background *back){
    back->x+= back->vlx * back->dirx;
    if(back->x + back->width <= 0)
        back->x = 0;
}
void draw_background(background *back){

    al_draw_bitmap(back->image, back->x, back->y, 0);

    if(back->x + back->width < 620){
        al_draw_bitmap(back->image, back->x+ back->width, back->y, 0);
    }
}