#include "ScriptSystem.h"

void ScriptSystem::addScript(int id, const std::string& path)
{
	sel::State state {true};
	state.Load(path);

	scripts.insert(std::make_pair(id, std::move(state)));
}

void ScriptSystem::update(MessageBus& message_bus)
{
	for (auto& script : scripts) {
		script.second["update"]();
	}
}
