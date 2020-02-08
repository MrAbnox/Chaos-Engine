#ifndef THEDEBUG_H
#define THEDEBUG_H

#include <string>
#include <fstream>

enum Logs
{
	LOG = 1, ALERT, WARNING, DEBUG, SUCCESS
};
class TheDebug
{

public:

	static TheDebug* Log(const std::string& debuglog, Logs l);
	static TheDebug* Instance();

public:

	void Error(const std::string& errorlog);

private:

	TheDebug() {};
	TheDebug(const TheDebug&);
	TheDebug& operator=(const TheDebug&);

private:

	std::ofstream t_logFile;
};

#endif
