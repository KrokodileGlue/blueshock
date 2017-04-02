#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include "SDL.h"

class InputHandler {
	static InputHandler* singleton;

	std::vector<int> keys_pressed;
	std::vector<int> keys_released;
	std::vector<int> keys_down;

	std::vector<SDL_Event> input_events;
public:
	static InputHandler* getSingleton() {
		if (singleton == nullptr) singleton = new InputHandler;
		return singleton;
	}

	void updateInput();
	void addKeyEvent(SDL_Event e);

	bool isKeyDown(int key);
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
};

#endif
