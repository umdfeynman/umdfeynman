//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <locale>
#include "PMACS_String.h"
#include "PMACS_Logger.h"
#include "PMACS_Globals.h"

/*
TEST_CASE("IntZeroFillTest")
{
std::string required = "00000000000000009999";
REQUIRE(StringZeroFill(20, 9999) == required);
cout << required;
}*/
/*TEST_CASE("IntZeroFillTest", "Number length > field length")
{
// Validated "Error" displayed when in_number > field length
}*/


std::string StringIntZeroFill(int required_field_length, int in_number)
{
	std::stringstream test_num_length;
	test_num_length << in_number;
	test_num_length.seekg(0, ios::end);
	int size = test_num_length.tellg();

	if (size > required_field_length)
		Plog.logError("StringIntZeroFill", "Error - input string length exceeds required field length");

	std::stringstream output_string;
	output_string << std::setw(required_field_length) << std::setfill('0') << in_number;
	output_string.flush();
	return output_string.str();
}

std::string StringLongLongZeroFill(int required_field_length, long long in_number)
{
	std::stringstream test_num_length;
	test_num_length << in_number;
	test_num_length.seekg(0, ios::end);
	int size = test_num_length.tellg();

	if (size > required_field_length)
		Plog.logError("StringLongLongZeroFill", "Error - input string length exceeds required field length");

	std::stringstream output_string;
	output_string << std::setw(required_field_length) << std::setfill('0') << in_number;
	output_string.flush();
	return output_string.str();
}


/*TEST_CASE("StringSpaceFillTest")
{
std::string required = "          tenspaces!";
std::string pass_in = "tenspaces!";
cout << "|" << StringSpaceFill(20, pass_in) << "|\n";
REQUIRE(StringSpaceFill(9, pass_in) == "tenspaces!");
}*/

/*TEST_CASE("StringSpaceFillTest", "String length > field length")
{
// Validated "Error" displayed when in_string > field length
}*/

std::string StringSpaceFill(int required_field_length, std::string in_string)
{

	if (in_string.size() > required_field_length)
		Plog.logError("StringSpaceFill", "Error - input string length exceeds required field length");

	std::stringstream output_string;
	output_string << std::setw(required_field_length) << std::setfill(' ') << in_string;
	output_string.flush();
	return output_string.str();
}

int StringToInt(std::string in_string)
{
	return stoi(in_string);
}

long long StringToLongLong(std::string in_string)
{
	return stoll(in_string);
}

double StringToDouble(std::string in_string)
{
	return stod(in_string);
}

std::string upperCase(std::string in_string)
{
	std::string out_string;
	std::locale loc;
	for (int i = 0; i < in_string.length(); ++i)
	{
		out_string += std::toupper(in_string[i], loc);
	}

	return out_string;
}

bool validateAllLetters(std::string in_string)
{
	for (int i = 0; i < in_string.length(); i++)
	{
		if (!((in_string[i] >= 65 && in_string[i] <= 90) || (in_string[i] >= 97 && in_string[i] <= 122)))
		{
			Plog.logError("validateAllLetters", "Found a non-letter!");
			return false;
		}

	}

	return true;
}

bool StringAllSpaceCheck(string in_string)
{
	for (int x = 0; x < in_string.length(); x++)
	{
		if (in_string[x] != ' ')
		{
			return false;
		}
	}
	return true;
}