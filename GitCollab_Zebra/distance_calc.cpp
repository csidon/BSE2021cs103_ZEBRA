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


//****************************************************************************************************
//  MAIN FUNCTION FOR DISTANCE CALCULATOR: 
//Takes input for start and end location (preset strings) and calculates the distance between the two
//****************************************************************************************************
double main_dist_calc(string startAdd, string endAdd)
{
	Location data_store[6];
	Location* storePlacePtr;
	storePlacePtr = data_store;

	stored_locations(storePlacePtr);
	//this returns the calculated distance between the start and end address, taking the coordinates from the data_store array
	double calculated_distance = get_coordinates(storePlacePtr, startAdd, endAdd);  
	cout << "The calculated distance between " << startAdd << " and " << endAdd << " is " << calculated_distance;

	return calculated_distance;

}

//*************************************************************************************************************************
//  FUNCTION RETRIEVES COORDINATES FROM STORED LIST 
//  Gets coordinates based on entered string "location", and calls the calc function to calculate the dist between the two
//*************************************************************************************************************************
double get_coordinates(struct Location* stored, string startLoc, string endLoc)
{
	Location start_coord, end_coord;

	/*cout << "The size of stored location arrays is " << sizeof(stored);
	cout << "The startlocation passed is " << startLoc;
	cout << "The endlocation passed is " << endLoc;*/

	for (int i = 0; i < 6; i++)
	{
		//cout << i << endl;//DEBUG
		/*cout << "the stored location for " << i << " is " << stored[i].id;*/
		if (startLoc == stored[i].id)
		{
			//cout << "\nDEBUG";
			start_coord.x = stored[i].x;
			start_coord.y = stored[i].y;
			start_coord.id = stored[i].id;
		}

		if (endLoc == stored[i].id)
		{
			//cout << "\nDEBUG";
			end_coord.x = stored[i].x;
			end_coord.y = stored[i].y;
			end_coord.id = stored[i].id;

		}
	}
	return calc(start_coord, end_coord);
}


////********************************************************
//// FUNCTION CALCULATES DISTANCE BETWEEN TWO LOCATIONS
////********************************************************
double calc(struct Location start, struct Location end)
{
	double dist;
	dist = sqrt(pow((start.x - end.x), 2) + pow((start.y - end.y), 2));
	return (dist);
}


//***************************************************************************
// STORES THE COORDINATES OF A PREDEFINED SET OF LOCATIONS (based on map.ai)
//***************************************************************************

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


////*****************
////FOLMULA FOR CALCULATION ON A COORDINATE PLANE
////*****************
//double calc(struct Area p, struct Area ptr)
//{
//	double dist;
//	dist = sqrt(pow((p.x - ptr.x), 2) + pow((p.y - ptr.y), 2));
//	return (dist);
//}

//struct Area* input_A(struct Area *p)
//>>>>>>> d134a2ef987422811d9cd507a235e34385faadc6
//{
//	double dist;
//	dist = sqrt(pow((p.x - ptr.x), 2) + pow((p.y - ptr.y), 2));
//	return (dist);
//}
//
////struct Area* input_A(struct Area *p)
////{
////	p = NULL;
////	p = new Area(1.0, 1.0, "Brooklyn");
////	p++;
////
////	p = NULL;
////	p = new Area(16.0, 2.5, "Hataitai");
////	p++;
////
////	p = NULL;
////	p = new Area(3.0, 8.0, "Aro_Valley");
////	p++;
////
////	p = NULL;
////	p = new Area(3.0, 13.0, "Kelburn");
////	p++;
////
////	p = NULL;
////	p = new Area(8.0, 8.0, "Te_Aro");
////	p++;
////
////	p = NULL;
////	p = new Area(6.5, 4.3, "Mt_Cook");
////	return (p);
////}
//
//


//*****************
//MANUALY INPUTING COORDINATES USING POINTER
//*****************

//struct Area* input(struct Area* ptr)
//{
//	ptr->id = "BROOKLYN";
//	ptr->x = 1.0;
//	ptr->y = 1.0;
//	ptr++;
//
//	ptr->id = "HATAITAI";
//	ptr->x = 16.0;
//	ptr->y = 2.5;
//	ptr++;
//
//	ptr->id = "ARO_VALLEY";
//	ptr->x = 3.0;
//	ptr->y = 8.0;
//	ptr++;
//
//	ptr->id = "KELBURN";
//	ptr->x = 3.0;
//	ptr->y = 13.0;
//	ptr++;
//
//
//	ptr->id = "MT_COOK";
//	ptr->x = 6.5;
//	ptr->y = 4.3;
//	ptr++;
//
//	ptr->id = "TE_ARO";
//	ptr->x = 8.0;
//	ptr->y = 8.0;
//
//	return (ptr);
//}
//
////*****************
////FUNCTION TO SET COORDINATES
////*****************
//
//bool set_coordinates(struct Area data_array[], struct Area* coordinates, string input)
//{
//	int arrSize = *(&data_array + 1) - data_array;//CALCULATING SIZE OF THE ARRAY
//	for (int i = 0; i < arrSize; i++)
//	{
//		//cout << i << endl;//DEBUG
//		if (input == data_array[i].id)
//		{
//			//cout << "\nDEBUG";
//			coordinates->x = data_array[i].x;
//			coordinates->y = data_array[i].y;
//			coordinates->id = data_array[i].id;
//			//cout << "\n"<<coordinates->id<<endl;//DEBUG
//			return(true);
//		}
//	}
//	return (false);
//}
//
////*****************
////MAIN FUNCTION
////*****************
//
//double dist_calc_main()
//{
//	double dist;
//	string a, b;
//	Area coordinates_A, coordinates_B;
//	Area* p;
//	Area arr[6];
//	p = arr;
//	input(p);
//	for (int i = 0; i < 6; i++)//debug
//	{
//		cout << arr[i].id << endl;//
//	}
//	cout << "\n\tPlease enter a pick up location: ";
//	cin >> a;
//	cout << "\n\tPlease enter a drop off location: ";
//	cin >> b;
//	set_coordinates(arr, &coordinates_A, a);
//	set_coordinates(arr, &coordinates_B, b);
//	dist = calc(coordinates_A, coordinates_B)/2;
//	cout <<"\n\tThe distance between to points is: "<< dist<<" KM";
//	return (dist);
//}
