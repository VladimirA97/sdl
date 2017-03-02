  #include <stdlib.h>
#include <iostream>
#include "include/SDL.h"

using namespace std;

#pragma comment(lib, "x86/SDL2.lib")
#pragma comment(lib, "x86/SDL2main.lib")

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);

	for (;;)
	{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	//SDL_RenderPresent(renderer);

	SDL_Rect r;
	r.x = 215;
	r.y = 125;
	r.w = 220;
	r.h = 220;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);

	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (state[SDL_SCANCODE_ESCAPE])
		{
			SDL_Quit();
		}
	}
	/*
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_Quit();
				}
			}
		}
		*/
	}
	

	return(EXIT_SUCCESS);
}