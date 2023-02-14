#include "ADV Game Engine/Game.h"
 

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
	Graphics = new GraphicsEngine();
 
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
	cout << "Game Over..." << endl;
}

void Game::Run()
{
	while (!bIsGameOver)
	{
		ProcessInput();

		Update();

		Draw();

	}

	    CloseGame();
}

void Game::Update()
{
	// handle logic
}

void Game::ProcessInput()
{
	// handle input
}

void Game::Draw()
{
	// draw graphics to screen
}

void Game::CloseGame()
{

}
