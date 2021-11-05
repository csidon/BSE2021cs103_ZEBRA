#ifndef ZEBRA_DRIVER_H
#define ZEBRA_DRIVER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//Coder: Anastasiia Karpova
//File: zebra_driver.cpp
//Edited on: 4 Nov 2021
//Last Edited Date:  4 Nov 2021
//Purpose: This file contains the functions for the Zebra Driver


//STRUCTURE

struct Drivers
{
	string fname;
	string sname;
	string pref_name;
	string phone_num;
	string address;
	string mail;
	string password;
	Drivers(string fn = "", string sn = "", string pn = "", string phn = "", string ad = "", string m = "", string pw = "")
	{
		fname = fn;
		sname = sn;
		pref_name = pn;
		phone_num = phn;
		address = ad;
		mail = m;
		password = pw;
	}
};


//###############################################
//		Function Prototype
//###############################################

void driver_main();
void driver_eligibility(vector<Drivers>& driver, vector<Drivers>&driverFromFile);
//void driver_login();
void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile);
vector <Drivers> input_drivers(vector<Drivers>& driver);
void writeToFile(vector<Drivers>& driver);//returns nothing
//vector <Drivers> readFromFile();
//vector<Drivers> searchAndUpdate(vector < Drivers > driverrFromFile);
void output_drivers(vector<Drivers>& driver);

#endif