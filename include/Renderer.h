#ifndef RENDERER_H
#define RENDERER_H

#include "glm/glm.hpp"
#include "GL/glew.h"

#include "ShaderProgram.h"
#include "Model.h"
#include "Camera.h"

namespace sia {

class Renderer {
public:
	Renderer(ShaderProgram in_shader_program) : shader_program(in_shader_program) {};
	void render(Model& model, Camera camera, glm::mat4 projection_matrix);
private:
	ShaderProgram shader_program;
};

}

#endif
