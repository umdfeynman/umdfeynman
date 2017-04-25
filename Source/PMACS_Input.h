#include <string>
#ifndef PMACS_INPUT_H
#define PMACS_INPUT_H

#define input_type_int 1
#define input_type_long_int 2
#define input_type_char 3

// Validates conversion from string (from file input)
bool validateStrToTypeBySize(std::string input, int expected_type);

#endif