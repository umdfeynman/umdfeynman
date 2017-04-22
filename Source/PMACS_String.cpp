//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "PMACS_String.h"

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


std::string StringZeroFill(int required_field_length, int in_number)
{
	std::stringstream test_num_length;
	test_num_length << in_number;
	test_num_length.seekg(0, ios::end);
	int size = test_num_length.tellg();

	if (size > required_field_length)
		std::cout << "StringZeroFill Error - input number length exceeds required field length\n";		
	
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
		std::cout << "StringSpaceFill Error - input string length exceeds required field length\n";


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