#ifndef __OBJETOS__
#define __OBJETOS__

#include <allegro5/bitmap.h>

struct objetos{
    int wx, wy, x, y, width, height;
    ALLEGRO_BITMAP *image;
};

#endif