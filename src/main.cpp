#define GLEW_STATIC

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Display.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Log.h"
#include "util.h"
#include "Camera.h"
#include "Input.h"
#include "Model.h"
#include "Renderer.h"

int main(int argc, char* argv[])
{
	Display display(512, 512);
	glewExperimental = GL_TRUE;
	glewInit();

	Shader vert_shader(GL_VERTEX_SHADER, "res/shader/vert_shader.txt", "static vertex shader");
	Shader frag_shader(GL_FRAGMENT_SHADER, "res/shader/frag_shader.txt", "static fragment shader");
	ShaderProgram shader_program(vert_shader, frag_shader);

	Renderer renderer(shader_program);
	Camera camera(0, 0, 0);

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	Model model(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	float delta = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		//camera.pitch = sin(delta) * 45.0f / 4.0f;
		//camera.yaw = cos(delta) * 45.0f / 4.0f;
		camera.setPos(glm::vec3(sin(delta) * 2.0f, 0.0f, cos(delta) * 2.0f));
		
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) input_add_key_event(e);
		
		display.update();
		update_input();

		renderer.render(model, camera, calc_projection_matrix(45.f, display.width, display.height));

		delta += 0.025f;
	}

	blueshock_quit();
	
	return 0;
}
