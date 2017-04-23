#ifndef PMACS_STRING_H
#define PMACS_STRING_H

using namespace std;

string StringIntZeroFill(int required_field_length, int number);
string StringLongLongZeroFill(int required_field_length, long long number);
string StringSpaceFill(int length, string fillMe);
int StringToInt(std::string in_string);
long long StringToLongLong(std::string in_string);
double StringToDouble(std::string in_string);
std::string upperCase(std::string in_string);
bool validateAllLetters(std::string in_string);
#endif