#ifndef ZEBRA_RIDER_H
#define ZEBRA_RIDER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//Coder: Chris C
//File: zebra_rider.cpp
//Edited on: 3 Nov 2021
//Last Edited Date:  3 Nov 2021
//Purpose: This file contains all functions specific to the rider

struct Rider_pid
{
	string r_fname, r_pname, r_lname, r_address, r_emailusrname, r_pswd, r_idalpha, r_defaultloc;
	int r_contact, r_idnum;

	//constructor
	Rider_pid(string rdl = "", string rfn = "", string rpn = "", string rln = "", string rad = "", string reu = "", string rpw = "", string ida = "", int idn = 0, int rcall = 0)
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
	}
};

struct Rider_ridestore
{
	string rr_UIDalpha, rr_pname, rr_defaultloc, rr_startloc, rr_endloc;
	int rr_UIDnum, rr_tripCost, rr_gst, rr_netTripRevenue;

	//Constructor
	Rider_ridestore(string uida = "", string rpn = "", string rdl = "", string rsl = "", string rel = "", int uidn = 0, int tc = 0, int gst = 0, int ntr = 0)
	{
		rr_UIDalpha = uida;
		rr_pname = rpn; 
		rr_defaultloc = rdl;
		rr_endloc = rel;
		rr_UIDnum = uidn;
		rr_tripCost = tc;
		rr_gst = gst;
		rr_netTripRevenue = ntr;
	}
};

//Rider Main function prototypes
int count_entries();
vector <Rider_pid> rider_main(vector <Rider_pid>& rinput);
vector <Rider_pid> rider_register(vector <Rider_pid>& rinput);
void writeRiderToFile(vector <Rider_pid>& write_r);
vector <Rider_pid> rider_retrieve_info();
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file);
void r_loggedIn_home(vector <Rider_pid>& rinput, Rider_ridestore& nopid_details);
Rider_ridestore r_login(vector <Rider_pid> temp_pull_file);
vector<Rider_pid> searchAndUpdate_defaultloc(Rider_ridestore& nopid_details, vector <Rider_pid> read_from_file);
string location_translate(int user_input);
void disp_fares_charges();

#endif