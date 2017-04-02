#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "GL/glew.h"

#include "Texture.h"
#include "Shader.h"
#include "ShaderProgram.h"

class QuadRenderer {
	GLuint quad_VAO, quad_VBO;
	Shader vertex_shader, fragment_shader;
	ShaderProgram shader_program;
public:
	QuadRenderer();
	void render(GLuint texture);
};

#endif
