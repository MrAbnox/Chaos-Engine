#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "glad/glad.h"

void ParseText(std::string& sentence, char& token, std::map<std::string, std::string>& map);
void ParseText(std::string& sentence, char& token, std::map<std::string, float>& map);
void ParseText(std::string& sentence, char& token, std::vector<std::string>& vector);
void ParseText(std::string& sentence, char& token, std::vector<GLfloat>& vector);
void ParseText(std::string& sentence, char& token, std::vector<GLint>& vector);