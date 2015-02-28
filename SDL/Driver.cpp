#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Driver.h"

SDL_Texture *tex;
SDL_Event e;

bool running = true;
int FPS = 60;

int main(int, char**){
	//The following three functions load SDL, SDL image and SDL font.
	//It then creates a window and a renderer for your game to be
	//drawn on. To edit window or renderer properties such as window
	//title, size, or fullscreen see the load_SDL_Window and
	//load_SDL_Renderer at the bottom.
	load_SDL_Libraries();
	SDL_Window *win = load_SDL_Window();
	SDL_Renderer *ren = load_SDL_Renderer(win);

	//To load an image you first declare the texture with:
	//SDL_Texture *texture_name, as seen above the int main function.
	//Then you call the load_Texture function with the relative image
	//path, and a reference to the renderer.
	tex = load_Texture("images/Test.png", ren);

	//After all of the basic setup, the game_loop is called with a
	//reference to the renderer. This is where all of the magic happens
	//and as so is located directly below.
	game_loop(ren);
	
	return 0;
}

//This is the main game_loop of the program. Once this loop is called it
//will run until running is set to false. This loop first calls the event_loop
//to process any events in the queue. Then it clears the screen and calls the
//paint_loop. Inside the paint loop function is where you would render textures.
//It then presents the renders to the screen and sleeps for 1000 / FPS ms. This 
//prevents the game_loop from running 1000s of time per second and putting an
//unessisary load on the CPU and GPU
void game_loop(SDL_Renderer *ren){
	while (running){
		event_loop();

		//The area below the event_loop being called, and above the SDL_RenderClear function being called
		//is where you would typically put any code that needs to be run every frame of the game.
		//Things such as updating the player position if a key is being held down, or moving an enemy
		//across the screen.

		//Don't modify any of the following lines unless you know what you are doing. Use the paint_loop
		//function below to paint your textures to the screen.
		SDL_RenderClear(ren);
		paint_loop(ren);
		SDL_RenderPresent(ren);

		SDL_Delay((1000 / FPS));
	}
}

//The paint_loop is resonsible for painting to the renderer every frame. This is
//where you would paint your player or enemies textures, or the map tiles using
//the render_Texture function to set the location and optionally the size of the image.
void paint_loop(SDL_Renderer * ren){
	render_Texture(tex, ren, 100, 100);
}

//The event loop. This will check the queue of events every time
//it is called from the game loop and will process events with 
//the SDL Event object e.
void event_loop(){
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT){
			running = false;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
			running = false;
		}
	}
}

//The load_Texture function uses the SDL_image library to load any image format
//to and SDL_Texture object in order to be rendered to the screen.
SDL_Texture* load_Texture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		running = false;
	}
	return texture;
}

//This is the first of the two render_Texture functions. This one accepts an x, y
//width and height argument. So the texture will be renderer in a certain location
//along with having a specific size.
void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
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
void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	render_Texture(tex, ren, x, y, w, h);
}

//Helper function for creating the SDL window. You can change the
//title of the window and the size and the position here.
SDL_Window* load_SDL_Window(){
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
SDL_Renderer* load_SDL_Renderer(SDL_Window *win){
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return ren;
}

//Helper function to load all of the SDL libraries needed to run the game.
void load_SDL_Libraries(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "SDL_Image_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
}