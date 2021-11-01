#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "zebra_rider.h"
#include "makepretty.h"
#include "pswd_email_validation.h"

using namespace std;

//Coder: Chris C
//File: zebra_rider.cpp
//Purpose: This file contains the main functions for Zebra Rider


//struct Rider_pid
//{
//	string r_fname, r_pname, r_lname, r_address, r_emailusrname, r_pswd;
//	int r_contact;
//
//	//constructor
//	Rider_pid(string rfn = "", string rpn = "", string rln = "", string rad = "", string reu = "", string rpw = "", int rcall = 0)
//	{
//		r_fname = rfn;
//		r_lname = rln;
//		r_pname = rpn;
//		r_address = rad;
//		r_emailusrname = reu;
//		r_pswd = rpw;
//		r_contact = rcall;
//	}
//};
//
////###############################################
////		RIDER FUNCTIONS
////###############################################
//
//void rider_main(vector <Rider_pid>& rinput, vector <Rider_pid>& rretrieve)
//{
//	int rider_main_input;
//	system("cls");
//	disp_rider_logo();
//	disp_h2_lines("Hello");
//	disp_h3_lines("Select: ");
//	cout << "\n\t1. Login\n";
//	disp_dash_line();
//	cout << "\n\t2. Register\n";
//	cout << "\n\t3. Forgot Password\n";
//	cout << "\n\t4. Back\n";
//	disp_star_line();
//	cout << "\tSelect [1], [2], [3], or [4]\n\tChoose: \n\t";
//	cin >> rider_main_input;
//	if (rider_main_input == 2)
//	{
//		system("cls");
//		rider_register(rinput);
//	}
//}