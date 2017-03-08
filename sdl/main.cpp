#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "include/SDL.h"

#define MAX_BULLETS 10

using namespace std;

#pragma comment(lib, "x86/SDL2.lib")
#pragma comment(lib, "x86/SDL2main.lib")

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

int main(int argc, char* argv[])
{
	int quit_game = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
	/*
	window = SDL_CreateWindow("LARA CROFT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 60);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	*/
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_Surface* sprite = SDL_LoadBMP("lara.bmp");
	SDL_Texture* texture_sprite = SDL_CreateTextureFromSurface(renderer, sprite);
	//
	SDL_Surface* bullet = SDL_LoadBMP("bullets.bmp");
	SDL_Texture* texture_bullet = SDL_CreateTextureFromSurface(renderer, bullet);
	//
	SDL_Surface* scrolling_background = SDL_LoadBMP("scrolling_back.bmp");
	SDL_Texture* texture_scrolling_back = SDL_CreateTextureFromSurface(renderer, scrolling_background);
	//
	SDL_Surface* scrolling_background_2 = SDL_LoadBMP("scrolling_back - copia.bmp");
	SDL_Texture* texture_scrolling_back_2 = SDL_CreateTextureFromSurface(renderer, scrolling_background_2);

	SDL_Rect background_1;
	background_1.x = 1920;
	background_1.y = 0;
	background_1.w = 1920;
	background_1.h = 720;

	SDL_Rect background_2;
	background_2.x = 0;
	background_2.y = 0;
	background_2.w = 1920;
	background_2.h = 720;

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
	};
	keys move;

	bool bulled_is_pressed[MAX_BULLETS];
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bulled_is_pressed[i] = false;
	}

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
				case SDLK_SPACE:
					for (int i = 0; i < MAX_BULLETS; i++)
					{
						if (bulled_is_pressed[i] == false)
						{
							bulled_is_pressed[i] = true;
							bullet_rect[i].x = rectangle.x;
							bullet_rect[i].y = rectangle.y;
							break;
						}
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
		}
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bulled_is_pressed[i] == true)
			{
				bullet_rect[i].x += 1;
				if (bullet_rect[i].x == WINDOW_WIDTH)
				{
					bulled_is_pressed[i] = false;
				}
			}
		}

		background_1.x -= 1;
		background_2.x -= 1;
		if (background_1.x <= -1920)
		{
			background_1.x = 1920;
		}
		if (background_2.x <= -1920)
		{
			background_2.x = 1920;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture_scrolling_back, NULL, &background_1);
		SDL_RenderCopy(renderer, texture_scrolling_back_2, NULL, &background_2);

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bulled_is_pressed[i] == true)
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