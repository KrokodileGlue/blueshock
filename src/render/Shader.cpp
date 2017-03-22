#include "Shader.h"

#include <iostream>
#include <cstdio>

#include "util.h"
#include "Log.h"

void check_gl_shader_error(GLint shader, GLenum shader_type)
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint log_size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		char* error_log = new char[log_size];

		glGetShaderInfoLog(shader, log_size, NULL, error_log);

		std::string shader_type_str;

		switch (shader_type) {
		case GL_VERTEX_SHADER:
			shader_type_str = "vertex "; break;
		case GL_FRAGMENT_SHADER:
			shader_type_str = "fragment "; break;
		default:
			shader_type_str = "unknown "; break;
		}

		log(LogLevel::WARNING) << shader_type_str << "shader compilation failed:\n" << error_log;
		delete error_log;
	}
}

Shader::Shader(GLenum shader_type, const std::string& filename, std::string shader_name) : name(shader_name), path(filename)
{
	log(LogLevel::INFO) << "compiling shader " << filename;

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
