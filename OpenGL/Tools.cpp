#include "Tools.h"
#include <iostream>

//-------------------------------------------------------------------------------
//Parse text function into a map
//-------------------------------------------------------------------------------
void ParseText(std::string& sentence, char& token, std::map<std::string, std::string>& map)
{
	int n = 0;

	n = sentence.find(token);

	if (n != std::string::npos)
	{

		std::string tempString = sentence.substr(0, n);
		sentence.erase(0, n + 1);
		map[tempString] = sentence;
	}
}

//-------------------------------------------------------------------------------
//Parse text function into a map
//-------------------------------------------------------------------------------
void ParseText(std::string& sentence, char& token, std::map<std::string, float>& map)
{
	int n = 0;

	n = sentence.find(token);

	if (n != std::string::npos)
	{

		std::string tempString = sentence.substr(0, n);
		sentence.erase(0, n + 1);
		map[tempString] = stof(sentence);
	}
}

//-------------------------------------------------------------------------------
//Parse text function into a vector
//-------------------------------------------------------------------------------
void ParseText(std::string& sentence, char& token, std::vector<std::string>& vector)
{
	int n = 0;

	n = sentence.find(token);

	if (n != std::string::npos)
	{

		std::string tempString = sentence.substr(0, n);
		sentence.erase(0, n + 1);
		vector.push_back(tempString);
		vector.push_back(sentence);
	}
}

//-------------------------------------------------------------------------------
//Parse text and convert to float, then put into vector
//-------------------------------------------------------------------------------
void ParseText(std::string& sentence, char& token, std::vector<GLfloat>& vector)
{
	int n = 0;

	n = sentence.find(token);

	if (n != std::string::npos)
	{
		//parse each line
		std::string tempString = sentence.substr(0, n);
		sentence.erase(0, n + 1);
		
		//convert string to float and add to vector
		vector.push_back(std::stof(tempString));
		vector.push_back(std::stof(sentence));
	}
}

//-------------------------------------------------------------------------------
//Parse text and convert to int, then put into vector
//-------------------------------------------------------------------------------
void ParseText(std::string& sentence, char& token, std::vector<GLint>& vector)
{
	int n = 0;

	n = sentence.find(token);

	if (n != std::string::npos)
	{
		//parse each line
		std::string tempString = sentence.substr(0, n);
		sentence.erase(0, n + 1);

		//convert string to float and add to vector
		vector.push_back(std::stoi(tempString));
		vector.push_back(std::stoi(sentence));
	}
}
