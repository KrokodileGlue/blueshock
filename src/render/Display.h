#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <GL/glew.h>

class Display {
public:
	Display(int default_width, int default_height);
	~Display();
	void update();
private:
	int width, height;
	SDL_Window* win;
	SDL_GLContext context;
};

#endif
