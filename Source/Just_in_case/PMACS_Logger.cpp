#define _CRT_SECURE_NO_WARNINGS
#include "PMACS_Logger.h"
#include <fstream>
#include <string>
#include <iostream>
#include <time.h>

Logger::Logger(std::string filename)
{
	try
	{
		logFile.open(filename.c_str(), std::ofstream::app);

		if (!logFile)
			throw 1;
	}
	catch (int e)
	{
		if (e == 1)
			printf("Error.  Unable to open file %s!\n", filename.c_str());		
	}
	
	logFile << getTime() << "\t[LOGGER] Logfile opened successfully.\n";
}

Logger::~Logger()
{
	logFile.flush();
	logFile.close();
}

std::string Logger::getTime()
{
	time_t now = time(0);

	tm* localtm = localtime(&now);

	std::string fullDate = asctime(localtm);
	std::string trimWeekday = fullDate.substr(4, fullDate.size() - 5);
	std::string trimYear = trimWeekday.substr(0, trimWeekday.size() - 5);

	return trimYear;
}

void Logger::logError(std::string message)
{
	logFile << getTime() << "\t[ERROR] [" << getContext() << "] " << message << "\n";
}

void Logger::logWarn(std::string message)
{
	logFile << getTime() << "\t[WARN] [" << getContext() << "] " << message << "\n";
}

void Logger::logInfo(std::string message)
{
	logFile << getTime() << "\t[INFO] [" << getContext() << "] " << message << "\n";
}

void Logger::setContext(std::string newcontext)
{
	context = newcontext;
}

std::string Logger::getContext()
{
	return context;
}