#pragma once
class Food
{
private:
	int location_x, location_y;
public:
	void generate(int,int);
	int get_location_x();
	int get_location_y();
};

