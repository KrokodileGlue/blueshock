#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

namespace sia {

void update_input();
void input_add_key_event(SDL_Event e);

bool is_key_down(int key);
bool is_key_pressed(int key);
bool is_key_released(int key);

}

#endif
