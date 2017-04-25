#ifndef PMACS_DATE_H
#define PMACS_DATE_H
#include <iostream>
#include <string>

using namespace std;



/*
//start 01/01/2017
struct Date_Format
{
unsigned int day = 01;			//2
unsigned int weekDay = 1;		//1
unsigned int weekNum = 01;		//2
unsigned int month = 01;		//2
unsigned int year = 01;			//4
};
*/


//day<space>weekday<space>weekNumber<space>month<space>year<space>
class Date
{
private:
	//Date_Format today;
	string baseDate;				//Date used in creation of the instance
	unsigned int day = 0;			//2
	unsigned int weekDay = 0;		//1
	unsigned int weekNum = 0;		//2
	unsigned int month = 0;			//2
	unsigned int year = 0;			//4

public:
	Date(string);
	Date();
	~Date();
	void ChangeDay(unsigned int);							//change day
	void ChangeMonth();								//change month
	void WeekDay();									//week day
	void WeekNumber();								//week counter
	void NewDate(string);							//change date values
	void ResetDate();								//resets date to base values
	void ChangeYear();								//change year
	Date CopyDate();								//return copy of date
	string GetDateStream();							//return string of date in class read format

													//int time return funcions
	int GetDay();
	int GetWeekDay();
	int GetWeekNumber();
	int GetMonth();
	int GetYear();

	//zero filled time return functions
	string sGetDay();
	string sGetWeekDay();
	string sGetWeekNumber();
	string sGetMonth();
	string sGetYear();

	int ProjectDate(int);							//returns date value of projected date

	string GetHeader(int, int);						//print date for header
	string GetDate();						 		//get date in YYYY-MM-DD
	int DateCompareValue();							//returns int representation of the date-state

	string StringZeroFill(int, int);				//returns a string representing a zero filled int
	string StringSpaceFill(int, string);			//returns string with spaces filled to right
};

#endif