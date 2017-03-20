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
	Camera camera(0, 0, 0);

	Model model("res/model/bunny.obj");

	float delta = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		//camera.pitch = sin(delta) * 45.0f / 4.0f;
		//camera.yaw = cos(delta) * 45.0f / 4.0f;
		camera.setPos(glm::vec3(sin(delta) * 5.0f, 2.0f, cos(delta) * 5.0f));
		
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) input_add_key_event(e);
		
		display.update();
		update_input();

		renderer.render(model, camera, calc_projection_matrix(90.f, display.width, display.height));

		delta += 0.025f;
	}

	blueshock_quit();
	
	return 0;
}
