
#include "BaseObject.h"
#include "main_include.h"
#include "setting_SDL2.h"
#include "Snake.h"
#include "Food.h"
#include "Texture.h"
#include "Menu.h"
#undef main
using namespace std;

int dir;
bool running;
int size_snake;
int size_wall;
UINT32 score;
SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event event;
SDL_Rect apple[50];
SDL_Rect snake[100];
SDL_Rect wall[1000];
BaseObject g_background;
BaseObject g_food;
BaseObject g_wall;

void main()
{
	RESTART:
	set_Data();
	bool test;

	test = g_background.loadImg("background.png", renderer);
	if (test == false)
	{
		cout << "cannot loading background";
		return;
	}

	test = g_food.loadImg("apple.png", renderer);
	if (test == false)
	{
		cout << "cannot loading food";
		return;
	}

	test = g_wall.loadImg("wall.png", renderer);
	if (test == false)
	{
		cout << "cannot loading food";
		return;
	}


	while (running)
	{
		move();
		if (snake[0].x == apple[0].x && snake[0].y == apple[0].y)
		{
			eat();
			create_food();
		}
		for (int i = 0; i < size_wall; i++)
		{
			if (snake[0].x == wall[i].x &&
				snake[0].y == wall[i].y)
			{
				//return ;
				int ret_menu = ShowMenu (renderer,
					"Player Again", "Exit",
					"background.png");
				switch (ret_menu)
				{
				case 1:
					goto EXIT;
				case 0:
					goto RESTART;
				}
			}
		} // đụng tường
		for (int i = 4; i < size_snake; i++)
		{
			if (snake[0].x == snake[i].x &&
				snake[0].y == snake[i].y)
			{
				//return ;
				int ret_menu = ShowMenu(renderer,
					"Player Again", "Exit",
					"background.png");
				switch (ret_menu)
				{
				case 1:
					goto EXIT;
				case 0:
					goto RESTART;
				}
			}
		}
		
		// CLEAR WINDOW
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Show background
		g_background.Render(renderer, NULL);

		// draw body
		draw_snake();

		// draw apples
		g_food.SetRect(apple[0].x, apple[0].y);
		g_food.Render(renderer, NULL);

		//draw wall
		for (int i = 0; i < size_wall; i++)
		{
			g_wall.SetRect(wall[i].x, wall[i].y);
			g_wall.Render(renderer, NULL);
		}

		// print score
		std::string text = "Scoce:";
		string point = to_string (score);
		text += point;
		draw_textchange(text.c_str(), 730, 50);


		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}
	EXIT: 
	return;
}