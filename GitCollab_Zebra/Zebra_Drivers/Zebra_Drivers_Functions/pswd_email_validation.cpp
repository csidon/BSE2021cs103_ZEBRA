#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "pswd_email_validation.h"

using namespace std;

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
		//cout << remail[0];
		//cout << (!(is_a_digit(remail[0])));
		//cout << (!(is_small_char(remail[0])));
		//cout << !(is_big_char(remail[0]));
		if (is_a_digit(remail[0]) || is_small_char(remail[0]) || is_big_char(remail[0]))
		{
			remail_arr.push_back(remail[i]);
			//cout << remail[i] << "\t"; //for debugging purposes

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
			cout << "\nPlease enter a valid email address -- why is this wrong";
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
		cout << "\nPlease enter a valid email address";
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