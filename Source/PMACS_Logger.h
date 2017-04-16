#pragma once

// Includes
#include <fstream>
#include <string>

// Header guard
#ifndef PMACS_Logger_H
#define PMACS_Logger_H

class Logger
{
public:
	void logInfo(std::string message, std::string subprogram);
	void logWarn(std::string message, std::string subprogram);
	void logError(std::string message, std::string subprogram);
	Logger(std::string filename);
	~Logger();
private:
	std::ofstream logFile;
	std::string getTime();
	
};

#endif