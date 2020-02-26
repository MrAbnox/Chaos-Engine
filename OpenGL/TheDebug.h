#ifndef THEDEBUG_H
#define THEDEBUG_H

#include <string>
#include <fstream>
#include <vector>

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

public:

	void Clear();
	void Stack();
	void ShowWarning();
	void ShowError();

public:

	static const std::vector<std::string> GetWarnings();
	static const std::vector<std::string> GetAlerts();
	static const std::vector<std::string> GetLogs();

public:

	bool GetShowingWarnings();
	bool GetShowingAlerts();

private:

	TheDebug() 
	{
		m_warnings.push_back("Showing Warnings!");
		m_alerts.push_back("Showing Alerts!");
	};

	TheDebug(const TheDebug&);
	TheDebug& operator=(const TheDebug&);

public:

	void CheckOpenGLErrors();

private:

	std::ofstream t_logFile;

private:

	static std::vector<std::string> m_logs;
	static std::vector<std::string> m_alerts;
	static std::vector<std::string> m_warnings;

private:

	bool isShowingWarnings = true;
	bool isShowingErrors = true;
};

#endif
