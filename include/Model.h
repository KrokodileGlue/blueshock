#ifndef MODEL_H
#define MODEL_H

#include "GL/glew.h"
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model {
public:
	Model(std::string path)
	{
		loadModel(path);
	}
	std::vector<Mesh> getMeshes() { return meshes; }
private:
	std::vector<Mesh> meshes;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
