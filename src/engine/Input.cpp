#include "Input.h"

#include <algorithm>
#include <vector>
#include <iostream>

namespace sia {

std::vector<int> keys_pressed;
std::vector<int> keys_released;
std::vector<int> keys_down;

std::vector<SDL_Event> input_events;

void sia::input_add_key_event(SDL_Event e)
{
	input_events.push_back(e);
}

void sia::update_input()
{
	keys_pressed.clear();
	keys_released.clear();

	for (auto e : input_events) {
		int key = e.key.keysym.sym;
		
		if (e.type == SDL_KEYDOWN) {
			if (!is_key_down(key)) {
				keys_pressed.push_back(key);
			}
			keys_down.push_back(key);
		}
		else if (e.type == SDL_KEYUP) {
			// remove the released key from the list
			keys_down.erase(std::remove(keys_down.begin(), keys_down.end(), key), keys_down.end());
			keys_released.push_back(key);
		}
	}

	input_events.clear();

#if 0
	for (auto key : keys_pressed)  std::cerr << "key " << key << " pressed\n";
	for (auto key : keys_released) std::cerr << "key " << key << " released\n";
	for (auto key : keys_down)     std::cerr << "key " << key << " is down!\n";
#endif
}

bool sia::is_key_down(int key)
{
	return std::find(keys_down.begin(), keys_down.end(), key) != keys_down.end();
}

bool sia::is_key_pressed(int key)
{
	return std::find(keys_pressed.begin(), keys_pressed.end(), key) != keys_pressed.end();
}

bool sia::is_key_released(int key)
{
	return std::find(keys_released.begin(), keys_released.end(), key) != keys_released.end();
}

}
