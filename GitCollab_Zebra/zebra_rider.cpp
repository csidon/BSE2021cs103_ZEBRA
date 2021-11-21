#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "makepretty.h"
#include "zebra_rider.h"
#include "pswd_email_validation.h"
#include "misc_functions.h"
#include "distance_calc.h"
#include <typeinfo>
#include <iomanip>

using namespace std;

//Coder: Chris C
//File: zebra_rider.cpp
//Purpose: This file contains the main functions for Zebra Rider


////###############################################
////		RIDER FUNCTIONS
////###############################################

//This function displays the options on the main Rider Page
int rider_main()
{
	vector <Rider_pid> rider_read_file_info, goBack;
	Rider_pid rider_pid_struct;

	int rider_main_input;

rider_main_page:
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

	//Login
	if (rider_main_input == 1)
	{
		system("cls");
		rider_pid_struct = r_login(rider_retrieve_info());
		cout << "\n\tdebug: Checking to make sure if r_login has passed the needed UIDs " << rider_pid_struct.r_idalpha << " and " << rider_pid_struct.r_idnum;
		//Once login is successful, pass the temp pidrider's UID to the r_loggedIn function
		r_loggedIn_home(rider_pid_struct);
	}
	//This section calls the Rider Registration function 
	else if (rider_main_input == 2)
	{
		system("cls");
		rider_pid_struct = rider_register();
		writeRiderToFile(rider_pid_struct);

		//cout << "Rinput has been written to file! "; //debugging purposes
		cout << "\n\tYou are now a Zebra Rider!\n\t";
		system("pause");
		goto rider_main_page;

	}
	//This section calls the password reset function 
	else if (rider_main_input == 3)
	{
		rider_read_file_info = rider_retrieve_info();
		rider_read_file_info = pswd_reset(rider_read_file_info);
		cout << "\n\t Password reset successful :)\n\t";
		system("pause");
		goto rider_main_page;
	}
	else
	{
		int flag = 1;

		return (flag);
	}
	return 0;
}

//_________________________________________________________________________________________________________________________________________________________________
//*****************************************************************************************************************************************************************
//THIS SECTION IS FOR ALL LOG IN RELATED FUNCTIONS
//_________________________________________________________________________________________________________________________________________________________________
//###########################################################################################################################
//  LOGGING IN: FUNCTION TO LOG ZEBRA RIDER INTO ACCOUNT
//  This function searches to find the username in the database, and checks that the password corresponds
//###########################################################################################################################
Rider_pid r_login(vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::in);
	Rider_pid tempRiderPIDStruct;

	string r_emailusrname_check, r_pswd_check;
	int login_success = 0, email_exists = 0;

	cout << "\n\tUsername:\t";
	cin >> r_emailusrname_check;
valid_emailusrname:
	cout << "\tPassword:\t";
	cin >> r_pswd_check;
	disp_dash_line();
	//cout << "\nCode made it to receiving user input\ntemp_pull_file.size() is " << read_from_file.size(); //debugging

	//searching for the provided emailusername
	for (int i = 0; i < read_from_file.size(); i++)
	{
		//The check_dup function checks to make sure that any duplicate email address matches regardless of case sensitivity
		if (check_dup(r_emailusrname_check, read_from_file[i].r_emailusrname) == 1)
		{
			//cout << "\nDebugging: Emails/usernames that exist\t" << read_from_file[i].r_emailusrname;
			//Flag email found
			email_exists = 1;
			//If email exists, check if password matches
			if (read_from_file[i].r_pswd == r_pswd_check)
			{
				//If email and pswd matches, transfer uid of rider to loggedIn function
				tempRiderPIDStruct.r_idalpha = read_from_file[i].r_idalpha;
				tempRiderPIDStruct.r_idnum = read_from_file[i].r_idnum;
			//cout << "\nDebugging: checking what the default location is that I'm passing upon successful login\t" << tempRider.rr_defaultloc << endl;
			////cout << "Debugging: Temp Rider's UID is " << tempRider.rr_UIDalpha << " + " << tempRider.rr_UIDnum << ", pname " << tempRider.rr_pname;
				cout << "\n\tLogin Successful!\n\t";
				//Copying over all data for that user into a structure to be passed on
				tempRiderPIDStruct = read_from_file[i];
				system("pause");
				//Flag successful login
				login_success = 1;
			}
		}
	}
	//User Error message if no matching email and password is found
	if (email_exists == 0 || login_success == 0)
	{
		cout << "\n\tYou don't have a Zebra account with that email address or password.\n\tPlease try again, or enter <BACK> to go back to the main Rider page.\n";
		cout << "\tUsername:\t";
		cin >> r_emailusrname_check;
		if (convert_string_to_upper(r_emailusrname_check) == "BACK")
		{
			riderpid_file.close();
			rider_main();
		}
		else
		{
			goto valid_emailusrname;
		}
	}
	riderpid_file.close();
	return (tempRiderPIDStruct);
	//if login successful, return the data copied over to tempRider struct 
}
//#######################################################################
//  LOGGED IN: FUNCTIONS AVAILABLE AFTER RIDER LOGS IN SUCCESSFULLY
//#######################################################################

//This function displays the homepage for a rider *after* login
void r_loggedIn_home(Rider_pid& userInfo)
{
	//Note: &userInfo contains all of the data captured in the riderpid.csv file for the logged in user
	//The idea is to (as much as possible) minimise pulling all of the riderpid.csv file into temporary vectors, since this is sensitive information

	//Rider_pid vector carries rider's personal information and push/pulls it to riderpid.csv
	//Rider_AllRidesInfo vector carries desensitised information about all rides and push/pulls it to trip_transactions.csv
	Rider_AllRidesInfo ridesInfo;

	system("cls");
	//cout << "\nLOGGEDIN DEBUG 1. Is the UID PASSED? " << userInfo.r_idalpha << userInfo.r_idnum;
	//cout << "\nLOGGEDIN DEBUG 2. Is the CARD TYPE PASSED? " << userInfo.r_card_type;

	//This section displays the login menu, checks if the rider has a default location set up. 
	//If no default location, it asks the user to select one, then pushes it back to PID file
	disp_rider_logo();
	string hello = "Kia Ora ";
	string name = userInfo.r_pname;
	string action = ", let's arrange your ride!";
	string title = hello + name + action;
	disp_h2_lines(title);

	//Checking to see if a default location has been stored. Otherwise ask user to set a default location
	//cout << "\nLOGGEDIN DEBUG 3. Is the DEFAULT LOCATION PASSED? " << userInfo.r_defaultloc;
	if (userInfo.r_defaultloc == "")
	{
		int locInput;
		cout << "\n\tPlease select a default pickup location: ";
		cout << "\n\t1. Brooklyn";
		cout << "\n\t2. Haitaitai";
		cout << "\n\t3. Aro Valley";
		cout << "\n\t4. Kelburn";
		cout << "\n\t5. Mount Cook\n\n\t";
		cin >> locInput;

		//temporarily storing it in userInfo struct, then updating records in riderpid.csv file 
		userInfo.r_defaultloc = location_translate(locInput);
		searchAndUpdate_userDefaultLoc(userInfo);
	}

	string stay_loggedIn = "y";
	while (stay_loggedIn == "y")
	{
		int booking_select;
		double defaultloc_dist, defaultloc_cost, userCalc_dist, userCalc_cost;
		cout << fixed;
		cout << setprecision(2); //this sets cost price to 2 decimal places

		defaultloc_dist = main_dist_calc(userInfo.r_defaultloc, "TE_ARO");
		defaultloc_cost = calc_ride_cost(defaultloc_dist);

		//cout << "\n\nDebugging: Distance from default loc to Te Aro is " << defaultloc_dist;
		//cout << "\n\nDebugging: Default Cost from default loc to Te Aro is " << defaultloc_cost;

		cout << "\n\n\tRides from " << userInfo.r_defaultloc << " to Te Aro costs $" << defaultloc_cost << " right now!";
		disp_dash_line();
		disp_h3_lines("Select: ");
		
		cout << "\n\n\t1. Express booking from " << userInfo.r_defaultloc << " to Te Aro\n";
		cout << "\n\t2. Book a trip from your default location, " << userInfo.r_defaultloc << "\n";
		cout << "\n\t3. Book a trip from a different starting location\n";
		disp_star_line();
		cout << "\n\t4. View your past rides\n";
		//cout << "\n\t5. View your account settings\n";
		cout << "\n\t6. Understand Zebra Fares and Charges\n";
		cout << "\n\t7. Exit\n\n\t";
		cin >> booking_select;

		switch (booking_select)
		{
		case 1:			//Express booking option - For user to be able to travel to Te Aro (city center) from their default location quickly
		{
			cout << "\n\tYou have selected to book an EXPRESS ride from " << userInfo.r_defaultloc << " to " << "Te Aro";
			ridesInfo.rr_UIDalpha = userInfo.r_idalpha;
			ridesInfo.rr_UIDnum = userInfo.r_idnum;
			//cout << "\nDEBUG: The registered rider UID and pname for RIDESINFO is " << ridesInfo.rr_UIDalpha << ridesInfo.rr_UIDnum << " and " << ridesInfo.rr_pname;
			//cout << "\nDEBUG: The registered rider UID and pname for USERINFO is " << userInfo.r_idalpha << userInfo.r_idnum << " and " << userInfo.r_pname;
			ridesInfo.rr_startloc = userInfo.r_defaultloc;
			ridesInfo.rr_endloc = "TE_ARO";
			book_ride(userInfo, ridesInfo, defaultloc_cost);
			system("pause");
			stay_loggedIn = "y";
			break;
		}
		case 2:			//Books a ride from user's stored default location
		{
			ridesInfo.rr_startloc = userInfo.r_defaultloc;
			int locInput = 0;
			cout << "\n\n";
			disp_star_line();
			cout << "\tYou are booking a ride from your default location, " << userInfo.r_defaultloc;
			cout << "\n\tWhere would you like to go?";
			disp_dash_line();

			string user_dest_input = show_destination_options(ridesInfo, locInput);
			//cout << "\nDEBUGGING: The destination that the user chose is " << user_dest_input;
			ridesInfo.rr_endloc = user_dest_input;
			//cout << "\nDEBUGGING: Destination registered is " << ridesInfo.rr_endloc;
			userCalc_dist = main_dist_calc(ridesInfo.rr_startloc, ridesInfo.rr_endloc);
			userCalc_cost = calc_ride_cost(userCalc_dist);
			book_ride(userInfo, ridesInfo, userCalc_cost);
			cout << "\t";
			system("pause");
			stay_loggedIn = "y";
			break;
		}
		case 3:				//Books a ride from pickup and dropoff point of user's choice
		{
			int startLocInput = 0, endLocInput = 0;
			disp_star_line();
			cout << "\tYou are booking a ride with Zebra :)";
			cout << "\n\tWhere should we pick you up from?";
			disp_dash_line();
			string user_pickup_input = show_pickup_options(ridesInfo, startLocInput);
			ridesInfo.rr_startloc = user_pickup_input;
			//cout << "\nDEBUGGING: Pickup point registered is " << ridesInfo.rr_startloc;
			disp_dash_line();
			cout << "\n\tAnd where would you like to go?";
			disp_dash_line();

			string user_dest_input = show_destination_options(ridesInfo, endLocInput);
			//cout << "\nDEBUGGING: The destination that the user chose is " << user_dest_input;
			ridesInfo.rr_endloc = user_dest_input;
			//cout << "\nDEBUGGING: Destination registered is " << ridesInfo.rr_endloc;
			userCalc_dist = main_dist_calc(ridesInfo.rr_startloc, ridesInfo.rr_endloc);
			userCalc_cost = calc_ride_cost(userCalc_dist);
			book_ride(userInfo, ridesInfo, userCalc_cost);
			cout << "\t";
			system("pause");
			stay_loggedIn = "y";
			break;
		}
		case 4:				//Provides a report of all the rider's trips
			indiv_rider_report(userInfo);
			cout << "\t";
			system("pause");
			stay_loggedIn = "y";
			break;
		case 5:
			cout << "\nFunctionality under construction. Please be patient with us!";
			cout << "\t";
			system("pause");
			stay_loggedIn = "y";
			break;
		case 6:
			disp_fares_charges();
			cout << "\t";
			system("pause");
			stay_loggedIn = "y";
			break;
		case 7:
			stay_loggedIn = "n";
			break;
		}
	}
	rider_main();
	//return rselect;
}

string show_pickup_options(Rider_AllRidesInfo rideInfo, int userInput)
{
	Location arr[6];
	Location* locationPtr;
	locationPtr = arr;
	stored_locations(locationPtr);
	cout << "\n";
	for (int i = 0; i < 6; i++)
	{
		cout << "\t" << i + 1 << ". ";
		cout << locationPtr[i].id << endl;
	}
	cout << "\t";
	cin >> userInput;
	string pickup = locationPtr[userInput - 1].id;
	return (pickup);
}

string show_destination_options(Rider_AllRidesInfo rideInfo, int userInput)
{
	Location arr[6];
	Location* locationPtr;
	locationPtr = arr;
	stored_locations(locationPtr);

	//Each location is assigned a number in Location Struct
	cout << "\n";
	for (int i = 0; i < 6; i++)
	{
		if (locationPtr[i].id != rideInfo.rr_startloc)
		{
			cout << "\t" << i + 1 << ". ";
			cout << locationPtr[i].id << endl;
		}
	}
	cout << "\t";
	cin >> userInput;
	string destination = locationPtr[userInput - 1].id;
	return (destination);
}

void book_ride(Rider_pid userPIDInfo, Rider_AllRidesInfo userRidesInfo, double cost)
{
	Trips temp_ride_struct;
	string creditcard;
	char booking_cfm;
	int flag = 0;

	//cout << "\n Are payment details stored? (card number) " << userPIDInfo.r_card_num; //debugging
	//cout << "\nDEBUG: Equating the start location with default location -- success? \t" << userRidesInfo.rr_startloc;
	//cout << "\nDEBUG: Is the end location correct? \t" << userRidesInfo.rr_endloc;
	//cout << "\nDEBUG: Are there payment methods stored right now? " << userPIDInfo.r_card_type << endl;

	main_dist_calc(userRidesInfo.rr_startloc, userRidesInfo.rr_endloc);
	if (userPIDInfo.r_card_type == "")
	{
		//cout << "\nDEBUG: Did the code come here?";
		//cout << "\nDEBUG: Before getting passed, UID is " << userPIDInfo.r_idalpha << userPIDInfo.r_idnum;
		userPIDInfo = pay_details(userPIDInfo);
	}
	disp_star_line();
	cout << "\tReady to book your ride?";
	disp_dash_line();
	cout << "\n\tBooking your ride from:\t" << userRidesInfo.rr_startloc << " to " << userRidesInfo.rr_endloc << "\n";
	cout << "\n\tYour trip cost is:\t$" << cost << endl;
	cout << "\n\tPayment method:\t\t" << userPIDInfo.r_card_type << " XXXX " << userPIDInfo.r_card_num.substr(15, 19);
	disp_dash_line();
	cout << "\n\tEnter 'Y' to confirm your booking or 'N' to cancel\t";
	cin >> booking_cfm;

	if (toupper(booking_cfm) == 'Y')
	{
		cout << "\n\n";
		disp_star_line();
		cout << "\tYour booking has been confirmed.";
		disp_star_line();
		cout << "\n\n\tTrip details:";
		disp_dash_line();
		cout << "\tPickup point\t\t" << userRidesInfo.rr_startloc;
		cout << "\n\tDropoff point\t\t" << userRidesInfo.rr_endloc;
		cout << "\n\tYour trip cost is \t$" << cost << endl;
		disp_dash_line();
		disp_star_line();
		//cout << "\nDEBUGGING: userRidesInfo before passing to input_rider_trip_data is: " << userRidesInfo.rr_UIDalpha << userRidesInfo.rr_UIDnum;

		//Copies desensitised ride booking information to a temporary structure, that then gets passed and written to trip_transactions.csv
		temp_ride_struct = input_rider_trip_data(userRidesInfo);
		write_to_trip_transactions(temp_ride_struct);
	}
	else
	{
		cout << "\n\tYour booking has been cancelled\n";
	}
	cout << "\t";
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
		trans_loc = "ARO_VALLEY";
		break;
	case 4:
		trans_loc = "KELBURN";
		break;
	case 5:
		trans_loc = "MT_COOK";
		break;
	case 6:
		trans_loc = "TE_ARO";
		break;
	}
	return trans_loc;
}
//------------END OF LOGIN, LOGGED IN, AND BOOKING RELATED FUNCTIONS-------------------------------------------------------------------------
//********************************************************************************************************************************************************


//#######################################################
//  DATA INPUT FUNCTIONS
//  rider_register(), pay_details()
//#######################################################

Rider_pid pay_details(Rider_pid& passed_pid_details)
{
	vector <Rider_pid> read_from_file;
	read_from_file = rider_retrieve_info();
	fstream riderpid_file("riderpid.csv", ios::out);

	int uid_exists = 0;
	int confirm;
	//cout << "\nDEBUG: nopid details passed to Pay_details are " << passed_pid_details.r_defaultloc;
	//cout << "\n\tDebugging - Checking if read_from_file is successfully passed with " << read_from_file[1].r_idalpha << " and " << read_from_file[1].r_idnum << " with filesize " << read_from_file.size();
	//cout << "\n\tDebugging - Unique ID that i'm looking to pass to database is:  " << passed_pid_details.r_idalpha << " and " << passed_pid_details.r_idnum << " with default location " << passed_pid_details.r_defaultloc;
	disp_dash_line();

	string store_pay = "y";
	while (store_pay == "y")
	{
		//searching for the provided ID so that we can write to file
		for (int i = 0; i < read_from_file.size(); i++)
		{
			//cout << "\nDEBUG: What is the searched r_idalpha? " << read_from_file[i].r_idalpha << " and " << read_from_file[i].r_idnum;

			// ******* FUNCTIONALITY TO ADD IF THERE'S TIME. LEFT OUT DURING REWRITE TO REDUCE TESTING TIME **************
			//This segment rewrites and maintains the header for the file
			//if (read_from_file[i].r_idalpha == "rr_UIDalpha")
			//{
			//	string num_to_string, contact_to_string;
			//	read_from_file[i].r_idalpha = "r_uidalpha";
				//stringstream ss;
				//ss << read_from_file[i].r_idnum;
				//ss >> num_to_string;
				//to_string(read_from_file[i].r_idnum) = "r_uidnum";
				//read_from_file[i].r_fname = "r_fname";
				//read_from_file[i].r_lname = "r_lname";
				//read_from_file[i].r_pname = "r_pname";
				//read_from_file[i].r_contact = ("r_contact");
				//read_from_file[i].r_address = "r_address";
				//read_from_file[i].r_emailusrname = "r_emailusrname";
				//read_from_file[i].r_pswd = "r_pswd";
				//read_from_file[i].r_defaultloc = "r_defaultloc";
				//read_from_file[i].r_card_type = "r_card_type"; 
				//read_from_file[i].r_cardholder_name = "r_cardholdername";
				//read_from_file[i].r_card_num = "r_cardnum";
				//read_from_file[i].r_expiry = char("r_expiry");
				//read_from_file[i].r_cvv = char("r_cvv");
			//}
			if (read_from_file[i].r_idalpha == passed_pid_details.r_idalpha && read_from_file[i].r_idnum == passed_pid_details.r_idnum)
			{
				int cardtype_translate;
				cout << "\n\tWe need your payment details to proceed";
				disp_dash_line();
				cout << "\n\tPayments are secured by WINDCAVE Security";
				disp_dash_line();
				cout << "\n\tCredit card Type. Select:";
				cout << "\n\t[1] for VISA";
				cout << "\n\t[2] for MASTERCARD";
				cout << "\n\t[3] for AMEX\n\t";
				cin >> cardtype_translate;
				if (cardtype_translate == 1)
				{
					passed_pid_details.r_card_type = "VISA";
					read_from_file[i].r_card_type = passed_pid_details.r_card_type;
				}
				else if (cardtype_translate == 2)
				{
					passed_pid_details.r_card_type = "MASTERCARD";
					read_from_file[i].r_card_type = passed_pid_details.r_card_type;
				}
				if (cardtype_translate == 3)
				{
					passed_pid_details.r_card_type = "AMEX";
					read_from_file[i].r_card_type = passed_pid_details.r_card_type;
				}

				cout << "\n\n\tCardholder Name\t:  ";
				cin.ignore();
				getline(cin, passed_pid_details.r_cardholder_name);
				read_from_file[i].r_cardholder_name = passed_pid_details.r_cardholder_name;
				//cout << "DEBUGGING: Cardholder name registered is " << passed_pid_details.r_cardholder_name;
				// 
				//Credit card # validation
				int flag = 0;
				while (flag == 0)
				{
					cin.ignore();
					cout << "\n\tCard number";
					cout << "\n\t[#### #### #### ####]\t:  ";
					getline(cin, passed_pid_details.r_card_num);

					//cout << "DEBUGGING: Credit card number to pass is " << passed_pid_details.r_card_num;
					read_from_file[i].r_card_num = passed_pid_details.r_card_num;
					flag = creditcard_num_valid(passed_pid_details.r_card_num);
					if (flag == 1)
					{
						//cout << "DEBUGGING: Creditcard entry success!";
						//system("pause");
						break;
					}
					else
					{
						cout << "\n\tYour card number format must be [XXXX XXXX XXXX XXXX].\n";
						cout << "\n\tHit Enter to try again.\n";
					}
				}
				cout << "\n\tExpiry date [MMYY]\t:  ";
				cin >> passed_pid_details.r_expiry;
				read_from_file[i].r_expiry = passed_pid_details.r_expiry;

				cout << "\n\tCVV\t";
				cout << "\n\t[3 digits on the back of your card]\t:  ";
				cin >> passed_pid_details.r_cvv;
				read_from_file[i].r_cvv = passed_pid_details.r_cvv;

				disp_dash_line();
				cout << "\n\tEnter:\n\t[1] Confirm your credit card details";
				cout << "\n\t[2]Cancel your booking and return to homepage\n\t";
				cin >> confirm;
				if (confirm == 2)
				{
					store_pay = "n";
					break;
				}
				else
				{
					//cout << "Card number to be input into system is \t:" << read_from_file[i].r_card_num; //debugging purposes
					uid_exists += 1;
					//cout << "\nUID_exists = " << uid_exists << endl;
					//cout << "\nDebugging: Default loc to be written for this human is " << read_from_file[i].r_defaultloc;
				}
			}
			cout << "\nDebugging: Default loc to be written for this human " << read_from_file[i].r_emailusrname << " is " << read_from_file[i].r_defaultloc;
			riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ",";
			riderpid_file << read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ",";
			riderpid_file << read_from_file[i].r_pswd << "," << read_from_file[i].r_defaultloc << "," << read_from_file[i].r_card_type << "," << read_from_file[i].r_cardholder_name << ",";
			riderpid_file << read_from_file[i].r_card_num << "," << read_from_file[i].r_expiry << "," << read_from_file[i].r_cvv << endl;
			cout << "\n\tPayment details registered. Thank you!";
		}
		if (uid_exists == 0)
		{
			//cout << "\n\t!!!! ERROR - UID DOES NOT EXIST IN SYSTEM. THIS SHOULD NOT HAPPEN --DEBUGGING \n";
		}
		riderpid_file.close();
		read_from_file = rider_retrieve_info();
	}

	
	//return (read_from_file);
	//passed_nopid_details = temp_creditcard;
	return (passed_pid_details); //Trying to see if returning the struct instead of vector is more productive
	/////////////////change pay_details function so that I'm passing (Rider &passed_pid_details, vector <Rider_pid> read_from_file) because i AM working with pid!!! Then transfer it back and equate it dummy

}

//void add_header_riderpid(fstream& addheader)
//{
//
//	Rider_pid header;
//	//cout << "How many lines does count_entries count? " << read_from_file;
//	header.r_fname = "r_fname";
//	header.r_lname = "r_lname";
//	header.r_pname = "r_pname";
//	header.r_header_contact = "r_contact";
//	header.r_address = "r_address";
//	header.r_emailusrname = "r_emailusrname";
//	header.r_pswd = "r_pswd";
//	header.r_defaultloc = "r_defaultloc";
//	header.r_card_type = "r_card_type";
//	header.r_cardholder_name = "r_cardholdername";
//	header.r_card_num = "r_cardnum";
//	header.r_headerexpiry = "r_expiry";
//	header.r_headercvv = "r_cvv";
//
//	addheader << header.r_fname << "," << header.r_lname << "," << header.r_pname << "," << header.r_header_contact << "," << header.r_address << "," << header.r_emailusrname << ",";
//	addheader << header.r_pswd << "," << header.r_defaultloc << "," << header.r_card_type << "," << header.r_cardholder_name << "," << header.r_card_num << "," << header.r_headerexpiry << "," << header.r_headercvv;
//
//	//##############!!!! IMPT!! THIS FUNCTION DOES NOT CLOSE THE FILE! MAKE SURE YOU CLOSE IT LATER!!!! ################
//
//}

//RIDER REGISTRATION FUNCTION: This section takes rider input data from user	
Rider_pid rider_register()
{
	vector <Rider_pid> temp_read_riderpid;
	//pulling current registered data into a temp file for later comparison
	temp_read_riderpid = rider_retrieve_info();

	int rreg_confirmation = 0;

	system("cls");
	disp_rider_logo();
	disp_h2_lines("Sign Up to Ride with Zebra!");
	disp_h3_lines("Enter your: ");
	Rider_pid ri;

	while (rreg_confirmation == 0)
	{
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

		int reg_pswd = 0;
		while (reg_pswd == 0)
		{
			cout << "\n\tPassword";
			cout << "\n\t[Passwords must be";
			cout << "\n\tlonger than 8 chars,";
			cout << "\n\tcontain both numbers &";
			cout << "\n\tbig and small letters\t:  ";
			getline(cin, ri.r_pswd);
			if (pswd_valid(ri.r_pswd) == 0)
			{
				reg_pswd = 0;
			}
			else
			{
				reg_pswd = 1;
			}
		}
		cout << "\n";
		//Once details are captured, display all captured details (except password) and ask user to confirm registration details
		disp_dash_line();

		cout << "\tHello " << ri.r_pname << ", please check your details:";
		disp_dash_line();
		cout << "\t" << ri.r_fname << " " << ri.r_lname << "\n\t";
		cout << ri.r_contact << "\n\t";
		cout << ri.r_address << "\n\t";
		cout << ri.r_emailusrname << "\t[Reminder: This will be your username]\n\t";

		//To write empty spaces to file for filling up later
		ri.r_defaultloc = "";
		ri.r_card_type = "";
		ri.r_card_num = "";
		ri.r_expiry = 0;
		ri.r_cvv = 0;

		disp_star_line();
		cout << "\n\tIs your information correct?\t:  ";
		cout << "\n\tSelect [1] to confirm and [2] to edit:\n\t";
		cin >> rreg_confirmation;

	}
	cout << "\nDEBUGGING: The r_idalpha at registration before creation is " << ri.r_idalpha;
	cout << "\nDEBUGGING: The default location upon registration before creation is " << ri.r_defaultloc;

	//This section creates an AlphaID for the registration person upon confirmation of account creation, based on their firstname and last name
	ri.r_idalpha += "R" + ri.r_fname.substr(0, 1);
	ri.r_idalpha += ri.r_lname.substr(0, 2);
	ri.r_idnum = 1001 + count_entries();
	cout << "The autogen ID alpha is" << ri.r_idalpha; //debugging
	cout << "The autogen ID num is" << ri.r_idnum; //debugging

	//temp_read_riderpid.push_back(ri);

	return (ri);
}

//This function stores details to the riderpid.csv file
void writeRiderToFile(Rider_pid write_r)
{
	//vector <Rider_pid> read_from_file;
	//read_from_file = rider_retrieve_info();
	fstream riderpid_file("riderpid.csv", ios::app);
	//add_header_riderpid(riderpid_file);

	//FOR LATER IF THERE'S TIME -- IF COUNT_ENTRIES == 0, INSERT HEADER
	cout << "Your code made it here"; //debugging
	riderpid_file << write_r.r_idalpha << "," << write_r.r_idnum << "," << write_r.r_fname << "," << write_r.r_lname << "," << write_r.r_pname << ",";
	riderpid_file << write_r.r_contact << "," << write_r.r_address << "," << write_r.r_emailusrname << ",";
	riderpid_file << write_r.r_pswd << "," << write_r.r_defaultloc << "," << write_r.r_card_type << "," << write_r.r_cardholder_name << ",";
	riderpid_file << write_r.r_card_num << "," << write_r.r_expiry << "," << write_r.r_cvv << endl;
	
	riderpid_file.close();
}

//void writeRiderPubFile(vector <Rider_ridestore>& write_r)
//{
//	fstream riderpub_file("riderrides.csv", ios::app);
//	for (int i = 0; i < write_r.size(); i++)
//	{
//		riderpub_file << endl << write_r[i].rr_UIDalpha << "," << write_r[i].rr_UIDnum << "," << write_r[i].rr_pname << "," << write_r[i].rr_defaultloc << "," << write_r[i].rr_startloc << "," << write_r[i].rr_endloc << ",";
//		riderpub_file << write_r[i].rr_pay_avail << "," << write_r[i].rr_tripCost << "," << write_r[i].rr_gst << "," << write_r[i].rr_netTripRevenue;
//	}
//	riderpub_file.close();
//}

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

		cout << "\n\nQuick check - What does r_defaultloc register BEFORE getline in rider_retrieve_info?\t" << read_r.r_defaultloc;
		getline(linestream, get_val, ',');
		read_r.r_defaultloc = get_val;

		getline(linestream, get_val, ',');
		read_r.r_card_type = get_val;
		getline(linestream, get_val, ',');
		read_r.r_cardholder_name = get_val;
		getline(linestream, get_val, ',');
		read_r.r_card_num = get_val;
		getline(linestream, get_val, ',');
		stringstream ssexp(get_val);
		ssexp >> read_r.r_expiry;
		getline(linestream, get_val, ',');
		stringstream sscvv(get_val);
		sscvv >> read_r.r_cvv;



		cout << "\nQuick check - What does r_defaultloc register after getline in rider_retrieve_info?\t" << read_r.r_defaultloc;
		//cout << "\n" << read_r.r_emailusrname << "\tyour code made it to pulling the username\n"; //debugging purposes
		//cout << read_r.r_pswd << "\tyour code made it to pulling the pswd\n"; //debugging purposes

		tempFile.push_back(read_r);
		cout << "\nFile pushed back"; //debugging purposes
	}
	riderpid_file.close();
	cout << "\nFile closed"; //debugging purposes
	return(tempFile);
}

//#################################################################################################################################
//  SEARCH AND UPDATE FUNCTIONS
//  Note: Many of these functions are quite repetitive as I'm not sure how to pass a generic version of a structure's data members
//#################################################################################################################################


//USERNAME: This function searches to find the username in the database, and updates the corresponding password
vector<Rider_pid> pswd_reset(vector <Rider_pid> read_from_file)
{
	fstream riderpid_file("riderpid.csv", ios::out);

	string search_email, new_pswd;
	int reset_code = 0, email_exists = 0;
valid_emailusrname:
	cout << "\n\tNeed to reset your password? Please enter your email address:\t";
	cin >> search_email;
	disp_dash_line();

	//searching for the provided email address/username
	for (int i = 0; i < read_from_file.size(); i++)
	{
		if (check_dup(search_email, read_from_file[i].r_emailusrname) == 1)
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
				email_exists = 1; 
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
	//Error message if email address isn't found
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
//The noPID details are passed for search, and the new default location is stored back in riderpid.csv
//vector<Rider_pid> searchAndUpdate_defaultloc(Rider_ridestore& passed_pid_details, vector <Rider_pid> read_from_file)
//{
//	fstream riderpid_file("riderpid.csv", ios::out);
//
//	string search_uida, search_uidn;
//	int uid_exists = 0;
//
//	//if this function is called, immediately transfer the rider's noPID details to compare with pid csv file
//	disp_dash_line();
//	cout << "\n\tUnique ID that i'm looking to pass to database is:\t" << passed_pid_details.rr_UIDalpha << " and " << passed_pid_details.rr_UIDnum << "\n"; //debugging purposes
//
//	//searching for the provided email address/username
//	for (int i = 0; i < read_from_file.size(); i++)
//	{
//		cout << "What is the searched r_idalpha? " << read_from_file[i].r_idalpha << " and " << read_from_file[i].r_idnum;
//		if (read_from_file[i].r_idalpha == passed_pid_details.rr_UIDalpha && read_from_file[i].r_idnum == passed_pid_details.rr_UIDnum)
//		{
//			cout << "\n\tUnique ID exists in database as:\t" << read_from_file[i].r_idalpha << "and" << read_from_file[i].r_idnum << "\n"; //debugging purposes
//			cout << "\nWe are now supposed to equate read_from_file default loc info " << read_from_file[i].r_defaultloc << " to " << passed_pid_details.rr_defaultloc << endl;
//			read_from_file[i].r_defaultloc = passed_pid_details.rr_defaultloc;
//			uid_exists += 1;
//		}
//		else if (read_from_file[i].r_defaultloc == "")
//		{
//			read_from_file[i].r_defaultloc = "";
//		}
//		else
//		{
//			read_from_file[i].r_defaultloc = read_from_file[i].r_defaultloc;
//		}
//		riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ",";
//		riderpid_file << read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ",";
//		riderpid_file << read_from_file[i].r_pswd << "," << read_from_file[i].r_defaultloc << "," << read_from_file[i].r_card_type << "," << read_from_file[i].r_cardholder_name << ",";
//		riderpid_file << read_from_file[i].r_card_num << "," << read_from_file[i].r_expiry << "," << read_from_file[i].r_cvv << endl;
//
//
//	}
//	if (uid_exists == 0)
//	{
//		cout << "\n\t!!!! ERROR - UID DOES NOT EXIST IN SYSTEM. THIS SHOULD NOT HAPPEN --DEBUGGING \n";
//	}
//
//	riderpid_file.close();
//	read_from_file = rider_retrieve_info();
//	cout << "Default location now stored for yoda is " << read_from_file[1].r_defaultloc;
//	return (read_from_file);
//
//}

vector <Rider_pid> searchAndUpdate_userDefaultLoc(Rider_pid & updateInfo)
{
	vector <Rider_pid> read_from_file;
	read_from_file = rider_retrieve_info();
	fstream riderpid_file("riderpid.csv", ios::out);
	
	cout << "\nUser reaches this part";
	
	for (int i = 0; i < read_from_file.size(); i++)
	{
		if (updateInfo.r_idnum == read_from_file[i].r_idnum && updateInfo.r_idalpha == read_from_file[i].r_idalpha)
		{
			cout << "\nDEBUGGING: UID found in riderpid file";
			cout << "\nDefault location to be pushed is " << updateInfo.r_defaultloc << " to " << read_from_file[i].r_defaultloc;
			read_from_file[i].r_defaultloc = updateInfo.r_defaultloc;
		}
		riderpid_file << read_from_file[i].r_idalpha << "," << read_from_file[i].r_idnum << "," << read_from_file[i].r_fname << "," << read_from_file[i].r_lname << "," << read_from_file[i].r_pname << ",";
		riderpid_file << read_from_file[i].r_contact << "," << read_from_file[i].r_address << "," << read_from_file[i].r_emailusrname << ",";
		riderpid_file << read_from_file[i].r_pswd << "," << read_from_file[i].r_defaultloc << "," << read_from_file[i].r_card_type << "," << read_from_file[i].r_cardholder_name << ",";
		riderpid_file << read_from_file[i].r_card_num << "," << read_from_file[i].r_expiry << "," << read_from_file[i].r_cvv << endl;
	}
	riderpid_file.close();
	//read_from_file = rider_retrieve_info();
	return (read_from_file);

}