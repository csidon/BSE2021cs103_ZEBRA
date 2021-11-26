#ifndef ALLHEADERS_H
#define ALLHEADERS_H

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>

#include "zebra_rider.h"
#include "zebra_driver.h"


using namespace std;

//############################################################
//  ALL DEFINED STRUCTURES
//############################################################

//Used for distance calculation
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
////Coder: Anastasiia Karpova
////File: zebra_driver.cpp
////Edited on: 4 Nov 2021
////Last Edited Date:  21 Nov 2021
////Purpose: This file contains the functions for the Zebra Driver
//Used for all trip transactions
struct Trips
{
	string trip_id;
	string driver_id;
	string rider_id;
	string start_loc;
	string end_loc;
	double trip_cost;
	string trip_date;
	double trip_dist;

	Trips(string trip_i = "", string di = "", string ri = "", string sl = "", string el = "", double tc = 0, string td = "", double tdist = 0)
	{
		trip_id = trip_i;
		driver_id = di;
		rider_id = ri;
		start_loc = sl;
		end_loc = el;
		trip_cost = tc;
		trip_date = td;
		trip_dist = tdist;
	}
};

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
	Drivers(string alph = "", int num = 0, string fn = "", string sn = "", string pn = "", string phn = "", string m = "", string pw = "", string g = "", string b = "", string n = "", string ln = "", string d = "", string vr = "", string va = "", string vm = "", string we = "", string bn = "", string ba = "", string e = "")

	{
		d_idAlph = alph;
		d_idNum = num;
		fname = fn;
		sname = sn;
		pref_name = pn;
		phone_num = phn;
		mail = m;
		password = pw;
		gender = g;
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

//Coder: Chris C
//File: zebra_rider.cpp
//Edited on: 3 Nov 2021
//Last Edited Date:  3 Nov 2021
//Purpose: This file contains all functions specific to the rider

struct Rider_pid
{
	string r_fname, r_pname, r_lname, r_address, r_emailusrname, r_pswd, r_idalpha, r_defaultloc, r_cardholder_name, r_card_num, r_card_type, r_header_contact, r_headeridnum, r_headerexpiry, r_headercvv;
	int r_contact, r_idnum, r_expiry, r_cvv;

	//constructor
	Rider_pid(string rdl = "", string rfn = "", string rpn = "", string rln = "", string rad = "", string reu = "", string rpw = "", string ida = "", string rccn = "", string rccnum = "", string ct = "", string rhc = "", string rhi = "", string rhe = "", string rhcvv = "", int cex = 0, int cvv = 0, int idn = 0, int rcall = 0)
	{
		r_defaultloc = rdl;
		r_fname = rfn;
		r_lname = rln;
		r_pname = rpn;
		r_address = rad;
		r_emailusrname = reu;
		r_pswd = rpw;
		r_idalpha = ida;
		r_contact = rcall;
		r_idnum = idn;
		//payment specific vars
		r_card_type = ct;
		r_cardholder_name = rccn;
		r_card_num = rccnum;
		r_expiry = cex;
		r_cvv = cvv;
		//header specific vars
		r_header_contact = rhc;
		r_headeridnum = rhi;
		r_headerexpiry = rhe;
		r_headercvv = rhcvv;

	}
};

//This struct is not strictly necessary, but created with the thought of eventually having a rider-unique trip transaction file. Due to time constraints this was not realised
struct Rider_AllRidesInfo
{
	string rr_UIDalpha, rr_pname, rr_defaultloc, rr_startloc, rr_endloc, rr_pay_avail, rr_tripIDa;
	int rr_UIDnum, rr_tripCost, rr_gst, rr_netTripRevenue, rr_tripIDn;
	double rr_tripDist;

	//Constructor
	Rider_AllRidesInfo(string uida = "", string rpn = "", string rdl = "", string rsl = "", string rel = "", string pay = "", int uidn = 0, int tc = 0, int gst = 0, int ntr = 0, string tida = "", int tidn = 0, double tdist = 0)
	{
		rr_tripIDa = tida;
		rr_tripIDn = tidn;
		rr_UIDalpha = uida;
		rr_pname = rpn;
		rr_defaultloc = rdl;
		rr_endloc = rel;
		rr_UIDnum = uidn;
		rr_tripCost = tc;
		rr_gst = gst;
		rr_netTripRevenue = ntr;
		rr_pay_avail = pay;
		rr_tripDist = tdist;
	}
};








//############################################################
//  FUNCTION PROTOTYPE
//############################################################

// ------------------------------------------------------------[Functions used by both Riders and Drivers]
// DISTANCE CALCULATION/TRIP COST FUNCTIONS
//  Functions for distance calculation and fare charges 
// Function located in shared_functions.cpp, line 39
double calc(struct Location start, struct Location end);
struct Location* stored_locations(struct Location* ptr);
bool set_coordinates(struct Location data_array[], struct Location* coordinates, string input);
double main_dist_calc(string startLoc, string endLoc);
//---
string random_locations(int n);
void disp_fares_charges();
double calc_ride_cost(double distance);


//---------------------------------------------------
// TRIP TRANSACTION RELATED FUNCTIONS
// Function located in shared_functions.cpp, line 185
string currentDateTime();
void write_to_trip_transactions(Trips this_trip);
vector <Trips> read_from_trips();
int count_entries_trips();
struct Trips input_trip_data(vector <Rider_pid>& rider, vector<Drivers>& driverFromFile, vector <Trips>& trip, string check_name, string d_username);
string convert_string_to_upper(string& string_entry);


//---------------------------------------------------
// VALIDATION FUNCTIONS
// Function located in shared_functions.cpp, line 340
bool is_small_char(char c);
bool is_big_char(char C);
bool is_a_digit(const char d);
bool has_AT(char at);
bool has_dot(char dot);
bool has_space(char space);
//---
int creditcard_num_valid(string credit);
int email_valid(string remail);
int pswd_valid(string rpswd);
int check_dup(string input, string from_file);


//---------------------------------------------------
// MAKING PRETTY
// Function located in shared_functions.cpp, line 548
void disp_main_logo();
void disp_driver_regist();
void disp_zebra_driver();
void disp_rider_logo();
//---
void disp_h2_lines(string title);
void disp_h3_lines(string title);
//---
void disp_dash_line();
void disp_star_line();


// ------------------------------------------------------------[Functions used by Drivers only, found in zebra_driver.cpp]
void driver_main();

//registration part
void driver_eligibility(vector<Drivers>& driver, vector<Drivers>& driverFromFile);
vector<Drivers> driver_login(vector<Drivers>& driverFromFile);
void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile);

//login
vector<Drivers> driver_login(vector<Drivers>& driverFromFile);

//DRIVERS file manipulations
vector <Drivers> input_drivers(vector<Drivers>& driver);
int count_entries_drive();
void writeToFile(vector<Drivers>& driver);
vector<Drivers> pswd_reset_driver(vector <Drivers> driverFromFile);
vector <Drivers> readFromFile();
vector<Drivers> update_acc_details(vector < Drivers > driverFromFile, string check_username);

void driver_account_main(vector<Drivers>& driverFromFile, string check_username);
void account_settings(vector<Drivers> driverFromFile, string check_username);

void job_screen(vector <Rider_pid>& rider, string d_username);

struct Trips input_trip_data(vector <Rider_pid>& rider, vector<Drivers>& driverFromFile, vector <Trips>& trip, string check_name, string d_username);//USING FOR BITH OF US
int count_entries_trips();//USIGN FOR BOTH OF US

void confirm_job_screen(vector <Rider_pid>& rider, Trips trip_struct, string check_name);



// ------------------------------------------------------------[Functions used by Riders only, found in zebra_rider.cpp]
int count_entries();
int rider_main();

// Option 1: Rider login
Rider_pid r_login(vector <Rider_pid> read_from_file);
Rider_pid pay_details(Rider_pid& passed_pid_details);

// Option 2: Rider registration
Rider_pid rider_register();
void writeRiderToFile(Rider_pid write_r);

// Option 3: Forgot Password
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file);

//**************************************
//  Rider logged in function prototypes
//**************************************
void r_loggedIn_home(Rider_pid& userInfo);

//Location translates user's int input to location string so that distance can be calculated
string location_translate(int user_input);

//------------------------------------------------------------------------------------------------------------
//   Rider Booking-specific functions
// 
//Initiates a ride booking process when given riderpid structure, allrides information structure, and cost
Rider_pid book_ride(Rider_pid userPIDInfo, Rider_AllRidesInfo userRidesInfo, double cost);

//Shows available destination options after removing the pickup options from selection
string show_destination_options(Rider_AllRidesInfo rideInfo, int userInput);

//Displays all locations available for user to select
string show_pickup_options(Rider_AllRidesInfo rideInfo, int userInput);

//Recording trip data to write to trip_transactions.csv file
Trips input_rider_trip_data(Rider_AllRidesInfo indiv_rider);

//Functions to help output rider trip transaction reports
void indiv_rider_report(Rider_pid indiv_user);
string endloc_space_control(vector <Trips> read_length, int j);
string startloc_space_control(vector <Trips> read_length, int j);

//---End Rider Booking-specific functions ----------------------------------------------------------------------

//Search and Update functions
vector <Rider_pid> rider_retrieve_info();
vector <Rider_pid> searchAndUpdate_allUserDetails(Rider_pid& updateInfo);

#endif