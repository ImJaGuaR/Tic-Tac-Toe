#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>

#include "renderer.h"

using namespace std;

const int boardHeight = 3;
const int boardWidth = 3;

const int screeenHeight = boardHeight * 256;
const int screenWidth = boardWidth * 256;

const int used = 1;
const int not_used = 0;

const int X = 1;
const int O = 2;

const int you_lost = 1;
const int you_won = 0;

int X_count = 0;
int O_count = 0;

RenderWindow window("Tik-Tak-Toe", screenWidth, screeenHeight);

SDL_Texture* tex_white_tile = window.loadTexture("gfx/white_tile.png");
SDL_Texture* tex_O = window.loadTexture("gfx/O.png");
SDL_Texture* tex_X_won = window.loadTexture("gfx/x_won.png");
SDL_Texture* tex_O_won = window.loadTexture("gfx/o_won.png");
SDL_Texture* tex_draw = window.loadTexture("gfx/draw.png");
SDL_Texture* tex_X = window.loadTexture("gfx/X.png");
SDL_Texture* tex_dfaw_background = window.loadTexture("gfx/draw_background.png");


bool game_running = true;

int mousex{};
int mousey{};

int tile_grid[boardWidth + 1][boardHeight + 1];
int used_grid[boardWidth + 1][boardHeight + 1];

int tile_x{};
int tile_y{};

void render_grid();
void check_win();
void post_game();

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initalizing SDL: " << SDL_GetError() << endl;
		return 0;
	}
	render_grid();
	window.display();
	bool xs = false;
	int ejimai = 0;

	while (game_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				game_running = false;
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&mousex, &mousey);
				tile_x = (mousex / 256) + 1;
				tile_y = (mousey / 256) + 1;
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (used_grid[tile_x][tile_y] == not_used) {
						if (xs) {
							tile_grid[tile_x][tile_y] = X;
							xs = false;
							used_grid[tile_x][tile_y] = used;
							ejimai++;
							render_grid();
							window.display();
						}
						else {
							tile_grid[tile_x][tile_y] = O;
							xs = true;
							ejimai++;
							used_grid[tile_x][tile_y] = used;
							render_grid();
							window.display();
						}
					}
				}
				check_win();

			}
		}
	}

	post_game();

	window.cleanUp();
	SDL_Quit();
	return 0;

}

void check_win() {
	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[i][i] == X)
			X_count++;
		if (tile_grid[i][i] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;

	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[boardWidth+1-i][i] == X)
			X_count++;
		if (tile_grid[boardWidth + 1 - i][i] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;
	
	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[1][i] == X)
			X_count++;
		if (tile_grid[1][i] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;

	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[2][i] == X)
			X_count++;
		if (tile_grid[2][i] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;

	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[3][i] == X)
			X_count++;
		if (tile_grid[3][i] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;

	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[i][1] == X)
			X_count++;
		if (tile_grid[i][1] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;

	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[i][2] == X)
			X_count++;
		if (tile_grid[i][2] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;

	for (int i = 1; i <= boardWidth; i++) {
		if (tile_grid[i][3] == X)
			X_count++;
		if (tile_grid[i][3] == O)
			O_count++;
	}
	if (X_count == 3 || O_count == 3) {
		game_running = false;
		return;
	}
	X_count = 0;
	O_count = 0;
	
	for (int i = 1; i <= boardWidth; i++) {
		for (int j = 1; j <= boardHeight; j++) {
			if (used_grid[i][j] == not_used)
				return;
		}
	}
	X_count = 3;
	O_count = 3;
	game_running = false;
	return;

}


void render_grid() {
	window.clear();
	for (int x = 1; x <= boardWidth; x++) {
		for (int y = 1; y <= boardHeight; y++) {
			window.render((256 * (x - 1)), (256 * (y - 1)), tex_white_tile);
			if (used_grid[x][y] == used) {
				if(tile_grid[x][y] == X)
					window.render((256 * (x - 1)), (256 * (y - 1)), tex_X);
				if (tile_grid[x][y] == O)
					window.render((256 * (x - 1)), (256 * (y - 1)), tex_O);
			}
		}
	}
}

void post_game() {
	bool on_menu = true;
	while (on_menu) {
		window.clear();
		window.render(0, 0, tex_dfaw_background);
		if (X_count == 3 && O_count == 3) {
			window.render(0, 0, tex_draw);
		}
		else if (X_count == 3) {
			window.render(0, 0, tex_X_won);
		}
		else if (O_count == 3) {
			window.render(0, 0, tex_O_won);
		}
		window.display();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				on_menu = false;
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT)
					on_menu = false;
			}
		}
	}
}