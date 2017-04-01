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

void ModelSystem::update()
{
	std::vector<Message>& messages = MessageBus::getSingleton()->getMessages();
	for (auto& m : messages) {
		if (m.type == MessageType::MOVE_MODEL) {
			auto model = models.find(m.entity);
			model->second.pos.x += m.arg1;
			model->second.pos.y += m.arg2;
		}
	}
}
