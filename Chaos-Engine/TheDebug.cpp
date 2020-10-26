#include "TheDebug.h"
#include "glad/glad.h"
#include <iostream>
#include <Windows.h>

std::vector<std::string> TheDebug::logs;
std::vector<std::string> TheDebug::alerts;
std::vector<std::string> TheDebug::warnings;

//-------------------------------------------------------------------------------
//Create a log and print it on the console (create the debug manager, only happens once)
//-------------------------------------------------------------------------------
TheDebug* TheDebug::Log(const std::string& debuglog, Logs l)
{
	//----------------------------- Create Debug Manager statically so it only happens once

	static TheDebug* debugManager = new TheDebug;

	//Temp string for console log
	std::string temp;
	//----------------------------- Set Log Color to bright white and print it

	if (l == ALERT)
	{
		//Red Color
		if (debuglog != "")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			std::cout << "=======================================" << std::endl;
			std::cout << "[ALERT] " << debuglog << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			alerts.push_back(temp);
		}
	}
	else if (l == WARNING)
	{
		if (debuglog != "")
		{
			//Yellow color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			std::cout << "=======================================" << std::endl;
			temp = "[WARNING] " + debuglog;
			std::cout << temp << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			warnings.push_back(temp);
		}
	}
	else if (l == LOG)
	{
		if (debuglog != "")
		{
			//White color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << "=======================================" << std::endl;
			temp = "[LOG] " + debuglog;
			std::cout << temp << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;

			logs.push_back(temp);
		}
	}
	else if (l == SUCCESS)
	{
		//Green color
 		if (debuglog != "")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << "=======================================" << std::endl;
			temp = "[SUCCESS] " + debuglog;
			std::cout << temp << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
	}
	else if (l == DEBUG)
	{
		if (debuglog != "")
		{
			//blue color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			std::cout << "=======================================" << std::endl;
			temp = "[DEBUG] " + debuglog;
			std::cout << temp << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
	}

	//----------------------------- Return Debug Manager

	return debugManager;
}
//-------------------------------------------------------------------------------
//Create Debug (only happens once) and return it
//-------------------------------------------------------------------------------
TheDebug* TheDebug::Instance()
{
	static TheDebug* debugManager = new TheDebug;
	return debugManager;
}

//-------------------------------------------------------------------------------
//Display error in the console and add it to the error log text file
//-------------------------------------------------------------------------------
void TheDebug::Error(const std::string& errorlog)
{
	//----------------------------- Check if file is open, if not create it

	if (!logFile.is_open())
	{
		//----------------------------- Create file

		logFile.open("ErrorLog.txt", std::ios_base::out, std::ios_base::app);

		//----------------------------- Add the header to the file

		logFile << "//---------------------------------------------------" << std::endl;
		logFile << "//ERROR LOG FILE" << std::endl;
		logFile << "//---------------------------------------------------" << std::endl;
		logFile << std::endl;
	}

	//----------------------------- Set color of Error log to red, print error log and add log to file

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

	std::cout << "[ERROR] " << errorlog << std::endl;

	logFile << "[ERROR] " << errorlog << std::endl;

	//----------------------------- If there's a problem writing to file make an error log in file and console

	if (logFile.bad())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

		std::cout << "[ERROR] Writing to Log File error" << std::endl;

		logFile << "[ERROR] Writing to Log File error" << std::endl;
	}
}

//-------------------------------------------------------------------------------
//Clear all vectors vector
//-------------------------------------------------------------------------------
void TheDebug::Clear()
{
	logs.clear();
	warnings.clear();
	alerts.clear();
}

//-------------------------------------------------------------------------------
//Stack Messages
//-------------------------------------------------------------------------------
void TheDebug::Stack()
{
	//TODO: Stack these together in a map
	//map<string, int>
	//Check if there is already a string with the same name, if yes just add to int
	//Display both int and string
	//Need a bool to say that maps are being used instead of vectors
}

//-------------------------------------------------------------------------------
//Show warning or not
//-------------------------------------------------------------------------------
void TheDebug::ShowWarning()
{
	if (isShowingWarnings)
	{
		isShowingWarnings = false;
	}
	else
	{
		isShowingWarnings = true;
	}
}

//-------------------------------------------------------------------------------
//Show error or not
//-------------------------------------------------------------------------------
void TheDebug::ShowError()
{
	if (isShowingErrors)
	{
		isShowingErrors = false;
	}
	else
	{
		isShowingErrors = true;
	}
}

//-------------------------------------------------------------------------------
//Get Warnings vector
//-------------------------------------------------------------------------------
const std::vector<std::string> TheDebug::GetWarnings()
{
	return warnings;
}

//-------------------------------------------------------------------------------
//Get Alerts vector
//-------------------------------------------------------------------------------
const std::vector<std::string> TheDebug::GetAlerts()
{
	return alerts;
}

//-------------------------------------------------------------------------------
//Get Logs vector
//-------------------------------------------------------------------------------
const std::vector<std::string> TheDebug::GetLogs()
{
	return logs;
}

//-------------------------------------------------------------------------------
//Get warnings
//-------------------------------------------------------------------------------
bool TheDebug::GetShowingWarnings()
{
	return isShowingWarnings;
}

//-------------------------------------------------------------------------------
//Get Errors Enabled
//-------------------------------------------------------------------------------
bool TheDebug::GetShowingAlerts()
{
	return isShowingErrors;
}

//-------------------------------------------------------------------------------
//Check OpenGL errors
//-------------------------------------------------------------------------------
void TheDebug::CheckOpenGLErrors()
{
	GLenum errorCode = glGetError();

	if (errorCode == GL_NO_ERROR)
	{
	}
	else if (errorCode == GL_INVALID_OPERATION)
	{
		Log("OpenGL invalid operation", WARNING);
	}
}
