#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "zebra_rider.h"
#include "makepretty.h"
#include "pswd_email_validation.h"
#include "misc_functions.h"

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
	vector <Rider_ridestore> rider_temp_file_info;

	int rider_main_input;
rider_main_page:
	system("cls");
	cout << "Number of lines currently in file are " << count_entries(); //debugging
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

	//This section calls the Rider Registration function 
	if (rider_main_input == 1)
	{
		system("cls");
		
		r_login(rider_read_file_info);
		system("pause");
		goto rider_main_page;
	}
	else if (rider_main_input == 2)
	{
		system("cls");
		rider_register(rinput);
		writeRiderToFile(rinput);
		
		cout << "Rinput has been written to file! "; //debugging purposes
		cout << "\nYou are now a Zebra Rider!\n";
		system("pause");
		goto rider_main_page;
		
	}
	//This section calls the password reset function 
	else if (rider_main_input == 3)
	{
		rider_read_file_info = rider_retrieve_info();

		rider_read_file_info = pswd_reset(rider_read_file_info);
		cout << "\n\t Password reset successful :)\n";
		system("pause");
		goto rider_main_page;
	}

	return (rider_read_file_info);

}

//This function searches to find the username in the database, and checks that the password corresponds
vector <Rider_pid> r_login(vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::out);
	Rider_ridestore tempRider;

	string r_emailusrname_check, r_pswd_check;
	int login_success = 0, email_exists = 0;
valid_emailusrname:
	cout << "\n\tUsername:\t";
	cin >> r_emailusrname_check;
	cout << "\n\Password:\t";
	cin >> r_pswd_check;
	disp_dash_line();
	read_from_file = rider_retrieve_info();
	cout << "\nCode made it to receiving user input\ntemp_pull_file.size() is " << read_from_file.size();
	//searching for the provided email address/username
	for (int i = 0; i < read_from_file.size(); i++)
	{
		cout << "\nCode made it to forloop\n";
		
		cout << "\nDebugging usernames available STAGE 2\t" << read_from_file[i].r_emailusrname;
		if (read_from_file[i].r_emailusrname == r_emailusrname_check)
		{
			cout << "\tEmail exists in database\n"; //debugging purposes
			cout << "\nDebugging usernames available Emails Exist\t" << read_from_file[i].r_emailusrname;
			email_exists += 1;
			//If email exists, check if password matches
			if (read_from_file[i].r_pswd == r_pswd_check)
			{
				
				tempRider.rr_UIDalpha = read_from_file[i].r_idalpha;
				tempRider.rr_UIDnum = read_from_file[i].r_idnum;
				tempRider.rr_pname = read_from_file[i].r_pname;
				cout << "Debugging: Temp Rider's UID is " << tempRider.rr_UIDalpha << " + " << tempRider.rr_UIDnum << ", pname " << tempRider.rr_pname;
				cout << "Login Successful!";
				system("pause");
				login_success += 1;
			}	
		}
	}
	cout << "\nCode made it to counting exists\n";

	if (email_exists == 0 || login_success == 0)
	{
		cout << "\n\tYou don't have a Zebra account with that email address or password.\n\tPlease try again.\n";
		goto valid_emailusrname;
	}
	riderpid_file.close();
	return (read_from_file);
	
	//read_from_file = rider_retrieve_info();
	//return (read_from_file);

}


//This function displays the homepage for a rider *after* login
vector<Rider_ridestore> r_li_home(vector <Rider_pid> &userEmail, vector <Rider_ridestore>& rselect)
{
	system("cls");
	disp_rider_logo();

	//Searching for 

	//string welcome_msg = 
	disp_h2_lines("Kia Ora <<preferredName>>, let's arrange your ride!");
	
	disp_h3_lines("Select: ");
	cout << "\n\t1. Login\n";

	return rselect;
}



//RIDER REGISTRATION FUNCTION: This section takes rider input data from user
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

	//This section creates an AlphaID for the registration person upon confirmation of account creation, based on their firstname and last name
	ri.r_idalpha += "R" + ri.r_fname.substr(0, 1);
	ri.r_idalpha += ri.r_lname.substr(0, 2);
	ri.r_idnum = 1001 + count_entries();
	cout << "The autogen ID alpha is" << ri.r_idalpha; //debugging
	cout << "The autogen ID num is" << ri.r_idnum; //debugging

	rinput.push_back(ri);

	return rinput;
}

//This function stores details to the riderpid.csv file
void writeRiderToFile(vector <Rider_pid>& write_r)
{
	fstream riderpid_file("riderpid.csv", ios::app);

	for (int i = 0; i < write_r.size(); i++)
	{
		//cout << "Your code made it here"; //debugging
		riderpid_file << write_r[i].r_idalpha << "," << write_r[i].r_idnum << "," << write_r[i].r_fname << "," << write_r[i].r_lname << "," << write_r[i].r_pname << ",";
		riderpid_file << write_r[i].r_contact << "," << write_r[i].r_address << "," << write_r[i].r_emailusrname << ",";
		riderpid_file << write_r[i].r_pswd << endl;
	}

	riderpid_file.close();
}

//This function counts the number of lines stored in the riderpid.csv file
int count_entries()
{
	int total_entries = 0;
	string s;
	fstream riderpid_file("riderpid.csv", ios::in);
	if (!riderpid_file)
	{
		total_entries = 0;
	}
	else
	{
		while (!riderpid_file.eof())
		{
			getline(riderpid_file, s);
			total_entries++;
		}
		total_entries = total_entries - 1;
		
	}
	//cout << "\nNumber of lines in file is " << total_entries; //debugging

	return total_entries;
}

//This function reads all of the values stored in the riderpid.csv file
vector <Rider_pid> rider_retrieve_info()
{
	fstream riderpid_file("riderpid.csv", ios::in);
	vector <Rider_pid> tempFile;

	Rider_pid read_r;
	string line;
	cout << "Your code made it to the start of rider_retrieve_info()"; //debugging purposes

	while (getline(riderpid_file, line))
	{
		istringstream linestream(line);  //splitting row into cell values
		string get_val;

		getline(linestream, get_val, ',');
		read_r.r_idalpha = get_val;
		cout << "\nDebugging: Your rider_retrieve_info()'s idalpha is " << read_r.r_idalpha;

		getline(linestream, get_val, ',');
		stringstream ssid(get_val);
		ssid >> read_r.r_idnum;

		getline(linestream, get_val, ',');
		read_r.r_fname = get_val;
		getline(linestream, get_val, ',');
		read_r.r_lname = get_val;
		getline(linestream, get_val, ',');
		read_r.r_pname = get_val;

		getline(linestream, get_val, ',');
		stringstream sscon(get_val);
		sscon >> read_r.r_contact;

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


//This function searches to find the username in the database, and updates the corresponding password
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::out);

	string search_email, new_pswd;
	int reset_code = 0, email_exists=0;
valid_emailusrname:
	cout << "\n\tNeed to reset your password? Please enter your email address:\t";
	cin >> search_email;
	disp_dash_line();

	//searching for the provided email address/username
	for (int i = 0; i < read_from_file.size(); i++)
	{
		if (read_from_file[i].r_emailusrname == search_email)
		{
			cout << "\tEmail exists in database\n"; //debugging purposes
			cout << "\tPlease check your email to reset your password and enter your 5-digit password reset code below.\n";
			cout << "\t[For the purposes of this assignment, please enter 12345]\n";
		//reset_code added to simulate "email verification"
		enter_reset_code:
			cout << "\n\tEnter password reset code:\t";
			cin >> reset_code;
			if (reset_code == 12345)
			{
			enter_new_pass:
				cin.ignore();
				cout << "\n\tGreat, let's reset your password!";
				cout << "\n\tEnter a new secure password:\t";
				cout << "\n\t[Passwords must be";
				cout << "\n\tlonger than 8 chars,";
				cout << "\n\tcontain both numbers &";
				cout << "\n\tbig and small letters\t:  ";
				getline(cin, new_pswd);
				if (pswd_valid(new_pswd) == 0)
				{
					cout << "New Pswd Invalid"; //debugging purposes
					goto enter_new_pass;
				}
				read_from_file[i].r_pswd = new_pswd;
				email_exists += 1; //****If we have time, to make sure that there are no username duplicates!
			
			}
			else
			{
				cout << "\n\tYou've entered the wrong password reset code.";
				cout << "\n\t[Hint: Just enter 12345 for the purposes of this assignment.";
				goto enter_reset_code;
			}
			

		}
		riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," <<  read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ","
			<< read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ","
			<< read_from_file[i].r_pswd << endl;

		
	}
	if (email_exists == 0)
	{
		cout << "\n\tYou don't have a Zebra account with that email address.\n\tPlease try again.\n";
		goto valid_emailusrname;
	}
	
	riderpid_file.close();
	read_from_file = rider_retrieve_info();
	return (read_from_file);

}
