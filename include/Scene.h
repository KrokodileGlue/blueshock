#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "InputSystem.h"
#include "ModelSystem.h"
#include "Camera.h"
#include "Renderer.h"

struct Scene {
	void update();
	void render(Renderer& renderer, Camera& camera, glm::mat4 proj_mat);
	void addModelComponent(int id, Model& model);
	void addInputComponent(int id);
private:
	InputSystem input_system;
	ModelSystem model_system;
};

#endif
