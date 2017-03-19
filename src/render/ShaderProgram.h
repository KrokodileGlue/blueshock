#ifndef GENERIC_SHADER_PROGRAM
#define GENERIC_SHADER_PROGRAM

#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram(Shader vert, Shader frag);
	~ShaderProgram();
	GLuint program_id;
	void bind() { glUseProgram(program_id); }
};

#endif