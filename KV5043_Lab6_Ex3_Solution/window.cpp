#include "window.h"
#include <iostream>
#include <SDL.h>

Window::Window()
{
	tickCount = 0;
	frameTime = 0.0f;
	deltaTimeMillis = 0;
	window = nullptr;
	renderer = nullptr;
	windowX = 0;
	windowY = 0;
	windowWidth = 0;
	windowHeight = 0;
	windowName = "";
	windowColour = { 255,255,255,255 };
	isRunning = true;
	showFrameRate = false;
	deltaTimeMillis = static_cast<Uint16>(round((1.0f / frameRate) * 1000));
	this->frameRate = frameRate;
	
	
}

void Window::Render()
{
	///////////////////////////////////
	//Render everything here
	///////////////////////////////////
	for (GameObject& obj : GameObjectsToRender)
	{
		SDL_Rect r;
		r.x = static_cast<int>(obj.xPosition);
		r.y = static_cast<int>(obj.yPosition);
		r.w = static_cast<int>(obj.width);
		r.h = static_cast<int>(obj.height);
		SDL_SetRenderDrawColor(
			renderer, 
			obj.colour.red,
			obj.colour.blue,
			obj.colour.green,
			obj.colour.alpha
		);
		SDL_RenderFillRect(renderer, &r);
	}
}

void Window::Run()
{
	if (!Initialise())
	{
		isRunning = false;
		std::cout << "Error initialising SDL..." << std::endl;
	}
	int count = 1;
	float aveFrameRate = 0.0f;
	while (isRunning)
	{
		///////////////////////////////////
		// set the frame rate
		///////////////////////////////////
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), tickCount + deltaTimeMillis)) {}
		frameTime = (SDL_GetTicks() - tickCount) / 1000.0f;
		//This is for debugging see Game programming architecture 8.5.5
		if (frameTime > (1.0f / frameRate) + 0.01)
		{
			frameTime = 1.0f / frameRate;
		}
		tickCount = SDL_GetTicks();
		
		if (showFrameRate)
		{
			 
			aveFrameRate += (1.0f / frameTime);
			count++;
			if (count >= 100)
			{
				std::cout << "frame rate = " << aveFrameRate/100 << std::endl;
				std::cout << "deltaTime = " << frameTime << std::endl;
				showFrameRate = false;
			}
			
		}
		/////////////////////////////////////
		//Process input here
		/////////////////////////////////////
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			
		}

		GameObject &player = GameObjectsToRender[0];
		GameObject &ball = GameObjectsToRender[1];

		// Check for collision between the BALL and PLAYER
		if (ball.type == ObjectType::BALL && player.type == ObjectType::PLAYER &&
			ball.xPosition < player.xPosition + player.width &&
			ball.xPosition + ball.width > player.xPosition &&
			ball.yPosition < player.yPosition + player.height &&
			ball.yPosition + ball.height > player.yPosition)
		{
			ball.OnCollision();  // Call OnCollision on the ball
		}
		
		//Every Object that has been added is updated here by calling it's Update() method
		for (GameObject& obj : GameObjectsToRender)
		{
			obj.Update(frameTime);
		}

		SDL_SetRenderDrawColor(renderer, windowColour.red, windowColour.green, windowColour.blue, windowColour.alpha);
		SDL_RenderClear(renderer);
		Render();
		SDL_RenderPresent(renderer);
	}
}

void Window::setName(const std::string& name)
{
	this->windowName = name;
}

void Window::setLocation(int x, int y)
{
	this->windowX = x;
	this->windowY = y;
}

void Window::setDimensions(int width, int height)
{
	this->windowWidth = width;
	this->windowHeight = height;
}

void Window::setWindowColour(Colour& colour)
{
	this->windowColour = colour;
}

void Window::addGameObject(GameObject& rect)
{
	GameObjectsToRender.push_back(rect);
}

Window::~Window()
{
	GameObjectsToRender.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::Initialise()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	// Initialise the keyboard engine
	if (HtKeyboard::instance.Initialise() == 0)
	{
		std::cerr << "Failed to initialise HtKeyboard in Initialise()." << std::endl;
		return false;
	}
	window = SDL_CreateWindow(windowName.c_str(), windowX, windowY, windowWidth, windowHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	return true;
}


