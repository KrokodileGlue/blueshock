#define GLEW_STATIC

#include <vector>

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
#include "Mesh.h"

int main(int argc, char* argv[])
{
	Display display(512, 512);
	glewExperimental = GL_TRUE;
	glewInit();

	Shader vert_shader(GL_VERTEX_SHADER, "res/shader/vert_shader.txt", "static vertex shader");
	Shader frag_shader(GL_FRAGMENT_SHADER, "res/shader/frag_shader.txt", "static fragment shader");
	ShaderProgram shader_program(vert_shader, frag_shader);

	Renderer renderer(shader_program);
	//Camera camera(0, 0, -15);
	Camera camera(0, 0, -25);

	Model model("res/model/Locomotive C36.obj");
	model.scale = 0.025f;
	//model.pos = glm::vec3(0.f, -7.25f, 0.f);
	//model.rot = glm::vec3(0.0f, 180.0f, 0.0f);

	float delta = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		//camera.setPos(glm::vec3(sin(delta) * 14.0f, 10.0f, cos(delta) * 14.0f));
		model.rot = glm::vec3(0.f, delta * 90.0f, 0.f);
		
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) input_add_key_event(e);
		
		display.update();
		update_input();

		renderer.render(model, camera, calc_projection_matrix(60.f, display.width, display.height));

		delta += 0.025f;
	}

	blueshock_quit();
	
	return 0;
}
