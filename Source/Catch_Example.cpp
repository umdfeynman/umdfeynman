#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include <cassert>
#include <string>
using namespace std;

unsigned int addition(unsigned int a, unsigned int b)
{
	return a + b;
}

void test_func()
{
	std::string test;
	std::string item_name = test.substr(18, 20);
	test.
}

int StringToPositiveInt(std::string input_string)
{
	int a;
	a = stoi(input_string);
	return a;
}

TEST_CASE("1+1 = 2", "[oneplusone]")
{
	REQUIRE(StringToPositiveInt("0004") == 4);
}



