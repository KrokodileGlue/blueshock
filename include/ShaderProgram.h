#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"
#include "glm/glm.hpp"

namespace sia {

class ShaderProgram {
public:
	ShaderProgram(Shader vert, Shader frag);
	~ShaderProgram();
	void bind() { glUseProgram(program_id); }
	void setUniform1f(const std::string& uniform_name, float num);
	void setUniform1i(const std::string& uniform_name, GLint num);
	void setUniform3f(const std::string& uniform_name, const glm::vec3& vec);
	void setUniformMatrix4fv(const std::string& uniform_name, const glm::mat4& mat);
private:
	GLuint program_id;
};

}

#endif
