#ifndef PMACS_FILE_H
#define PMACS_FILE_H
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_String.h"
#include "PMACS_Logger.h"
#include <string>


bool createFile(string file_name, std::ofstream& the_file);
bool openFile(std::string file_name, std::ifstream& file_object);
bool headerCheck(ifstream& input_file);
bool sequenceCheck(ifstream& input_file, int seq_index);
int trailerCheck(ifstream& input_file, bool count_c_records);
void positionFileForRecords(ifstream& input_file);
void insertTrailer(ofstream& output_file, int num_items);
void insertHeader(ostream& input_file, int file_index);

#endif