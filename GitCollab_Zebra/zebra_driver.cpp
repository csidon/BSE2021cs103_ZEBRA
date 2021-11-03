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
	cout << "\n1. Register";
	cout << "\n2. Login";
	cout << "\n3. Back";
	cout << "\n[Enter your choice - 1, 2, 3 or 4]";
	cout << "\nChoose: ";
	cin >> n;
	switch (n)
	{
	case 1:
	//	driver_eligibility(driver, driverFromFile);
		driverFromFile = readFromFile();
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
	char full, n;
	int car_age, driver_age;
	cout << "[Enter Y/N]";
	cout << "\n Do you have full NZ drive license? " << "\t";
	cin >> full;

	cout << "\nHave you had your full drivers' license for a minimum of 2 years? " << "\t";
	cin >> n;

	cout << "\nHow old is your taxi vehicle?" << "\t";
	cin >> car_age;

	cout << "\nPlease enter your age: " << "\t";
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
	//input_drivers(driver);
	//cout << driver[0].fname << endl;
	//writeToFile(driver);
	driverFromFile = readFromFile();
	cout << driverFromFile[0].mail << driverFromFile[0].password<<endl;
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
	//email_valid(d.mail);
	cout << "\n\tPassword: ";
	cin >> d.password;
	//pswd_valid(d.password);
	driver.push_back(d);
	return (driver);
}

void writeToFile(vector<Drivers>& driver)
{
	//cout << driver[0].fname;
	cout << "\nFisrt debug";
	fstream driverFile("driverFile.csv", ios::app);
	cout <<"/nsize of driver"<< driver.size();
	for (int i = 0; i < driver.size(); i++)
	{
		cout << "\nsecond DEBUG";
		driverFile << driver[i].fname << "," << driver[i].sname << "," << driver[i].pref_name << "," << driver[i].phone_num << "," << driver[i].mail << "," << driver[i].password << endl;
	}
	driverFile.close();

}

vector <Drivers> readFromFile()
{
	fstream driverFile("driverFile.csv", ios::in);
	vector<Drivers> tempDriver;

	Drivers d;
	string line;
	
	while (getline(driverFile, line))
	{
		cout << line << endl;
		istringstream linestream(line);
		string user;
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
		tempDriver.push_back(d);
	}

	cout << "\n\tHello " <<tempDriver[0].pref_name << ", please check your registration details: ";

	driverFile.close();
	return(tempDriver);
}