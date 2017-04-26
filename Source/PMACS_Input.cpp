//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "PMACS_Logger.h"
#include "PMACS_Globals.h"
#include "PMACS_Input.h"
#include "PMACS_Defines.h"
#include "PMACS_String.h"

/*TEST_CASE("ValidateStrToTypeBySize types test")
{
Logger theLog("test.txt");
std::string too_long_for_int = "3000000000";
std::string too_long_for_char = "HI";
REQUIRE(validateStrToTypeBySize(&theLog, too_long_for_int, input_type_int) == false);
REQUIRE(validateStrToTypeBySize(&theLog, too_long_for_char, input_type_char) == false);
REQUIRE(validateStrToTypeBySize(&theLog, std::to_string(INT_MAX), input_type_int) == true);
REQUIRE(validateStrToTypeBySize(&theLog, "H", input_type_char) == true);
REQUIRE(validateStrToTypeBySize(&theLog, too_long_for_int, 4) == false);
}*/

// Utility function to confirm that a type we are converting from a string fits into the type we are targeting.
bool validateStrToTypeBySize(std::string input, int expected_type)
{
	long long int input_size_int;

	switch (expected_type)
	{
	case g_type_int:
		input_size_int = std::stoll(input);
		if (input_size_int > INT_MAX)
		{
			Plog.logError("validateInputTypeBySize", "(int) failed: \"" + input + "\" larger than int max bytes (" + std::to_string(INT_MAX) + ")\n");
			return false;
		}
		return true;
		break;
	case g_type_char_any:
		if (input.size() > 1)
		{
			Plog.logError("validateInputTypeBySize", "(char) failed: \"" + input + "\" larger than char max bytes (1)\n");
			return false;
		}
		return true;
		break;
	default:
		Plog.logError("validateInputTypeBySize", "failed:  Invalid expected_type specifier.\n");
		return false;
		break;
	}

	Plog.logError("validateInputTypeBySize", "failed:  WOW.  Somehow you circumvented the switch statement that convered all cases.  WTF?");
	return false;
}

bool validateInput(std::string in_string, int expected_type, int max_length, int min_length)
{
	if (in_string.length() > max_length)
	{
		Plog.logError("validateInput", "User entered string of length [" + std::to_string(in_string.length()) + "], exceeds max length [" + std::to_string(max_length) + "], returning error");
		return false;
	}

	if (in_string.length() < min_length)
	{
		Plog.logError("validateInput", "User entered string of length [" + std::to_string(in_string.length()) + "], fails to meet min length [" + std::to_string(min_length) + "], returning error");
		return false;
	}

	if (in_string.length() > 1 && (expected_type == g_type_char_any || expected_type == g_type_char_letter))
		return false;

	if (expected_type == g_type_string_letter)
	{
		if (!validateAllLetters(in_string))
		{
			Plog.logError("validateInput", "Expected g_type_string_letter but found non-letter, returning error");
			return false;
		}
	}
	else if (expected_type == g_type_char_letter)
	{
		if (!validateAllLetters(in_string))
		{
			Plog.logError("validateInput", "Expected g_type_char_letter but found non-letter, returning error");
			return false;
		}
	}
	else if (expected_type == g_type_int)
	{		
		if (!validateAllNumbers(in_string))
		{
			Plog.logError("validateInput", "Expected g_type_int but found non-number, returning error");
			return false;
		}

		std::string trimmedString = trimZeroes(in_string, g_type_int);

		try
		{	
			if (!validateStringConversion(trimmedString, g_type_int))
			{
				Plog.logError("validateInput", "Unable to convert from string to int (due to overflow or other issue), returning error");
				return false;
			}
		}
		catch (const std::out_of_range& e)
		{
			Plog.logError("validateInput", "Unable to convert from string to int (due to overflow or other issue), returning error");
			return false;
		}
		return true;

	}
	else if (expected_type == g_type_longlong)
	{
		if (!validateAllNumbers(in_string))
		{
			Plog.logError("validateInput", "Expected g_type_longlong but found non-number, returning error");
			return false;
		}
				
		std::string trimmedString = trimZeroes(in_string, g_type_longlong);
		
		try
		{
			if (!validateStringConversion(trimmedString, g_type_longlong))
			{
				Plog.logError("validateInput", "Unable to convert from string to longlong (stoll input differed from what you entered), returning error");
				return false;
			}
		}
		catch (const std::out_of_range& e)
		{
			Plog.logError("validateInput", "Unable to convert from string to longlong (due to overflow), returning error");
			return false;
		}

		return true;
	}
	else if (expected_type == g_type_double)
	{
		if (!validateDoubleAsString(in_string))
		{
			Plog.logError("validateInput", "Expected g_type_double but found non-number, returning error");
			return false;
		}
				
		std::string trimmedString = trimZeroes(in_string, g_type_double);

		try
		{
			if (!validateStringConversion(trimmedString, g_type_double))
			{
				Plog.logError("validateInput", "Unable to convert from string to double (due to overflow or other issue), returning error");
				return false;
			}
		}
		catch (const std::out_of_range& e)
		{
			Plog.logError("validateInput", "Unable to convert from string to double (due to overflow or other issue), returning error");
			return false;
		}

		return true;
	}
	
	return true;
}