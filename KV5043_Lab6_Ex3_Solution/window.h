#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include "HtKeyboard.h"

struct Vec2D
{
	float x;
	float y;
};

struct Colour
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;
};

//ToDo: Exercise 1: Create an enum named ObjectType with UNKNOWN, PLAYER and BALL 
enum class ObjectType 
{
	UNKNOWN,
	PLAYER,
	BALL
};

//ToDo: Exercise 2: Create a struct named GameObject with the following member variables to store the following: objType (ObjectType), x position (float),
// y position (float), width (float), height (float), colour using the above Colour struct and velocity using the above Vec2D struct, use list initialisation to initialise the colour to white and the velocity to 0.
struct GameObject
{
	ObjectType type;
	float xPosition;
	float yPosition;
	float width;
	float height;
	Colour colour{ 0,255,0,255 };
	Vec2D velocity{ 0.0f ,0.0f };

	//ToDo: Create a constructor that initialises all the member variables
	GameObject(ObjectType theType, float x, float y, float w, float h, Colour col, Vec2D vel)
	{
		type = theType;
		xPosition = x;
		yPosition = y;
		width = w;
		height = h;
		colour = col;
		velocity = vel;
	}

	//ToDo: create an Update(double frameTime) method that updates the position based on adding the velocity
	// and frameTime to the current position 
	void Update(double frameTime)
	{
		//ToDo: Use HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_UP) to move the player paddle up
		if (HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_UP) && type == ObjectType::PLAYER)
		{
			velocity.y = velocity.y - 200;
		}
		//ToDo: Use HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_DOWN) to move the player paddle down
		else if (HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_DOWN) && type == ObjectType::PLAYER)
		{
			velocity.y = velocity.y + 200;
		}

		xPosition = xPosition + velocity.x * static_cast<float>(frameTime);
		yPosition = yPosition + velocity.y * static_cast<float>(frameTime);

		//ToDo: make sure the player paddle can't got outside the top or bottom boundaries
		if (type == ObjectType::PLAYER)
		{
			yPosition = yPosition < 0 ? 0 : yPosition;
			yPosition = yPosition > 550 ? 550 : yPosition;
		}
		//ToDo: make sure the ball can't got outside the top, bottom or right boundaries
		if (type == ObjectType::BALL)
		{
			velocity.y = yPosition < 0 || yPosition > 590 ? -velocity.y : velocity.y;
			velocity.x = xPosition > 800 ? -velocity.x : velocity.x;
		}
		
	}

	//ToDo: Create an on collision method that only works for the ball
	void OnCollision()
	{
		if (type == ObjectType::BALL)
		{
			velocity.x = -velocity.x;
		}
	}

};

struct Window
{
public:
	Window();
	void Run();
	void setName(const std::string& name);
	void setLocation(int x, int y);
	void setDimensions(int width, int height);
	void setWindowColour(Colour &colour);
	void addGameObject(GameObject& object);
	bool showFrameRate;
	~Window();
	
private:
	bool Initialise();
	void Render();
	bool isRunning;
	Uint32 tickCount;
	Uint16 frameRate;
	float frameTime;
	Uint16 deltaTimeMillis;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowX;
	int windowY;
	int windowWidth;
	int windowHeight;
	std::string windowName;
	Colour windowColour;

	//A vector of Game Objects
	std::vector<GameObject> GameObjectsToRender;
};
