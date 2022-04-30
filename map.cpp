#include "snake.h"
#include "map.h"
#include "food.h"
#include <iostream>
using namespace std;

Map::Map() // set defult map dimention 25x25
{
	width = 25;
	hight = 25;
}

Map::Map(int w, int h) // set a specific map dimention (width is x axis and h is y axis)
{
	width = w;
	hight = h;
}

int Map::get_width() //0
{
	return width;
}

int Map::get_hight() //0
{
	return hight;
}

void Map::draw(Snake* COM, Snake* snake, Food* food, Map* map)
{
	int food_x = food->get_location_x();
	int food_y = food->get_location_y();
	int snake_length = snake->get_length();
	int COM_length = COM->get_length();

	node** snake_head = snake->get_head();
	node* snake_temp = (*snake_head)->prev;
	node** COM_head = COM->get_head();
	node* COM_temp = (*COM_head)->prev;

	bool printed = false;

	for (int i = 0; i < hight; i++)  // i --> rows --> y-axis
	{
		for (int j = 0; j < width; j++)  // j --> columns --> x-axis __ note: the origin is at the top left
		{
			if (j == width - 1)
			{
				cout << "* \n";
				printed = true;
			}
			else if (i == 0 || i == hight - 1 || j == 0)
			{
				cout << "* ";
				printed = true;
			}
			else if (j == food_x && i == food_y)
			{
				cout << "# ";
				printed = true;
			}
			else
			{
				snake_temp = (*snake_head)->prev;
				for (int k = 1; k < snake_length; k++) // printing player snake
				{
					if (j == (*snake_head)->x && i == (*snake_head)->y) { cout << "O "; printed = true; break; }
					else if (j == snake_temp->x && i == snake_temp->y) { cout << "o "; printed = true; break; }
					snake_temp = snake_temp->prev;
				}

				COM_temp = (*COM_head)->prev;
				for (int k = 1; k < COM_length; k++) // printing player snake
				{
					if (j == (*COM_head)->x && i == (*COM_head)->y) { cout << "# "; printed = true; break; }
					else if (j == COM_temp->x && i == COM_temp->y) { cout << "0 "; printed = true; break; }
					COM_temp = COM_temp->prev;
				}
			}

			if (printed == false) cout << "  ";
			printed = false;
		}
	}
}

