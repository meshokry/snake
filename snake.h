#pragma once
class Snake
{
private:
	int length, head_locations_x[50], head_locations_y[50], *current_head_index_x,*current_head_index_y;
	/*
		length --> length of the snake
		head_locations_x & head_locations_y --> store the past head places
		
		note: snake is just a head and the tail is just following the head so we store head places (up to 50) and show only
		the head and finite number of past locations equal to the snake length so when snake eat length is raised and we will
		show extra spaces of our array

		current_head_index_x & current_head_index_y--> is a pointer to the current place of the head of the snake
	*/
public:
	Snake(int,int);
	void set_current_head_index(int* x,int* y);
	int get_length();
	int* get_current_head_x();
	int* get_current_head_y();
	int* get_locations_x();
	int* get_locations_y();
	void operator ++(int);
};

