#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <vector>

class InputSystem {
	std::vector<int> entities;
public:
	void update();
	void addEntity(int entity) { entities.push_back(entity); };
};

#endif
