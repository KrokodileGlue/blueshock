#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
	Shader(const std::string& filename, GLenum shader_type);
	~Shader();
	GLuint shader_id;
};

#endif
