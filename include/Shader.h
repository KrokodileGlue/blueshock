#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

namespace sia {

class Shader {
public:
	Shader(GLenum shader_type, const std::string& filename, std::string shader_name);
	~Shader();
	GLuint shader_id;
	std::string name, path;
};

}

#endif
