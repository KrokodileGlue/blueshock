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
#include "FrameBuffer.h"
#include "QuadRenderer.h"

extern "C" {
#include "lua.h"
}

#include "json.hpp"
#include "selene.h"

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

	GLint gl_version_major, gl_version_minor;
	glGetIntegerv(GL_MAJOR_VERSION, &gl_version_major);
	glGetIntegerv(GL_MINOR_VERSION, &gl_version_minor);
	log(LogLevel::INFO) << "OpenGL version: " << std::to_string(int(gl_version_major)) << "." << std::to_string(int(gl_version_minor));

	Shader vert_shader(GL_VERTEX_SHADER, "res/shader/vert.txt", "static vertex shader");
	Shader frag_shader(GL_FRAGMENT_SHADER, "res/shader/frag.txt", "static fragment shader");
	ShaderProgram shader_program(vert_shader, frag_shader);

	Renderer renderer(shader_program);
	Camera camera(0, 0, -15);

	Model model("res/model/star-wars-arc-170-pbr.obj");
	//model.scale = 0.25f;
	//model.pos = glm::vec3(0, -1, 20);
	//model.rot = glm::vec3(-90.0f, 0.0f, 0.0f);
	model.rot = glm::vec3(0, 180, 0);

	Scene scene;
	scene.addModelComponent(0, model);
	scene.addInputComponent(0);

	FrameBuffer multisampled_fbo(display.width, display.height, true);
	FrameBuffer fbo(display.width, display.height, false);
	QuadRenderer quad_renderer;

	sel::State state {true};
	state.Load("res/script/test.lua");

	float time = 0.;
	SDL_Event e;
	bool running = true;
	while (running) {
		bool was_window_resized = false;
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT) running = false;
			else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
				was_window_resized = true;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				InputHandler::getSingleton()->addKeyEvent(e);
		
		display.update();
		InputHandler::getSingleton()->updateInput();
		scene.update();

		if (was_window_resized) {
			multisampled_fbo.resize(display.width, display.height);
			fbo.resize(display.width, display.height);
		}

		multisampled_fbo.bind();
		scene.render(renderer, camera, calc_projection_matrix(60.f, display.width, display.height));
		multisampled_fbo.unbind();

		fbo.blit(multisampled_fbo);
		quad_renderer.render(fbo.getTexture());

		time += 0.25f;
	}

	blueshock_finish();
	
	return EXIT_SUCCESS;
}
