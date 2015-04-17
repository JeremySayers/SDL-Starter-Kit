#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Game {
public:
	SDL_Window *win;
	SDL_Renderer *ren;

	Game();
	void load_SDL_Libraries();
	SDL_Window * load_SDL_Window();
	SDL_Renderer * load_SDL_Renderer(SDL_Window*);
	SDL_Texture* load_Texture(const std::string &file, SDL_Renderer *ren);
	void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	void render_Texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	SDL_Texture* render_Text(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);
	std::string get_Directory();
	void cleanup_SDL();
};
