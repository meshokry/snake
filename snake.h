#pragma once
struct node { int x, y; node* next; node* prev; };
class Snake
{
private:
	
	int length; node* head;
	/*
		note: snake is just a head and the tail is just following the head so we store head places (up to 50) and show only
		the head and finite number of past locations equal to the snake length so when snake eat length is raised and we will
		show extra spaces of our array
	*/
public:
	Snake();
	Snake(int,int);
	int get_length();
	node** get_head();
	void operator ++(int);
};

