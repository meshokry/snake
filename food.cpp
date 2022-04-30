#include "food.h"
#include <random>
#include<time.h>

void Food::generate(int width,int hight) // generating food at random place intire the map
{
	srand(time(0));
	location_x = rand() % (width - 2) + 1;
	location_y = rand() % (hight - 2) + 1;
}

int Food::get_location_x()//0
{
	return location_x;
}

int Food::get_location_y()//0
{
	return location_y;
}
