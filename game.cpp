#include "snake.h"
#include "map.h"
#include "food.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
//************************************************************************************************
int snake_score = 0;
int COM_score = 0;
bool snake_lose = false;
bool COM_lose = false;
bool solid_wall = true;
bool play_again = true;

void DATA_snake(Snake*, Snake*, Food*, Map*); // this function is the main function in the code (back end) of the player
void DATA_COM(Snake*, Snake*, Food*, Map*); // this function is the main function in the code (back end) of the computer

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


int main()
{	
	int width, hight;
	while (play_again)
	{
		cout << "Enter Map dimentions 'recomended: 25x25 ':\n" << "width: ";
		cin >> width;
		cout << "hight: ";
		cin >> hight;
		system("cls");
		cout << "Solid walls ??\n0.No\t1.Yes\n";
		cin >> solid_wall;
		system("cls");

		//****************************      initializing the main objects     ****************************

		Map map;
		Snake snake(map.get_width(), map.get_hight());
		Snake COM;
		Food food;

		//************************************************************************************************

		ShowConsoleCursor(0);  // hide cursor
		food.generate(map.get_width(), map.get_hight()); // generating food in random place

		map.draw(&COM, &snake, &food, &map);

		while (snake_lose == false && COM_lose == false)
		{
			system("cls"); // clear screen after each frame
			DATA_snake(&COM, &snake, &food, &map);
			DATA_COM(&snake, &COM, &food, &map);

			map.draw(&COM, &snake, &food, &map);

			cout << "player score: " << snake.get_length() - 3 << endl;
			cout << "COM score: " << COM.get_length() - 3;
		}

		Sleep(2000);
		system("cls");
		cout << "player score: " << snake.get_length() - 3 << "\n";
		cout << "COM score: " << COM.get_length() - 3 << "\n\n\n\n";
		if (snake_lose) cout << "COMPUTER WINS, HARD LUCK" << endl;
		else cout << "YOU WIN, CONGRATULATIONS";
		Sleep(5000); // delay function, it take inputs in milliseconds
		
		system("cls");
		cout << "play again??\n0.No\t1.Yes\n";
		cin >> play_again;
		system("cls");
		snake_lose = false;
		COM_lose = false;
	}
	return 0;
}


/*
	this function consists of three main sections
	1. change snake directions according to the input from the user
	2. check if the player had lost or not
	3. check if the snake had eaten a food or not
*/
void DATA_snake(Snake* COM, Snake* snake, Food* food, Map* map)
{
	node** snake_head = snake->get_head();
	node* snake_temp = *snake_head; // we need this pointer as a temporary pointer that take the previous value of the head pointer
	node** COM_head = COM->get_head();
	node* COM_temp = *COM_head;
	int food_x = food->get_location_x();
	int food_y = food->get_location_y();
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
		snake_temp = *snake_head;
		*snake_head = (*snake_head)->next;
		(*snake_head)->x = snake_temp->x;
		(*snake_head)->y = (snake_temp->y) - 1;
	}
	else if (state == 2)
	{
		snake_temp = *snake_head;
		*snake_head = (*snake_head)->next;
		(*snake_head)->x = snake_temp->x;
		(*snake_head)->y = (snake_temp->y) + 1;
	}
	else if (state == 3)
	{
		snake_temp = *snake_head;
		*snake_head = (*snake_head)->next;
		(*snake_head)->x = (snake_temp->x) + 1;
		(*snake_head)->y = snake_temp->y;
	}
	else
	{
		snake_temp = *snake_head;
		*snake_head = (*snake_head)->next;
		(*snake_head)->x = (snake_temp->x) - 1;
		(*snake_head)->y = snake_temp->y;
	}


	// check if the snake had crashed with borders
	if ((*snake_head)->x == 0 || (*snake_head)->x == map->get_width() - 1 || (*snake_head)->y == 0 || (*snake_head)->y == map->get_hight() - 1)
	{
		if (solid_wall)
			snake_lose = true;
		else if ((*snake_head)->x == 0) (*snake_head)->x = map->get_width() - 2;
		else if ((*snake_head)->x == map->get_width() - 1) (*snake_head)->x = 1;
		else if ((*snake_head)->y == 0) (*snake_head)->y = map->get_hight() - 2;
		else (*snake_head)->y = 1;
	}
	// check if the snake had eaten a food
	else if ((*snake_head)->x == food_x && (*snake_head)->y == food_y)
	{
		snake_temp = new node;
		snake_temp->next = (*snake_head)->next;
		((*snake_head)->next)->prev = snake_temp;
		(*snake_head)->next = snake_temp;
		snake_temp->prev = *snake_head;
		
		snake->operator++(1);
		food->generate(map->get_width(), map->get_hight());
		snake_score++;
	}

	// check if the snake had eaten itself or had eaten his friend
	else
	{
		snake_temp = *snake_head;
		for (int i = 1; i < snake->get_length(); i++)
		{
			if ((*snake_head)->x == (snake_temp->prev)->x && (*snake_head)->y == (snake_temp->prev)->y)
			{
				snake_lose = true;
				break;
			}
			snake_temp = snake_temp->prev;
		}
		COM_temp = *COM_head;
		for (int i = 1; i < COM->get_length(); i++)
		{
			if ((*snake_head)->x == COM_temp->prev->x && (*snake_head)->y == COM_temp->prev->y)
			{
				snake_lose = true;
				break;
			}
			COM_temp = COM_temp->prev;
		}
	}
}

void DATA_COM(Snake* snake, Snake* COM, Food* food, Map* map)
{
	node** snake_head = snake->get_head();
	node* snake_temp = *snake_head; // we need this pointer as a temporary pointer that take the previous value of the head pointer
	node** COM_head = COM->get_head();
	node* COM_temp = *COM_head;
	int food_x = food->get_location_x();
	int food_y = food->get_location_y();
	static int state = 3; // initial state (moving right)
	static int slow = 0;
	//state = 1; // move up
	//state = 2; // move down
	//state = 3; // move right
	//state = 4; // move left

	if (state == 1 && slow%2 == 0)
	{
		COM_temp = *COM_head;
		*COM_head = (*COM_head)->next;
		(*COM_head)->x = COM_temp->x;
		(*COM_head)->y = (COM_temp->y) - 1;

		if (food_y == (*COM_head)->y && food_x > (*COM_head)->x || food_y > (*COM_head)->y && food_x >= (*COM_head)->x) state = 3;
		else if (food_y == (*COM_head)->y && food_x < (*COM_head)->x || food_y >(*COM_head)->y && food_x <= (*COM_head)->x) state = 4;
	}
	else if (state == 2 && slow % 2 == 0)
	{
		COM_temp = *COM_head;
		*COM_head = (*COM_head)->next;
		(*COM_head)->x = COM_temp->x;
		(*COM_head)->y = (COM_temp->y) + 1;

		if (food_y == (*COM_head)->y && food_x > (*COM_head)->x || food_y < (*COM_head)->y && food_x >= (*COM_head)->x) state = 3;
		else if (food_y == (*COM_head)->y && food_x < (*COM_head)->x || food_y < (*COM_head)->y && food_x <= (*COM_head)->x) state = 4;
	}
	else if (state == 3 && slow % 2 == 0)
	{
		COM_temp = *COM_head;
		*COM_head = (*COM_head)->next;
		(*COM_head)->x = (COM_temp->x) + 1;
		(*COM_head)->y = COM_temp->y;

		if (food_x < (*COM_head)->x && food_y <= (*COM_head)->y || food_x == (*COM_head)->x && food_y < (*COM_head)->y) state = 1;
		else if (food_x < (*COM_head)->x && food_y >= (*COM_head)->y || food_x == (*COM_head)->x && food_y >(*COM_head)->y) state = 2;
	}
	else if(slow % 2 == 0)
	{
		COM_temp = *COM_head;
		*COM_head = (*COM_head)->next;
		(*COM_head)->x = (COM_temp->x) - 1;
		(*COM_head)->y = COM_temp->y;
		
		if (food_x > (*COM_head)->x && food_y <= (*COM_head)->y || food_x == (*COM_head)->x && food_y < (*COM_head)->y) state = 1;
		else if (food_x > (*COM_head)->x && food_y >= (*COM_head)->y || food_x == (*COM_head)->x && food_y > (*COM_head)->y) state = 2;
	}
	slow = slow + 1;

	// check if the snake had crashed with borders
	if ((*COM_head)->x == 0 || (*COM_head)->x == map->get_width() - 1 || (*COM_head)->y == 0 || (*COM_head)->y == map->get_hight() - 1)
	{
		if (solid_wall)
			COM_lose = true;
		else if ((*COM_head)->x == 0) (*COM_head)->x = map->get_width() - 2;
		else if ((*COM_head)->x == map->get_width() - 1) (*COM_head)->x = 1;
		else if ((*COM_head)->y == 0) (*COM_head)->y = map->get_hight() - 2;
		else (*COM_head)->y = 1;
	}

	// check if the snake had eaten a food
	else if ((*COM_head)->x == food_x && (*COM_head)->y == food_y)
	{
		COM_temp = new node;
		COM_temp->next = (*COM_head)->next;
		((*COM_head)->next)->prev = COM_temp;
		(*COM_head)->next = COM_temp;
		COM_temp->prev = *COM_head;

		COM->operator++(1);
		food->generate(map->get_width(), map->get_hight());
		COM_score++;
	}

	// check if the snake had eaten itself
	else
	{
		COM_temp = *COM_head;
		for (int i = 1; i < COM->get_length(); i++)
		{
			if ((*COM_head)->x == (COM_temp->prev)->x && (*COM_head)->y == (COM_temp->prev)->y)
			{
				COM_lose = true;
				break;
			}
			COM_temp = COM_temp->prev;
		}
		snake_temp = *snake_head;
		for (int i = 1; i < snake->get_length(); i++)
		{
			if ((*COM_head)->x == snake_temp->prev->x && (*COM_head)->y == snake_temp->prev->y)
			{
				COM_lose = true;
				break;
			}
			snake_temp = snake_temp->prev;
		}
	}
}