#ifndef PMACS_STRING_H
#define PMACS_STRING_H

using namespace std;

std::string StringIntZeroFill(int required_field_length, int number);
std::string StringLongLongZeroFill(int required_field_length, long long number);
std::string StringSpaceFill(int length, string fillMe);
int StringToInt(std::string in_string);
long long StringToLongLong(std::string in_string);
double StringToDouble(std::string in_string);
std::string upperCase(std::string in_string);
bool validateAllLetters(std::string in_string);
bool StringAllSpaceCheck(string in_string);
bool validateAllNumbers(std::string in_string);
bool validateStringConversion(std::string in_string, int expected_type);
std::string trimZeroes(std::string in_string, int expected_type);
bool validateDoubleAsString(std::string in_string);
string StringTrimToSize(int length, string entry);
int StringFindLastCharacter(string entry);
string StringSpaceTrim(string entry);
bool DigitCheck(char test);

#endif