#include "BaseObject.h"
#include <iostream>

extern SDL_Window* g_window;
extern SDL_Renderer* g_screen;

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = rect_.y = rect_.w = rect_.h = 0;
}
BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::loadImg(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = NULL;
	load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE,
			SDL_MapRGB(load_surface->format,
				167,175,180));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		else {
			std::cout << "ko load duoc anh";
		}
		SDL_FreeSurface(load_surface);
	}
	else {
		std::cout << "ko load duoc anh";
	}
	p_object_ = new_texture;
	//p_object_ = load_surface;
	return load_surface != NULL;
}
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect_.x,rect_.y,rect_.w,rect_.h };
	SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = rect_.h = 0;
	}
}


