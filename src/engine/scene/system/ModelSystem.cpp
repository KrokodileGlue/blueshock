#include <vector>

#include "ModelSystem.h"
#include "MessageBus.h"
#include "Renderer.h"
#include "Camera.h"

void ModelSystem::render(Renderer& renderer, Camera& camera, glm::mat4 proj_mat)
{
	for (auto m : models) {
		renderer.renderModel(m.second, camera, proj_mat);
	}
}

void ModelSystem::update(MessageBus& message_bus)
{
	std::vector<Message>& messages = message_bus.getMessages();
	for (auto& m : messages) {
		auto model = models.find(m.entity);
		if (model == models.end()) continue; /* the entity does not have a model,
		                                      * theoretically this should log a warning or something */

		switch (m.type) {
			case MessageType::ENTITY_MOVE:
				model->second.pos.x += m.arg1;
				model->second.pos.y += m.arg2;
				break;
			case MessageType::ENTITY_CENTER:
				model->second.pos.x = 0;
				model->second.pos.y = 0;
				break;
		}
	}
}
