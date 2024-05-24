#include "main_include.h"
#include "map_.h"
void set_Data()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow("Snake",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		max_x, // width
		max_y,  // height
		0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Snake head
	snake[0] = { 500,   // x
					 200, // y
					 10,10 };
	//Snake body
	size_snake = size_snake_auto;

	//Create apples on map
	apple[0] = { 500,
		         100,10,10 };

	//Create map
	size_wall = 0;
	create_map_();

	//Score
	score = 0;

	//setting newgame
	running = true;
	dir = DOWN;
}