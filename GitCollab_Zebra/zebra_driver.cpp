#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "makepretty.h"
#include "pswd_email_validation.h"
#include "GitCollab_Zebra.h"
#include "zebra_driver.h"
#include "zebra_rider.h"
#include "distance_calc.h"
#include "misc_functions.h"
using namespace std;

//Coder: Anastasiia Karpova
//File: zebra_driver.cpp
//Edited on: 4 Nov 2021
//Last Edited Date:  15 Nov 2021
//Purpose: This file contains the functions for the Zebra Driver

void driver_main()
{
	vector <Drivers> driver;
	vector <Drivers> driverFromFile;
	vector <Trips> trip;
	vector <Rider_pid> rider;


	int n;
	cout << "\n\t1. Register";
	cout << "\n\t2. Login";
	cout << "\n\t3. Back";
	cout << "\n\t[Enter your choice - 1, 2, 3 or 4]";
	cout << "\n\tChoose: ";
	cin >> n;
	switch (n)
	{
	case 1:
		//read_last_line();
		disp_driver_regist();
		cout << endl;
		driver_eligibility(driver, driverFromFile);
		break;
	case 2:
		driver_login(driverFromFile);
		break;
	case 3:
		//main();
		break;
	}
}


void driver_eligibility(vector<Drivers>& driver, vector<Drivers>& driverFromFile)
{
	disp_h3_lines("Eligibility Check");
	char full, n;
	int car_age, driver_age;
	cout << "\n\t[Enter Y/N]";
	cout << "\n\t Do you have full NZ drive license? " << "\t";
	cin >> full;

	cout << "\n\tHave you had your full drivers' license for a minimum of 2 years? " << "\t";
	cin >> n;

	cout << "\n\tHow old is your taxi vehicle?" << "\t";
	cin >> car_age;

	cout << "\n\tPlease enter your age: " << "\t";
	cin >> driver_age;

	if (full == 'Y' && n == 'Y' && car_age <= 10 && driver_age >= 21)
	{
		driver_registration(driver, driverFromFile);
	}
	else
	{
		cout << "\nSorry, you are not eligible to be our driver.";
		system("pause");
		//main();
	}
}

void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile)
{
	disp_driver_regist();
	cout << endl;
	disp_h2_lines("Be Your Own Boss - Sign up to be a Zebra Driver today!");
	input_drivers(driver);
	//**********************
	//cout << driver[0].fname << endl;//debugging purposes 
	//**********************
	writeToFile(driver);
	driver_login(driverFromFile);

}


vector <Drivers> input_drivers(vector<Drivers>& driver)
{
	Drivers d;
	cout << "\n\tPlease, enter your: ";
	cout << "\n\tFirst Name: ";
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

	cout << "\n\tPlease, enter your: ";

	cout << "\n\tDrivers' License #	[Format:AB123456]: ";
	cin >> d.lice_num;
	cout << "\n\tDate of Expiry Format:DD / MM / YY]: ";
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

	d.d_idAlph += "D" + d.fname.substr(0, 1);
	d.d_idAlph += d.sname.substr(0, 2);
	d.d_idNum = 1001 + count_entries_drive();

	driver.push_back(d);
	return (driver);

}

int count_entries_drive()
{
	int total_entries = 0;
	string s;
	fstream driverFile("driverFile_pid.csv", ios::in);
	if (!driverFile)
	{
		total_entries = 0;
	}
	else
	{
		while (!driverFile.eof())
		{
			getline(driverFile, s);
			total_entries++;
		}
		total_entries = total_entries - 1;

	}
	//cout << "\nNumber of lines in file is " << total_entries; //debugging

	return (total_entries);
}


void output_drivers(vector<Drivers>& driver)
{
	for (int i = 0; i < driver.size(); i++)
	{
		cout << "\n\tHello, " << driver[i].pref_name << " please, check your information and confirm" << endl;
		cout << " \n\t " << driver[i].fname << "\t" << driver[i].sname;
		cout << " \n\t " << driver[i].phone_num << "\t" << driver[i].mail << "      will be used as your username";
	}
}




void writeToFile(vector<Drivers>& driver)
{
	//cout << driver[0].fname;//debugging purposes
	//cout << "\nFisrt debug";
	fstream driverFile("driverFile_pid.csv", ios::app);
	//cout <<"/nsize of driver"<< driver.size();
	for (int i = 0; i < driver.size(); i++)
	{
		//cout << "\nsecond DEBUG";	
		driverFile << driver[i].d_idAlph << "," << driver[i].d_idNum << "," << driver[i].fname << "," << driver[i].sname << "," << driver[i].pref_name << "," << driver[i].phone_num << "," << driver[i].mail << "," << driver[i].password << "," << driver[i].gender << "," << driver[i].birth << "," << driver[i].nationality << "," << driver[i].lice_num << "," << driver[i].doex << "," << driver[i].exp << "," << driver[i].veh_regist << "," << driver[i].veh_age << "," << driver[i].veh_model << "," << driver[i].wof_exp << "," << driver[i].bank_acc << "," << driver[i].bank_name << endl;
	}
	driverFile.close();
	//cout <<"/nsize of driver"<< driver.size();
}




vector<Drivers> driver_login(vector<Drivers>& driverFromFile)
{
	fstream driverFile("driverFile_pid.csv", ios::in);
	string login, password;
	cout << "\n\tEnter your: ";
	cout << "\n\tUsername: ";
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

			driver_account_main(driverFromFile, login);

		}

	}
	driverFile.close();
	//driverFromFile = readFromFile();
	return(driverFromFile);
}

void driver_account_main(vector<Drivers>& driverFromFile, string check_username)
{
	vector <Rider_pid> rider;
	Rider_pid r;
	int n;
	cout << "\n\tKia ora, we are all good to go!";
	cout << "\n\tPlease choose from the following options: ";
	cout << "\n\t1. Account settings";
	cout << "\n\t2. Pick a ride";
	cout << "\n\t3. Reset your password";
	cin >> n;
	switch (n)
	{
	case 1:
		account_settings(driverFromFile, check_username);
		break;
	case 2:
		job_screen(rider, check_username);

		break;
	case 3:
		//reset_passsword();
		break;

	}
}


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
		stringstream ss(user);
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


void account_settings(vector<Drivers> driverFromFile, string check_username)
{

	char n;
	fstream driverFile("driverFile_pid.csv", ios::in);
	driverFromFile = readFromFile();
	cout << "\n\tYour account details: ";
	cout << "\n\tPlease enter your username: ";
	cin >> check_username;
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		if (check_username == driverFromFile[i].mail)
		{
			cout << "\n\tHello, " << driverFromFile[i].pref_name << endl;
			/*cout <<"\n\t" <<"First name:			"<<driverFromFile[i].fname;
			cout << "\n\t" << "Second name:			" << driverFromFile[i].sname;
			cout << "\n\t" << "Phone number:			" << driverFromFile[i].phone_num;
			cout << "\n\t" << "Gender:				" << driverFromFile[i].gender;
			cout << "\n\t" << "Date of birth:			" << driverFromFile[i].birth;
			cout << "\n\t" << "Nationality:			" << driverFromFile[i].nationality;*/
			cout << "\n\t" << "1. Driver's License #:		" << driverFromFile[i].lice_num;
			cout << "\n\t" << "2. Date of Expiry:			" << driverFromFile[i].doex;
			cout << "\n\t" << "3. Driving experience:		" << driverFromFile[i].exp;
			cout << "\n\t" << "4. Vehical Registration Number:	" << driverFromFile[i].veh_regist;
			cout << "\n\t" << "5. Vehical Age:			" << driverFromFile[i].veh_age;
			cout << "\n\t" << "6. Vehical Model:			" << driverFromFile[i].veh_model;
			cout << "\n\t" << "7. WOF Expiry date:		" << driverFromFile[i].wof_exp;
			cout << "\n\t" << "8. Bank Account Number:		" << driverFromFile[i].bank_acc;
			cout << "\n\t" << "9. Bank Name:			" << driverFromFile[i].bank_name;

			break;
		}
	}
	driverFile.close();
	cout << "\n\tSelect [e] to edit your deatils.";
	cout << "\n\tSelect [b] to go back";
	cout << "\n\tChoose: ";
	cin >> n;
	if (n == 'e')
	{

		update_acc_details(driverFromFile, check_username);

	}
}



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
	cout << "\n\tPlease, choose what would you like to change: ";
	cin >> choice;
	fstream driverFile("driverFile_pid.csv", ios::out);
	switch (choice)
	{
	case 1:
		cin.ignore();
		cout << "\nEnter the new Drivers' License #	[Format:AB123456]: ";
		getline(cin, new_lice_num);

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
		cout << "\nEnter the new date of expiry: ";
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
		cout << "\nEnter driving experience: ";
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
		cout << "\nEnter the new vehical registration number: ";
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

		cout << "\nEnter the new vehical age: ";
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
		cout << "\nEnter the new vehical model: ";
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
		cout << "\nEnter new WOF Expiry date: ";
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
		cout << "\nEnter the new bank account: ";
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
		cout << "\nEnter the new bank name: ";
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
	cout << "\n\tThe information updated! Would you like to update anything else?";

	for (int i = 0; i < 3; i++)
	{
		cout << "\n\tChoose[select 'Y' for yes, 'N' for no]: ";
		cin >> a;
		if (a == 'Y')
		{
			update_acc_details(driverFromFile, check_username);
			break;
		}
		else if (a == 'N')
		{
			driver_account_main(driverFromFile, check_username);
			break;
		}
		else
		{
			cout << "\n\tPlease enter only 'Y' or 'N': ";
		}
	}
	driver_account_main(driverFromFile, check_username);

	return (driverFromFile);
}





void job_screen(vector <Rider_pid>& rider, string d_username)
{
	vector<Drivers> driverFromFile;
	vector <Trips> trip;
	Trips temp_struct;

	fstream riderFile("riderpid.csv", ios::in);
	rider = rider_retrieve_info();

	//cout << "debug" << rand_rider;

	cout << "\n\t\tKia Ora! Ready to work?";
	cout << "\n\t\tThere's the available jobs waiting for you to pick up:  ";
	cout << endl;
	cout << "\n\t\t" << rider[1].r_pname;
	cout << "\n\tDistance from you	:  2.2 kms";
	cout << endl;
	cout << "\n\t" << rider[2].r_pname;
	cout << "\n\tDistance from you	:  3.1 kms";
	cout << endl;
	//cout << "\n\t" << rider[i].r_pname;
	//cout << "\n\tDistance from you	:  5.2 kms";
	//cout << endl;
	//cout << "\n\t" << rider[i].r_pname;
	//cout << "\n\tDistance from you	:  3.2 kms";


	riderFile.close();

	cout << "\n\tEnter the name of the rider to pick up a job: ";
	string check_name;
	cin >> check_name;



	//input_trip_data(rider, driverFromFile, trip, check_name);
	//write_to_trip_transactions(trip);

	temp_struct = input_trip_data(rider, driverFromFile, trip, check_name, d_username);
	//cout << temp_struct.driver_id;
	write_to_trip_transactions(temp_struct);
	//string trip_id_check = t.trip_id;
	//trip.push_back(t);
	//confirm_job_screen(rider, trip, check_name, trip_id_check);

	confirm_job_screen(rider, temp_struct, check_name);

}


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

int count_entries_trips_chrisTest()
{
	int total_entries = 0;
	string s;
	fstream tripFile("trip_transactions_chris.csv", ios::in);
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
	cout << "\nNumber of lines in file is " << total_entries; //debugging

	return (total_entries);
}

struct Trips input_trip_data(vector <Rider_pid>& rider, vector<Drivers>& driverFromFile, vector <Trips>& trip, string check_name, string d_username)
{
	Trips t;
	//time_t now = time(0);// current date/time based on current system
	//char* dt = ctime_s(&now); //convert now to string form
	//char dt = 0;


	srand(time(NULL)); //initialize the random seed
	int randloc1 = rand() % 6;
	int randloc2 = rand() % 6;
	cout << randloc2 << randloc1;
	driverFromFile = readFromFile();
	rider = rider_retrieve_info();
	for (int i = 0; i < rider.size(); i++)
	{
		string id_num_string_r = to_string(rider[i].r_idnum);
		if (check_name == rider[i].r_pname)
		{
			t.rider_id = rider[i].r_idalpha + id_num_string_r;
		}

	}
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		string id_num_string_d = to_string(driverFromFile[i].d_idNum);
		if (d_username == driverFromFile[i].mail)
		{
			t.driver_id = driverFromFile[i].d_idAlph + id_num_string_d;
		}

	}
	string count_entries_string = to_string(count_entries_trips() + 1);
	t.trip_id = "TR" + count_entries_string;// revise
	t.start_loc = random_locations(randloc1);
	t.end_loc = random_locations(randloc2);
	t.trip_cost = main_dist_calc(t.start_loc, t.end_loc);
	t.trip_date = currentDateTime();

	//trip.push_back(t);



	return (t);
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



void confirm_job_screen(vector <Rider_pid>& rider, Trips trip_struct, string check_name)
{
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
			cout << "\n\n\n\tYour are picking up:	 " << rider[i].r_pname;
		}
	}
	riderFile.close();
	cout << "\n\tTrip number is:	" << trip_struct.trip_id << "\t" << trip_struct.trip_date;
	cout << "\n\tFrom:	" << trip_struct.start_loc;
	cout << "\n\tDestination:		" << trip_struct.end_loc;
	/*trip.push_back(t);*/

	//tripFile.close();

	string check_username;
	cout << "\n\tPress any button when you've picked them up";
	cout << "\n\t[CANCEL] to cancel this booking";
	cout << "\n\tChoose: ";
	string choice;
	cin >> choice;
	if (choice == "CANCEL")
	{

		cout << "\n\tEnter you username to continue	: ";
		cin >> check_username;
		cout << "\n\tWARNING! You are about to cancel booking. Would you like to continue?";
		cout << "\n\t[Y] for yes. [N] for no: ";
		char can_choice;
		cin >> can_choice;
		if (can_choice == 'Y')
		{
			driver_account_main(driver, check_username);
		}
	}
	else
	{
		cout << "\n\tAwesome! Press ant button when you've dropped them off";
		cout << "\n\tEnter you username to to access billing info	: ";
		cin >> check_username;
		cout << "\n\tNice! You have earned " << trip_struct.trip_cost;
		system("pause");
		driver_account_main(driver, check_username);
	}
	//return (trip);

}



