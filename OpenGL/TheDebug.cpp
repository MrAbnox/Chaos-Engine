#include "TheDebug.h"
#include <iostream>
#include <Windows.h>

//-------------------------------------------------------------------------------
//Create a log and print it on the console (create the debug manager, only happens once)
//-------------------------------------------------------------------------------
TheDebug* TheDebug::Log(const std::string& debuglog, Logs l)
{
	//----------------------------- Create Debug Manager statically so it only happens once

	static TheDebug* debugManager = new TheDebug;

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
		}
	}
	else if (l == WARNING)
	{
		if (debuglog != "")
		{
			//Yellow color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			std::cout << "=======================================" << std::endl;
			std::cout << "[WARNING] " << debuglog << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
	}
	else if (l == LOG)
	{
		if (debuglog != "")
		{
			//White color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << "=======================================" << std::endl;
			std::cout << "[LOG] " << debuglog << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
		}
	}
	else if (l == SUCCESS)
	{
		//Green color
		if (debuglog != "")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << "=======================================" << std::endl;
			std::cout << "[SUCCESS] " << debuglog << std::endl;
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
			std::cout << "[DEBUG] " << debuglog << std::endl;
			std::cout << "=======================================" << std::endl;
			std::cout << "" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
	}

	//----------------------------- Return Debug Manager

	return debugManager;
}

//-------------------------------------------------------------------------------
//Display error in the console and add it to the error log text file
//-------------------------------------------------------------------------------
void TheDebug::Error(const std::string& errorlog)
{
	//----------------------------- Check if file is open, if not create it

	if (!t_logFile.is_open())
	{
		//----------------------------- Create file

		t_logFile.open("ErrorLog.txt", std::ios_base::out, std::ios_base::app);

		//----------------------------- Add the header to the file

		t_logFile << "//---------------------------------------------------" << std::endl;
		t_logFile << "//ERROR LOG FILE" << std::endl;
		t_logFile << "//---------------------------------------------------" << std::endl;
		t_logFile << std::endl;
	}

	//----------------------------- Set color of Error log to red, print error log and add log to file

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

	std::cout << "[ERROR] " << errorlog << std::endl;

	t_logFile << "[ERROR] " << errorlog << std::endl;

	//----------------------------- If there's a problem writing to file make an error log in file and console

	if (t_logFile.bad())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

		std::cout << "[ERROR] Writing to Log File error" << std::endl;

		t_logFile << "[ERROR] Writing to Log File error" << std::endl;
	}
}
