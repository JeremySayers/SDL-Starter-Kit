#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Window * load_SDL_Window();
SDL_Renderer * load_SDL_Renderer(SDL_Window*);
SDL_Texture* load_Texture(const std::string &file, SDL_Renderer *ren);
void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void cleanup_SDL();
void game_loop(SDL_Renderer *);
void event_loop();

SDL_Texture *tex;
SDL_Event e;

bool running = true;

int main(int, char**){
	//**********************************************
	//*********** SDL LOADING AND INIT *************
	//**********************************************
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "SDL_Image_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Window *win = load_SDL_Window();
	SDL_Renderer *ren = load_SDL_Renderer(win);

	//**********************************************
	//*********** Image Loading  *******************
	//*****(Declare outside of main for global)*****
	//**********************************************
	tex = load_Texture("images/Test.png", ren);

	//**********************************************
	//************* Calling Game_Loop **************
	//**********************************************
	game_loop(ren);
	

	
	return 0;
}

//Main game loop. Will run until an event sets running to false
//All of the drawing and updating will take place here
void game_loop(SDL_Renderer *ren){
	while (running){
		event_loop();

		//All of the drawing code goes in between RenderClear and RenderPresent
		SDL_RenderClear(ren);
		render_Texture(tex, ren, 100, 100);
		SDL_RenderPresent(ren);

		SDL_Delay((1000 / 60));
	}
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

SDL_Texture* load_Texture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		running = false;
	}
	return texture;
}

void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

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