#ifndef __INIMIGO__
#define __INIMIGO__

typedef struct {
    unsigned char side_x;
    unsigned char side_y;
    unsigned int x;
    unsigned int y;
    //unsigned char hp; -> cenas para proximos capitulos

} inimigo;

inimigo *inimigo_create(unsigned char side_x, unsigned char side_y, unsigned int x, unsigned int y, unsigned int max_x, unsigned int max_y);
void inimigo_move();
void inimigo_destroy(inimigo *enemy);
#endif