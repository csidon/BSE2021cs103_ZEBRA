#include <iostream>
#include <string>
#include <fstream> // to handle file operations
#include <sstream> // to handle string stream convertion
#include "pswd_email_validation.h"
#include <vector> // to handle unlimited structure array
using namespace std;


//STRUCTURE

struct Drivers
{
	string fname;
	string sname;
	string pref_name;
	string phone_num;
	string address;
	string mail;
	string password;
	Drivers(string fn = "",string sn ="", string pn = "", string phn = "", string ad = "", string m = "", string pw = "")
	{
		fname = fn;
		sname = sn;
		pref_name = pn;
		phone_num = phn;
		address = ad;
		mail = m;
		password = pw;
	}
};

//Function Prototype
void disp_main_logo();
void disp_h3_lines(string title);
void disp_h2_lines(string title);
void disp_dash_line();
void disp_star_line();
void driver_main();
void driver_eligibility();
//void driver_login();
void driver_registration();
vector <Drivers> input_drivers(vector<Drivers>& driver);//returns a Marker vector
void writeToFile(vector<Drivers>& driver);//returns nothing
vector <Drivers> readFromFile();//returns a Marker vector
//vector<Drivers> searchAndUpdate(vector < Drivers > markerFromFile);


int main()
{
	Drivers;
	int main_input;
	//####### Main Page ########
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
	cout << "\t[Enter your choice - 1, 2, 3, or 4]\n\tChoose: \n";
	cin >> main_input;
	if (main_input == 1)
	{
		driver_main();
	}

	system("Color 9");
}

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

void driver_main()
{

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
		driver_eligibility();
		break;
	case 2:
		//driver_login();
		break;
	case 3:
		main();
		break;
	}
}


void driver_eligibility()
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
		driver_registration();
	}
	else
	{
		cout << "\nSorry, you are not eligible to be our driver.";
		system("pause");
		main();
	}
}

void driver_registration()
{
	vector <Drivers> driver;
	vector <Drivers> driverFromFile;
	input_drivers(driver);
	writeToFile(driver);
	driverFromFile = readFromFile();

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
	return (driver);
}

void writeToFile(vector<Drivers>& driver)
{
	cout << "\nFisrt debug";
	fstream driverFile("driverFile.csv", ios::app);
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
	cout << "\n\tHello " << d.pref_name << ", please check your registration details: ";
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
		d.phone_num = user;
		getline(linestream, user, ',');
		d.mail = user;
		tempDriver.push_back(d);
	}
	driverFile.close();
	return(tempDriver);
}