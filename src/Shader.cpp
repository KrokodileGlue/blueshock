#include "Shader.h"

#include <iostream>
#include <cstdio>

#include "util.h"

void check_gl_shader_error(GLint shader, GLenum shader_type)
{
#define ERROR_LOG_SIZE 4096
	GLint success;
	GLchar error_log[ERROR_LOG_SIZE];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(shader, ERROR_LOG_SIZE, NULL, error_log);

		switch (shader_type) {
		case GL_VERTEX_SHADER:
			std::cout << "vertex "; break;
		case GL_FRAGMENT_SHADER:
			std::cout << "fragment "; break;
		default:
			std::cout << "unknown "; break;
		}

		std::cout << "shader compilation failed: " << error_log << std::endl;
	}
#undef ERROR_LOG_SIZE
}

Shader::Shader(const std::string& filename, GLenum shader_type)
{
	char* src = load_file(filename.c_str());
	
	shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &src, NULL);
	glCompileShader(shader_id);
	
	check_gl_shader_error(shader_id, shader_type);

	free(src);
}

Shader::~Shader()
{
	glDeleteShader(shader_id);
}
