#ifndef MODEL_H
#define MODEL_H

#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "engine/render/Mesh.h"
#include "engine/io/ModelLoader.h"

class Model {
public:
	Model(std::string path) {
		meshes = load_model(path);
	}
	std::vector<Mesh> getMeshes() { return meshes; }
	glm::mat4 getModelMatrix();
	
	glm::vec3 pos, rot;
	float scale = 1.0f;
private:
	std::vector<Mesh> meshes;
};

#endif
