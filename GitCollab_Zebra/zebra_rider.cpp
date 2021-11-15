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
#include "distance_calc.h"
#include <typeinfo>

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
	
	vector <Rider_pid> rider_read_file_info, goBack;
	Rider_ridestore rider_read_rides;

	int rider_main_input;
rider_main_page:
	system("cls");
	//cout << "Number of lines currently in file are " << count_entries(); //debugging
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

	//Login
	if (rider_main_input == 1)
	{
		system("cls");
		
		rider_read_rides = r_login(rider_retrieve_info());
		cout << "\n\tdebug: Checking to make sure if r_login has passed the needed UIDs " << rider_read_rides.rr_UIDalpha << " and " << rider_read_rides.rr_UIDnum;
		//Once login is successful, pass the temp rider struct info to the r_loggedIn function
		r_loggedIn_home(rider_read_rides);

		////If there are no registrations at all, bring user back to main page to register #############!! Do i need this?? ############
		//if (!"riderrides.csv")
		//{
		//	cout << "\n\tPlease register for an account before logging in.\n\t";
		//	system("pause");
		//	goto rider_main_page;
		//}
		////r_li_home(rider_read_rides);
		//else
		//{
		//	rider_read_file_info = rider_retrieve_info();
		//	cout << "Debug: Checking that tempRider has been passed back " << rider_read_rides.rr_UIDalpha << rider_read_rides.rr_UIDnum << "\tPreferred name: " << rider_read_rides.rr_pname;
		//	//pass the structure received from r_login to the logged in home page
		//	r_loggedIn_home(rider_read_file_info, rider_read_rides);
		//}

	}
	//This section calls the Rider Registration function 
	else if (rider_main_input == 2)
	{
		system("cls");
		rider_register(rinput);
		writeRiderToFile(rinput);
		
		//cout << "Rinput has been written to file! "; //debugging purposes
		cout << "\t\nYou are now a Zebra Rider!\n";
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
Rider_ridestore r_login(vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::in);
	Rider_ridestore tempRider;

	string r_emailusrname_check, r_pswd_check;
	int login_success = 0, email_exists = 0;

	cout << "\n\tUsername:\t";
	cin >> r_emailusrname_check;
valid_emailusrname:
	cout << "\tPassword:\t";
	cin >> r_pswd_check;
	disp_dash_line();
	//read_from_file = rider_retrieve_info(); //see if this is necessary ************#######
	//cout << "\nCode made it to receiving user input\ntemp_pull_file.size() is " << read_from_file.size(); //debugging
	//searching for the provided email address/username
	for (int i = 0; i < read_from_file.size(); i++)
	{
		//cout << "\nCode made it to forloop\n"; //Debugging
		
		//cout << "\nDebugging usernames available STAGE 2\t" << read_from_file[i].r_emailusrname;
		if (check_dup(r_emailusrname_check,read_from_file[i].r_emailusrname) == 1)
		//if (read_from_file[i].r_emailusrname == r_emailusrname_check)
		{
			//cout << "\tEmail exists in database\n"; //debugging purposes
			//cout << "\nDebugging usernames available Emails Exist\t" << read_from_file[i].r_emailusrname;
			email_exists += 1;
			//If email exists, check if password matches
			if (read_from_file[i].r_pswd == r_pswd_check)
			{
				//cout << "\nThe default location stored in the file at this time is: \t" << read_from_file[i].r_defaultloc;
				tempRider.rr_UIDalpha = read_from_file[i].r_idalpha;
				tempRider.rr_UIDnum = read_from_file[i].r_idnum;
				//tempRider.rr_pname = read_from_file[i].r_pname;
				//tempRider.rr_defaultloc = read_from_file[i].r_defaultloc;
				//if (read_from_file[i].r_card_type == 0)				//###############################WORKING ON  CARD
				//{
				//	tempRider.rr_pay_avail = "No";
				//}
				//else
				//{
				//	tempRider.rr_pay_avail = "Yes";
				//}
			
			//cout << "\nDebugging: checking what the default location is that I'm passing upon successful login\t" << tempRider.rr_defaultloc << endl;
			////cout << "Debugging: Temp Rider's UID is " << tempRider.rr_UIDalpha << " + " << tempRider.rr_UIDnum << ", pname " << tempRider.rr_pname;
			cout << "\n\tLogin Successful!\n\t";
			system("pause");
			login_success += 1;
			}
		}
	}
	//cout << "\nCode made it to counting exists\n"; //debugging purposes

	if (email_exists == 0 || login_success == 0)
	{
		cout << "\n\tYou don't have a Zebra account with that email address or password.\n\tPlease try again, or enter <BACK> to go back to the main Rider page.\n";
		cout << "\tUsername:\t";
		cin >> r_emailusrname_check;
		if (convert_string_to_upper(r_emailusrname_check) == "BACK") 
		{
			riderpid_file.close();
			rider_main(read_from_file);
		}
		else
		{
			goto valid_emailusrname;
		}
	}
	riderpid_file.close();
	//if login successful, return the data copied over to tempRider struct 
	return (tempRider); 

}

//#######################################################################
//  LOGIN: FUNCTIONS AVAILABLE AFTER RIDER LOGS IN SUCCESSFULLY
//#######################################################################

//This function displays the homepage for a rider *after* login
void r_loggedIn_home(Rider_ridestore &uid)
{
	Rider_ridestore temp_nopid;
	vector <Rider_ridestore> rider_rides;
	Rider_pid pid_pushback_details;
	vector <Rider_pid> temp_retrieve_info;

	system("cls");
	//Pulling in all important rinput details for the logged in rider
	temp_retrieve_info = rider_retrieve_info();
	cout << "\nDebugging: Checking that temp_retrieve_info is passed " << temp_retrieve_info[1].r_pname;
	cout << "\nDebugging: Checking what the temp_retrieve_info file size is " << temp_retrieve_info.size();
	cout << "\nDebugging: Is the rider_ridestore UID passed?  " << uid.rr_UIDalpha << " and " << uid.rr_UIDnum;
	for (int i = 0; i < temp_retrieve_info.size(); i++)
	{
		if (temp_retrieve_info[i].r_idalpha == uid.rr_UIDalpha && temp_retrieve_info[i].r_idnum == uid.rr_UIDnum)
		{
			cout << "\nThe default location stored in the file at this time is: \t" << temp_retrieve_info[i].r_defaultloc;
			temp_nopid.rr_UIDalpha = temp_retrieve_info[i].r_idalpha;
			temp_nopid.rr_UIDnum = temp_retrieve_info[i].r_idnum;
			temp_nopid.rr_pname = temp_retrieve_info[i].r_pname;
			temp_nopid.rr_defaultloc = temp_retrieve_info[i].r_defaultloc;
			cout << "\nPreferred name and transferred temp_nopid default loc are " << temp_nopid.rr_pname << " and " << temp_nopid.rr_defaultloc;
			if (temp_retrieve_info[i].r_card_num == "nil")			
			{
				temp_nopid.rr_pay_avail = "No";
			}
			else
			{
				temp_nopid.rr_pay_avail = "Yes";
			}
			
			//NEED TO WRITE TEMP_NOPID TO NEW RIDERRIDESFILE HERE!!!!######################################################### WORKING HERE
		}
	}
	
	disp_rider_logo();
	string hello = "Kia Ora ";
	string name = temp_nopid.rr_pname;
	string action = ", let's arrange your ride!";
	string title = hello + name + action;
	disp_h2_lines(title);
	
	//Checking to see if rider currently exists in riderrides.csv file
	cout << "\n\Check what temp details are already stored:\t" << temp_nopid.rr_defaultloc << "\n"; //debugging purposes

	if (temp_nopid.rr_defaultloc == "nil")
	{
		int locInput;
		cout << "\n\tPlease select a default pickup location: ";
		cout << "\n\t1. Brooklyn";
		cout << "\n\t2. Haitaitai";
		cout << "\n\t3. Aro Valley";
		cout << "\n\t4. Kelburn";
		cout << "\n\t5. Mount Cook\n\n\t";
		cin >> locInput;

		temp_nopid.rr_defaultloc = location_translate(locInput);
		cout << "\n\Temp details registered for new default loc is:\t" << temp_nopid.rr_defaultloc << "\n"; //debugging purposes
		
		//Lessons learnt - I don't actually need to pass temp_retrieve_info - I can retrieve the info on the other end
		searchAndUpdate_defaultloc(temp_nopid, temp_retrieve_info);
	}

	string stay_loggedIn = "y";
	while (stay_loggedIn == "y")
	{
		int booking_select;
		double dist, cost;
		dist = main_dist_calc(temp_nopid.rr_defaultloc, "TE_ARO");
		cost = dist * 0.6;
		//cout << "\n\nDebugging: Distance from default loc to Te Aro is " << dist;

		disp_h3_lines("Select: ");
		cout << "\n\n\tRides from " << temp_nopid.rr_defaultloc << " to Te Aro costs $" << cost << " right now!";
		disp_dash_line;
		cout << "\n\n\t1. Express booking from " << temp_nopid.rr_defaultloc <<  " to Te Aro\n";
		cout << "\n\t2. Book a trip from your default location, " << temp_nopid.rr_defaultloc << "\n";
		cout << "\n\t3. Book a trip from a different starting location\n";
		disp_star_line();
		cout << "\n\t4. View your past rides\n";
		cout << "\n\t5. View your account settings\n";
		cout << "\n\t6. Understand Zebra Fares and Charges\n\n\t";
		cin >> booking_select;

		
		switch (booking_select)
		{
		case 1:
		{
			string creditcard;
			int flag = 0;
			cout << "debug: checking if user reached case 1";
			temp_nopid.rr_startloc = temp_nopid.rr_defaultloc;
			temp_nopid.rr_endloc = "TE_ARO";
			if (temp_nopid.rr_pay_avail == "No")
			{
				pay_details(temp_nopid);
			}
			cout << "\n\tYour booking has been confirmed.";
			cout << "\n\n\tTrip details:";
			cout << "\n\tPickup point\t\t" << temp_nopid.rr_startloc;
			cout << "\n\tDropoff point\t\t" << temp_nopid.rr_endloc;
			cout << "\n\tDropoff point\t\t: 3";
			main_dist_calc(temp_nopid.rr_defaultloc, "TE_ARO");
			cost = main_dist_calc(temp_nopid.rr_startloc, temp_nopid.rr_endloc) * 0.6;
			cout << "\n\tYour trip cost is " << cost;
			disp_dash_line;
			break;
		}

		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			disp_fares_charges();
			stay_loggedIn = "y";
			break;
		}
	}
	
	//return rselect;
}

void disp_fares_charges()
{
	disp_star_line();
	cout << "\n\tZebra charges a flat rate of $0.60 per km.";
	cout << "\n\t[More to be added if there's time]\n\t";
	system("pause");
	disp_star_line();
}

string location_translate(int user_input)
{
	string trans_loc;
	switch (user_input)
	{
	case 1: 
		trans_loc = "BROOKLYN";
		break;
	case 2: 
		trans_loc = "HAITAITAI";
		break;
	case 3: 
		trans_loc = "AROVALLEY";
		break;
	case 4:
		trans_loc = "KELBURN";
		break;
	case 5:
		trans_loc = "MOUNTCOOK";
		break;

	}
	return trans_loc;
	//{
	//default:
	//	break;
	//}

	//if (user_input == 1)
	//{
	//	
	//}
}



//#######################################################
//  DATA INPUT FUNCTIONS
//  rider_register(), pay_details()
//#######################################################
 vector <Rider_pid> pay_details(Rider_ridestore& passed_nopid_details)
{
	//vector <Rider_pid> temp_creditcard;
	Rider_pid temp_creditcard;
	vector <Rider_pid> read_from_file;

	fstream riderpid_file("riderpid.csv", ios::out);
	read_from_file = rider_retrieve_info();
	int uid_exists = 0;
	int confirm;
	cout << "\n\tDebugging - Checking if read_from_file is successfully passed with " << read_from_file[1].r_idalpha << " and " << read_from_file[1].r_idnum << " with filesize " << read_from_file.size();
	//if this function is called, immediately transfer the rider's noPID details to compare with pid csv file
	disp_dash_line();
	cout << "\n\tUnique ID that i'm looking to pass to database is:\t" << passed_nopid_details.rr_UIDalpha << " and " << passed_nopid_details.rr_UIDnum << "\n"; //debugging purposes

	//searching for the provided ID so that we can eventually write to file
	for (int i = 0; i < read_from_file.size(); i++)
	{
		cout << "What is the searched r_idalpha? " << read_from_file[i].r_idalpha << " and " << read_from_file[i].r_idnum;
		if (read_from_file[i].r_idalpha == passed_nopid_details.rr_UIDalpha && read_from_file[i].r_idnum == passed_nopid_details.rr_UIDnum)
		{
			cout << "\n\tWe need your payment details to proceed";
			disp_dash_line;
			cout << "\n\tPayments are secured by WINDCAVE Security";
			disp_dash_line;
			cout << "\n\tCredit card Type. Select:";
			cout << "\n\t[1] for VISA";
			cout << "\n\t[2] for MASTERCARD";
			cout << "\n\t[3] for AMEX";
			cin >> read_from_file[i].r_card_type;

			cout << "\n\n\tCardholder Name\t:";

			//Credit card # validation
			int flag = 0;
			while (flag == 0)
			{
				cin.ignore();
				cout << "\n\tCard number";
				cout << "\n\t[#### #### #### ####]\t:";
				getline(cin, temp_creditcard.r_card_num);
				flag = creditcard_num_valid(temp_creditcard.r_card_num);
				if (flag == 1)
				{
					cout << "creditcard success!";
					system("pause");
					break;
				}
				else
				{
					cout << "\n\tYour card number format must be [XXXX XXXX XXXX XXXX].\n";
					cout << "\n\tHit Enter to try again.\n";
				}
			}
			cout << "\n\tExpiry date\t";
			cout << "[MMYY]\t\t:";
			cin >> read_from_file[i].r_expiry;

			cout << "\n\tCVV\t";
			cout << "[3 digits on the back of your card\t:";
			cin >> read_from_file[i].r_cvv;

			cout << "\n\tEnter:\n\t[1] Confirm your credit card details";
			cout << "\n\t[2]Cancel your booking and return to homepage";
			cin >> confirm;
			if (confirm == 2)
			{
				r_loggedIn_home(passed_nopid_details);
			}
			read_from_file[i].r_card_num = temp_creditcard.r_card_num;
			cout << "Card number to be input into system is \t:" << read_from_file[i].r_card_num; //debugging purposes
			uid_exists += 1;
			riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ",";
			riderpid_file << read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ",";
			riderpid_file << read_from_file[i].r_pswd << "," << read_from_file[i].r_defaultloc << "," << read_from_file[i].r_card_type << "," << read_from_file[i].r_cardholder_name << ",";
			riderpid_file << read_from_file[i].r_card_num << "," << read_from_file[i].r_expiry << "," << read_from_file[i].r_cvv <<  endl;
			cout << "\n\tPayment details registered. \n\tPress Enter to confirm your booking";
		}
	}
	if (uid_exists == 0)
	{
		cout << "\n\t!!!! ERROR - UID DOES NOT EXIST IN SYSTEM. THIS SHOULD NOT HAPPEN --DEBUGGING \n";
	}
	
	riderpid_file.close();
	read_from_file = rider_retrieve_info();
	return (read_from_file);

}

//RIDER REGISTRATION FUNCTION: This section takes rider input data from user
vector <Rider_pid> rider_register(vector <Rider_pid>& rinput)
{
	vector <Rider_pid> temp_read_riderpid;
	int rreg_confirmation;
	//pulling current registered data into a temp file for later comparison
	temp_read_riderpid = rider_retrieve_info();

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

	int dup_flag_triggered = 0;
	for (int i = 0; i < count_entries(); i++)
	{
		dup_flag_triggered = check_dup(ri.r_emailusrname, temp_read_riderpid[i].r_emailusrname);
		if (dup_flag_triggered == 1)
		{
			cout << "\n\tThis username is already in use";
			goto valid_email;
		}
	}

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
	cout << ri.r_emailusrname << "\t[Reminder: This will be your username]\n\t";
	disp_star_line();
	cout << "\n\tIs your information correct?\t:  ";
	cout << "\n\tSelect [1] to confirm and [2] to edit:\n\t";
	cin >> rreg_confirmation;
	if (rreg_confirmation == 2)
	{
		goto change_riderpid;
	}
	ri.r_defaultloc = "nil";
	ri.r_card_type = 0;
	ri.r_card_num = "nil";
	ri.r_expiry = 0;
	ri.r_cvv = 0;

	cout << "\nThe r_idalpha at registration before creation is " << ri.r_idalpha;
	cout << "\nThe default location upon registration before creation is " << ri.r_defaultloc;

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
		riderpid_file << write_r[i].r_pswd << "," << write_r[i].r_defaultloc << "," << write_r[i].r_card_type << "," << write_r[i].r_cardholder_name << ",";
		riderpid_file << write_r[i].r_card_num << "," << write_r[i].r_expiry << "," << write_r[i].r_cvv << endl;
	}

	riderpid_file.close();
}

void writeRiderPubFile(vector <Rider_ridestore>& write_r)
{
	fstream riderpub_file("riderrides.csv", ios::app);
	for (int i = 0; i < write_r.size(); i++)
	{
		riderpub_file << write_r[i].rr_UIDalpha << "," << write_r[i].rr_UIDnum << "," << write_r[i].rr_pname << "," << write_r[i].rr_defaultloc << "," << write_r[i].rr_startloc << "," << write_r[i].rr_endloc << ",";
		riderpub_file << write_r[i].rr_pay_avail << "," << write_r[i].rr_tripCost << "," << write_r[i].rr_gst << "," << write_r[i].rr_netTripRevenue << endl ;
	}
	riderpub_file.close();
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

	Rider_pid read_r, check_r;
	string line;
	//cout << "Your code made it to the start of rider_retrieve_info()"; //debugging purposes

	while (getline(riderpid_file, line))
	{
		istringstream linestream(line);  //splitting row into cell values
		string get_val;

		getline(linestream, get_val, ',');
		read_r.r_idalpha = get_val;
		//cout << "\nDebugging: Your rider_retrieve_info()'s idalpha is " << read_r.r_idalpha;

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
		
		cout << "\nQuick check - What does r_defaultloc register BEFORE getline in rider_retrieve_info?\t" << read_r.r_defaultloc;
		getline(linestream, get_val, ',');
		read_r.r_defaultloc = get_val;
		getline(linestream, get_val, ',');
		read_r.r_card_num = get_val;
		


		cout << "\nQuick check - What does r_defaultloc register after getline in rider_retrieve_info?\t" << read_r.r_defaultloc;
		//cout << "\n" << read_r.r_emailusrname << "\tyour code made it to pulling the username\n"; //debugging purposes
		//cout << read_r.r_pswd << "\tyour code made it to pulling the pswd\n"; //debugging purposes

		tempFile.push_back(read_r);

	}
	riderpid_file.close();
	return(tempFile);
}

//#####################################################################
//  SEARCH AND UPDATE FUNCTIONS
//#####################################################################


//USERNAME: This function searches to find the username in the database, and updates the corresponding password
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
			cout << "\n\tEmail exists in database\n"; //debugging purposes
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
		riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ",";
		riderpid_file << read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ",";
		riderpid_file << read_from_file[i].r_pswd << "," << read_from_file[i].r_defaultloc << "," << read_from_file[i].r_card_type << "," << read_from_file[i].r_cardholder_name << ",";
		riderpid_file << read_from_file[i].r_card_num << "," << read_from_file[i].r_expiry << "," << read_from_file[i].r_cvv << endl;


		
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


//DEFAULT LOCATION: This function searches to find the user's default location in the database, and either adds or updates it
//The noPID details are passed for search 
vector<Rider_pid> searchAndUpdate_defaultloc(Rider_ridestore& passed_nopid_details, vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::out);

	string search_uida, search_uidn;
	int uid_exists = 0;

	//if this function is called, immediately transfer the rider's noPID details to compare with pid csv file
	disp_dash_line();
	cout << "\n\tUnique ID that i'm looking to pass to database is:\t" << passed_nopid_details.rr_UIDalpha << " and " << passed_nopid_details.rr_UIDnum << "\n"; //debugging purposes

	//searching for the provided email address/username
	for (int i = 0; i < read_from_file.size(); i++)
	{
		cout << "What is the searched r_idalpha? " << read_from_file[i].r_idalpha << " and " << read_from_file[i].r_idnum;
		if (read_from_file[i].r_idalpha == passed_nopid_details.rr_UIDalpha && read_from_file[i].r_idnum == passed_nopid_details.rr_UIDnum)
		{
			cout << "\n\tUnique ID exists in database as:\t"<< read_from_file[i].r_idalpha << "and" << read_from_file[i].r_idnum << "\n"; //debugging purposes
			cout << "\nWe are now supposed to equate read_from_file default loc info " << read_from_file[i].r_defaultloc << " to " << passed_nopid_details.rr_defaultloc << endl;
			read_from_file[i].r_defaultloc = passed_nopid_details.rr_defaultloc;
			uid_exists += 1;
		}
		else if (read_from_file[i].r_defaultloc == "")
		{
			read_from_file[i].r_defaultloc = "";
		}
		else
		{
			read_from_file[i].r_defaultloc = read_from_file[i].r_defaultloc;
		}
		riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ",";
		riderpid_file << read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ",";
		riderpid_file << read_from_file[i].r_pswd << "," << read_from_file[i].r_defaultloc << "," << read_from_file[i].r_card_type << "," << read_from_file[i].r_cardholder_name << ",";
		riderpid_file << read_from_file[i].r_card_num << "," << read_from_file[i].r_expiry << "," << read_from_file[i].r_cvv << endl;


	}
	if (uid_exists == 0)
	{
		cout << "\n\t!!!! ERROR - UID DOES NOT EXIST IN SYSTEM. THIS SHOULD NOT HAPPEN --DEBUGGING \n";
	}

	riderpid_file.close();
	read_from_file = rider_retrieve_info();
	return (read_from_file);

}