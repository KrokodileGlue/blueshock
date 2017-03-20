#ifndef RENDERER_H
#define RENDERER_H

#include "glm.hpp"
#include "GL/glew.h"

#include "ShaderProgram.h"
#include "Model.h"
#include "Camera.h"

class Renderer {
public:
	Renderer(ShaderProgram in_shader_program) : shader_program(in_shader_program) {};
	void render(const Model& model, Camera camera, glm::mat4 projection_matrix);
private:
	ShaderProgram shader_program;
};

#endif
