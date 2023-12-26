#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow {
public:
	RenderWindow(const char* title, int window_w, int window_h);
	SDL_Texture* loadTexture(const char* filePath);
	void render(int x, int y, SDL_Texture* tex);
	void cleanUp();
	void clear();
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};