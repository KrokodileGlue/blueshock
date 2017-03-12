#include <iostream>
#include <SDL2/SDL.h>

int main ()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("Hello, world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN);

	SDL_Delay(1000);

	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}