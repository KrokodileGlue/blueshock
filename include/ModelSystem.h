#ifndef MODEL_SYSTEM_H
#define MODEL_SYSTEM_H

#include "Model.h"
#include "Renderer.h"

#include <map>

class ModelSystem {
	std::map<int, Model> models;
public:
	void addModel(int id, Model model) {
		models.insert(std::make_pair(id, model));
	}
	
	void render(Renderer& renderer, Camera& camera, glm::mat4 proj_mat);
	void update();
};

#endif
