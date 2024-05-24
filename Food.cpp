#include "Food.h"
#include "main_include.h"

void create_food()
{
		int x, y;
		srand(time(NULL));
	re_check:
		x = (min_ + 80) + + rand() % ((max_x - 80) - (min_ + 80) + 1);// tính lại tọ độ sao chia hết cho 10
		y = (min_ + 80) + rand() % ((max_y - 80) - (min_ + 80) + 1);
		if (x % 20 == 0 && y % 20 == 0) {
			for (int i = 0; i < size_snake; i++)
			{
				if (x == snake[i].x && y == snake[i].y)
				{
					goto re_check;
				}
			}
			apple[0] = { x,y,10,10 };
		}
		else
			goto re_check;
}

void draw_food()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &apple[0]);
}
