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
		void logInfo(std::string message);
		void logWarn(std::string message);
		void logError(std::string message);
		Logger(std::string filename);
		~Logger();
		void setContext(std::string newcontext);
		std::string getContext();
	private:
		std::ofstream logFile;
		std::string context;
		std::string getTime();	
};

#endif