#include <string>

#ifndef PMACS_STRING_H

#define PMACS_STRING_H
//takes a length and a numnber
//doesnt check if length is longer than digits. so dont be stupid.
//number given is preceeded by zeros to make length given
string Date::StringZeroFill(int length, int number)

//takes a length and a string
//doesnt check if length is longer than string. so dont be stupid.
//fills string with spaces until string length is the length provided
string Date::StringSpaceFill(int length, string fillMe)
#endif