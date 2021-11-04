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




////###############################################
////		RIDER FUNCTIONS
////###############################################

//This function displays the options on the main Rider Page
vector <Rider_pid> rider_main(vector <Rider_pid>& rinput)
{
	vector <Rider_pid> rider_read_file_info;

	int rider_main_input;
	system("cls");
	disp_rider_logo();
	disp_h2_lines("Hello");
	disp_h3_lines("Select: ");
	cout << "\n\t1. Login\n";
	disp_dash_line();
	cout << "\n\t2. Register\n";
	cout << "\n\t3. Forgot Password\n";
	cout << "\n\t4. Back\n";
	disp_star_line();
	cout << "\tSelect [1], [2], [3], or [4]\n\tChoose: \n\t";
	cin >> rider_main_input;
	if (rider_main_input == 2)
	{
		system("cls");
		rider_register(rinput);
		writeRiderToFile(rinput);
		
		cout << "Rinput has been written to file? ";
	}
	rider_read_file_info=rider_retrieve_info();
	return (rider_read_file_info);
	//pswd_reset(rinput);
	//rretrieve = pswd_reset(rinput);

}


//This section takes rider input data from user
vector <Rider_pid> rider_register(vector <Rider_pid>& rinput)
{
	int rreg_confirmation;

	system("cls");
	disp_rider_logo();
	disp_h2_lines("Sign Up to Ride with Zebra!");
	disp_h3_lines("Enter your: ");

change_riderpid:
	Rider_pid ri;
	cin.ignore();
	cout << "\n\tFirst Name\t\t:  ";
	getline(cin, ri.r_fname);
	cout << "\tLast Name\t\t:  ";
	getline(cin, ri.r_lname);
	cout << "\tPreferred Name\t\t:  ";
	getline(cin, ri.r_pname);

	cin.ignore(0, 'n');
	cout << "\n\tContact #\t\t:  ";
	cin >> ri.r_contact;
	cin.ignore();
	cout << "\tPhysical Address\t:  ";
	getline(cin, ri.r_address);
valid_email:
	cout << "\n\tEnter Your Email Address";
	cout << "\n\t[Note: This will also";
	cout << "\n\tbe your username]\t:  ";
	getline(cin, ri.r_emailusrname);

	if (email_valid(ri.r_emailusrname) == 0)
	{
		cout << "\n\t!!Please enter a valid email address!!";
		goto valid_email;
	}
valid_pass:
	cout << "\n\tPassword";
	cout << "\n\t[Passwords must be";
	cout << "\n\tlonger than 8 chars,";
	cout << "\n\tcontain both numbers &";
	cout << "\n\tbig and small letters\t:  ";
	getline(cin, ri.r_pswd);
	if (pswd_valid(ri.r_pswd) == 0)
	{
		goto valid_pass;
	}

	cout << "\n";

	disp_dash_line();
	cout << "\tHello " << ri.r_pname << ", please check your details:";
	disp_dash_line();
	cout << "\t" << ri.r_fname << " " << ri.r_lname << "\n\t";
	cout << ri.r_contact << "\n\t";
	cout << ri.r_address << "\t[Note: This will be your default pickup address]\n\t";
	cout << ri.r_emailusrname << "\t\t[Reminder: This will be your username]\n\t";
	disp_star_line();
	cout << "\n\tIs your information correct?\t:  ";
	cout << "\n\tSelect [1] to confirm and [2] to edit:\n\t";
	cin >> rreg_confirmation;
	if (rreg_confirmation == 2)
	{
		goto change_riderpid;
	}

	rinput.push_back(ri);

	return rinput;
}

//This function stores details to the riderpid.csv file
void writeRiderToFile(vector <Rider_pid>& write_r)
{
	fstream riderpid_file("riderpid.csv", ios::app);
	for (int i = 0; i < write_r.size(); i++)
	{
		cout << "Your code made it here"; //debugging
		riderpid_file << write_r[i].r_fname << "," << write_r[i].r_lname << "," << write_r[i].r_pname << ",";
		riderpid_file << write_r[i].r_contact << "," << write_r[i].r_address << "," << write_r[i].r_emailusrname << ",";
		riderpid_file << write_r[i].r_pswd << endl;
	}

	riderpid_file.close();
}

//This function reads all of the values stored in the riderpid.csv file
vector <Rider_pid> rider_retrieve_info()
{
	fstream riderpid_file("riderpid.csv", ios::in);
	vector <Rider_pid> tempFile;

	Rider_pid read_r;
	string line;
	cout << "Your code made it here"; //debugging purposes

	while (getline(riderpid_file, line))
	{
		istringstream linestream(line);  //splitting row into cell values
		string get_val;
		getline(linestream, get_val, ',');
		read_r.r_fname = get_val;
		getline(linestream, get_val, ',');
		read_r.r_lname = get_val;
		getline(linestream, get_val, ',');
		read_r.r_pname = get_val;

		getline(linestream, get_val, ',');
		stringstream ss(get_val);
		ss >> read_r.r_contact;

		getline(linestream, get_val, ',');
		read_r.r_address = get_val;
		getline(linestream, get_val, ',');
		read_r.r_emailusrname = get_val;
		getline(linestream, get_val, ',');
		read_r.r_pswd = get_val;
		cout << "\n" << read_r.r_emailusrname << "\tyour code made it to pulling the username\n"; //debugging purposes
		cout << read_r.r_pswd << "\tyour code made it to pulling the pswd\n"; //debugging purposes

		tempFile.push_back(read_r);

	}
	riderpid_file.close();
	return(tempFile);
}


/////******#############***************CURRENTLY WORKING ON THIS!!!! *******************#################*************
//This function searches for the username and updates the corresponding password
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::out);

	string search_email, new_pswd;
	int reset_code = 0;
valid_emailusrname:
	cout << "\t\nPlease enter your email address:\t";
	cin >> search_email;
	disp_dash_line();
	cout << "\tPlease check your email to reset your password and enter your 5-digit password reset code below.\n";
	cout << "\t[For the purposes of this assignment, please enter 12345]\n";
	cout << "\tEnter password reset code:\t";
	cin >> reset_code; 
	if (reset_code == 12345)
	{
		for (int i = 0; i < read_from_file.size(); i++)
		{

			if (read_from_file[i].r_emailusrname == search_email)
			{
				//Keeping it simple to start:

				cout << "Email exists in database"; //debugging purposes
			valid_pass:
				cout << "\n\tEnter a new secure password:\t";
				cin >> new_pswd;
				if (pswd_valid(new_pswd) == 0)
				{
					cout << "New Pswd Invalid"; //debugging purposes
					goto valid_pass;
				}
				else
				{
					cout << "New Pswd valid - Writing to file"; //debugging purposes
					read_from_file[i].r_pswd = new_pswd;
				}

			}
			else
			{
				cout << "Email doesn't exist in database";
				goto valid_emailusrname;
			}
		
				
				
			/*valid_pass:
				cout << "\n\tEnter a new secure password:\t";
				cout << "\n\t[Passwords must be";
				cout << "\n\tlonger than 8 chars,";
				cout << "\n\tcontain both numbers &";
				cout << "\n\tbig and small letters\t:  ";
				getline(cin, new_pswd);
				if (pswd_valid(new_pswd) == 0)
				{
					goto valid_pass;
				}
				else
				{
					read_from_file[i].r_pswd = new_pswd;
				}
				
			}
			else
			{
				cout << "You don't have a Zebra account with that email address.\n\tPlease try again.";
				goto valid_emailusrname;
			}*/
			riderpid_file << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ","
			<< read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ","
			<< read_from_file[i].r_pswd << endl;
		}
	}
	riderpid_file.close();

	read_from_file = rider_retrieve_info();
	return (read_from_file);

}
