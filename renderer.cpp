#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>

#include "renderer.h"

using namespace std;

RenderWindow::RenderWindow(const char* title, int window_w, int window_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window failed to open ERROR: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL)
		std::cout << "failed to load texture ERROR: " << SDL_GetError() << std::endl;
	return texture;
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(int x, int y, SDL_Texture* texture) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = (src.w * 2);
	dst.h = (src.h * 2);
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}