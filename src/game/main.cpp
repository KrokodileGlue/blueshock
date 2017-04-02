#define GLEW_STATIC

#include <vector>
#include <fstream>

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
#include "Game.h"

#include "json.hpp"

using nlohmann::json;

/*
std::ifstream game_json_file("res/game.json");

json j;
game_json_file >> j;
game_json_file.close();

std::cout << j.dump(8) << std::endl;
*/

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
	model.scale = 0.25f;
	model.pos = glm::vec3(0, -1, 20);
	model.rot = glm::vec3(-90.0f, 0.0f, 0.0f);

	Scene scene;
	scene.addModelComponent(0, model);
	scene.addInputComponent(0);

	float time = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		model.rot = glm::vec3(0.0f, time * 90.0, 0.0f);

		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				InputHandler::getSingleton()->addKeyEvent(e);
		
		display.update();
		InputHandler::getSingleton()->updateInput();
		scene.update();
		scene.render(renderer, camera, calc_projection_matrix(60.f, display.width, display.height));

		time += 0.0025f;
	}

	blueshock_finish();
	
	return EXIT_SUCCESS;
}
