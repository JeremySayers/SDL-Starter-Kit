#include "Game.h"
#include <sstream>

SDL_Texture *tex;
SDL_Texture *image;
SDL_Texture *mouse_pos_font;
SDL_Color color;
SDL_Event e;

bool running = true;
int FPS = 60;

Game game;

void game_loop(SDL_Renderer *);
void paint_loop(SDL_Renderer *);
void event_loop();

//*NOTE*
//To get access to the console, make sure you run the program in Debug instead of release, when doing so
//a command prompt will pop up along with the SDL window.
int main(int, char**){
	//To load an image you first declare the texture with:
	//SDL_Texture *texture_name, as seen above the int main function.
	//Then you call the load_Texture function with the relative image
	//path, and a reference to the renderer.
	tex = game.load_Texture(game.get_Directory() + "images/Test.png", game.ren);

	//We set a color here for use in creating font textures such as in the mouse move
	//event where we create a text image of the current mouse X and Y.
	color = { 0, 255, 0, 125 };

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
	game.render_Texture(tex, ren, 150, 150);
	//This is is where we render the mouse X and Y position as stated below in the event loop.
	game.render_Texture(mouse_pos_font, ren, 0, 0);
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
		//Shows the basic use of an event to report information to the screen.
		//In this case whenever the mouse moves we take its X and Y location,
		//render it into a text, and then it gets rendered to the screen during
		//the next paint loop!
		if (e.type == SDL_MOUSEMOTION){
			std::stringstream info;
			info << "Mouse X: " << e.motion.x << "   Y: " << e.motion.y;
			mouse_pos_font = game.render_Text(info.str(), game.get_Directory() + "sample.ttf", color, 16, game.ren);
		}
	}
}