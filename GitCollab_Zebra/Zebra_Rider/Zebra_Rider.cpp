#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;


struct Rider_pid 
{
	string r_fname, r_pname, r_lname, r_address, r_emailusrname, r_pswd;
	int r_contact;

	//constructor
	Rider_pid(string rfn = "", string rpn = "", string rln = "", string rad = "", string reu = "", string rpw = "", int rcall = 0)
	{
		r_fname = rfn;
		r_lname = rln;
		r_pname = rpn;
		r_address = rad;
		r_emailusrname = reu;
		r_pswd = rpw;
		r_contact = rcall;
	}
};

//###############################################
//		Function Prototype
//###############################################
//Making pretty
void disp_main_logo();
void disp_h3_lines(string title);
void disp_h2_lines(string title);
void disp_dash_line();
void disp_star_line();
void disp_rider_logo();
//Rider Main
void rider_main(vector <Rider_pid>& rinput, vector <Rider_pid>& rretrieve);
vector <Rider_pid> rider_register(vector <Rider_pid>& rinput);
void writeRiderToFile(vector <Rider_pid>& write_r);

//Validation Functions
bool is_small_char(char c);
bool is_big_char(char C);
bool is_a_digit(const char d);
bool has_AT(char at);
bool has_dot(char dot);
int email_valid(string remail);
int pswd_valid(string rpswd);

//###############################################
//		Main Function
//###############################################

int main()
{
	int main_input;
	
	//Initialising vector class for structure Rider_pid so that structure is unlimited
	vector <Rider_pid> rider_input_info;
	vector <Rider_pid> rider_retrieve_info;

	//####### Main Page ########[Chris]
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
	if (main_input == 2)
	{
		//####### Goes To Main Rider Page #######[Chris]
		system("Color 9"); //anything rider-related will be displayed in this color
		rider_main(rider_input_info, rider_retrieve_info);
		writeRiderToFile(rider_input_info);
		//email_valid(rider_input_info);
	}
	
	
	
	

}

//###############################################
//		DISPLAY/DECORATIVE FUNCTIONS
//###############################################

//This function displays the Main Page's ZEBRA logo
void disp_main_logo()
{
	cout << "\n\n\t\t$$$$$$$$\\          $$\\                          ";
	cout <<   "\n\t\t\\____$$  |         $$ |                         ";
	cout <<   "\n\t\t     $$  /$$$$$$\\  $$$$$$$\\   $$$$$$\\  $$$$$$\\  ";
	cout <<   "\n\t\t   $$  / $$  __$$\\ $$  __$$\\ $$  __$$\\ \\____$$\\ ";
	cout <<   "\n\t\t  $$  /  $$$$$$$$ |$$ |  $$ |$$ |  \\__|$$$$$$$ |";
	cout <<   "\n\t\t $$  /   $$   ____|$$ |  $$ |$$ |     $$  __$$ |";
	cout <<   "\n\t\t $$$$$$$$\\$$$$$$$\\ $$$$$$$  |$$ |     \\$$$$$$$ |";
	cout <<   "\n\t\t\\\________|\\_______|\\_______/ \\__|      \\_______|\n";
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


//This function displays the Rider pages' logo
void disp_rider_logo()
{
	cout << "\n\t  _____    _                 ____  _     _            ";
	cout <<   "\n\t |__  /___| |__  _ __ __ _  |  _ \\(_) __| | ___ _ __ ";
	cout << "\n\t   / // _ \\ '_ \\| '__/ _` | | |_) | |/ _` |/ _ \\ '__|";
	cout << "\n\t  / /|  __/ |_) | | | (_| | |  _ <| | (_| |  __/ |   ";
	cout << "\n\t /____\\___|_.__/|_|  \\__,_| |_| \\_\\_|\\__,_|\\___|_|   \n";
}

//###############################################
//		RIDER FUNCTIONS
//###############################################

void rider_main(vector <Rider_pid>& rinput, vector <Rider_pid>& rretrieve)
{
	int rider_main_input;
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
	if (rider_main_input == 2)
	{
		system("cls");
		rider_register(rinput);
	}
}


//This section takes rider input data from user
vector <Rider_pid> rider_register(vector <Rider_pid>& rinput)
{
	int rreg_confirmation;

	system("cls");
	disp_rider_logo();
	disp_h2_lines("Sign Up to Ride with Zebra!");
	disp_h3_lines("Enter your: ");

change_riderpid:
	Rider_pid ri;
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
	if (email_valid(ri.r_emailusrname) == 0)
	{
		cout << "\n\t!!Please enter a valid email address!!";
		goto valid_email;
	}
valid_pass:
	cout << "\n\tPassword";
	cout << "\n\t[Passwords must be";
	cout << "\n\tlonger than 8 chars,";
	cout << "\n\tcontain both numbers &";
	cout << "\n\tbig and small letters\t:  ";
	getline(cin, ri.r_pswd);
	if (pswd_valid(ri.r_pswd) == 0)
	{
		goto valid_pass;
	}

	cout << "\n";

	disp_dash_line();
	cout << "\tHello " << ri.r_pname << ", please check your details:";
	disp_dash_line();
	cout << "\t" << ri.r_fname << " " << ri.r_lname << "\n\t";
	cout << ri.r_contact << "\n\t";
	cout << ri.r_address << "\t[Note: This will be your default pickup address]\n\t";
	cout << ri.r_emailusrname << "\t\t[Reminder: This will be your username]\n\t";
	disp_star_line();
	cout << "\n\tIs your information correct?\t:  ";
	cout << "\n\tSelect [1] to confirm and [2] to edit:\n\t";
	cin >> rreg_confirmation;
	if (rreg_confirmation == 2)
	{
		goto change_riderpid;
	}

	rinput.push_back(ri);

	return rinput;
}

//This function stores details to the riderpid.csv file
void writeRiderToFile(vector <Rider_pid>& write_r)
{
	fstream riderpid_file("riderpid.csv", ios::app);
	for (int i = 0; i < write_r.size(); i++)
	{
		riderpid_file << write_r[i].r_fname << "," << write_r[i].r_lname << "," << write_r[i].r_pname << ",";
		riderpid_file << write_r[i].r_contact << "," << write_r[i].r_address << "," << write_r[i].r_emailusrname << ",";
		riderpid_file << write_r[i].r_pswd << endl;
	}
	
	riderpid_file.close();
}


//###############################################
//		VALIDATION FUNCTIONS
//###############################################
// This function checks that there is a lowercase letter in string
bool is_small_char(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool is_big_char(char C)
{
	return (C >= 'A' && C <= 'Z');
}

bool is_a_digit(const char d)
{
	return (d >= '0' && d <= '9');
}

bool has_AT(char at)
{
	return (at == '@');
}

bool has_dot(char dot)
{
	return (dot == '.');
}

// 
//This function validates that the user's input includes an @ and at least one "." -- EMAIL VALIDATION
//int email_valid(vector <Rider_pid>& rinput )
int email_valid(string remail)
{
	int AT_num = 0, dot_num = 0;
	//remail.length() is the number of chars in the email address provided by user
	//## This section pushes each char in remail to a vector called remail_arr
	vector<char> remail_arr; //defining a vector called remail_arr
	for (int i = 0; i < remail.length(); i++)
	{
		remail_arr.push_back(remail[i]);
		cout << remail[i] << "\t"; //for debugging purposes

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
	if (AT_num == 1 && (dot_num >= 1 && dot_num <= 3)) //allow 3 dots for domains like .co.nz
	{
		cout << "EMAIL IS VALID!!";
		return 1;
	}
	else
	{
		cout << "EMAIL FAIL!!";
		return 0;
	}
}


//This function validates that the user's input has min 8 chars, 
//contains a number and Large and small letters -- PASSWORD VALIDATION
int pswd_valid(string rpswd)
{
	int smchar = 0, bchar = 0, num = 0;
	//remail.length() is the number of chars in the email address provided by user
	//## This section pushes each char in remail to a vector called remail_arr
	vector<char> rpswd_arr; //defining a vector called remail_arr
	if (rpswd.length() < 8)
	{
		cout << "\nPlease enter a password with more than 8 characters\n";
		return 0;
	}
	for (int i = 0; i < rpswd.length(); i++)
	{
		rpswd_arr.push_back(rpswd[i]);
		cout << rpswd[i] << "\t"; //for debugging purposes
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
		cout << "\nPlease use at least one small letter\n";
		return 0;
	}
	else if (bchar == 0)
	{
		cout << "\nPlease use at least one capital letter\n";
		return 0;
	}
	else if (num == 0)
	{
		cout << "\nPlease use at least one number\n";
		return 0;
	}
	else
	{
		return 1;
	}
}



//@chris' to do: debug email and password validation and provide clear instructions as to why fail!!