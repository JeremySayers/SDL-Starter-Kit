#include "Game.h"

SDL_Texture *tex;
SDL_Event e;

bool running = true;
int FPS = 60;

Game game;

void game_loop(SDL_Renderer *);
void paint_loop(SDL_Renderer *);
void event_loop();

int main(int, char**){
	//To load an image you first declare the texture with:
	//SDL_Texture *texture_name, as seen above the int main function.
	//Then you call the load_Texture function with the relative image
	//path, and a reference to the renderer.
	tex = game.load_Texture("images/Test.png", game.ren);

	//After all of the basic setup, the game_loop is called with a
	//reference to the renderer. This is where all of the magic happens
	//and as so is located directly below.
	game_loop(game.ren);

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
	game.render_Texture(tex, ren, 100, 100);
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