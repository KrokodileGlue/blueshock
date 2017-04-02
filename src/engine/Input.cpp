#include "Input.h"

#include <algorithm>
#include <iostream>

InputHandler* InputHandler::singleton;

void InputHandler::updateInput()
{
	keys_pressed.clear();
	keys_released.clear();

	for (auto e : input_events) {
		int key = e.key.keysym.sym;

		if (e.type == SDL_KEYDOWN) {
			if (!isKeyDown(key)) {
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

void InputHandler::addKeyEvent(SDL_Event e)
{
	input_events.push_back(e);
}

bool InputHandler::isKeyDown(int key)
{
	return std::find(keys_down.begin(), keys_down.end(), key) != keys_down.end();
}

bool InputHandler::isKeyPressed(int key)
{
	return std::find(keys_pressed.begin(), keys_pressed.end(), key) != keys_pressed.end();
}

bool InputHandler::isKeyReleased(int key)
{
	return std::find(keys_released.begin(), keys_released.end(), key) != keys_released.end();
}
