#pragma once
#include "snake.h"
#include "map.h"
#include "food.h"
class Map
{
private:
	int width, hight;
public:
	Map();
	Map(int, int);
	int get_width();
	int get_hight();
	void draw(Snake*, Snake*, Food*, Map*);
};

