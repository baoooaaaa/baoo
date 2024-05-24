#include "Texture.h"
#include "main_include.h"
#include "BaseObject.h"
#include "setting_SDL2.h"
#include "Snake.h"
#include "Food.h"
void draw_textchange(const char* text, int posX, int posY)
{
	TTF_Init();
	TTF_Font* font = NULL;
	font = TTF_OpenFont("font-times-new-roman/dlxfont_.ttf", 24);
	SDL_Color fg = { 243, 156, 18 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, fg);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(font, text, &srcRest.w, &srcRest.h);

	srcRest.x = 0; // độ dãn text chiều ngang
	srcRest.y = 0; // độ dãn text chiều dọc

	desRect.x = posX;
	desRect.y = posY;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;
	SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
}
