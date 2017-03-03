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
	int quit_game = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_Surface* sprite = SDL_LoadBMP("lara.bmp");
	SDL_Texture* texture_sprite = SDL_CreateTextureFromSurface(renderer, sprite);
	//SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Surface* background = SDL_LoadBMP("background.bmp");
	SDL_Texture* texture_background = SDL_CreateTextureFromSurface(renderer, background);

	SDL_Rect rectangle;
	rectangle.x = 215;
	rectangle.y = 125;
	rectangle.w = 220;
	rectangle.h = 220;

	while (!quit_game)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit_game = 1;
					break;
				case SDLK_LEFT:
					rectangle.x -= 25;
					break;
				case SDLK_RIGHT:
					rectangle.x += 25;
					break;
				case SDLK_UP:
					rectangle.y -= 25;
					break;
				case SDLK_DOWN:
					rectangle.y += 25;
					break;
				}

				if (rectangle.x < 0) 
				{
					rectangle.x = 0;
				}
				else if (rectangle.x > WINDOW_WIDTH - rectangle.w) 
				{
					rectangle.x = WINDOW_WIDTH - rectangle.w;
				}
				if (rectangle.y < 0) 
				{
					rectangle.y = 0;
				}
				else if (rectangle.y > WINDOW_HEIGHT - rectangle.h) 
				{
					rectangle.y = WINDOW_HEIGHT - rectangle.h;
				}
			}
		}
		//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);
		//SDL_BlitSurface(image, NULL, screen, &rectngl);
		SDL_RenderCopy(renderer, texture_background, NULL, NULL);
		SDL_RenderCopy(renderer, texture_sprite, NULL, &rectangle);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return(EXIT_SUCCESS);
}