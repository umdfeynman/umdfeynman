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
#include "PMACS_Defines.h"
#include "PMACS_Utility.h"

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

bool validateAllNumbers(std::string in_string)
{
	for (int i = 0; i < in_string.length(); i++)
	{
		if (!(in_string[i] >= 48 && in_string[i] <= 57))
		{
			Plog.logError("validateAllNumbers", "Found a non-number!");
			return false;
		}
	}
	return true;
}

bool validateDoubleAsString(std::string in_string)
{
	// For making sure doubles have at least one number

	// For making sure doubles have at least one period and at least one number
	int numPeriods = 0;
	int numDigits = 0;

	for (int i = 0; i < in_string.size(); i++)
	{
		if (in_string[i] == '.')
			numPeriods++;
		if (in_string[i] >= 48 && in_string[i] <= 57)
			numDigits++;
	}

	if (numPeriods > 1)
		return false;

	if (numDigits < 1)
		return false;

	// For making sure doubles contain only 1-9 and .
	for (int i = 0; i < in_string.length(); i++)
	{
		if (!((in_string[i] >= 48 && in_string[i] <= 57) || in_string[i] == 46))
		{
			Plog.logError("validateOnlyDoubleChars", "Found a non-double character!");
			return false;
		}
	}
	return true;
}

bool validateStringConversion(std::string in_string, int expected_type)
{
	int testInt;
	long long testLongLong;
	double testDouble;

	std::string convertString;

	switch (expected_type)
	{
	case g_type_int:
		testInt = StringToInt(in_string);
		convertString = std::to_string(testInt);
		if (in_string != convertString)
		{
			Plog.logError("validateStringConversion", "Resultant int after string conversion [" + convertString + "] did not match original [" + in_string + "], returning false");
			return false;
		}
		return true;
		break;
	case g_type_longlong:
		testLongLong = StringToLongLong(in_string);
		convertString = std::to_string(testLongLong);
		if (in_string != convertString)
		{
			Plog.logError("validateStringConversion", "Resultant long long after string conversion [" + convertString + "] did not match original [" + in_string + "], returning false");
			return false;
		}
		return true;
		break;
	case g_type_double:
		testDouble = StringToDouble(in_string);
		convertString = trimZeroes(std::to_string(testDouble), g_type_double); // Need trimZeroes because stod inserts trailing zeroes
		if (in_string != convertString)
		{
			Plog.logError("validateStringConversion", "Resultant double after string conversion [" + convertString + "] did not match original [" + in_string + "], returning false");
			return false;
		}
		return true;
		break;
	}

	Plog.logError("validateStringConversion", "Invalid expected type: [" + std::to_string(expected_type) + "], returning false");
	return false;

}



std::string trimZeroes(std::string in_string, int expected_type)
{
	// Leading zeroes

	std::string trimmedLeading;
	std::string trimmedAll;
	int stringLoc = 0;

	//Skip past zeroes and then begin outputting to outputString;
	while (in_string[stringLoc] == '0')
	{
		stringLoc++;
	}

	// Check to see if this is all zeroes and periods
	bool allZeroes = true;

	for (int i = 0; i < in_string.size(); i++)
	{
		if (in_string[i] != '.' && in_string[i] != '0')
			allZeroes = false;
	}

	if (allZeroes)
		return "0";

	// If this is a double and everything to the left of the decimal point is 0, we need at least one zero
	if (expected_type == g_type_double && in_string[stringLoc] == '.' && stringLoc > 0)
		stringLoc--;

	// Now start outputting
	for (int i = stringLoc; i < in_string.size(); i++)
	{
		trimmedLeading.push_back(in_string[i]);
	}

	if (expected_type == g_type_int || expected_type == g_type_longlong)
		return trimmedLeading;

	// If this is a double and the string starts with a . and is nonzero, add a zero
	if (expected_type == g_type_double && trimmedLeading[0] == '.')
		trimmedLeading = "0" + trimmedLeading;

	if (trimmedLeading.size() == 0)
		return 0;
	// If double, also remove trailing zeroes	
	stringLoc = trimmedLeading.size() - 1;
	if (expected_type == g_type_double)
	{

		while ((trimmedLeading[stringLoc] == '0' || trimmedLeading[stringLoc] == '.') && stringLoc > 0)
		{

			stringLoc--;

			// If we hit the decimal, advance past it and quit
			if (trimmedLeading[stringLoc] == '.')
			{
				stringLoc--;
				break;
			}
		}

		// Now start outputting
		for (int i = 0; i <= stringLoc; i++)
		{
			trimmedAll.push_back(trimmedLeading[i]);
		}
	}

	return trimmedAll;
}

//can be used to cut off input strings to the correct size
string StringTrimToSize(int length, string entry)
{
	if (entry.length() > length)
	{
		string cutString = entry.erase(length, entry.length());
		//cout << "Warning. Entry too long. Will be cut at character limit" << endl;
		//cout << "Saved entry: " << cutString << endl;
		return cutString;
	}
	return entry;
}

string StringSpaceTrim(string entry)
{
	string trimmedEntry = entry.erase(StringFindLastCharacter(entry), entry.length());
	return trimmedEntry;
}

//returns length of string excluding trailing spaces
int StringFindLastCharacter(string entry)
{
	int end = entry.length();
	for (int x = entry.length(); x > 0; x--)
	{
		if (entry[x - 1] == ' ')
		{
			end = x - 1;
		}
		else
		{
			break;
		}
	}
	return end;
}

//------Check whether or not a character is a number
bool DigitCheck(char test)
{
	if ((test >= 48) && (test <= 57))					 //If the character is within the range of numbers
	{
		return true;										//it is a number -> digit
	}
	return false;											//else it is not accepted as a digit
}

