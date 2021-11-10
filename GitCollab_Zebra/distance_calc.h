#ifndef DISTANCE_CALC_H
#define DISTANCE_CALC_H

#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>

using namespace std;

struct Area {
	double x;
	double y;
	string id;

	//Area(double x1, double y1, string id1)
	//{
	//	x = x1;
	//	y = y1;
	//	id = id1;
	//}
	//*****************
	//CONSTRUCTURE
	//*****************
	Area()//default structure
	{
		x = 0.0;
		y = 0.0;
		id = "";
	}
};

double calc(struct Area p, struct Area ptr);
struct Area* input(struct Area* ptr);
bool set_coordinates(struct Area data_array[], struct Area* coordinates, string input);
double dist_calc_main();

#endif