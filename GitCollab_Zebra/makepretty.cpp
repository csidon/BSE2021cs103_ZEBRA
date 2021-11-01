#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "makepretty.h"

using namespace std;

//Coder: Chris C
//File: makepretty.cpp
//Edited on: 2 Nov 2021
//Last Edited Date:  2 Nov 2021
//Purpose: This file contains the decorative functions for the Zebra program



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


//This function displays the Rider pages' logo
void disp_rider_logo()
{
	cout << "\n\t  _____    _                 ____  _     _            ";
	cout << "\n\t |__  /___| |__  _ __ __ _  |  _ \\(_) __| | ___ _ __ ";
	cout << "\n\t   / // _ \\ '_ \\| '__/ _` | | |_) | |/ _` |/ _ \\ '__|";
	cout << "\n\t  / /|  __/ |_) | | | (_| | |  _ <| | (_| |  __/ |   ";
	cout << "\n\t /____\\___|_.__/|_|  \\__,_| |_| \\_\\_|\\__,_|\\___|_|   \n";
}