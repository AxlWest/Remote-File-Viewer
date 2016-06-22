#include "ServerLog.h"
#include <ctime>
#include <string>

using std::string ;
using std::to_string ;

ServerLog::ServerLog(void)
{
}

ServerLog::~ServerLog(void)
{
}



void ServerLog::failedToAcceptLog(void)
{
	string logMessage ;
	std::time_t currnetTime ;
	std::tm *localTime ;

	std::time(&currnetTime) ;
	localTime = localtime(&currnetTime) ;

	logMessage = to_string(localTime->tm_mday) ; //Day of the month
	logMessage += "/" ;
	logMessage += to_string((localTime->tm_mon + 1)) ; //Current month (range is from 0 - 11 so add one to make 1 - 12)
	logMessage += "/" ;
	logMessage += to_string((localTime->tm_year + 1900)) ; //Current year (returns the number of years past 1900 so add 1900 to get current years numerical value)
	logMessage += "::" ;
	logMessage += to_string(localTime->tm_hour) ; //Hours
	logMessage += ":" ;
	logMessage += to_string(localTime->tm_min) ; //Minutes

}