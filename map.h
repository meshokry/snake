#pragma once
class Map
{
private:
	int width, hight;
public:
	Map();
	Map(int, int);
	int get_width();
	int get_hight();
	void draw(int,int,int,int*,int*,int*,int*);
};

