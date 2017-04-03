#include "Display.h"
#include "Log.h"
#include "util.h"

Display::Display(int default_width, int default_height)
{
	log(LogLevel::INFO) << "initializing SDL";
	width = default_width, height = default_height;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		log(LogLevel::ERROR) << "could not initialize SDL:\n\t" << SDL_GetError();
		blueshock_finish();
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) || SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3)) {
		log(LogLevel::ERROR) << "could not set SDL GL attributes:\n\t" << SDL_GetError();
		blueshock_finish();
		exit(EXIT_FAILURE);
	}
	
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	win = SDL_CreateWindow("blueshock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	context = SDL_GL_CreateContext(win);
	SDL_GL_SetSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	log(LogLevel::INFO) << "finished initializing SDL";
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void Display::update()
{
	SDL_GL_SwapWindow(win);

	SDL_GetWindowSize(win, &width, &height);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
