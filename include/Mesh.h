#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include "assimp/Importer.hpp"
#include "GL/glew.h"
#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 pos, normal;
	glm::vec2 tex_coord;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices,
		std::vector<GLuint> indices,
		std::vector<Texture> textures)
		: vertices(vertices), indices(indices), textures(textures)
	{
		setupMesh();
	}
	GLuint getVAO() { return vao; }
	size_t getNumIndices() { return indices.size(); }
	std::vector<Texture> getTextures() { return textures; }
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	GLuint vao, vbo, ebo;
	void setupMesh();
};

#endif
