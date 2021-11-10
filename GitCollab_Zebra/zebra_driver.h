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
	string d_idAlph;
	int d_idNum;
	string fname;
	string sname;
	string pref_name;
	string phone_num;
	string address;
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
	Drivers(string alph="", int num = 0, string fn = "", string sn = "", string pn = "", string phn = "", string ad = "", string m = "", string pw = "", string g = "", string b = "", string n = "", string ln = "", string d = "", string vr = "", string va = "", string vm = "", string we = "", string bn = "", string ba = "", string e = "")
	
	{	
		d_idAlph = alph;
		d_idNum = num;
		fname = fn;
		sname = sn;
		pref_name = pn;
		phone_num = phn;
		address = ad;
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


//###############################################
//		Function Prototype
//###############################################

void driver_main();
void driver_eligibility(vector<Drivers>& driver, vector<Drivers>&driverFromFile);
vector<Drivers> driver_login(vector<Drivers>& driverFromFile);
void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile);
vector <Drivers> input_drivers(vector<Drivers>& driver);
int count_entries_drive();
void writeToFile(vector<Drivers>& driver);//returns nothing
vector <Drivers> readFromFile();
//vector<Drivers> searchAndUpdate(vector < Drivers > driverrFromFile);
void output_drivers(vector<Drivers>& driver);
void driver_account_main(vector<Drivers>& driverFromFile);
void account_settings(vector<Drivers>& driverFromFile);

#endif