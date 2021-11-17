#ifndef ZEBRA_DRIVER_H
#define ZEBRA_DRIVER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include "zebra_rider.h"

using namespace std;

//Coder: Anastasiia Karpova
//File: zebra_driver.cpp
//Edited on: 4 Nov 2021
//Last Edited Date:  4 Nov 2021
//Purpose: This file contains the functions for the Zebra Driver


//STRUCTURE

struct Drivers
{
	string d_idAlph;
	int d_idNum;
	string fname;
	string sname;
	string pref_name;
	string phone_num;
	string mail;
	string password;
	string gender;
	string birth;
	string nationality;
	string lice_num;
	string doex;
	string exp;
	string veh_regist;
	string veh_age;
	string veh_model;
	string wof_exp;
	string bank_name;
	string bank_acc;
	Drivers(string alph="", int num = 0, string fn = "", string sn = "", string pn = "", string phn = "", string m = "", string pw = "", string g = "", string b = "", string n = "", string ln = "", string d = "", string vr = "", string va = "", string vm = "", string we = "", string bn = "", string ba = "", string e = "")
	
	{	
		d_idAlph = alph;
		d_idNum = num;
		fname = fn;
		sname = sn;
		pref_name = pn;
		phone_num = phn;
		mail = m;
		password = pw;
		gender =g;
		birth = b;
		nationality = n;
		lice_num = ln;
		doex = d;
		exp = e;
		veh_regist = vr;
		veh_age = va;
		veh_model = vm;
		wof_exp = we;
		bank_name = bn;
		bank_acc = ba;
	}
};

struct Trips
{

	string trip_id;
	string driver_id;
	string rider_id;
	string start_loc;
	string end_loc;
	double trip_cost;
	string trip_date;
	Trips(string trip = "", string di ="", string ri="", string sl = "", string el = "", double tc = 0, string td = "")
	{
		trip_id = trip;
		driver_id = di;
		rider_id = ri;
		start_loc = sl;
		end_loc = el;
		trip_cost = tc;
		trip_date = td;
	}
};



//###############################################
//		   Function Prototype
//###############################################

void driver_main();
void driver_eligibility(vector<Drivers>& driver, vector<Drivers>&driverFromFile, vector <Trips> trip, vector <Rider_pid> rider);
vector<Drivers> driver_login(vector<Drivers>& driverFromFile, vector <Trips> trip, vector <Rider_pid> rider);
void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile, vector <Trips> trip, vector <Rider_pid> rider);
vector <Drivers> input_drivers(vector<Drivers>& driver);
int count_entries_drive();
void writeToFile(vector<Drivers>& driver);//returns nothing
vector <Drivers> readFromFile();


vector<Drivers> update_acc_details(vector < Drivers > driverFromFile, string check_username, vector <Trips> trip, vector <Rider_pid> rider);


void output_drivers(vector<Drivers>& driver);
void driver_account_main(vector<Drivers>& driverFromFile, string check_username, vector <Trips> trip, vector <Rider_pid> rider);
void account_settings(vector<Drivers>& driverFromFile, string check_username, vector <Trips> trip, vector <Rider_pid> rider);
void job_screen(vector <Drivers> driver_rides, vector <Trips> trip, vector <Rider_pid> rider);

vector<Trips> input_trip_data(vector<Trips> trip, vector<Drivers> driverFromFile, vector <Rider_pid> rider, string check_name);
void write_to_trip_transactions(struct Trips trip);
vector <Trips> read_trips();
//vector <Trips> confirm_job_screen(vector<Trips> trip, string check_trip_id);

#endif