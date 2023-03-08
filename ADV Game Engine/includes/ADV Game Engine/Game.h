#pragma once
  #include "ADV Game Engine/CoreMinimal.h"


 

class Game
{
public:
	//Get the game instance 

	static Game& GetGameInstance();
	// Destroy the game instance

	static void DestroyGameInstance();

	// it will start the game and it will load the window
	void Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight);
	 
	// Get percise delta time 
	double GetDeltaTime()	{	return DeltaTime;	}

	// get less percise delta time 
	double GetFDeltaTime() {     return static_cast<float>(DeltaTime);    }
	 


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

		GraphicEnginePtr  Graphics;

		// Time between each frame 
		double DeltaTime;


		// temporary mesh variables 

		MeshPtr Tri;
		MeshPtr Poly;
	 
};
