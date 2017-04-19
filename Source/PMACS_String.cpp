#define CATCH_CONFIG_MAIN
#include <sstream>
#include "PMACS_String.h"
#include "catch.hpp"

//takes a length and a numnber
//doesnt check if length is longer than digits. so dont be stupid.
//number given is preceeded by zeros to make length given
string Date::StringZeroFill(int length, int number)
{
	int fill = length - 1;
	string a = "0";
	string b = to_string(number);

	//adds 0's to fill string
	for (int x = 0; x < fill; x++)
	{
		a += to_string(0);
	}

	//writes digits in reverse order
	for (int x = b.length() - 1; x >= 0; x--)
	{
		a[fill] = b[x];
		fill--;
	}
	return a;
};

TEST_CASE("IntZeroFillTest")
{
	std::string required = "00000000000000009999"
	REQUIRE(Date::StringZeroFill(20, 9999) == required)
}

string Date::StringZeroFill(int required_field_length, int number)
{
	std::stringstream output_string;
	output_string << std::setw(required_field_length) << std::setfill('0') << number;
	output_string.flush();
	return output_string.str();
}



//takes a length and a string
//doesnt check if length is longer than string. so dont be stupid.
//fills string with spaces until string length is the length provided
string Date::StringSpaceFill(int length, string fillMe)
{
	for (int x = fillMe.length(); x < length; x++)
	{
		fillMe += " ";
	}
	return fillMe;
}
