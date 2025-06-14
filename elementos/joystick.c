#include <stdlib.h>
#include "joystick.h"

joystick *joystick_create(){
    joystick *js = (joystick*) malloc (sizeof(joystick));
    if(!js) return NULL;
	js->right = 0;
	js->left = 0;
	js->up = 0;
	js->down = 0;
	return js;	
}
void joystick_destroy(joystick *js){
    free(js);
}
void joystick_left(joystick *js){
    js->left = js->left ^ 1;
}
void joystick_right(joystick *js){
    js->right = js->right ^ 1;
}
void joystick_up(joystick *js){
    js->up = js->up ^ 1;
}
void joystick_down(joystick *js){
    js->down = js->down ^ 1;
}
/*void joystick_fire(joystick *js){
    js->fire = js->fire ^ 1;
}*/