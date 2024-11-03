#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "filehandling.h"
#include "window.h"

void readFromFile(const std::string& fileName)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: " << fileName << " could not be opened." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }

    inputFile.close();
}



void readFromFile(const std::string& fileName, std::string& fileContents)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: " << fileName << " could not be opened." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        fileContents += line + '\n';
    }

    inputFile.close();
}

void setWindowFromFile(const std::string& fileName, Window& aWindow)
{
	std::string fileContents;

	readFromFile(fileName, fileContents);

	std::stringstream sStream(fileContents);

	std::string line;

	std::vector<std::string> tokens;

	std::getline(sStream, line);

	splitString(line, fileParameters::DELIMITER, tokens);

	aWindow.setName(tokens[1]);
	aWindow.setLocation(stoi(tokens[2]), stoi(tokens[3]));
	aWindow.setDimensions(stoi(tokens[4]), stoi(tokens[5]));
	Uint8 red = static_cast<Uint8>(stoi(tokens[6]));
	Uint8 green = static_cast<Uint8>(stoi(tokens[7]));
	Uint8 blue = static_cast<Uint8>(stoi(tokens[8]));
	Uint8 alpha = static_cast<Uint8>(stoi(tokens[9]));
	Colour windowColour = { red, green, blue, alpha };
	aWindow.setWindowColour(windowColour);
}

void addGameObjectsFromFile(const std::string& fileName, Window& aWindow)
{
	std::string fileContents;

	readFromFile(fileName, fileContents);

	std::stringstream sStream(fileContents);

	std::string line;

	std::vector<std::string> tokens;

	while (std::getline(sStream, line))
	{
		splitString(line, fileParameters::DELIMITER, tokens);

		float xPos, yPos, width, height;
		
		if (tokens[0] == objectLabels::BALL || tokens[0] == objectLabels::PLAYER)
		{
			ObjectType type = StringToObjectType(tokens[0]);
			xPos = stof(tokens[1]);
			yPos = stof(tokens[2]);
			width = stof(tokens[3]);
			height = stof(tokens[4]);
			Uint8 red = static_cast<Uint8>(stoi(tokens[5]));
			Uint8 green = static_cast<Uint8>(stoi(tokens[6]));
			Uint8 blue = static_cast<Uint8>(stoi(tokens[7]));
			Uint8 alpha = static_cast<Uint8>(stoi(tokens[8]));
			Colour colour = { red, green, blue, alpha };
			float xVelocity = stof(tokens[9]);
			float yVelocity = stof(tokens[10]);
			Vec2D velocity = { xVelocity, yVelocity };

			//The Game Object struct needs a constructor for this to work
			GameObject rec = GameObject( type, xPos, yPos, width, height, colour, velocity);

			//All game objects are added to the GameObjects Vector 
			aWindow.addGameObject(rec);

		}
		tokens.clear();
	}
}

//ToDo: Exercise 2: Create a function definition with this signature: ObjectType StringToObjectType(std::string& objectName)
//It should take a string reference and return an Object Type (the enum you created in Exercise 1)
//this call: StringToObjectType("Player") should return ObjectType::Player
ObjectType StringToObjectType(std::string& objectName)
{
	if (objectName == objectLabels::BALL)
	{
		return ObjectType::BALL;
	}
	else if (objectName == objectLabels::PLAYER)
	{
		return ObjectType::PLAYER;
	}
	else
	{
		return ObjectType::UNKNOWN;
	}
}

void splitString(const std::string& str, char delimiter, std::vector<std::string> &result)
{
    std::stringstream sStream(str);
    std::string token;
    while (std::getline(sStream, token, delimiter))
    {
        result.push_back(token);
    }
}