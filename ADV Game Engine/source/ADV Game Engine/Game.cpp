#include "ADV Game Engine/Game.h"
#include "ADV Game Engine/Graphics/GraphicsEngine.h"


Game& Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();
	delete GameInstance;
}

void Game::Start(const char* WTitle, bool bFullScreen, int WWidth, int WHeight)
{
	Graphics = make_shared<GraphicsEngine>();
 
	if (!Graphics->InitGE(WTitle, bFullScreen, WWidth, WHeight))
	{
		bIsGameOver = true;
	}



	Run();
}

Game::Game()
{
	cout << "Game Initialised..." << endl;
	Graphics = nullptr;
	bIsGameOver = false;
}

Game::~Game()
{
	// this will destroy the graphics
	Graphics = nullptr;
	cout << "Game Over..." << endl;
}

void Game::Run()
{
	if (!bIsGameOver)
	{
		Graphics->CreateShader({

			L"Game/Shaders/SimpleShader/SimpleShader.svert", 
			L"Game/Shaders/SimpleShader/SimpleShader.sfrag "
			
			});

		 



		// craete a triangel 
		Graphics->CreatVAO(GeometricShapes::Triangle);
		Graphics->CreatVAO(GeometricShapes::Polygon);
	}


	// as long as the game is not over run the loop 

	while (!bIsGameOver)
	{
		// making sure the process what the user has done 
		ProcessInput();

		// apply the logic base on the game inputs and the game logics 
		Update();

		// render the screen 
		Draw();

	}
	// claen the game after it ends 
	    CloseGame();
}

void Game::Update()
{
	// handle logic
}

void Game::ProcessInput()
{
 	SDL_Event PollEvent;

	while (SDL_PollEvent(&PollEvent))
	{
		switch (PollEvent.type)
		{
		  case SDL_QUIT:

		     bIsGameOver = true;
		  break;

		 default:
			  break;
		}
	}

}

void Game::Draw()
{
	// draw graphics to screen
	Graphics->Draw();
}

void Game::CloseGame()
{

}
