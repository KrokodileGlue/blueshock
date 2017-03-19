#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"
#include "glm.hpp"

class ShaderProgram {
public:
	ShaderProgram(Shader vert, Shader frag);
	~ShaderProgram();
	void bind() { glUseProgram(program_id); }
	void setUniform3f(const std::string& uniform_name, const glm::vec3& vec);
	void setUniformMatrix4fv(const std::string& uniform_name, const glm::mat4& mat);
private:
	GLuint program_id;
};

#endif
