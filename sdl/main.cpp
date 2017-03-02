  #include <stdlib.h>
#include <iostream>
#include "include/SDL.h"

using namespace std;

#pragma comment(lib, "x86/SDL2.lib")
#pragma comment(lib, "x86/SDL2main.lib")

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);

	SDL_Rect rectngl;
	rectngl.x = 215;
	rectngl.y = 125;
	rectngl.w = 220;
	rectngl.h = 220;

	for (;;)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
		//SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &rectngl);
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					SDL_Quit();
					break;
				case SDLK_LEFT:
					rectngl.x -= 25;
					break;
				case SDLK_RIGHT:
					rectngl.x += 25;
					break;
				case SDLK_UP:
					rectngl.y -= 25;
					break;
				case SDLK_DOWN:
					rectngl.y += 25;
					break;
				}
				/*
				if (rectngl.x == WINDOW_WIDTH)
				{
					rectngl.x -= 215;
				}
				if (rectngl.x == 0)
				{
					rectngl.x += 215;
				}
				if (rectngl.y == WINDOW_HEIGHT)
				{
					rectngl.y -= 125;
				}
				if (rectngl.y == 0)
				{
					rectngl.y += 125;
				}
				*/
			}
		}
	}

	return(EXIT_SUCCESS);
}