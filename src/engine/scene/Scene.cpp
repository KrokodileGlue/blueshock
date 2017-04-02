#include "Scene.h"

#include "MessageBus.h"

void Scene::addModelComponent(int id, Model& model)
{
	model_system.addModel(id, model);
}

void Scene::addInputComponent(int id)
{
	input_system.addEntity(id);
}

void Scene::render(Renderer& renderer, Camera& camera, glm::mat4 proj_mat)
{
	model_system.render(renderer, camera, proj_mat);
}

void Scene::update()
{
	input_system.update(message_bus);
	model_system.update(message_bus);
	message_bus.clearMessages();
}
