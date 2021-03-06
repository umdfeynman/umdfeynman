#include "PMACS_Date.h"
#include "PMACS_Menu.h"
#include "PMACS_Globals.h"

void setSystemDate()
{
	Menu systemDateChange;
	std::string newDate = systemDateChange.displayDialogGetEntryString("Enter date as <day><day> <weekday> <week><week> <month><month> <year><year><year><year>");
	systemDate.NewDate(newDate);
}

Date::Date()
{

};

Date::Date(string info)
{
	baseDate = info;
	NewDate(info);
};

Date::~Date()
{

};

//reset class to initialization values(original instantiation state)
void Date::ResetDate()
{
	NewDate(baseDate);
}

//takes dateStream format string and reassigns values to match 
void Date::NewDate(string info)
{
	int index = 0;

	//get day
	int x = 0;
	string temp = "  ";
	while (info[index] != ' ')
	{
		temp[x] = info[index];
		index++;
		x++;
		day = stoi(temp);
	}
	index++;

	//get weekDay
	x = 0;
	temp = " ";
	while (info[index] != ' ')
	{
		temp[x] = info[index];
		index++;
		x++;
		weekDay = stoi(temp);
	}
	index++;

	//get weekNumber
	x = 0;
	temp = " ";
	while (info[index] != ' ')
	{
		temp[x] = info[index];
		index++;
		x++;
		weekNum = stoi(temp);
	}
	index++;

	//get month
	x = 0;
	temp = "  ";
	while (info[index] != ' ')
	{
		temp[x] = info[index];
		index++;
		x++;
		month = stoi(temp);
	}
	index++;

	//get year
	x = 0;
	temp = "    ";
	while (index < info.size())
	{
		temp[x] = info[index];
		index++;
		x++;
		year = stoi(temp);
	}
};


//change the date by an positve number of days
void Date::ChangeDay(unsigned int days)
{
	for (int x = 0; x < days; x++)
	{
		int nextDay = day + 1;

		WeekDay();

		//if 31, reset to 1 and add to month
		if (nextDay == 31)
		{
			day = 1;
			ChangeMonth();
		}
		else
		{
			day = nextDay;
		}
	}
};
void Date::ChangeMonth()
{
	int nextMonth = month + 1;

	//reset month
	if (nextMonth == 13)
	{
		month = 1;
		ChangeYear();
	}
	else
	{
		month = nextMonth;
	}

};
void Date::WeekDay()
{
	int counter = weekDay + 1;

	//reset week
	if (counter == 8)
	{
		weekDay = 1;
		WeekNumber();
	}
	else
	{
		weekDay = counter;
	}
};
void Date::WeekNumber()
{
	weekNum += 1;
};
void Date::ChangeYear()
{
	year += 1;
	//reset week count
	weekNum = 1;
};

//useless trash
int Date::ProjectDate(int days)
{
	Date a(GetDateStream());
	a.ChangeDay(days);
	int value = a.DateCompareValue();
	//a.~Date();
	return value;
};

//return string of date state in class-read format
string Date::GetDateStream()
{
	string send;
	send = to_string(day);
	send += " ";
	send += to_string(weekDay);
	send += " ";
	send += to_string(weekNum);
	send += " ";
	send += to_string(month);
	send += " ";
	send += to_string(year);

	return send;
};


//provides int value representation of date in YYYYMMDD 
//can be used for date value comparisons
int Date::DateCompareValue()
{
	//YYYMMDD to create int value for comparison
	string a;
	a = StringZeroFill(4, year);
	a += StringZeroFill(2, month);
	a += StringZeroFill(2, day);

	int comp;
	comp = stoi(a);
	return comp;
};

//returns date string in YYYY-MM-DD format
string Date::GetDate()
{
	string a;
	a = sGetYear();
	a += "-";
	a += sGetMonth();
	a += "-";
	a += sGetDay();
	return a;
};


//get integer representation of the day
int Date::GetDay()
{
	return day;
};

//get integer representation of the weekday
int Date::GetWeekDay()
{
	return weekDay;
};

//get integer representation of the week number
int Date::GetWeekNumber()
{
	return weekNum;
};

//get integer representation of the month
int Date::GetMonth()
{
	return month;
};

//get integer representation of the year
int Date::GetYear()
{
	return year;
};


//get zero-filled representation of the day
string Date::sGetDay()
{
	string a = StringZeroFill(2, day);								//assumes 2 digit days
	return a;
};

//get zero-filled representation of the weekday
string Date::sGetWeekDay()
{
	return to_string(weekDay);										//assumes 1 digit week day
};

//get zero-filled representation of the week number
string Date::sGetWeekNumber()
{
	string a = StringZeroFill(2, weekNum);							//assumes 2 digit week numbers
	return a;
};

//get zero-filled representation of the month
string Date::sGetMonth()
{
	string a = StringZeroFill(2, month);							//assumes 2 digit months
	return a;
};

//get zero-filled representation of the year
string Date::sGetYear()
{
	string a = StringZeroFill(4, year);								//assumes 4 digit years
	return a;
};


//takes a length and a numnber
//doesnt check if length is longer than digits. so dont be stupid.
//number given is preceeded by zeros to make length given
string Date::StringZeroFill(int length, long long number)
{
	int fill = length - 1;
	string a = "0";
	string b = to_string(number);

	//adds 0's to fill string
	for (int x = 0; x < fill; x++)
	{
		a += to_string(0);
	}

	//writes digits in reverse order
	for (int x = b.length() - 1; x >= 0; x--)
	{
		a[fill] = b[x];
		fill--;
	}
	return a;
};

//takes a length and a string
//doesnt check if length is longer than string. so dont be stupid.
//fills string with spaces until string length is the length provided
string Date::StringSpaceFill(int length, string fillMe)
{
	for (int x = fillMe.length(); x < length; x++)
	{
		fillMe += " ";
	}
	return fillMe;
}


//header format
//HD<space>SEQ#(4 digits - zero fill)<6 spaces>YYYY - MM - DD<remainder of line to file record size is spaces>
//Requires integer sequence number and record line length, returns string header line
string Date::GetHeader(int seq, int length)
{
	string sequenceNum = StringZeroFill(4, seq);						//zerofill sequence number

	string header;														//create header string
	header = "HD";														//add "HD"
	header = StringSpaceFill((header.length() + 1), header);			//add 1 space
	header += sequenceNum;					 						//add sequence number
	header = StringSpaceFill((header.length() + 6), header);				//add 6 spaces
	header += GetDate();												//add date
	header = StringSpaceFill(length, header);							//space fill to end of record

	return header;
};