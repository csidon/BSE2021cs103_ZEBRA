#ifndef DISTANCE_CALC_H
#define DISTANCE_CALC_H

#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Location {
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
	Location()//default structure
	{
		x = 0.0;
		y = 0.0;
		id = "";
	}
};

//function prototype
struct Location* stored_locations(struct Location* ptr);
double main_dist_calc(string startLoc, string endLoc);
//double get_coordinates(struct Location* stored, string startLoc, string endLoc);
double calc(struct Location start, struct Location end);
string random_locations(int n);

//Functions for fare charges [Used by both Rider and Driver]
void disp_fares_charges();
double calc_ride_cost(double distance);

#endif