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
	string r_fname, r_pname, r_lname, r_address, r_emailusrname, r_pswd;
	int r_contact;

	//constructor
	Rider_pid(string rfn = "", string rpn = "", string rln = "", string rad = "", string reu = "", string rpw = "", int rcall = 0)
	{
		r_fname = rfn;
		r_lname = rln;
		r_pname = rpn;
		r_address = rad;
		r_emailusrname = reu;
		r_pswd = rpw;
		r_contact = rcall;
	}
};

//Rider Main function prototypes
void rider_main(vector <Rider_pid>& rinput, vector <Rider_pid>& rretrieve);
vector <Rider_pid> rider_register(vector <Rider_pid>& rinput);
void writeRiderToFile(vector <Rider_pid>& write_r);
vector <Rider_pid> rider_retrieve_info();
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file);

#endif