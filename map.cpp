#include "map.h"
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

void Map::draw(int food_x,int food_y,int length,int* first_x_pointer,int* first_y_pointer,int* current_x_pointer,int* current_y_pointer)
{
	int* last_x_pointer = first_x_pointer + 49;
	int* last_y_pointer = first_y_pointer + 49;
	int* fixed_head_x_pointer = current_x_pointer;
	int* fixed_head_y_pointer = current_y_pointer;
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
			else for (int k = 0; k < length; k++)
			{
				if (j == *current_x_pointer && i == *current_y_pointer && current_x_pointer == fixed_head_x_pointer && current_y_pointer == fixed_head_y_pointer) { cout << "O "; printed = true; break; }
				else if (j == *current_x_pointer && i == *current_y_pointer) { cout << "o "; printed = true; break; }
				
				current_x_pointer--;
				current_y_pointer--;
				if (current_x_pointer == first_x_pointer - 1 && current_y_pointer == first_y_pointer - 1)
				{
					current_x_pointer = last_x_pointer;
					current_y_pointer = last_y_pointer;
				}
			}
			if(printed == false) cout << "  ";
			current_x_pointer = fixed_head_x_pointer;
			current_y_pointer = fixed_head_y_pointer;
			printed = false;
		}
	}
}
