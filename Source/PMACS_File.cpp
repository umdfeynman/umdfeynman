#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_String.h"
#include "PMACS_Logger.h"
#include "PMACS_Utility.h"
#include <string>

bool createFile(string file_name, ofstream& the_file)
{
    the_file.open(file_name, ios::out);
    if (!the_file.good())
	{
		Plog.logError("existenceCheck", "Unable to create file.");
		return false;
	}
    
    return true;
}

//std::string header = systemDate.getHeader(file_index, recordLength);
//the_file.write(header + "\n");
//the_file.writeline(header);

//std::ifstream file;
//bool openFileResult = openFile("test_file.txt", file);

bool openFile(std::string file_name, std::ifstream& file_object)
{
	file_object.open(file_name);
	if (!file_object || !file_object.good())
	{
		Plog.logError("existenceCheck", "Unable to open file " + file_name + "\n");
		return false;
	}
	return true;
}

bool headerCheck(ifstream& input_file)
{
    // Go to beginning of file
    input_file.seekg(0);
    
    std::string headerLine;
    std::getline(input_file, headerLine);
    if (headerLine[0] != 'H' || headerLine[1] != 'D' || headerLine[2] != ' ')
    {
		Plog.logError("headerCheck", "Header read failed, \"HD \" not found");
        return false;
    }
    return true;
}

bool sequenceCheck(ifstream& input_file, int seq_index)
{
    // Go to beginning of file
    input_file.seekg(0);
    
    std::string headerLine;
    std::getline(input_file, headerLine);
    std::string s_inputSeqNumber = headerLine.substr(3, 4);
    
    int inputSeqNumber = StringToInt(s_inputSeqNumber);
    int expectedSeqNumber;

	if (seq_index >= 9999)
		expectedSeqNumber = 1;
	else
		expectedSeqNumber = getSequenceNumber(seq_index) + 1;
    
    
    if (inputSeqNumber != expectedSeqNumber)
    {
        Plog.logError("sequenceCheck", "Sequence number retrieved " + s_inputSeqNumber + " did not match stored sequence number " + std::to_string(getSequenceNumber(seq_index)) + " + 1");
        return false;
    }
    
    return true;
}

int trailerCheck(ifstream& input_file)
{
    // Go to beginning of file
    input_file.seekg(0);
    
    // Search for trailer ("T")
    std::string readLine = "";
    
    int rowCount = 0;
    
    while (!input_file.eof())
    {
		std::getline(input_file, readLine);
        
        if (readLine[0] != 'H' &&
            readLine[0] != 'T' &&
            readLine[0] != 'C' &&
            readLine[0] != 'N')
            rowCount++;
    }
    
    if (readLine[0] != 'T' || readLine[1] != ' ')
    {
        Plog.logError("trailerCheck", "Unable to locate trailer");
        return -1;
    }
    
	std::string s_trailerCount = readLine.substr(2, 4);
    int trailerCount = StringToInt(s_trailerCount);
    
    if (rowCount != trailerCount)
    {
        Plog.logError("trailerCheck", "Trailer count number " + s_trailerCount + " does not match item count number " + std::to_string(rowCount));
		return -1;
    }
    
	if (trailerCount == 0)
		return 0;

	return trailerCount;
}

void positionFileForRecords(ifstream& input_file)
{
    // Go to beginning of file
    input_file.seekg(0);
    
    std::string dummy;
    std::getline(input_file, dummy);  // Read one line (skip header)
}

void insertTrailer(ofstream& output_file, int num_items)
{
    output_file << "T " << StringIntZeroFill(4, num_items);
}

void insertHeader(ostream& input_file, int file_index)
{
    std::string header = systemDate.GetHeader(getSequenceNumber(file_index), getRecordLength(file_index));
    input_file << header << std::endl;
}



