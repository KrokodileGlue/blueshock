#include "GenericShaderProgram.h"

#include <iostream>

void check_gl_shader_program_error(GLint program_id)
{
#define ERROR_LOG_SIZE 4096
	GLint success;
	GLchar error_log[ERROR_LOG_SIZE];

	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(program_id, 512, NULL, error_log);
		std::cout << "shader program linking failed: " << error_log << std::endl;
	}
#undef ERROR_LOG_SIZE
}

GenericShaderProgram::GenericShaderProgram(Shader vert, Shader frag)
{
	program_id = glCreateProgram();
	glAttachShader(program_id, vert.shader_id);
	glAttachShader(program_id, frag.shader_id);
	glLinkProgram(program_id);

	check_gl_shader_program_error(program_id);
}

GenericShaderProgram::~GenericShaderProgram()
{

}
