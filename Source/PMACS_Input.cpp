//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include <string>
//#include "PMACS_Logger.h"
#include "PMACS_Globals.h"
#include "PMACS_Input.h"

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
	case input_type_int:
		input_size_int = std::stoll(input);
		if (input_size_int > INT_MAX)
		{
			Plog.logError("validateInputTypeBySize", "(int) failed: \"" + input + "\" larger than int max bytes (" + std::to_string(INT_MAX) + ")\n");
			return false;
		}
		return true;
		break;
	case input_type_char:
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