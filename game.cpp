#include "snake.h"
#include "map.h"
#include "food.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
//************************************************************************************************
int score = 0;
bool lose = false;

void frame(int,int,int*,int*,int*,int*);  // this function is the main function in the code (back end)

/*************************************************************************************************

	this function (ShowConsoleCursor) removes the white cursor while running the code
	to see the difference go to '1' label, pass 1 and see the difference            */

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

//************************************************************************************************



//****************************      initializing the main objects     ****************************

Map map;
Snake snake(map.get_width(), map.get_hight());
Food food;

//************************************************************************************************

int main()
{	
	ShowConsoleCursor(0);  // hide cursor

	food.generate(map.get_width(), map.get_hight()); // generating food in random place
	map.draw(food.get_location_x(), food.get_location_y(),snake.get_length(),snake.get_locations_x(),snake.get_locations_y(),snake.get_current_head_x(),snake.get_current_head_y());
	
	while (!lose)
	{
		system("cls"); // clear screen after each frame
		frame(food.get_location_x(), food.get_location_y(),snake.get_locations_x(), snake.get_locations_y(), snake.get_current_head_x(), snake.get_current_head_y());
		map.draw(food.get_location_x(), food.get_location_y(), snake.get_length(), snake.get_locations_x(), snake.get_locations_y(), snake.get_current_head_x(), snake.get_current_head_y());
		cout << "score: " << snake.get_length() - 3;
	}
	system("cls");
	cout << "score: " << snake.get_length() - 3 << "\n\n\n\n";
	Sleep(10000); // delay function, it take inputs in milliseconds
	return 0;
}


/*
	this function consists of three main sections
	1. change snake directions according to the input from the user
	2. check if the player had lost or not
	3. check if the snake had eaten a food or not

	arguments:
	1. food_x & food_y --> index of the food
	2. first_x_pointer & first_y_pointer --> two pointers to the first index in the array
	3. current_x_pointer & current_y_pointer --> two pointers to the current head location
*/
void frame(int food_x, int food_y, int* first_x_pointer, int* first_y_pointer, int* current_x_pointer, int* current_y_pointer)
{
	int* last_x_pointer = first_x_pointer + 49; // pointer to the last element in the snake array x
	int* last_y_pointer = first_y_pointer + 49; // pointer to the last element in the snake array y
	int* prev_x_pointer; // we need this pointer as a temporary pointer that take the previous value of the head pointer
	int* prev_y_pointer; // we need this pointer as a temporary pointer that take the previous value of the head pointer
	char temp;
	static char current_input = 'a', prev_input = 'd';
	static int state = 4; // initial state (moving left)
	if (_kbhit()) // checking if a key was pressed
	{
		temp = _getch(); // get that key and store in temp
		if (current_input != temp) 
		{
			prev_input = current_input;
			current_input = temp;
		}
	}
	
	if (current_input == 'w' && prev_input != 's') state = 1; // move up
	else if (current_input == 's' && prev_input != 'w') state = 2; // move down
	else if (current_input == 'd' && prev_input != 'a') state = 3; // move right
	else if (current_input == 'a' && prev_input != 'd') state = 4; // move left

	if (state == 1)
	{
		prev_x_pointer = current_x_pointer;
		prev_y_pointer = current_y_pointer;
		current_x_pointer++;
		current_y_pointer++;
		if (current_x_pointer == last_x_pointer + 1 && current_y_pointer == last_y_pointer + 1) //if we reach the end of the array we loop in a circle to the first element again
		{
			current_x_pointer = first_x_pointer;
			current_y_pointer = first_y_pointer;
		}
		*current_x_pointer = *prev_x_pointer;
		*current_y_pointer = *prev_y_pointer - 1;
		snake.set_current_head_index(current_x_pointer, current_y_pointer);
	}
	else if (state == 2)
	{
		prev_x_pointer = current_x_pointer;
		prev_y_pointer = current_y_pointer;
		current_x_pointer++;
		current_y_pointer++;
		if (current_x_pointer == last_x_pointer + 1 && current_y_pointer == last_y_pointer + 1)
		{
			current_x_pointer = first_x_pointer;
			current_y_pointer = first_y_pointer;
		}
		*current_x_pointer = *prev_x_pointer;
		*current_y_pointer = *prev_y_pointer + 1;
		snake.set_current_head_index(current_x_pointer, current_y_pointer);
	}
	else if (state == 3)
	{
		prev_x_pointer = current_x_pointer;
		prev_y_pointer = current_y_pointer;
		current_x_pointer++;
		current_y_pointer++;
		if (current_x_pointer == last_x_pointer + 1 && current_y_pointer == last_y_pointer + 1)
		{
			current_x_pointer = first_x_pointer;
			current_y_pointer = first_y_pointer;
		}
		*current_x_pointer = *prev_x_pointer + 1;
		*current_y_pointer = *prev_y_pointer;
		snake.set_current_head_index(current_x_pointer, current_y_pointer);
	}
	else
	{
		prev_x_pointer = current_x_pointer;
		prev_y_pointer = current_y_pointer;
		current_x_pointer++;
		current_y_pointer++;
		if (current_x_pointer == last_x_pointer + 1 && current_y_pointer == last_y_pointer + 1)
		{
			current_x_pointer = first_x_pointer;
			current_y_pointer = first_y_pointer;
		}
		*current_x_pointer = *prev_x_pointer - 1;
		*current_y_pointer = *prev_y_pointer;
		snake.set_current_head_index(current_x_pointer, current_y_pointer);
	}


	// check if the snake had crashed with borders
	if (*current_x_pointer == 0 || *current_x_pointer == map.get_width() - 1 || *current_y_pointer == 0 || *current_y_pointer == map.get_hight() - 1)
		lose = true;
	
	// check if the snake had eaten a food
	else if (*current_x_pointer == food_x && *current_y_pointer == food_y)
	{
		snake++;
		food.generate(map.get_width(), map.get_hight());
		score++;
	}

	// check if the snake had eaten itself
	else for (int i = 1; i < snake.get_length(); i++)
	{
		if (*current_x_pointer == *(current_x_pointer - i) && *current_y_pointer == *(current_y_pointer - i))
		{
			lose = true;
			break;
		}
	}
}