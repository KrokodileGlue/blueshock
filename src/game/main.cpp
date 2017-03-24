#define GLEW_STATIC

#include <vector>

#include <GL/glew.h>

#include "engine/render/Display.h"
#include "engine/render/Shader.h"
#include "engine/render/ShaderProgram.h"
#include "engine/Log.h"
#include "engine/util.h"
#include "engine/render/Camera.h"
#include "engine/Input.h"
#include "engine/render/Model.h"
#include "engine/render/Renderer.h"
#include "engine/render/Mesh.h"

int main(int argc, char* argv[])
{
	Display display(512, 512);
	glewExperimental = GL_TRUE;
	glewInit();

	Shader vert_shader(GL_VERTEX_SHADER, "res/shader/vert_shader.txt", "static vertex shader");
	Shader frag_shader(GL_FRAGMENT_SHADER, "res/shader/frag_shader.txt", "static fragment shader");
	ShaderProgram shader_program(vert_shader, frag_shader);

	Renderer renderer(shader_program);
	Camera camera(0, 0, -15);

	Model model("res/model/star-wars-arc-170-pbr.obj");
	model.scale = 0.5f;
	model.pos = glm::vec3(0, -1, 0);
	model.rot = glm::vec3(0.0f, 0.0f, 0.0f);

	float time = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		model.rot = glm::vec3(0.0f, time * 90.0, 0.0f);

		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				input_add_key_event(e);
		
		display.update();
		update_input();

		renderer.render(model, camera, calc_projection_matrix(60.f, display.width, display.height));

		time += 0.0025f;
	}

	blueshock_quit();
	
	return 0;
}
