#include <iostream>
#include <fstream>
#include <string>
#include "makepretty.h"
#include "pswd_email_validation.h"
#include "zebra_rider.h"
#include "zebra_driver.h"
#include "GitCollab_Zebra.h"


using namespace std;





int main()
{
	disp_main_logo();
	int main_input;

	//Initialising vector class for structure Rider_pid so that the structure can take unlimited entries
	vector <Rider_pid> rider_input_info;
	vector <Rider_pid> rider_read_file_info;
	vector <Rider_pid> rider_tempfile;

<<<<<<< HEAD
=======
<<<<<<< HEAD
	//Initialising vector class for structure Rider_pid so that the structure can take unlimited entries

=======

>>>>>>> 32d0ff8a31a1647ef19d6245f7d1bd5f722c55de
>>>>>>> 0158707d1c308c94f755346749710f8fe6bf9192
>>>>>>> 399a6ce996ddec83c3124dc02ad2ef880b427c27
	////####### Main Page ########[Chris]
	system("Color 8");
	disp_main_logo();
	disp_h2_lines("The Best NZ Taxi Booking System");
	disp_h3_lines("Select: ");
	cout << "\n\t1. Driver\n";
	cout << "\n\t2. Passenger\n";
	disp_dash_line();
	cout << "\n\t3. Admin\n";
	cout << "\n\t4. Exit\n";

	disp_star_line();
	cout << "\tSelect [1], [2], [3], or [4]\n\tChoose: \n\t";
	cin >> main_input;
	if (main_input == 1)
	{
		driver_main();
	}
	else if (main_input == 2)
	{
		//####### Goes To Main Rider Page #######[Chris]
		system("Color 9"); //anything rider-related will be displayed in this color
		//rider_main(rider_input_info);
		rider_read_file_info = rider_main(rider_input_info);

	}

	//disp_star_line();
	//cout << "\tSelect [1], [2], [3], or [4]\n\tChoose: \n\t";
	//cin >> main_input;
	//if (main_input == 2)
	//{
	//	//####### Goes To Main Rider Page #######[Chris]
	//	system("Color 9"); //anything rider-related will be displayed in this color
	//	rider_main(rider_input_info, rider_retrieve_info);
	//	writeRiderToFile(rider_input_info);
	//	//email_valid(rider_input_info);
	//}
	


//>>>>>>> a3080d111c3957b7c983a8ae3b3457cb094692a3
=======

>>>>>>> 32d0ff8a31a1647ef19d6245f7d1bd5f722c55de
	//*****************************************************************************
	//Examples on how to use decorative functions available in makepretty.cpp file
	//*****************************************************************************
	//disp_main_logo();
	//disp_rider_logo();
	//disp_dash_line();
	//disp_star_line();
	//disp_h2_lines(string title);
	//disp_h3_lines(string title);

	
	//***************************************************************************
	//Example on how to use username/pswd validation in pswd_email_validation.h
	//***************************************************************************
//	string r_emailusrname, r_pswd;
//
//valid_email:
//	cout << "\n\tEnter Your Email Address";
//	cin >> r_emailusrname;
//
//	if (email_valid(r_emailusrname) == 0)
//	{
//		cout << "\n\t!!Please enter a valid email address!!";
//		goto valid_email;
//	}
//	
//valid_pass:
//	cout << "\n\tPassword";
//	cout << "\n\t[Passwords must be";
//	cout << "\n\tlonger than 8 chars,";
//	cout << "\n\tcontain both numbers &";
//	cout << "\n\tbig and small letters\t:  ";
//	cin >> r_pswd;
//	if (pswd_valid(r_pswd) == 0)
//	{
//		goto valid_pass;
//	}

}

