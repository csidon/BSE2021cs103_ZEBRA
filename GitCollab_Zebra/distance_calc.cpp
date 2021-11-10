//#include <iostream>
//#include<cmath>
//using namespace std;
////Coder: Anastasiia K
////File: distance_calc.cpp
////Edited on: 2 Nov 2021
////Last Edited Date:  2 Nov 2021
////Purpose: This file contains the decorative functions for the Zebra program
//
//struct Area {
//	double x;
//	double y;
//	string id;
//
//	Area(double x1, double y1, string id1)
//	{
//		x = x1;
//		y = y1;
//		id = id1;
//	}
//	Area()
//	{
//		x = 0.0;
//		y = 0.0;
//		id = "";
//	}
//};
//
//double calc(struct Area p, struct Area ptr)
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
//struct Area* input_B(struct Area* ptr)
//{
//	ptr->id = "Brooklyn";
//	ptr->x = 1.0;
//	ptr->y = 1.0;
//	ptr++;
//
//	ptr->id = "Hataitai";
//	ptr->x = 16.0;
//	ptr->y = 2.5;
//	ptr++;
//
//	ptr->id = "Aro_Valley";
//	ptr->x = 3.0;
//	ptr->y = 8.0;
//	ptr++;
//
//	ptr->id = "Kelburn";
//	ptr->x = 3.0;
//	ptr->y = 13.0;
//	ptr++;
//
//	ptr->id = "Te_Aro";
//	ptr->x = 8.0;
//	ptr->y = 8.0;
//	ptr++;
//
//	ptr->id = "Mt_Cook";
//	ptr->x = 6.5;
//	ptr->y = 4.3;
//	ptr++;
//	return (ptr);
//}
//
//bool set_coordinates(struct Area data_array[], struct Area* coordinates, string input)
//{
//	int arrSize = *(&data_array + 1) - data_array;
//	for (int i = 0; i < arrSize; i++)
//	{
//		//cout << i << endl;
//		if (input == data_array[i].id)
//		{
//			//cout << "\nDEBUG";
//			coordinates->x = data_array[i].x;
//			coordinates->y = data_array[i].y;
//			coordinates->id = data_array[i].id;
//			//cout << "\n"<<coordinates->id<<endl;
//			return(true);
//		}
//	}
//	return (false);
//}
//
//int main()
//{
//	double a;
//	Area coordinates_A, coordinates_B;
//	Area* p;
//	Area f[6];
//	p = f;
//	input_B(p);
//	for (int i = 0; i < 6; i++)
//	{
//		cout << f[i].id << endl;
//	}
//	set_coordinates(f, &coordinates_A, "Hataitai");
//	set_coordinates(f, &coordinates_B, "Brooklyn");
//	a = calc(coordinates_A, coordinates_B)/2;
//	cout << a;
//}