#ifndef MISCFUNC_H
#define MISCFUNC_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "zebra_driver.h"

using namespace std;

//Coder: Chris C
//File: makepretty.cpp
//Edited on: 2 Nov 2021
//Last Edited Date:  2 Nov 2021
//Purpose: This file contains the decorative functions for the Zebra program


//###############################################
//		Function Prototype
//###############################################
//Misc functions available for global use
string convert_string_to_upper(string& string_entry);
Trips input_rider_trip_data(Rider_AllRidesInfo indiv_rider);
void write_to_trip_transactions(Trips this_trip);
vector <Trips> read_from_trips();
string currentDateTime();
void indiv_rider_report(Rider_pid indiv_user);

#endif