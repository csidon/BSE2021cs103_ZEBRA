#include <iostream>
#include <stdlib.h>

using namespace std;



//Function Prototype
void disp_main_logo();
void disp_h3_lines(string title);
void disp_h2_lines(string title);
void disp_dash_line();
void disp_star_line();


int main()
{
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
	if (main_input == 2)
	{
		//rider_main();
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
