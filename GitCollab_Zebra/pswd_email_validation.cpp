#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "pswd_email_validation.h"

using namespace std;

//Coder: Chris C
//File: pswd_email_validation.cpp
//Edited on: 2 Nov 2021
//Last Edited Date:  2 Nov 2021
//Purpose: This file contains the functions that we will use (and reuse) to validate passwords and emails


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

bool has_space(char space)
{
	return (space == ' ');
}

// This function validates that the card number is in number format #### #### #### ####
int creditcard_num_valid(string credit)
{
	int num = 0, space = 0;
	if (credit.length() == 19)
	{
		if ((!has_space(credit[4])) || (!has_space(credit[9])) || (!has_space(credit[14])))
		{
			cout << "\n\tPlease enter a valid credit card number in the format #### #### #### ####\n";
			return 0;
		}

		//DO/WHILE STATEMENT HERE

		string temppull = (credit.substr(0, 4));
		cout << "\ndebugging temppull 1  " << temppull;
		for (int i = 0; i < 4; i++)
		{
			if (!is_a_digit(temppull[i]))
			{
				cout << "\n\tPlease enter a valid credit card number in the format #### #### #### ####\n";
				return 0;
			}
		}

		string temppull2 = (credit.substr(5, 4));
		cout << "\ndebugging temppull 2  " << temppull2;
		for (int i = 0; i < 4; i++)
		{
			if (!is_a_digit(temppull2[i]))
			{
				cout << "\n\tPlease enter a valid credit card number in the format #### #### #### ####\n";
				return 0;
			}
		}
		string temppull3 = (credit.substr(10, 4));
		cout << "\ndebugging temppull 3  " << temppull3;
		for (int i = 0; i < 4; i++)
		{
			if (!is_a_digit(temppull3[i]))
			{
				cout << "\n\tPlease enter a valid credit card number in the format #### #### #### ####\n";
				return 0;
			}
		}
		string temppull4 = (credit.substr(15, 4));
		cout << "\ndebugging temppull 4  " << temppull4;
		for (int i = 0; i < 4; i++)
		{
			if (!is_a_digit(temppull4[i]))
			{
				cout << "\n\tPlease enter a valid credit card number in the format #### #### #### ####\n";
				return 0;
			}
		}
		return 42;
	}
	
	
}


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
		//cout << remail[0]; //debugging
		//cout << (!(is_a_digit(remail[0]))); //debugging
		//cout << (!(is_small_char(remail[0]))); //debugging
		//cout << !(is_big_char(remail[0])); //debugging
		if (is_a_digit(remail[0]) || is_small_char(remail[0]) || is_big_char(remail[0]))
		{
			remail_arr.push_back(remail[i]);
			//cout << remail[i] << "\t"; //uncomment for debugging purposes

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
		else
		{
			cout << "\nPlease enter a valid email address\n";
			return 0;
		}

	}
	if (AT_num == 1 && (dot_num >= 1 && dot_num <= 3)) //allow 3 dots for domains like .co.nz
	{
		//cout << "EMAIL IS VALID!!";  //for debugging purposes
		return 1;
	}
	else
	{
		cout << "\nPlease enter a valid email address\n";
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
		//cout << rpswd[i] << "\t"; //for debugging purposes
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
