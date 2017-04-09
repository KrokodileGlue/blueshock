#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "selene.h"

#include <map>
#include <string>

#include "MessageBus.h"

class ScriptSystem {
	std::map <int, sel::State> scripts;
public:
	void addScript(int id, const std::string& path);
	void update(MessageBus& message_bus);
};

#endif
