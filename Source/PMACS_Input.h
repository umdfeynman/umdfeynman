#include <string>
#ifndef PMACS_INPUT_H
#define PMACS_INPUT_H

// Validates conversion from string (from file input)
bool validateStrToTypeBySize(std::string input, int expected_type);
bool validateInput(std::string in_string, int expected_type, int max_length, int min_length = 0);

#endif