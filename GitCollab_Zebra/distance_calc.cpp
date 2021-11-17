#include <iostream>
#include <string>
#include "distance_calc.h"
#include<cmath>

using namespace std;

////Coder: Anastasiia K
////File: distance_calc.cpp
////Edited on: 10 Nov 2021
////Last Edited Date:  11 Nov 2021
////Purpose: This file contains the distance CALCULATION for the Zebra program



//string random_locations(struct Location* stored, int n)
//{
//	//srand(time(NULL)); //initialize the random seed 
//	Location temp_loc;
//	//int randloc = rand() % 6; //generates a random number between  1 and 6
//	cout << stored[0].id;
//	temp_loc.id = stored[n].id;
//	string random_location = temp_loc.id;
//	//cout << randloc;
//	cout << n;
//	cout << "\n" << random_location;
//	return random_location;
//}


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

	ptr->id = "HATAITAI";
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

//*****************
//FUNCTION TO SET COORDINATES
//*****************

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
	//for (int i = 0; i < 6; i++)//debug
	//{
	//	cout << arr[i].id << endl;//
	//}
	//cout << "\n\tPlease enter a pick up location: ";
	//cin >> startLoc;
	//cout << "\n\tPlease enter a drop off location: ";
	//cin >> endLoc;
	set_coordinates(arr, &coordinates_A, startLoc);
	set_coordinates(arr, &coordinates_B, endLoc);
	dist = calc(coordinates_A, coordinates_B) / 2;
	cout << "The calculated distance between " << startLoc << " and " << endLoc << " is " << dist;
	return (dist);
}
//double main_dist_calc(string startAdd, string endAdd)
//{
//	Location data_store[6];
//	Location* storePlacePtr;
//	storePlacePtr = data_store;
//
//	stored_locations(storePlacePtr);
//	//this returns the calculated distance between the start and end address, taking the coordinates from the data_store array
//	double calculated_distance = get_coordinates(storePlacePtr, startAdd, endAdd);  
//	cout << "The calculated distance between " << startAdd << " and " << endAdd << " is " << calculated_distance;
//
//	return calculated_distance;
//
//}

//*************************************************************************************************************************
//  FUNCTION RETRIEVES COORDINATES FROM STORED LIST 
//  Gets coordinates based on entered string "location", and calls the calc function to calculate the dist between the two
//*************************************************************************************************************************
//double get_coordinates(struct Location* stored, string startLoc, string endLoc)
//{
//	Location start_coord, end_coord;
//
//	/*cout << "The size of stored location arrays is " << sizeof(stored);
//	cout << "The startlocation passed is " << startLoc;
//	cout << "The endlocation passed is " << endLoc;*/
//
//	for (int i = 0; i < 6; i++)
//	{
//		//cout << i << endl;//DEBUG
//		/*cout << "the stored location for " << i << " is " << stored[i].id;*/
//		if (startLoc == stored[i].id)
//		{
//			//cout << "\nDEBUG";
//			start_coord.x = stored[i].x;
//			start_coord.y = stored[i].y;
//			start_coord.id = stored[i].id;
//		}
//
//		if (endLoc == stored[i].id)
//		{
//			//cout << "\nDEBUG";
//			end_coord.x = stored[i].x;
//			end_coord.y = stored[i].y;
//			end_coord.id = stored[i].id;
//
//		}
//	}
//	return calc(start_coord, end_coord);
//}