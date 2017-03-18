#ifndef GENERIC_SHADER_PROGRAM
#define GENERIC_SHADER_PROGRAM

#include "Shader.h"

class GenericShaderProgram {
public:
	GenericShaderProgram(Shader vert, Shader frag);
	~GenericShaderProgram();
	GLuint program_id;
	void bind() { glUseProgram(program_id); }
};

#endif