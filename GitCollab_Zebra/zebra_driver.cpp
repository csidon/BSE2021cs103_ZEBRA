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

using namespace std;

//Coder: Anastasiia Karpova
//File: zebra_driver.cpp
//Edited on: 4 Nov 2021
//Last Edited Date:  4 Nov 2021
//Purpose: This file contains the functions for the Zebra Driver

void driver_main()
{
	vector <Drivers> driver;
	vector <Drivers> driverFromFile;
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
		disp_driver_regist();
		cout << endl;
		driver_eligibility(driver, driverFromFile);
		break;
	case 2:
		//driver_login();
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
	output_drivers(driver);

	//**********************
	//cout << driver[0].fname << endl;//debugging purposes 
	//**********************

	writeToFile(driver);

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
	cout << "\n\tE-mail adress";
	cout << "\n\t[Note: This will also be  Your username]: ";
	cin >> d.mail;
	email_valid(d.mail);
	cout << "\n\tPassword: ";
	cin >> d.password;
	pswd_valid(d.password);
	driver.push_back(d);
	return (driver);
}

void output_drivers(vector<Drivers>& driver)
{
	for (int i = 0; i < driver.size(); i++)
	{
		cout << "\n\tHello, " << driver[i].pref_name << " please, check your information and confirm" << endl;
		cout << " \n\t " << driver[i].fname << "\t" << driver[i].sname;
		cout << " \n\t " << driver[i].phone_num << "\t" << driver[i].mail << " will be used as your user name";
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
		driverFile << driver[i].fname << "," << driver[i].sname << "," << driver[i].pref_name << "," << driver[i].phone_num << "," << driver[i].mail << "," << driver[i].password << endl;
	}
	driverFile.close();

}

//vector <Drivers> readFromFile()
//{
//	fstream driverFile("driverFile_pid.csv", ios::in);
//	vector<Drivers> tempDriver;
//
//	Drivers d;
//	string line;
//	
//	while (getline(driverFile, line))
//	{
//		cout << line << endl;
//		istringstream linestream(line);
//		string user;
//		getline(linestream, user, ',');
//		d.fname = user;
//		getline(linestream, user, ',');
//		d.sname = user;
//		getline(linestream, user, ',');
//		d.pref_name = user;
//		getline(linestream, user, ',');
//		d.phone_num = user;
//		getline(linestream, user, ',');
//		d.mail = user;
//		getline(linestream, user, ',');
//		d.password = user;
//		tempDriver.push_back(d);
//	}
//
//	driverFile.close();
//	return(tempDriver);
//}


vector<Drivers> driver_login(vector<Drivers>& driverFromFile)
{
	fstream driverFile("driverFile_pid.csv", ios::out);
	string login, password;
	cout << "\n\tEnter your: ";
	cout << "\n\tUsername: ";
	cin >> login;
	cout << "\n\tPassword: ";
	cin >> password;
	for (int i = 0; i < driverFromFile.size(); i++)
	{
		while (true)
		{
			if (driverFromFile[i].mail == login && driverFromFile[i].password == password)
			{
				//driver_account();
			}
			else
			{
				cout << "\n\tForgot your password?";
			}
		}

	}
	return(driverFromFile);
}