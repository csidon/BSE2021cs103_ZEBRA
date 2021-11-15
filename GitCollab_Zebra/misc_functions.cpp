#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "zebra_rider.h"
#include "zebra_driver.h"
#include "makepretty.h"
#include "pswd_email_validation.h"
#include "misc_functions.h"

using namespace std;

////Coder: Chris C
////File: small_misc.cpp
////Edited on: 7 Nov 2021
////Last Edited Date:  7 Nov 2021
////Purpose: This file contains small misc functions that can be used globally in the program


string convert_string_to_upper(string &string_entry)
{
	char c;
	string converted_string;
	for (int i = 0; i < string_entry.length(); i++)
	{
		c = toupper(string_entry[i]);
		converted_string += c;
	}

	//cout << "\n This is the converted string " << converted_string;  //for debugging purposes
	return converted_string;
}


//void count_file_entries(string &filename)
//{
//	fstream file(filename, ios::in);
//
//
//	while (getline(file, line))
//}