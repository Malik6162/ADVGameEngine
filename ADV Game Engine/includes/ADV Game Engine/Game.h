#pragma once
#include "iostream"
#include "ADV Game Engine/Graphics/GraphicsEngine.h"


using namespace std;

class Game
{
public:
	//Get the game instance 

	static Game& GetGameInstance();
	// Destroy the game instance

	static void DestroyGameInstance();

	// it will start the game and it will load the window
	void Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight);
	 

private:
 
	Game();
	~Game();

	// Run the game loop
	void Run();
	 
	// Handle the game logic 
	void Update();

	// handle the game input
	void ProcessInput();
	
	// it will hamdle the 3D graphic on screen 
	void Draw();

	// it will close any thing in the game that needs to be closed

	void CloseGame();

	private:
  // this variable will ends the game 
		bool bIsGameOver;

		GraphicsEngine* Graphics;
};
