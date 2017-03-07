#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "include/SDL.h"

#define MAX_BULLETS 2

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
	//SDL_Surface* background = SDL_LoadBMP("background.bmp");
	//SDL_Texture* texture_background = SDL_CreateTextureFromSurface(renderer, background);
	SDL_Surface* bullet = SDL_LoadBMP("bullets.bmp");
	SDL_Texture* texture_bullet = SDL_CreateTextureFromSurface(renderer, bullet);
	//
	SDL_Surface* scrolling_background = SDL_LoadBMP("scrolling_back.bmp");
	SDL_Texture* texture_scrolling_back = SDL_CreateTextureFromSurface(renderer, scrolling_background);

	SDL_Rect rectangle;
	rectangle.x = 215;
	rectangle.y = 125;
	rectangle.w = 110;
	rectangle.h = 110;

	SDL_Rect bullet_rect[MAX_BULLETS];
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullet_rect[i].x = rectangle.x;
		bullet_rect[i].y = rectangle.y;
		bullet_rect[i].w = 55;
		bullet_rect[i].h = 55;
	}
	
	struct keys
	{
		bool k_left = false;
		bool k_right = false;
		bool k_down = false;
		bool k_up = false;

		bool k_d_l = false;
		bool k_d_r = false;
		bool k_u_l = false;
		bool k_u_r = false;
	};
	keys move;

	bool bulled_is_pressed = false;
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
					move.k_left = true;
					break;
				case SDLK_RIGHT:
					move.k_right = true;
					break;
				case SDLK_UP:
					move.k_up = true;
					break;
				case SDLK_DOWN:
					move.k_down = true;
					break;
					/*
				case (SDLK_DOWN && SDLK_LEFT):
					move.k_d_l = true;
					break;
				case (SDLK_DOWN && SDLK_RIGHT):
					move.k_d_r = true;
					break;
				case SDLK_DOWN && SDLK_LEFT:
					move.k_d_l = true;
					break;
				case SDLK_DOWN && SDLK_LEFT:
					move.k_d_l = true;
					break;
					*/
				case SDLK_SPACE:
					bulled_is_pressed = true;
					for (int i = 0; i < MAX_BULLETS; i++)
					{
						bullet_rect[i].x = rectangle.x;
						bullet_rect[i].y = rectangle.y;
					}
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
		if (move.k_left == true)
		{
			rectangle.x -= 5;
			move.k_left = false;
		}
		if (move.k_right == true)
		{
			rectangle.x += 5;
			move.k_right = false;
		}
		if (move.k_down == true)
		{
			rectangle.y += 5;
			move.k_down = false;
		}
		if (move.k_up == true)
		{
			rectangle.y -= 5;
			move.k_up = false;			
		}

		if (bulled_is_pressed == true)
		{
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				bullet_rect[i].x += 1;
				if (bullet_rect[i].x == WINDOW_WIDTH)
				{
					bulled_is_pressed = false;
				}
			}
		}

		//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);
		//SDL_BlitSurface(image, NULL, screen, &rectngl);
		//SDL_RenderCopy(renderer, texture_background, NULL, NULL);

		SDL_RenderCopy(renderer, texture_scrolling_back, NULL, NULL);

		if (bulled_is_pressed == true)
		{
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				SDL_RenderCopy(renderer, texture_bullet, NULL, &bullet_rect[i]);
			}
		}
		SDL_RenderCopy(renderer, texture_sprite, NULL, &rectangle);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return(EXIT_SUCCESS);
}