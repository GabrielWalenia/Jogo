#ifndef __BACKGROUND__
#define __BACKGROUND__

#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
typedef struct {
    int x , y;
    float vlx, vly;
    int dirx, diry;
    int width, height;
    ALLEGRO_BITMAP *image;       
}background;

background *init_background(int x, int y, float vlx, float vly, int width, int heigth,
    int dirx, int diry, ALLEGRO_BITMAP *image);
void update_background(background *back);
void draw_background(background *back);
#endif