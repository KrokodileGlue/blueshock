#include "ShaderProgram.h"

#include <iostream>
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

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

	GLint position_attribute = glGetAttribLocation(program_id, "position");
	glEnableVertexAttribArray(position_attribute);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	check_gl_shader_program_error(program_id);
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
