#include "ShaderProgram.h"

#include <iostream>
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

using namespace sia;

void check_gl_shader_program_error(GLint program_id)
{
	GLint success;
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);

	if (success == GL_FALSE) {
		GLint log_size = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
		char* error_log = new char[log_size];

		glGetProgramInfoLog(program_id, log_size, NULL, error_log);
		log(LogLevel::WARNING) << "shader program linking failed:\n" << error_log;

		delete error_log;
	}
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

void ShaderProgram::setUniform1f(const std::string& uniform_name, float num)
{
	GLint uniform_loc = glGetUniformLocation(program_id, uniform_name.c_str());
	if (uniform_loc != -1) {
		glUniform1f(uniform_loc, num);
	}
}

void ShaderProgram::setUniform1i(const std::string& uniform_name, GLint num)
{
	GLint uniform_loc = glGetUniformLocation(program_id, uniform_name.c_str());
	if (uniform_loc != -1) {
		glUniform1i(uniform_loc, num);
	}
}

void ShaderProgram::setUniform3f(const std::string& uniform_name, const glm::vec3& vec)
{
	GLint uniform_loc = glGetUniformLocation(program_id, uniform_name.c_str());
	if (uniform_loc != -1) {
		glUniform3fv(uniform_loc, 1, glm::value_ptr(vec));
	}
}

void ShaderProgram::setUniformMatrix4fv(const std::string& uniform_name, const glm::mat4& mat)
{
	GLint uniform_loc = glGetUniformLocation(program_id, uniform_name.c_str());
	if (uniform_loc != -1) {
		glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(mat));
	}
}

ShaderProgram::~ShaderProgram()
{

}
