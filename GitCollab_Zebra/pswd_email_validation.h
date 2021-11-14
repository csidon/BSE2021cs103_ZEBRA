#ifndef PSWD_EMAIL_VALIDATION_H
#define PSWD_EMAIL_VALIDATION_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//Coder: Chris C
//File: pswd_email_validation.cpp
//Edited on: 2 Nov 2021
//Last Edited Date:  2 Nov 2021
//Purpose: This file contains the functions that we will use (and reuse) to validate passwords and emails



//###############################################
//		Function Prototype
//###############################################
//Validation Functions
bool is_small_char(char c);
bool is_big_char(char C);
bool is_a_digit(const char d);
bool has_AT(char at);
bool has_dot(char dot);
int email_valid(string remail);
int pswd_valid(string rpswd);
bool has_space(char space);
int creditcard_num_valid(string credit);


#endif