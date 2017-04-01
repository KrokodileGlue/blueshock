#include "InputSystem.h"
#include "Input.h"
#include "MessageBus.h"

#define INPUT_SCALAR 0.05

void InputSystem::update()
{
	if (is_key_down(SDLK_w) || is_key_down(SDLK_UP)) {
		for (auto i : entities)
			MessageBus::getSingleton()->addMessage({ i, 0.0, 1.0 * INPUT_SCALAR, MessageType::MOVE_MODEL });
	}

	if (is_key_down(SDLK_s) || is_key_down(SDLK_DOWN)) {
		for (auto i : entities)
			MessageBus::getSingleton()->addMessage({ i, 0.0, -1.0 * INPUT_SCALAR, MessageType::MOVE_MODEL });
	}

	if (is_key_down(SDLK_a) || is_key_down(SDLK_LEFT)) {
		for (auto i : entities)
			MessageBus::getSingleton()->addMessage({ i, 1.0 * INPUT_SCALAR, 0.0, MessageType::MOVE_MODEL });
	}

	if (is_key_down(SDLK_d) || is_key_down(SDLK_RIGHT)) {
		for (auto i : entities)
			MessageBus::getSingleton()->addMessage({ i, -1.0 * INPUT_SCALAR, 0.0, MessageType::MOVE_MODEL });
	}
}
