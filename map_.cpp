#include "map_.h"
#include "main_include.h"
void create_map_()
{
	for (int i = 20; i <= max_x - 40 ; i += 20)
	{
		for (int j = 20; j <= max_y - 40; j+=20)
		{
			if (i == 20 || i == max_x - 40 ||
				j == 20 || j == max_y - 40)
			{
				wall[size_wall] = { i,j, 10,40 };
				size_wall++;
			}
		}
	}
}
