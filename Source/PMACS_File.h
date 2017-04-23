#ifndef PMACS_FILE_H
#define PMACS_FILE_H
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_String.h"
#include "PMACS_Logger.h"
#include <string>

// bool?
ofstream createFile(string file_name, int file_index);
bool openFile(std::string file_name, std::ifstream& file_object);
bool headerCheck(ifstream& input_file);
bool sequenceCheck(ifstream& input_file, int seq_index);
bool trailerCheck(ifstream& input_file);
void positionFileForRecords(ifstream& input_file);
void insertTrailer(ofstream& output_file, int num_items);
void InsertHeader(ostream& input_file, int file_index);

#endif