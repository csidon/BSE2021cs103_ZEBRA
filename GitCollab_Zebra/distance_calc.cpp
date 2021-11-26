#include <iostream>
#include <string>
#include "distance_calc.h"
#include<cmath>
#include "makepretty.h"
#include <iomanip>

using namespace std;

////Coder: Anastasiia K
////File: distance_calc.cpp
////Edited on: 10 Nov 2021
////Last Edited Date:  11 Nov 2021
////Purpose: This file contains the distance CALCULATION for the Zebra program


//*****************
//FOLMULA FOR CALCULATION ON A COORDINATE PLANE
//*****************
double calc(struct Location p, struct Location ptr)
{
	double dist;
	dist = sqrt(pow((p.x - ptr.x), 2) + pow((p.y - ptr.y), 2));
	return (dist);
}

//*****************
//MANUALY INPUTING COORDINATES USING POINTER
//*****************

struct Location* stored_locations(struct Location* ptr)
{
	ptr->id = "BROOKLYN";
	ptr->x = 1.0;
	ptr->y = 1.0;
	ptr++;

	ptr->id = "HAITAITAI";
	ptr->x = 16.0;
	ptr->y = 2.5;
	ptr++;

	ptr->id = "ARO_VALLEY";
	ptr->x = 3.0;
	ptr->y = 8.0;
	ptr++;

	ptr->id = "KELBURN";
	ptr->x = 3.0;
	ptr->y = 13.0;
	ptr++;


	ptr->id = "MT_COOK";
	ptr->x = 6.5;
	ptr->y = 4.3;
	ptr++;

	ptr->id = "TE_ARO";
	ptr->x = 8.0;
	ptr->y = 8.0;

	return (ptr);
}

//*****************************
//FUNCTION TO SET COORDINATES
//*****************************

bool set_coordinates(struct Location data_array[], struct Location* coordinates, string input)
{
	int arrSize = *(&data_array + 1) - data_array;//CALCULATING SIZE OF THE ARRAY
	for (int i = 0; i < arrSize; i++)
	{
		//cout << i << endl;//DEBUG
		if (input == data_array[i].id)
		{
			//cout << "\nDEBUG";
			coordinates->x = data_array[i].x;
			coordinates->y = data_array[i].y;
			coordinates->id = data_array[i].id;
			//cout << "\n"<<coordinates->id<<endl;//DEBUG
			return(true);
		}
	}
	return (false);
}


//****************************************************************************************************
//  MAIN FUNCTION FOR DISTANCE CALCULATOR: 
//Takes input for start and end location (preset strings) and calculates the distance between the two
//****************************************************************************************************

double main_dist_calc(string startLoc, string endLoc)
{
	double dist;
	Location coordinates_A, coordinates_B;
	Location* p;
	Location arr[6];
	p = arr;
	stored_locations(p);
	set_coordinates(arr, &coordinates_A, startLoc);
	set_coordinates(arr, &coordinates_B, endLoc);

	dist = calc(coordinates_A, coordinates_B) / 2;
	//cout << "The calculated distance between " << startLoc << " and " << endLoc << " is " << dist;
	return (dist);
}

string random_locations(int n)
{
	Location* ptr_location_stored;
	Location arr_of_loc[6];
	ptr_location_stored = arr_of_loc;

	stored_locations(ptr_location_stored);

	string random_location = arr_of_loc[n].id;
	//cout << "\n" << random_location;
	return random_location;
}

//****************************************************************************************************
//  FUNCTION TO CALCULATE COST BASED ON DISTANCE: 
//  Based off Ola and Uber's rate cards
//****************************************************************************************************

void disp_fares_charges()
{
	disp_star_line();
	disp_h3_lines("Zebra Taxi: Our Rate Card");
	cout << "\n\n\tBASE FARE";
	cout << "\n\tZebra charges a flat booking fee of 45 cents, and base fare\n\tof $1.10 for the first kilometer.\n";
	disp_dash_line();
	cout << "\n\tSUBSEQUENT RATE PER KM";
	cout << "\n\t$1.10 per km - The lowest rates in town!\n";
	disp_dash_line();
	cout << "\n\tMINIMUM FARE";
	cout << "\n\t$3.50\n";
	//cout << "\n\t[More to be added if there's time]\n\t";
	cout << "\n\t";

	
}

double calc_ride_cost(double distance)
{
	double calc_cost, subs_rate_per_km, base_fare;
	cout << fixed;
	cout << setprecision(2); //this sets cost price to 2 decimal places

	base_fare = 0.45 + 1.1;
	subs_rate_per_km = (distance - 1) * 1.1;
	calc_cost = base_fare + subs_rate_per_km;

	if (calc_cost < 3.5)
	{
		return (3.5);
	}
	else
	{
		return (calc_cost);
	}

}