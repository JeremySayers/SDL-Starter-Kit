#include "Game.h"

//The following three functions load SDL, SDL image and SDL font.
//It then creates a window and a renderer for your game to be
//drawn on. To edit window or renderer properties such as window
//title, size, or fullscreen see the load_SDL_Window and
//load_SDL_Renderer at the bottom.
Game::Game(){
	load_SDL_Libraries();
	win = load_SDL_Window();
	ren = load_SDL_Renderer(win);
}

//The load_Texture function uses the SDL_image library to load any image format
//to and SDL_Texture object in order to be rendered to the screen.
SDL_Texture* Game::load_Texture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){

	}
	return texture;
}

//This is the first of the two render_Texture functions. This one accepts an x, y
//width and height argument. So the texture will be renderer in a certain location
//along with having a specific size.
void Game::render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

//This is the second render_Texture function. This one only accepts an x and y argument,
//and as such uses the images actualy width and height property instead of scaling it.
void Game::render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	render_Texture(tex, ren, x, y, w, h);
}

//Helper function for creating the SDL window. You can change the
//title of the window and the size and the position here.
SDL_Window* Game::load_SDL_Window(){
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return win;
}

//Helper function for creating the rendering surface. The two options right now
//tell the renderer to use hardware acceleration and Vsync. Things such as Fullscreen
//and creating an OpenGL context would be done here.
SDL_Renderer* Game::load_SDL_Renderer(SDL_Window *win){
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return ren;
}

//Helper function to load all of the SDL libraries needed to run the game.
void Game::load_SDL_Libraries(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "SDL_Image_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
}