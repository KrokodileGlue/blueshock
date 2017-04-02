#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "MessageBus.h"

#include <vector>

class InputSystem {
	std::vector<int> entities;
public:
	void update(MessageBus& message_bus);
	void addEntity(int entity) { entities.push_back(entity); };
};

#endif
