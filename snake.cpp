#include <iostream>
#include "snake.h"


/*******************************  constructor to set initial data of the snake ****************************/
/*
    storing mechanism in head "from 1 to the end of the snake then 1 again" : structure : circurly doubly linked list
    - - -  - - -  - - -           -   -   - 
    | 1 |  | 2 |  | 3 |  -------> |  end  |    -----
    - - -  - - -  - - -           -   -   -        |
    ^                                              |
    |______________________________________________|
    
    at the constructor we want the initial shape of the snake be as follows Ooo and not only one head like this O
    so we want to add some tails at the beginning and we want the snake to be in the middle of the screen
 */
Snake::Snake()
{
    length = 3;
    node* p1 = new node;
    node* p2 = new node;
    node* p3 = new node;
    
    p1->x = 1;
    p1->y = 1;
    p2->x = 2;
    p2->y = 1;
    p3->x = 3;
    p3->y = 1;

    p1->next = p2;
    p1->prev = p3;
    p2->next = p3;
    p2->prev = p1;
    p3->next = p1;
    p3->prev = p2;

    head = p3;
}

Snake::Snake(int width,int hight)
{
    length = 3;

    node* p1 = new node;
    node* p2 = new node;
    node* p3 = new node;


    //setting the snake to be in the middle of the screen like this Ooo
    p1->x = width / 2 + 2;
    p2->x = width / 2 + 1;
    p3->x = width / 2;

    p1->y = hight / 2;
    p2->y = hight / 2;
    p3->y = hight / 2;

    p1->next = p2;
    p1->prev = p3;
    p2->next = p3;
    p2->prev = p1;
    p3->next = p1;
    p3->prev = p2;

    head = p3;
}

//**********************************************************************************************************

int Snake::get_length() // 0
{
    return length;
}

node** Snake::get_head()
{
    return &head;
}

void Snake::operator++(int) // overload ++ operator to increase the length of the snake by 1
{
    ++length;
}

