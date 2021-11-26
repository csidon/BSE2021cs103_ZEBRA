#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>

#include "all_headers.h"

using namespace std;



//---------------------------------------------------------------- NEXT SECTION [DISTANCE/COST CALCULATION FUNCTIONS] --------------------------------------------------------------------------------------
////Coder: Anastasiia K
////File: distance_calc.cpp
////Edited on: 10 Nov 2021
////Last Edited Date:  11 Nov 2021
////Purpose: This file contains the distance CALCULATION for the Zebra program

//########################################################################################################
//   DISTANCE CALCULATION FUNCTIONS
//   Used for calculating distance between start and end locations, to derive trip cost calculations
// #######################################################################################################
//
//FOLMULA FOR CALCULATION ON A COORDINATE PLANE
//***************************************************
double calc(struct Location p, struct Location ptr)
{
	double dist;
	dist = sqrt(pow((p.x - ptr.x), 2) + pow((p.y - ptr.y), 2));
	return (dist);
}

//***************************************************
//MANUALY INPUTING COORDINATES USING POINTER
//***************************************************
struct Location* stored_locations(struct Location* ptr)
{
	ptr->id = "BROOKLYN";
	ptr->x = 1.0;
	ptr->y = 1.0;
	ptr++;

	ptr->id = "HAITAITAI";
	ptr->x = 16.0;
	ptr->y = 2.5;
	ptr++;

	ptr->id = "ARO_VALLEY";
	ptr->x = 3.0;
	ptr->y = 8.0;
	ptr++;

	ptr->id = "KELBURN";
	ptr->x = 3.0;
	ptr->y = 13.0;
	ptr++;


	ptr->id = "MT_COOK";
	ptr->x = 6.5;
	ptr->y = 4.3;
	ptr++;

	ptr->id = "TE_ARO";
	ptr->x = 8.0;
	ptr->y = 8.0;

	return (ptr);
}
//***************************************************
//FUNCTION TO SET COORDINATES
//***************************************************

bool set_coordinates(struct Location data_array[], struct Location* coordinates, string input)
{
	int arrSize = *(&data_array + 1) - data_array;//CALCULATING SIZE OF THE ARRAY
	for (int i = 0; i < arrSize; i++)
	{
		//cout << i << endl;//DEBUG
		if (input == data_array[i].id)
		{
			//cout << "\nDEBUG";
			coordinates->x = data_array[i].x;
			coordinates->y = data_array[i].y;
			coordinates->id = data_array[i].id;
			//cout << "\n"<<coordinates->id<<endl;//DEBUG
			return(true);
		}
	}
	return (false);
}


//****************************************************************************************************
//  MAIN FUNCTION FOR DISTANCE CALCULATOR: 
//Takes input for start and end location (preset strings) and calculates the distance between the two
//****************************************************************************************************

double main_dist_calc(string startLoc, string endLoc)
{
	double dist;
	Location coordinates_A, coordinates_B;
	Location* p;
	Location arr[6];
	p = arr;
	stored_locations(p);
	set_coordinates(arr, &coordinates_A, startLoc);
	set_coordinates(arr, &coordinates_B, endLoc);

	dist = calc(coordinates_A, coordinates_B) / 2;
	//cout << "The calculated distance between " << startLoc << " and " << endLoc << " is " << dist;
	return (dist);
}

string random_locations(int n)
{
	Location* ptr_location_stored;
	Location arr_of_loc[6];
	ptr_location_stored = arr_of_loc;

	stored_locations(ptr_location_stored);

	string random_location = arr_of_loc[n].id;
	//cout << "\n" << random_location;
	return random_location;
}

//****************************************************************************************************
//  FUNCTION TO CALCULATE COST BASED ON DISTANCE: 
//  Based off Ola and Uber's rate cards
//****************************************************************************************************

void disp_fares_charges()
{
	disp_star_line();
	disp_h3_lines("Zebra Taxi: Our Rate Card");
	cout << "\n\n\tBASE FARE";
	cout << "\n\tZebra charges a flat booking fee of 45 cents, and base fare\n\tof $1.10 for the first kilometer.\n";
	disp_dash_line();
	cout << "\n\tSUBSEQUENT RATE PER KM";
	cout << "\n\t$1.10 per km - The lowest rates in town!\n";
	disp_dash_line();
	cout << "\n\tMINIMUM FARE";
	cout << "\n\t$3.50\n";
	//cout << "\n\t[More to be added if there's time]\n\t";
	cout << "\n\t";


}

double calc_ride_cost(double distance)
{
	double calc_cost, subs_rate_per_km, base_fare;
	cout << fixed;
	cout << setprecision(2); //this sets cost price to 2 decimal places

	base_fare = 0.45 + 1.1;
	subs_rate_per_km = (distance - 1) * 1.1;
	calc_cost = base_fare + subs_rate_per_km;

	if (calc_cost < 3.5)
	{
		return (3.5);
	}
	else
	{
		return (calc_cost);
	}

}

//------------------------------------------------------------------ NEXT SECTION [TRIP TRANSACTION FILE FUNCTIONS] --------------------------------------------------------------------------------------
////Coder: Anastasiia Karpova and Chris C
////Edited on: 7 Nov 2021
////Last Edited Date:  26 Nov 2021

string currentDateTime()
{
	time_t now = time(0);// current date/time based on current system
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	//cout << buf;
	return(buf);
}

void write_to_trip_transactions(Trips this_trip)
{
	fstream trip_file("trip_transactions.csv", ios::app);
	trip_file << this_trip.trip_id << "," << this_trip.driver_id << "," << this_trip.rider_id << "," << this_trip.start_loc << ",";
	trip_file << this_trip.end_loc << "," << this_trip.trip_cost << "," << this_trip.trip_date << endl;

	trip_file.close();
}

vector <Trips> read_from_trips()
{
	fstream tripFile("trip_transactions.csv", ios::in);
	vector <Trips> temp_trip;
	Trips t;

	string line;
	while (getline(tripFile, line))
	{
		istringstream linestream(line);
		string single_trip;

		getline(linestream, single_trip, ',');
		t.trip_id = single_trip;

		getline(linestream, single_trip, ',');
		t.driver_id = single_trip;

		getline(linestream, single_trip, ',');
		t.rider_id = single_trip;

		getline(linestream, single_trip, ',');
		t.start_loc = single_trip;

		getline(linestream, single_trip, ',');
		t.end_loc = single_trip;

		getline(linestream, single_trip, ',');
		stringstream ss(single_trip);
		ss >> t.trip_cost;

		getline(linestream, single_trip, ',');
		t.trip_date = single_trip;

		temp_trip.push_back(t);
	}

	tripFile.close();
	return (temp_trip);
}

//**********************
//FUNCTION TO count line in the file
//**********************
int count_entries_trips()
{
	int total_entries = 0;
	string s;
	fstream tripFile("trip_transactions.csv", ios::in);
	if (!tripFile)
	{
		total_entries = 0;
	}
	else
	{
		while (!tripFile.eof())
		{
			getline(tripFile, s);
			total_entries++;
		}
		total_entries = total_entries - 1;

	}
	//cout << "\nNumber of lines in file is " << total_entries; //debugging

	return (total_entries);
}

//**********************
//FUNCTION TO input data for the trip
//**********************


struct Trips input_trip_data(vector <Rider_pid>& rider, vector<Drivers>& driverFromFile, vector <Trips>& trip, string check_name, string d_username)

{
	Trips t;

	srand(time(NULL)); //initialize the random seed
	int randloc1 = rand() % 6;
	int randloc2 = rand() % 6;
	//cout << randloc2 << randloc1;
	driverFromFile = readFromFile();
	rider = rider_retrieve_info();
	for (int i = 0; i < rider.size(); i++)
	{

		string id_num_string_r = to_string(rider[i].r_idnum);//converting int datatype to a string

		if (check_name == rider[i].r_pname)
		{
			t.rider_id = rider[i].r_idalpha + id_num_string_r;
		}

	}
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		string id_num_string_d = to_string(driverFromFile[i].d_idNum);//converting int datatype to a string
		if (d_username == driverFromFile[i].mail)
		{
			t.driver_id = driverFromFile[i].d_idAlph + id_num_string_d;
		}
	}

	//filling the struct with data
	string count_entries_string = to_string(count_entries_trips() + 1);
	t.trip_id = "TR" + count_entries_string;// revise

	t.start_loc = random_locations(randloc1);
	t.end_loc = random_locations(randloc2);
	t.trip_cost = main_dist_calc(t.start_loc, t.end_loc);
	t.trip_date = currentDateTime();

	return (t);
}

string convert_string_to_upper(string& string_entry)
{
	char c;
	string converted_string;
	for (int i = 0; i < string_entry.length(); i++)
	{
		c = toupper(string_entry[i]);
		converted_string += c;
	}

	//cout << "\n This is the converted string " << converted_string;  //for debugging purposes
	return converted_string;
}

//------------------------------------------------------------------ NEXT SECTION [VALIDATION FUNCTIONS] --------------------------------------------------------------------------------------

//Coder: Chris C
//File: pswd_email_validation.cpp
//Edited on: 2 Nov 2021
//Last Edited Date:  2 Nov 2021
//Purpose: This file contains the functions that we will use (and reuse) to validate passwords and emails

//###############################################
//		VALIDATION FUNCTIONS
//###############################################
// This function checks that there is a lowercase letter in string
bool is_small_char(char c)
{
	return (c >= 'a' && c <= 'z');
}
// This function checks that there is a uppercase letter in string
bool is_big_char(char C)
{
	return (C >= 'A' && C <= 'Z');
}
// This function checks that there is a digit (0-9) in string
bool is_a_digit(const char d)
{
	return (d >= '0' && d <= '9');
}
// This function checks that there is an @ symbol in string
bool has_AT(char at)
{
	return (at == '@');
}
// This function checks that there is a "." in string
bool has_dot(char dot)
{
	return (dot == '.');
}
// This function checks that there is an empty char in string
bool has_space(char space)
{
	return (space == ' ');
}

//******************************************************************************************
//  CREDIT CARD VALIDATION
// This function validates that the card number is in number format #### #### #### ####
//******************************************************************************************
int creditcard_num_valid(string credit)
{
	int flag = 0;
	//cout << "\nChecking card length " << credit.length() << endl;
	//If the input has correct length
	if (credit.length() == 19)

	{
		//cout << "\n length ok";
		//if input at positions 4, 9, 14, are spaces
		if ((has_space(credit[4])) || (has_space(credit[9])) || (has_space(credit[14])))
		{
			//cout << "\nSpace ok";
			int chunk = 0;
			for (int i = 0; i < 4; i++)
			{
				//cout << "\n chunked value " << chunk;
				string temppull = (credit.substr(chunk, 4));
				//cout << "\ndebugging temppull 1  " << temppull;
				for (int i = 0; i < 4; i++)
				{
					if (is_a_digit(temppull[i]))
						flag = 1;
					else
						flag = 0;

				}
				//cout << "\nflag value after isdigit loop is " << flag;
				chunk += 5;
				//cout << "\n chunked value after loop " << chunk;
			}
		}
	}
	//cout << "\n" << flag << "  <--This is the flag value\n";
	return flag;
}

//******************************************************************************************
//  EMAIL VALIDATION FUNCTION
//  This function validates that the user's input includes an @ and at least one "." 
//******************************************************************************************
int email_valid(string remail)
{
	int AT_num = 0, dot_num = 0;
	//remail.length() is the number of chars in the email address provided by user
	//## This section pushes each char in remail to a vector called remail_arr
	vector<char> remail_arr; //defining a vector called remail_arr
	for (int i = 0; i < remail.length(); i++)
	{
		//cout << remail[0]; //debugging
		//cout << (!(is_a_digit(remail[0]))); //debugging
		//cout << (!(is_small_char(remail[0]))); //debugging
		//cout << !(is_big_char(remail[0])); //debugging
		if (is_a_digit(remail[0]) || is_small_char(remail[0]) || is_big_char(remail[0]))
		{
			remail_arr.push_back(remail[i]);
			//cout << remail[i] << "\t"; //uncomment for debugging purposes

			//This section checks that there is only ONE @ and at least one '.' char
			if (has_AT(remail[i]))
			{
				AT_num += 1;
			}
			if (has_dot(remail[i]))
			{
				dot_num += 1;
			}
		}
		else
		{
			cout << "\n\tPlease enter a valid email address\n";
			return 0;
		}

	}
	if (AT_num == 1 && (dot_num >= 1 && dot_num <= 3)) //allow 3 dots for domains like .co.nz
	{
		//cout << "EMAIL IS VALID!!";  //for debugging purposes
		return 1;
	}
	else
	{
		cout << "\n\tPlease enter a valid email address\n";
		return 0;
	}
}

//******************************************************************************************
//  PASSWORD VALIDATION FUNCTION
//This function validates that the user's input has min 8 chars, 
//contains a number and Large and small letters -- PASSWORD VALIDATION
//******************************************************************************************
int pswd_valid(string rpswd)
{
	int smchar = 0, bchar = 0, num = 0;
	//remail.length() is the number of chars in the email address provided by user
	//## This section pushes each char in remail to a vector called remail_arr
	vector<char> rpswd_arr; //defining a vector called remail_arr
	if (rpswd.length() < 8)
	{
		cout << "\n\tPlease enter a password with more than 8 characters\n";
		return 0;
	}
	for (int i = 0; i < rpswd.length(); i++)
	{
		rpswd_arr.push_back(rpswd[i]);
		//cout << rpswd[i] << "\t"; //for debugging purposes
		if (is_small_char(rpswd[i]))
		{
			smchar += 1;
		}
		if (is_big_char(rpswd[i]))
		{
			bchar += 1;
		}
		if (is_a_digit(rpswd[i]))
		{
			num += 1;
		}
	}
	if (smchar == 0)
	{
		cout << "\n\tPlease use at least one small letter\n";
		return 0;
	}
	else if (bchar == 0)
	{
		cout << "\n\tPlease use at least one capital letter\n";
		return 0;
	}
	else if (num == 0)
	{
		cout << "\n\tPlease use at least one number\n";
		return 0;
	}
	else
	{
		return 1;
	}
}

//******************************************************************************************
//  CHECKING FOR DUPLICATES FUNCTION
//This function checks to see that there is no duplicate values in a specified file
//******************************************************************************************
int check_dup(string input, string from_file)
{
	int has_dup_flag = 0;
	string converted_input = convert_string_to_upper(input);
	string converted_filevalue = convert_string_to_upper(from_file);
	//cout << "\nDebugging checkdup converted input \t:" << converted_input;
	//cout << "\nDebugging checkdup converted filevalue? \t:" << converted_filevalue;

	if (converted_input == converted_filevalue)
	{
		has_dup_flag = 1;
	}
	//cout << "\nDebugging checkdup has_flag? \t:" << has_dup_flag;
	return has_dup_flag;
}


//------------------------------------------------------------------ NEXT SECTION [MAKE PRETTY FUNCTIONS] --------------------------------------------------------------------------------------

//Coder: Chris C
//File: makepretty.cpp
//Edited on: 2 Nov 2021
//Last Edited Date:  2 Nov 2021
//Purpose: This file contains the decorative functions for the Zebra program

//###############################################
//		DISPLAY/DECORATIVE FUNCTIONS
//###############################################

//This function displays the Main Page's ZEBRA logo
void disp_main_logo()
{
	cout << "\n\n\t\t$$$$$$$$\\          $$\\                          ";
	cout << "\n\t\t\\____$$  |         $$ |                         ";
	cout << "\n\t\t     $$  /$$$$$$\\  $$$$$$$\\   $$$$$$\\  $$$$$$\\  ";
	cout << "\n\t\t   $$  / $$  __$$\\ $$  __$$\\ $$  __$$\\ \\____$$\\ ";
	cout << "\n\t\t  $$  /  $$$$$$$$ |$$ |  $$ |$$ |  \\__|$$$$$$$ |";
	cout << "\n\t\t $$  /   $$   ____|$$ |  $$ |$$ |     $$  __$$ |";
	cout << "\n\t\t $$$$$$$$\\$$$$$$$\\ $$$$$$$  |$$ |     \\$$$$$$$ |";
	cout << "\n\t\t\\\________|\\_______|\\_______/ \\__|      \\_______|\n";
}


void disp_driver_regist()
{
	cout << "\n\n\t _____    _                 ____       _";
	cout << "\n\t|__  /___| |__  _ __ __ _  |  _ \\ _ __(_)_   _____ _ __ ";
	cout << "\n\t  / // _ \\ '_ \\| '__/ _` | | | | | '__| \\ \\ / / _ \\ '__|";
	cout << "\n\t / /|  __/ |_) | | | (_| | | |_| | |  | |\\ V /  __/ |";
	cout << "	\n\t/____\\___|_.__/|_|  \\__,_| |____/|_|  |_| \\_/ \\___|_|";
	cout << "\n\t\t ____            _     _             _   _             ";
	cout << "\n\t\t|  _ \\ ___  __ _(_)___| |_ _ __ __ _| |_(_) ___  _ __";
	cout << "\n\t\t| |_) / _ \\/ _` | / __| __| '__/ _` | __| |/ _ \\| '_ \\";
	cout << "\n\t\t|  _ <  __/ (_| | \\__ \\ |_| | | (_| | |_| | (_) | | | |";
	cout << "\n\t\t|_| \\_\\___|\\__, |_|___/\\__|_|  \\__,_|\\__|_|\\___/|_| |_|";
	cout << "\n\t\t           |___/                                       ";
}

void disp_zebra_driver()
{
	cout << "\n\n\t _____    _                 ____       _";
	cout << "\n\t|__  /___| |__  _ __ __ _  |  _ \\ _ __(_)_   _____ _ __ ";
	cout << "\n\t  / // _ \\ '_ \\| '__/ _` | | | | | '__| \\ \\ / / _ \\ '__|";
	cout << "\n\t / /|  __/ |_) | | | (_| | | |_| | |  | |\\ V /  __/ |";
	cout << "	\n\t/____\\___|_.__/|_|  \\__,_| |____/|_|  |_| \\_/ \\___|_|";
}

//This function displays the Rider pages' logo
void disp_rider_logo()
{
	cout << "\n\t  _____    _                 ____  _     _            ";
	cout << "\n\t |__  /___| |__  _ __ __ _  |  _ \\(_) __| | ___ _ __ ";
	cout << "\n\t   / // _ \\ '_ \\| '__/ _` | | |_) | |/ _` |/ _ \\ '__|";
	cout << "\n\t  / /|  __/ |_) | | | (_| | |  _ <| | (_| |  __/ |   ";
	cout << "\n\t /____\\___|_.__/|_|  \\__,_| |_| \\_\\_|\\__,_|\\___|_|   \n";
}

//This function displays a "#####" H2 border around (string title)
void disp_h2_lines(string title)
{
	int title_length = title.length();
	cout << "\n\t";
	for (int i = 0; i < 64; i++)
	{
		cout << "#";
	}
	cout << "\n\t#";
	int center_text = (62 - title_length) / 2;
	if (title_length % 2 == 1)
	{
		for (int i = 0; i < center_text + 1; i++)
		{
			cout << " ";
		}
	}
	else
	{
		int center_text = (62 - title_length) / 2;
		for (int i = 0; i < center_text; i++)
		{
			cout << " ";
		}
	}

	cout << title;

	for (int i = 0; i < center_text; i++)
	{
		cout << " ";
	}
	cout << "#\n\t";
	for (int i = 0; i < 64; i++)
	{
		cout << "#";
	}
}

//This function displays a "+---+" H3 border around (string title)
void disp_h3_lines(string title)
{
	int title_length = title.length();
	cout << "\n\t+";
	for (int i = 0; i < (title_length + 4); i++)
	{
		cout << "-";
	}
	cout << "+";
	cout << "\n\t|  " << title << "  |";
	cout << "\n\t+";
	for (int i = 0; i < (title_length + 4); i++)
	{
		cout << "-";
	}
	cout << "+";
}

//This function displays a ----- section dividing line
void disp_dash_line()
{
	cout << "\n\t";
	for (int i = 0; i < 64; i++)
	{
		cout << "-";
	}
	cout << "\n";
}

///This function displays a ***** section dividing line
void disp_star_line()
{
	cout << "\n\t";
	for (int i = 0; i < 64; i++)
	{
		cout << "*";
	}
	cout << "\n";
}


