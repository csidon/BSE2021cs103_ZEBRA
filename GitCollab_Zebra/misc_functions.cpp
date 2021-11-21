#pragma warning(disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "zebra_rider.h"
#include "zebra_driver.h"
#include "makepretty.h"
#include "pswd_email_validation.h"
#include "misc_functions.h"
#include "distance_calc.h"
#include <ctime>


using namespace std;

////Coder: Chris C
////File: small_misc.cpp
////Edited on: 7 Nov 2021
////Last Edited Date:  7 Nov 2021
////Purpose: This file contains small misc functions that can be used globally in the program


string convert_string_to_upper(string &string_entry)
{
	char c;
	string converted_string;
	for (int i = 0; i < string_entry.length(); i++)
	{
		c = toupper(string_entry[i]);
		converted_string += c;
	}

	//cout << "\n This is the converted string " << converted_string;  //for debugging purposes
	return converted_string;
}

//ALL
string currentDateTime()
{
	time_t now = time(0);// current date/time based on current system
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	cout << buf;
	return(buf);
}

//RIDER ONLY
Trips input_rider_trip_data(Rider_AllRidesInfo indiv_rider)
{
	vector <Trips> allTrips;
	vector <Drivers> driverFromFile;
	Trips t;

	allTrips = read_allTrips();
	driverFromFile = readFromFile();
	//Randomising a driver for this trip
	srand(time(NULL)); //initialize the random seed
	int rand_driver = rand() % driverFromFile.size();
	//cout << "\nDEBUGGING: What is the driverFromFile size? " << driverFromFile.size();
	//cout << "\nDEBUGGING: What is the random driver index number? " << rand_driver;
	
	string rand_driver_alpha = driverFromFile[rand_driver].d_idAlph;
	string rand_driver_num = to_string(driverFromFile[rand_driver].d_idNum);
	string rand_driver_combined_id = rand_driver_alpha + rand_driver_num;

	string rider_alpha = indiv_rider.rr_UIDalpha;
	string rider_num = to_string(indiv_rider.rr_UIDnum);
	string rider_combined_id = rider_alpha + rider_num;
	//cout << "\nDEBUGGING: userRidesInfo after passing to input_rider_trip_data (now indiv_rider) is: " << indiv_rider.rr_UIDalpha << indiv_rider.rr_UIDnum;

	string count_entries_string = to_string(count_entries_trips_chrisTest() + 1);
	t.trip_id = "TR" + count_entries_string;
	t.driver_id = rand_driver_combined_id;
	t.rider_id = rider_combined_id;
	t.start_loc = indiv_rider.rr_startloc;
	t.end_loc = indiv_rider.rr_endloc;
	t.trip_cost = main_dist_calc(t.start_loc, t.end_loc);
	t.trip_date = currentDateTime();
	//cout << "\nDEBUGGING: Trip ID = " << t.trip_id << "\tDriver ID = " << t.driver_id << "\tRider ID = " << t.rider_id;
	//cout << "\nDEBUGGING: Trip startLoc = " << t.start_loc << "\tEnd loc = " << t.end_loc << "\tTrip cost = " << t.trip_cost << "\tTrip Date = " << t.trip_date;
	return(t);
}


//ALL -- ***********CHECK WITH ANA!!! I PASSSED A STRUCT, NOT VECTOR, FOR ARGUMENT!!!********
void write_to_trip_transactions(Trips this_trip)
{
	fstream trip_file("trip_transactions_chris.csv", ios::app);
	trip_file << this_trip.trip_id << "," << this_trip.driver_id << "," << this_trip.rider_id << "," << this_trip.start_loc << ",";
	trip_file << this_trip.end_loc << "," << this_trip.trip_cost << "," << this_trip.trip_date << endl ;

	trip_file.close();
}



vector <Trips> read_allTrips()
{
	fstream tripFile("trip_transactions_chris.csv", ios::in);
	vector <Trips> temp_trip;
	Trips t;

	string line;
	while (getline(tripFile, line))
	{
		istringstream linestream(line);
		string single_trip;

		getline(linestream, single_trip, ',');
		t.trip_id = single_trip;

		getline(linestream, single_trip, ',');
		t.driver_id = single_trip;

		getline(linestream, single_trip, ',');
		t.rider_id = single_trip;

		getline(linestream, single_trip, ',');
		t.start_loc = single_trip;

		getline(linestream, single_trip, ',');
		t.end_loc = single_trip;

		getline(linestream, single_trip, ',');
		stringstream ss(single_trip);
		ss >> t.trip_cost;

		getline(linestream, single_trip, ',');
		t.trip_date = single_trip;

		temp_trip.push_back(t);
	}

	tripFile.close();

	return (temp_trip);
}

void indiv_rider_report(Rider_pid indiv_user)
{
	vector <Trips> read_from_allTrips;
	read_from_allTrips = read_allTrips();
	fstream allTrips_file("trip_transactions_chris.csv", ios::in);
	string indiv_userID = indiv_user.r_idalpha + to_string(indiv_user.r_idnum);
	//cout << "\nDEBUGGING: The combined rider's userID alpha and num is " << indiv_userID;

	string title_msg = "Ride History for ";
	string rider_name = indiv_user.r_pname;
	string full_title = title_msg + rider_name;

	disp_h2_lines(full_title);
	cout << "\n\tDate/Time\tTrip #\tDriver ID\tPickup from\tDropoff at\t\tCost\n";
	for (int i = 0; i < read_from_allTrips.size(); i++)
	{
		//cout << "\nDEBUGGING: The combined riderID from the all trip transactions file is " << read_from_allTrips[i].rider_id <<endl; 
		if (indiv_userID == read_from_allTrips[i].rider_id)
		{
			cout << "\t" << read_from_allTrips[i].trip_date << "\t\t" << read_from_allTrips[i].trip_id << "\t" << read_from_allTrips[i].driver_id;
			cout << "\t" << read_from_allTrips[i].start_loc << "\t" << read_from_allTrips[i].end_loc << "\t\t" << read_from_allTrips[i].trip_cost << endl;
		}
	}
}


//void confirm_job_screen(vector <Rider_pid>& rider, vector<Trips>& trip, string check_name)
//{
//	vector <Drivers> driver;
//	Trips t;
//	//fstream tripFile("trip_transactions.csv", ios::in);
//	fstream riderFile("riderpid.csv", ios::in);
//	rider = rider_retrieve_info();
//	//trip = read_from_trips();
//	for (int i = 0; i < rider.size(); i++)
//	{
//		if (check_name == rider[i].r_pname)
//		{
//			cout << "\n\n\n\tYour are picking up:	 " << rider[i].r_pname;
//		}
//	}
//	riderFile.close();
//	cout << "\n\tTrip number is:	" << t.trip_id << "\t" << t.trip_date;
//	cout << "\n\tFrom:	" << t.start_loc;
//	cout << "\n\tDestination:		" << t.end_loc;
//	trip.push_back(t);
//
//	//tripFile.close();
//
//	string check_username;
//	cout << "\n\tPress any button when you've picked them up";
//	cout << "\n\t[CANCEL] to cancel this booking";
//	cout << "\n\tChoose: ";
//	string choice;
//	cin >> choice;
//	if (choice == "CANCEL")
//	{
//
//		cout << "\n\tEnter you username to continue	: ";
//		cin >> check_username;
//		cout << "\n\tWARNING! You are about to cancel booking. Would you like to continue?";
//		cout << "\n\t[Y] for yes. [N] for no: ";
//		char can_choice;
//		cin >> can_choice;
//		if (can_choice == 'Y')
//		{
//			driver_account_main(driver, check_username);
//		}
//	}
//	else
//	{
//		cout << "\n\tAwesome! Press ant button when you've dropped them off";
//		cout << "\n\tEnter you username to to access billing info	: ";
//		cin >> check_username;
//		trip.push_back(t);
//		cout << "\n\tNice! You have earned " << t.trip_cost;
//		system("pause");
//		driver_account_main(driver, check_username);
//	}
//	//return (trip);
//
//}