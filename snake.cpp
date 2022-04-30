#include <iostream>
#include "snake.h"

/*******************************  constructor to set initial data of the snake ****************************/
/*
    storing mechanism in head array "from 1 to 50 then 1 again" :
    - - -  - - -  - - -           -   -  - 
    | 1 |  | 2 |  | 3 |  -------> |  50  |    -----
    - - -  - - -  - - -           -   -  -        |
    ^                                             |
    |_____________________________________________|
    
    at the constructor we want the initial shape of the snake be as follows Ooo and not only one head like this O
    so we want to add some tails at the beginning and we want the snake to be in the middle of the screen
 */
Snake::Snake(int width,int hight)
{
    length = 3;
    current_head_index_x = &head_locations_x[2];
    current_head_index_y = &head_locations_y[2];

    //setting the snake to be in the middle of the screen like this Ooo
    head_locations_x[0] = width / 2 + 2;
    head_locations_x[1] = width / 2 + 1;
    head_locations_x[2] = width / 2;
  //=====================================
    head_locations_y[0] = hight / 2;
    head_locations_y[1] = hight / 2;
    head_locations_y[2] = hight / 2;
}

//**********************************************************************************************************


void Snake::set_current_head_index(int* x, int* y) // update the pointer to the head when we add new head location
{
    current_head_index_x = x;
    current_head_index_y = y;
}

int Snake::get_length() // 0
{
    return length;
}

int* Snake::get_current_head_x() // 0
{
    return current_head_index_x;
}

int* Snake::get_current_head_y() // 0
{
    return current_head_index_y;
}

int* Snake::get_locations_x() // return a pointer to the first place in the array of x
{
    return head_locations_x;
}

int* Snake::get_locations_y() // return a pointer to the first place in the array of y
{
    return head_locations_y;
}

void Snake::operator++(int) // overload ++ operator to increase the length of the snake by 1
{
    ++length;
}
