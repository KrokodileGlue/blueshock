#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"
#include "selene.h"

#include "InputSystem.h"
#include "ModelSystem.h"
#include "Camera.h"
#include "Renderer.h"
#include "ScriptSystem.h"

struct Scene {
	void update();
	void render(Renderer& renderer, Camera& camera, glm::mat4 proj_mat);
	void addModelComponent(int id, Model& model);
	void addInputComponent(int id);
	void addScriptComponent(int id, const std::string& path);
private:
	MessageBus message_bus;
	InputSystem input_system;
	ModelSystem model_system;
	ScriptSystem script_system;
};

#endif
