#include "InputSystem.h"
#include "Input.h"
#include "MessageBus.h"

#define INPUT_SCALAR 0.25

void InputSystem::update(MessageBus& message_bus)
{
	InputHandler* is = InputHandler::getSingleton();
	if (is->isKeyDown(SDLK_w) || is->isKeyDown(SDLK_UP)) {
		for (auto i : entities)
			message_bus.addMessage({ i, 0.0, 1.0 * INPUT_SCALAR, MessageType::ENTITY_MOVE });
	}

	if (is->isKeyDown(SDLK_s) || is->isKeyDown(SDLK_DOWN)) {
		for (auto i : entities)
			message_bus.addMessage({ i, 0.0, -1.0 * INPUT_SCALAR, MessageType::ENTITY_MOVE });
	}

	if (is->isKeyDown(SDLK_a) || is->isKeyDown(SDLK_LEFT)) {
		for (auto i : entities)
			message_bus.addMessage({ i, 1.0 * INPUT_SCALAR, 0.0, MessageType::ENTITY_MOVE });
	}

	if (is->isKeyDown(SDLK_d) || is->isKeyDown(SDLK_RIGHT)) {
		for (auto i : entities)
			message_bus.addMessage({ i, -1.0 * INPUT_SCALAR, 0.0, MessageType::ENTITY_MOVE });
	}

	if (is->isKeyPressed(SDLK_SPACE)) {
		for (auto i : entities)
			message_bus.addMessage({ i, -1, -1, MessageType::ENTITY_CENTER });
	}
}
