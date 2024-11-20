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

enum class ObjectType 
{
	UNKNOWN,
	PLAYER,
	BALL
};

class GameObject
{
	ObjectType m_type;
	float m_xPosition;
	float m_yPosition;
	float m_width;
	float m_height;
	Colour m_colour{ 0,255,0,255 };
	Vec2D m_velocity{ 0.0f ,0.0f };

public:
	GameObject()
	{
		m_type = ObjectType::UNKNOWN;
		m_xPosition = 0.0f;
		m_yPosition = 0.0f;
		m_width = 0.0f;
		m_height = 0.0f;
		m_colour = { 255, 255, 255, 255 };
		m_velocity = { 0.0f, 0.0f };
	}

	GameObject(ObjectType type, float x, float y, float w, float h, Colour col, Vec2D vel):
		m_type(type), m_xPosition(x), m_yPosition(y), m_width(w), m_height(h), m_colour(col),
		m_velocity(vel)
	{}

	ObjectType getType() const
	{
		return m_type;
	}

	float getXPosition() const
	{
		return m_xPosition;
	}

	float getYPosition() const
	{
		return m_yPosition;
	}

	float getWidth() const
	{
		return m_width;
	}

	float getHeight() const
	{
		return m_height;
	}

	Colour getColour() const
	{
		return m_colour;
	}

	void Update(double frameTime)
	{
		
		if (HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_UP) && m_type == ObjectType::PLAYER)
		{
			m_velocity.y = m_velocity.y - 200;
		}
		else if (HtKeyboard::instance.NewKeyPressed(SDL_SCANCODE_DOWN) && m_type == ObjectType::PLAYER)
		{
			m_velocity.y = m_velocity.y + 200;
		}

		m_xPosition = m_xPosition + m_velocity.x * static_cast<float>(frameTime);
		m_yPosition = m_yPosition + m_velocity.y * static_cast<float>(frameTime);

		if (m_type == ObjectType::PLAYER)
		{
			m_yPosition = m_yPosition < 0 ? 0 : m_yPosition;
			m_yPosition = m_yPosition > 550 ? 550 : m_yPosition;
		}
		
		if (m_type == ObjectType::BALL)
		{
			m_velocity.y = m_yPosition < 0 || m_yPosition > 590 ? -m_velocity.y : m_velocity.y;
			m_velocity.x = m_xPosition > 800 ? -m_velocity.x : m_velocity.x;
		}
		
	}

	
	void OnCollision()
	{
		if (m_type == ObjectType::BALL)
		{
			m_velocity.x = -m_velocity.x;
		}
	}



};

class Window
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
