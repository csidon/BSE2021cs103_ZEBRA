#include <iostream>
#include <fstream>
#include <string>
#include "makepretty.h"
#include "pswd_email_validation.h"
#include "zebra_rider.h"
#include "zebra_driver.h"
#include "GitCollab_Zebra.h"
#include "distance_calc.h"
#include "all_headers.h"

using namespace std;



int main()
{
	
	int main_input;
	
	string keep_going = "y";

	////####### Main Page ########[Chris]
	while (keep_going == "y")
	{
		system("Color 4");

		disp_main_logo();
		disp_h2_lines("The Best NZ Taxi Booking System");
		disp_h3_lines("Select: ");
		cout << "\n\t1. Driver\n";
		cout << "\n\t2. Passenger\n";
		disp_dash_line();
		//cout << "\n\t3. Admin\n";
		cout << "\n\t4. Exit\n";

		disp_star_line();
		cout << "\tSelect [1], [2], [3], or [4]\n\tChoose: \n\t";
		cin >> main_input;
		if (main_input == 1)
		{
			system("cls");
			system("Color 6");
			driver_main();
			keep_going = "y";
		}
		else if (main_input == 2)
		{
			//####### Goes To Main Rider Page #######[Chris]
			//anything rider-related will be displayed in this color
			system("Color 9");
			//This function will write the new data into the riderpid.csv file. Full function in zebra_rider.cpp file
			rider_main();
			keep_going = "y";

		}
		else if (main_input == 3)
		{
			cout << "\n\tFunctionality under construction. \n\tPlease be patient with us!\n";
			cout << "\t";
			system("pause");
			keep_going = "y";
		}
		else
		{
			keep_going = "n";
		}
	}
	


}
