#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include <string>
#include <vector>
#include "window.h"

namespace fileParameters
{
	const std::string FILE_NAME = "windowParameters.txt";
	const char DELIMITER = ',';
}

namespace objectLabels
{
	const std::string BALL = "ball";
	const std::string PLAYER = "player";
}

void readFromFile(const std::string& fileName);

void readFromFile(const std::string& fileName, std::string& fileContents);

void setWindowFromFile(const std::string& fileName, Window& aWindow);

void addGameObjectsFromFile(const std::string& fileName, Window& aWindow);

//ToDo: Exercise 2: Create the definition for this method in the filehandling.cpp file
ObjectType StringToObjectType(std::string& objectName);

void splitString(const std::string& str, char delimiter, std::vector<std::string> &result);

#endif // FILEHANDLING_H



