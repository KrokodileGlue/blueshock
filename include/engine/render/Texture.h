#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "GL/glew.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "engine/io/TextureLoader.h"

class Texture {
public:
	Texture(const std::string& path) {
		id = load_texture(path);
	}
	std::string type; /* make this an enum or something */
	GLuint id;
private:
	aiString path;
};

#endif