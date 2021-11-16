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
		//readFromFile();
		disp_driver_regist();
		cout << endl;
		driver_eligibility(driver, driverFromFile, trip);
		break;
	case 2:
		driver_login(driverFromFile, trip);
		break;
	case 3:
		//main();
		break;
	}
}


void driver_eligibility(vector<Drivers>& driver, vector<Drivers>& driverFromFile, vector <Trips> trip)
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
		driver_registration(driver, driverFromFile, trip);
	}
	else
	{
		cout << "\nSorry, you are not eligible to be our driver.";
		system("pause");
		//main();
	}
}

void driver_registration(vector<Drivers>& driver, vector<Drivers>& driverFromFile, vector <Trips> trip)
{
	disp_driver_regist();
	cout << endl;
	disp_h2_lines("Be Your Own Boss - Sign up to be a Zebra Driver today!");
	input_drivers(driver);
	//**********************
	//cout << driver[0].fname << endl;//debugging purposes 
	//**********************
	writeToFile(driver);
	driver_login(driverFromFile, trip);

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
	
	output_drivers(driver);

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
		driverFile << driver[i].d_idAlph<<","<<driver[i] .d_idNum<< "," << driver[i].fname << "," << driver[i].sname << "," << driver[i].pref_name << "," << driver[i].phone_num << "," << driver[i].mail << "," << driver[i].password << "," << driver[i].gender << "," << driver[i].birth << "," << driver[i].nationality << "," << driver[i].lice_num << "," << driver[i].doex << "," << driver[i].exp << "," << driver[i].veh_regist << "," << driver[i].veh_age << "," << driver[i].veh_model << "," << driver[i].wof_exp << "," << driver[i].bank_acc << "," << driver[i].bank_name << endl;
	}
	driverFile.close();
	//cout <<"/nsize of driver"<< driver.size();
}




vector<Drivers> driver_login(vector<Drivers>& driverFromFile, vector <Trips> trip)
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
				
				driver_account_main(driverFromFile, login, trip);
				
			}

		}
	driverFile.close();
	//driverFromFile = readFromFile();
	return(driverFromFile);
}

void driver_account_main(vector<Drivers>& driverFromFile, string check_username, vector <Trips> trip)
{
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
		account_settings(driverFromFile, check_username, trip);
		break;
	case 2:
		job_screen(driverFromFile, trip);
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


void account_settings(vector<Drivers>& driverFromFile, string check_username, vector <Trips> trip)
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
			cout << "\n\tHello, " << driverFromFile[i].pref_name<<endl;
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

		update_acc_details(driverFromFile, check_username, trip);

	}
}



vector<Drivers> update_acc_details(vector < Drivers > driverFromFile, string check_username, vector <Trips> trip)
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

	for (int i=0; i<3; i++)
	{
		cout << "\n\tChoose[select 'Y' for yes, 'N' for no]: ";
		cin >> a;
		if (a == 'Y')
		{
			update_acc_details(driverFromFile, check_username, trip);
			break;
		}
		else if (a == 'N')
		{
			driver_account_main(driverFromFile, check_username, trip);
			break;
		}
		else
		{
			cout << "\n\tPlease enter only 'Y' or 'N': ";
		}
	}
	driver_account_main(driverFromFile, check_username, trip);

	return (driverFromFile);
}
	


void job_screen(vector <Drivers> driver_rides, vector <Trips> trip)
{
	//create_driver_trips(driver_rides);
	string check_id;
	cout << "\n\tKia Ora! Ready to work?";
	cout << "\n\tThere's the available jobs waiting for you to pick up:  ";
	cout << endl;
	cout << "\n\tAnakin Skywalker  Trip ID: TR1001";
	cout << "\n\tDistance from you	:  2.2 kms";
	cout << endl;
	cout << "\n\tLuke Skywalker  Trip ID: TR1002";
	cout << "\n\tDistance from you	:  3.1 kms";
	cout << endl;
	cout << "\n\tYoda  Trip ID: TR1003";
	cout << "\n\tDistance from you	:  5.2 kms";
	cout << endl;
	cout << "\n\tBaby Yoda  Trip ID: TR1004";
	cout << "\n\tDistance from you	:  3.2 kms";
	cout << endl;
	cout << "\n\tTom Kruz  Trip ID:  TR1005";
	cout << "\n\tDistance from you	:  4.7 kms";
	cout << endl;
	cout << "\n\tJhonny Depp  Trip ID: TR1006";
	cout << "\n\tDistance from you	:  5.3 kms";
	cout << "\n\tEnter trip ID to pick up a job: ";
	cin >> check_id;
	confirm_job_screen(trip, check_id);

}

//vector<Trips> input_trip_data(vector<Trips> trip, vector<Drivers> driverFromFile)
//{
//	Trips t;
//	Drivers d;
//	t.trip_id = "TR" + 1001 + count_entries_trip();
//	t.driver_id = d.d_idNum;
//
//}
//vector<Trips> write_to_trip_transactions(vector<Trips> trip, vector <Drivers> driverFromFile, vector < Rider_pid>)
//{
//	fstream trip_file("trip_transactions.csv", ios::app);
//
//}


//vector <Drivers> read_driver_trips()
//{
//
//	fstream driverRidesFile("driver_rides.csv", ios::in);
//	vector<Drivers> tempRides;
//
//	Drivers d;
//	string line;
//
//	while (getline(driverRidesFile, line))
//	{
//		//cout << line << endl;
//		istringstream linestream(line);
//		string user;
//		getline(linestream, user, ',');
//		d.d_idAlph = user;
//		getline(linestream, user, ',');
//		stringstream ss(user);
//		ss >> d.d_idNum;
//		getline(linestream, user, ',');
//		d.trip_id_d = user;
//		tempRides.push_back(d);
//	}
//
//	driverRidesFile.close();
//	return(tempRides);
//}
//
//
//vector <Trips> read_trips()
//{
//	fstream tripsFile("trip.csv", ios::in);
//	vector <Trips> tempTrips;
//	Trips t;
//	string line;
//	while (getline(tripsFile, line))
//	{
//		istringstream linestream(line);
//		string trip;
//		getline(linestream, trip, ',');
//		t.trip_id = trip;
//		getline(linestream, trip, ',');
//		t.start_loc = trip;
//		getline(linestream, trip, ',');
//		t.end_loc = trip;
//		getline(linestream, trip, ',');
//		stringstream ss(trip);
//		ss >> t.trip_cost;
//		getline(linestream, trip, ',');
//		t.trip_date = trip;
//		getline(linestream, trip, ',');
//		t.trip_time = trip;
//		tempTrips.push_back(t);
//	}
//	tripsFile.close();
//	return (tempTrips);
//
//}
//
//int count_entries_trip()
//{
//	int total_entries = 0;
//	string s;
//	fstream tripFile("driver_rides.csv", ios::in);
//	if (!tripFile)
//	{
//		total_entries = 0;
//	}
//	else
//	{
//		while (!tripFile.eof())
//		{
//			getline(tripFile, s);
//			total_entries++;
//		}
//		total_entries = total_entries - 1;
//
//	}
//	//cout << "\nNumber of lines in file is " << total_entries; //debugging
//
//	return (total_entries);
//}
//
//vector <Trips> confirm_job_screen(vector<Trips> trip, string check_trip_id)
//{
//	cout << "\n\tDEBUG";
//	fstream tripFiles("trip.csv", ios::in);
//	trip = read_trips();
//	for (int i = 0; i < trip.size(); i++)
//	{
//		if (check_trip_id == trip[i].trip_id)
//		{
//			cout << "\n\tTrip Number is: " << trip[i].trip_id;
//			cout << "\t" << trip[i].trip_date << ", " << trip[i].trip_time << endl;
//			if (trip[i].trip_id == "TR1001")
//			{
//				cout << "\n\tYou are picking up Anakin Skywalker";
//			}
//			else if (trip[i].trip_id == "TR1002")
//			{
//				cout << "\n\tYou are picking up Luke Skywalker";
//			}
//			else if (trip[i].trip_id == "TR1003")
//			{
//				cout << "\n\tYou are picking up Yoda";
//			}
//			else if (trip[i].trip_id == "TR1004")
//			{
//				cout << "\n\tYou are picking up Baby Yoda";
//			}
//			else if (trip[i].trip_id == "TR1005")
//			{
//				cout << "\n\tYou are picking up Tom Kruz";
//			}
//			else if (trip[i].trip_id == "TR1006")
//			{
//				cout << "\n\tYou are picking up Johnny Depp";
//
//			}
//			cout << "\n\n\tFrom: " << trip[i].start_loc;
//			cout << "\n\tDestination: " << trip[i].end_loc;
//		}
//	}
//	tripFiles.close();
//	return (trip);
//}
