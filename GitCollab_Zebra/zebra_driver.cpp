#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "all_headers.h"


using namespace std;

//Coder: Anastasiia Karpova
//File: zebra_driver.cpp
//Edited on: 4 Nov 2021
//Last Edited Date:  15 Nov 2021
//Purpose: This file contains the functions for the Zebra Driver


	//**********************
	//MAIN FUNCTION FOR THE DRIVER 
	//**********************
void driver_main()
{
	//initialising vectors
	vector <Drivers> driver;
	vector <Drivers> driverFromFile;
	vector <Trips> trip;
	vector <Rider_pid> rider;

	disp_zebra_driver();
	cout << endl;
	disp_h2_lines("What are you up to?");
	int n;
	cout << "\n\n\t1. Register\n";
	cout << "\n\t2. Login\n";
	cout << "\n\t3. Back\n\n";
	cout << "\n\t[Enter your choice - 1, 2, 3 or 4]";
	cout << "\n\tChoose:\t";
	cin >> n;
	system("cls");
	switch (n)
	{
	case 1:
		//read_last_line();

		disp_driver_regist();//"pretty function"
		cout << endl;
		driver_eligibility(driver, driverFromFile);//calling function to check if driver is eligible
		break;
	case 2:
		driver_login(driverFromFile);//calling function to login into the system
		break;
	case 3:
		//main();
		break;
	}
}


//**********************
//FUNCTION TO CHECK IF DRIVER IS ELIGIBLE
//**********************

void driver_eligibility(vector<Drivers>& driver, vector<Drivers>& driverFromFile)
{
	disp_h3_lines("Eligibility Check");
	char full, n;
	int car_age, driver_age;
	disp_h3_lines("Enter Y / N");

	cout << "\n\t Do you have full NZ drive license?" << "\t";
	cin >> full;

	cout << "\n\tHave you had your full drivers' license for a minimum of 2 years?" << "\t";
	cin >> n;

	cout << "\n\tHow old is your taxi vehicle?" << "\t";
	cin >> car_age;

	cout << "\n\tPlease enter your age" << "\t";
	cin >> driver_age;

	if (full == 'Y' && n == 'Y' && car_age <= 10 && driver_age >= 21)//checking if driver meets criteria
	{
		system("cls");
		driver_registration(driver, driverFromFile);
	}
	else
	{
		cout << "\nSorry, you are not eligible to be our driver.";
		system("pause");
		system("cls");
		//main();
	}
}

//**********************
//FUNCTION TO REGISTER(MOSTLY CALLING ANOTHER FUNCTIONS
//**********************

void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile)
{
	disp_driver_regist();//pretty function
	cout << endl;
	disp_h2_lines("Be Your Own Boss - Sign up to be a Zebra Driver today!");//pretty function
	input_drivers(driver);//calling function to input data to the Drivers struct
	//**********************
	//cout << driver[0].fname << endl;//debugging purposes 
	//**********************
	writeToFile(driver);//calling function to write data to the file
	system("cls");
	driver_login(driverFromFile);//calling function to login to the system

}

//**********************
//FUNCTION TO INPUT DATA TO THE DRIVERS STRUCT(TAKING INPUT FROM USER)
//**********************

vector <Drivers> input_drivers(vector<Drivers>& driver)
{
	disp_driver_regist();//pretty function
	cout << endl;
	disp_h2_lines("Sign up to Drivers Zeabra!");//pretty function
	Drivers d;// struct with a temporary varible 
	disp_h3_lines("Please, enter your:");

	cout << "\n\n\n\tFirst Name: ";
	cin >> d.fname;
	cout << "\n\tSecond Name: ";
	cin >> d.sname;
	cout << "\n\tPreferred Name: ";
	cin >> d.pref_name;
	cout << "\n\tContact number: ";
	cin >> d.phone_num;
	cout << "\n\tGender(male/female): ";
	cin >> d.gender;
	cout << "\n\tDate of birth(dd/mm/yyyy): ";
	cin >> d.birth;
	cout << "\n\tNationality: ";
	cin >> d.nationality;
	cout << "\n\tE-mail adress";
	cout << "\n\t[Note: This will also be  Your username]: ";
	cin >> d.mail;
	email_valid(d.mail);
	cout << "\n\tPassword: ";
	cin >> d.password;
	pswd_valid(d.password);

	//output_drivers(driver);

	cout << "\n\n\tPlease, enter your: ";

	cout << "\n\tDrivers' License #	[Format:AB123456]: ";
	cin >> d.lice_num;
	cout << "\n\tDate of Expiry Format[DD / MM / YYYY]: ";
	cin >> d.doex;
	cout << "\n\tDriving Experience # of years: ";
	cin >> d.exp;
	cout << "\n\tVehicle Registration #: ";
	cin >> d.veh_regist;
	cout << "\n\tVehicle Age: ";
	cin >> d.veh_age;
	cout << "\n\tVehicle Model: ";
	cin >> d.veh_model;
	cout << "\n\tWOF Expiry date: ";
	cin >> d.wof_exp;
	cout << "\n\tBank account number: ";
	cin >> d.bank_acc;
	cout << "\n\tBank name: ";
	cin >> d.bank_name;

	//**********************
	//this part creates UID for drivers
	//**********************
	d.d_idAlph += "D" + d.fname.substr(0, 1);
	d.d_idAlph += d.sname.substr(0, 2);
	d.d_idNum = 1001 + count_entries_drive();

	driver.push_back(d);
	return (driver);

}

//**********************
//this part creates UID for drivers
//**********************
int count_entries_drive()
{
	int total_entries = 0;
	string s;
	fstream driverFile("driverFile_pid.csv", ios::in);
	if (!driverFile)//check if the file exists and if it is open
	{
		total_entries = 0;
	}
	else
	{
		while (!driverFile.eof())//while it is not the endo of the file, do the following
		{
			getline(driverFile, s);
			total_entries++;
		}
		total_entries = total_entries - 1;

	}
	//cout << "\nNumber of lines in file is " << total_entries; //debugging

	return (total_entries);
}


//void output_drivers(vector<Drivers>& driver)
//{
//	for (int i = 0; i < driver.size(); i++)
//	{
//		cout << "\n\tHello, " << driver[i].pref_name << " please, check your information and confirm" << endl;
//		cout << " \n\t " << driver[i].fname << "\t" << driver[i].sname;
//		cout << " \n\t " << driver[i].phone_num << "\t" << driver[i].mail << "      will be used as your username";
//	}
//}


	//**********************
	//CREATING DRIVER FILE AND FILLING IT UP WITH DATA
	//**********************
void writeToFile(vector<Drivers>& driver)
{
	//cout << driver[0].fname;//debugging purposes
	//cout << "\nFisrt debug";
	fstream driverFile("driverFile_pid.csv", ios::app);// open file using append mode, to ADD info, not overwrite
	//cout <<"/nsize of driver"<< driver.size();
	for (int i = 0; i < driver.size(); i++)
	{
		//cout << "\nsecond DEBUG";	
		driverFile << driver[i].d_idAlph << "," << driver[i].d_idNum << "," << driver[i].fname << "," << driver[i].sname << "," << driver[i].pref_name << "," << driver[i].phone_num << "," << driver[i].mail << "," << driver[i].password << "," << driver[i].gender << "," << driver[i].birth << "," << driver[i].nationality << "," << driver[i].lice_num << "," << driver[i].doex << "," << driver[i].exp << "," << driver[i].veh_regist << "," << driver[i].veh_age << "," << driver[i].veh_model << "," << driver[i].wof_exp << "," << driver[i].bank_acc << "," << driver[i].bank_name << endl;
	}
	driverFile.close();
	//cout <<"/nsize of driver"<< driver.size();
}


//**********************
//FUNCTION TO LET USER ENTER THEIR ACCOUNT
//**********************

vector<Drivers> driver_login(vector<Drivers>& driverFromFile)

{
	disp_zebra_driver();
	cout << endl;
	disp_h2_lines("Login to your Zebra account");
	fstream driverFile("driverFile_pid.csv", ios::in);
	string login, password;
loginprocess:
	disp_h3_lines("Please, enter your:");

	cout << "\n\n\tUsername: ";
	cin >> login;
	cout << "\n\tPassword: ";

	cin >> password;
	driverFromFile = readFromFile();
	//cout << "\n\tThe size on vector: " << driverFromFile.size();
	//cout << driverFromFile[0].fname;

	for (int i = 0; i < driverFromFile.size(); i++)
	{
		//cout << "\nLooping through";//debug

		if (driverFromFile[i].mail == login && driverFromFile[i].password == password)
		{

			system("cls");

			driver_account_main(driverFromFile, login);

		}
		else
		{
			cout << "\n\n\tUsername or Password is incorrect";
			cout << "\n\n\t1. Sign in";
			cout << "\n\t2. Reset password";
			int n;
			cout << "\n\n\tChoose:\t";
			cin >> n;
			if (n == 1)
			{
				goto loginprocess;
			}
			else
			{
				pswd_reset_driver(driverFromFile);
			}
		}

	}
	driverFile.close();
	//driverFromFile = readFromFile();
	return(driverFromFile);
}

//**********************
//FUNCTION TO DISPLAY MAIN SCREEN OF THE DRIVER ACCOUNT
//**********************

void driver_account_main(vector<Drivers>& driverFromFile, string check_username)//passing vector and drivers email, to retrieve the correct info from the file
{
	disp_zebra_driver();
	cout << endl;
	disp_h2_lines("Welcome to your account!");
	vector <Rider_pid> rider;
	Rider_pid r;
	int n;
	cout << "\n\n\tKia ora, we are all good to go!";

	disp_dash_line();

	cout << "\n\n\tPlease choose from the following options:\n";
	cout << "\n\t1. Account settings\n";
	cout << "\n\t2. Pick a ride\n";
	cout << "\n\t3. Reset your password\n";
	cout << "\n\t4. Back\n\n";

	cout << "\n\t Choice:\t";
	cin >> n;

	system("cls");

	switch (n)
	{
	case 1:

		account_settings(driverFromFile, check_username);//calling function for account settings
		break;
	case 2:
		job_screen(rider, check_username);//calling function to pick up a rider

		break;
	case 3:
		pswd_reset_driver(driverFromFile);//calling password reset function
		break;

	case 4:
		driver_main();
		break;
	}
	
}

//**********************
//FUNCTION TO RESET PASSWORD
//**********************

vector<Drivers> pswd_reset_driver(vector <Drivers> driverFromFile)
{
	disp_zebra_driver();
	cout << endl;
	disp_h2_lines("Reset your password");
	fstream driver_file("driverFile_pid.csv", ios::out);

	string username, new_pswd;
	int reset_code = 0, email_exists = 0;
valid_emailusrname:
	cout << "\n\tNeed to reset your password? Please enter your email address:\t";
	cin >> username;
	disp_dash_line();//pretty function

	//searching for the provided email address/username
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		if (check_dup(username, driverFromFile[i].mail) == 1)
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
					cout << "New password IS Invalid"; //debugging purposes
					goto enter_new_pass;
				}
				driverFromFile[i].password = new_pswd;
				email_exists = 1;
			}
			else
			{
				cout << "\n\tYou've entered the wrong password reset code.";
				cout << "\n\t[Hint: Just enter 12345 for the purposes of this assignment.";
				goto enter_reset_code;
			}
		}
		driver_file << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
	}
	//Error message if email address isn't found
	if (email_exists == 0)
	{
		cout << "\n\tYou don't have a Zebra account with that email address.\n\tPlease try again.\n";
		goto valid_emailusrname;
	}

	driver_file.close();
	driverFromFile = readFromFile();
	return (driverFromFile);

}

//**********************
//FUNCTION TO READ FROM THE FILE
//**********************

vector <Drivers> readFromFile()
{
	fstream driverFile("driverFile_pid.csv", ios::in);
	vector<Drivers> tempDriver;

	Drivers d;
	string line;

	while (getline(driverFile, line))
	{
		//cout << line << endl;
		istringstream linestream(line);
		string user;
		getline(linestream, user, ',');
		d.d_idAlph = user;
		getline(linestream, user, ',');
		stringstream ss(user);//converting int to a string
		ss >> d.d_idNum;
		getline(linestream, user, ',');
		d.fname = user;
		getline(linestream, user, ',');
		d.sname = user;
		getline(linestream, user, ',');
		d.pref_name = user;
		getline(linestream, user, ',');
		d.phone_num = user;
		getline(linestream, user, ',');
		d.mail = user;
		getline(linestream, user, ',');
		d.password = user;
		getline(linestream, user, ',');
		d.gender = user;
		getline(linestream, user, ',');
		d.birth = user;
		getline(linestream, user, ',');
		d.nationality = user;
		getline(linestream, user, ',');
		d.lice_num = user;
		getline(linestream, user, ',');
		d.doex = user;
		getline(linestream, user, ',');
		d.exp = user;
		getline(linestream, user, ',');
		d.veh_regist = user;
		getline(linestream, user, ',');
		d.veh_age = user;
		getline(linestream, user, ',');
		d.veh_model = user;
		getline(linestream, user, ',');
		d.wof_exp = user;
		getline(linestream, user, ',');
		d.bank_acc = user;
		getline(linestream, user, ',');
		d.bank_name = user;
		getline(linestream, user, ',');
		tempDriver.push_back(d);
	}

	driverFile.close();
	return(tempDriver);
}


//**********************
//FUNCTION TO DISPLAY DATA FOR PARTICULAR DRIVER FROM THE FILE
//**********************

void account_settings(vector<Drivers> driverFromFile, string check_username)
{
	disp_zebra_driver();
	cout << endl;
	disp_h2_lines("Account settings");
	char n;
	fstream driverFile("driverFile_pid.csv", ios::in);
	driverFromFile = readFromFile();//assigning read from file data to the vector
usernamecheck:
	disp_h3_lines("Please, enter your USERNAME:");
	cout << endl;
	cin >> check_username;
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		if (check_username == driverFromFile[i].mail)
		{
			break;
		}
		else
		{
			cout << "\n\n\tPlease, enter valid username(case sensative)";
			goto usernamecheck;
		}
	}
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		if (check_username == driverFromFile[i].mail)
		{
			cout << "\n\n\tHello, " << driverFromFile[i].pref_name << endl;
			disp_dash_line();
			/*cout <<"\n\t" <<"First name:			"<<driverFromFile[i].fname;
			cout << "\n\t" << "Second name:			" << driverFromFile[i].sname;
			cout << "\n\t" << "Phone number:			" << driverFromFile[i].phone_num;
			cout << "\n\t" << "Gender:				" << driverFromFile[i].gender;
			cout << "\n\t" << "Date of birth:			" << driverFromFile[i].birth;
			cout << "\n\t" << "Nationality:			" << driverFromFile[i].nationality;*/
			cout << endl;
			cout << "\n\t" << "1. Driver's License #:\t" << driverFromFile[i].lice_num;
			cout << endl;
			cout << "\n\t" << "2. Date of Expiry:\t" << driverFromFile[i].doex;
			cout << endl;
			cout << "\n\t" << "3. Driving experience:\t" << driverFromFile[i].exp;
			cout << endl;
			cout << "\n\t" << "4. Vehical Registration Number:\t" << driverFromFile[i].veh_regist;
			cout << endl;
			cout << "\n\t" << "5. Vehical Age:\t" << driverFromFile[i].veh_age;
			cout << endl;
			cout << "\n\t" << "6. Vehical Model:\t" << driverFromFile[i].veh_model;
			cout << endl;
			cout << "\n\t" << "7. WOF Expiry date:\t" << driverFromFile[i].wof_exp;
			cout << endl;
			cout << "\n\t" << "8. Bank Account Number:\t" << driverFromFile[i].bank_acc;
			cout << endl;
			cout << "\n\t" << "9. Bank Name:\t" << driverFromFile[i].bank_name;

			break;
		}
	}
	driverFile.close();
	cout << "\n\tSelect [E] to edit your deatils.";
	cout << "\n\tSelect [B] to go back\n";
	cout << "\n\tChoose:\t";
	cin >> n;

	disp_dash_line();

	if (n == 'e'||n=='E')
	{

		update_acc_details(driverFromFile, check_username);//calling function to change data in the file

	}
	else
	{
		system("cls");
		driver_account_main(driverFromFile, check_username);//passing vector and drivers email, to retrieve the correct info from the file

	}
}


//**********************
//FUNCTION TO RE-WRITE 
//**********************

vector<Drivers> update_acc_details(vector < Drivers > driverFromFile, string check_username)
{
	string new_lice_num;
	string new_doex;
	string new_exp;
	string new_veh_regist;
	string new_veh_age;
	string new_veh_model;
	string new_wof_exp;
	string new_bank_acc;
	string new_bank_name;
	int choice;
	cout << "\n\tPlease, choose what would you like to change:\t";
	cin >> choice;
	//opining file to overwrite data in the file
	fstream driverFile("driverFile_pid.csv", ios::out);
	//rewwiting one piece og the data at a time
	switch (choice)
	{
	case 1:
		cin.ignore();
		cout << "\nEnter the new Drivers' License #	[Format:AB123456]:\t";
		getline(cin, new_lice_num);

		//passing a new data to the file
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].lice_num = new_lice_num;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}

		driverFile.close();
		break;
	case 2:
		cin.ignore();
		cout << "\nEnter the new date of expiry:\t";
		getline(cin, new_doex);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].doex = new_doex;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	case 3:
		cin.ignore();
		cout << "\nEnter driving experience:\t";
		getline(cin, new_exp);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].exp = new_exp;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	case 4:
		cin.ignore();
		cout << "\nEnter the new vehical registration number:\t";
		getline(cin, new_veh_regist);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].veh_regist = new_veh_regist;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	case 5:

		cout << "\nEnter the new vehical age:\t";
		getline(cin, new_veh_age);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].veh_age = new_veh_age;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	case 6:
		cin.ignore();
		cout << "\nEnter the new vehical model:\t";
		getline(cin, new_veh_model);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].veh_model = new_veh_model;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	case 7:
		cin.ignore();
		cout << "\nEnter new WOF Expiry date:\t";
		getline(cin, new_wof_exp);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].wof_exp = new_wof_exp;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
	case 8:
		cin.ignore();
		cout << "\nEnter the new bank account:\t";
		getline(cin, new_bank_acc);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].bank_acc = new_bank_acc;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	case 9:
		cin.ignore();
		cout << "\nEnter the new bank name:\t";
		getline(cin, new_bank_name);
		for (int i = 0; i < driverFromFile.size(); i++)
		{
			if (check_username == driverFromFile[i].mail)
			{
				driverFromFile[i].bank_name = new_bank_name;
				driverFile << driverFromFile[i].d_idAlph << "," << driverFromFile[i].d_idNum << "," << driverFromFile[i].fname << "," << driverFromFile[i].sname << "," << driverFromFile[i].pref_name << "," << driverFromFile[i].phone_num << "," << driverFromFile[i].mail << "," << driverFromFile[i].password << "," << driverFromFile[i].gender << "," << driverFromFile[i].birth << "," << driverFromFile[i].nationality << "," << driverFromFile[i].lice_num << "," << driverFromFile[i].doex << "," << driverFromFile[i].exp << "," << driverFromFile[i].veh_regist << "," << driverFromFile[i].veh_age << "," << driverFromFile[i].veh_model << "," << driverFromFile[i].wof_exp << "," << driverFromFile[i].bank_acc << "," << driverFromFile[i].bank_name << endl;
			}
		}
		break;
	}
	driverFile.close();
	driverFromFile = readFromFile();

	char a;
	disp_h3_lines("The information updated! Would you like to update anything else?");


	for (int i = 0; i < 3; i++)
	{
		cout << "\n\tChoose[select 'Y' for yes, 'N' for no]:\t";
		cin >> a;
		if (a == 'Y')
		{
			system("cls");
			update_acc_details(driverFromFile, check_username);//if user wants to cahnge smth else, direct them to the uppdate function
			break;
		}
		else if (a == 'N')
		{
			system("cls");
			driver_account_main(driverFromFile, check_username);// if user if satified, direct them to main screen of the driver acc
			break;
		}
		else
		{
			cout << "\n\tPlease enter only 'Y' or 'N':\t";//if user chose the unidentified letter
		}
	}

	system("cls");
	driver_account_main(driverFromFile, check_username);//after 3 unsuccesfull attempts direct user to the main screen

	return (driverFromFile);
}




//**********************
//FUNCTION TO DISPLAY AVAILABLE RIDES TO PICK
//**********************



void job_screen(vector <Rider_pid>& rider, string d_username)
{
	disp_zebra_driver();
	cout << endl;
	disp_h2_lines("Time to pick a rider!");
	vector<Drivers> driverFromFile;
	vector <Trips> trip;
	Trips temp_struct;

	//opening the RIDER file for reading
	fstream riderFile("riderpid.csv", ios::in);
	rider = rider_retrieve_info();

	//cout << "debug" << rand_rider;

	cout << "\n\t\tKia Ora! Ready to work?";
	disp_dash_line();
	cout << "\n\t\tThere's the available jobs waiting for you to pick up:  ";
	cout << endl;
	cout << "\n\t" << rider[1].r_pname;//hardcoding in the tearms of the assignment
	cout << "\n\tDistance from you	:  2.2 kms";
	cout << endl;
	cout << "\n\t" << rider[2].r_pname;
	cout << "\n\tDistance from you	:  3.1 kms";//dummy info
	cout << endl;
	//cout << "\n\t" << rider[i].r_pname;
	//cout << "\n\tDistance from you	:  5.2 kms";
	//cout << endl;
	//cout << "\n\t" << rider[i].r_pname;
	//cout << "\n\tDistance from you	:  3.2 kms";


	riderFile.close();
	disp_dash_line();
	cout << "\n\tEnter the name of the rider to pick up a job:\t";

	string check_name;
	cin >> check_name;

	system("cls");

	//input_trip_data(rider, driverFromFile, trip, check_name);
	//write_to_trip_transactions(trip);

	temp_struct = input_trip_data(rider, driverFromFile, trip, check_name, d_username);//passing input struct to the main struct

	//cout << temp_struct.driver_id;

	write_to_trip_transactions(temp_struct);//creating and writing to a new file. Linked to misc header

	temp_struct = input_trip_data(rider, driverFromFile, trip, check_name, d_username);
	//cout << temp_struct.driver_id;
	write_to_trip_transactions(temp_struct);
	//string trip_id_check = t.trip_id;
	//trip.push_back(t);
	//confirm_job_screen(rider, trip, check_name, trip_id_check);

	confirm_job_screen(rider, temp_struct, check_name);


	//string trip_id_check = t.trip_id;
	//trip.push_back(t);
	//confirm_job_screen(rider, trip, check_name, trip_id_check);

	confirm_job_screen(rider, temp_struct, check_name);//final billing screen

}



//**********************
//FUNCTION TO READ DATA FROM THE TRIP FILE
//**********************

//vector <Trips> read_from_trips()
//{
//	fstream tripFile("trip_transactions.csv", ios::in);
//	vector <Trips> temp_trip;
//	Trips t;
//
//	string line;
//	while (getline(tripFile, line))
//	{
//		istringstream linestream(line);
//		string single_trip;
//
//		getline(linestream, single_trip, ',');
//		t.trip_id = single_trip;
//
//		getline(linestream, single_trip, ',');
//		t.driver_id = single_trip;
//
//		getline(linestream, single_trip, ',');
//		t.rider_id = single_trip;
//
//		getline(linestream, single_trip, ',');
//		t.start_loc = single_trip;
//
//		getline(linestream, single_trip, ',');
//		t.end_loc = single_trip;
//
//		getline(linestream, single_trip, ',');
//		stringstream ss(single_trip);
//		ss >> t.trip_cost;
//
//
//
//		getline(linestream, single_trip, ',');
//		t.trip_date = single_trip;
//
//		temp_trip.push_back(t);
//	}
//
//	tripFile.close();
//
//	return (temp_trip);
//}


//**********************
//FUNCTION TO FOR THE FINAL BILLING SCREEN AFTER RIDE IS COMPLETE
//**********************

void confirm_job_screen(vector <Rider_pid>& rider, Trips trip_struct, string check_name)
{
	disp_dash_line();
	vector <Drivers> driver;
	vector <Rider_pid> rider_temp;
	//fstream tripFile("trip_transactions.csv", ios::in);
	fstream riderFile("riderpid.csv", ios::in);
	rider = rider_retrieve_info();
	//trip = read_from_trips();
	for (int i = 0; i < rider.size(); i++)
	{
		if (check_name == rider[i].r_pname)
		{
			cout << "\n\n\n\tYour are picking up:\t" << rider[i].r_pname;
		}
	}
	riderFile.close();

	cout << "\n\n\tTrip number is:\t" << trip_struct.trip_id << "\t" << trip_struct.trip_date;
	cout << "\n\n\tFrom:\t" << trip_struct.start_loc;
	cout << "\n\n\tDestination:\t" << trip_struct.end_loc;

	/*trip.push_back(t);*/

	//tripFile.close();

	disp_dash_line();

	string check_username;
	cout << "\n\tPress any button when you've picked them up\n";
	cout << "\n\t[CANCEL] to cancel this booking\n";
	cout << "\n\tChoose:\t";
	string choice;
	cin >> choice;
	if (choice == "CANCEL")
	{

		cout << "\n\tWARNING! You are about to cancel booking. Would you like to continue?";
		cout << "\n\t[Y] for yes. [N] for no:\t";
		char can_choice;
		cin >> can_choice;
		if (can_choice == 'Y')
		{
			system("cls");
			driver_account_main(driver, check_username);//directing user to the main screen
		}
	}



	else
	{
		disp_dash_line();
		cout << "\n\tAwesome! Press ant button when you've dropped them off";
		cout << "\n\tEnter you username to to access billing info\t: ";
		cin >> check_username;
	usernamecheck:
		disp_h3_lines("Please, enter your USERNAME to access bill information:");
		cin >> check_username;
		for (int i = 0; i < driver.size(); i++)
		{
			if (check_username == driver[i].mail)
			{
				break;
			}
			else
			{
				cout << "\n\n\tPlease, enter valid username(case sensative)";
				goto usernamecheck;
			}
		}
		cout << "\n\tNice! You have earned\t" << trip_struct.trip_cost;


		system("pause");

		system("cls");

		driver_account_main(driver, check_username);//directing user to the main screen
	}
	//return (trip);

}



