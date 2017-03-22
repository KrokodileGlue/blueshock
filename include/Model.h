#ifndef MODEL_H
#define MODEL_H

#include <iostream>

#include "GL/glew.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "glm/glm.hpp"

class Model {
public:
	Model(std::string path)
	{
		loadModel(path);
	}
	std::vector<Mesh> getMeshes() { return meshes; }
	glm::mat4 getModelMatrix();
	
	glm::vec3 pos, rot;
	float scale = 1.0f;
private:
	std::vector<Mesh> meshes;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
