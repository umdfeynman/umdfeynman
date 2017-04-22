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
		void logInfo(std::string context, std::string message);
		void logWarn(std::string context, std::string message);
		void logError(std::string context, std::string message);
		Logger(std::string filename);
		~Logger();
		bool good = false;
	private:
		std::ofstream logFile;
		std::string getTime();
};

#endif