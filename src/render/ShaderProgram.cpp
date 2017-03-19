#include "ShaderProgram.h"

#include <iostream>
#include "Log.h"

void check_gl_shader_program_error(GLint program_id)
{
#define ERROR_LOG_SIZE 4096
	GLint success;
	char error_log[ERROR_LOG_SIZE];

	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(program_id, ERROR_LOG_SIZE, NULL, error_log);
		log(LogLevel::INFO) << "shader program linking failed:\n" << error_log;
	}
#undef ERROR_LOG_SIZE
}

ShaderProgram::ShaderProgram(Shader vert, Shader frag)
{
	log(LogLevel::INFO) << "linking shader program from shaders \"" << vert.name << "\" (" << vert.path << ") "
	<< "and \"" << frag.name << "\" (" << frag.path << ")";
	program_id = glCreateProgram();
	glAttachShader(program_id, vert.shader_id);
	glAttachShader(program_id, frag.shader_id);
	glLinkProgram(program_id);

	check_gl_shader_program_error(program_id);
}

ShaderProgram::~ShaderProgram()
{

}
