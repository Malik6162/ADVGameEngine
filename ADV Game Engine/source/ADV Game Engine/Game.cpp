#include "ADV Game Engine/Game.h"
#include "ADV Game Engine/Graphics/GraphicsEngine.h"
#include "ADV Game Engine/Graphics/Mesh.h"
  

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
		ShaderPtr TextureShader  = Graphics->CreateShader({

			L"Game/Shaders/TextureShader/TextureShader.svert", 
			L"Game/Shaders/TextureShader/TextureShader.sfrag "
			
			});
         // Create textures 
		TexturePtr TConcrete =  Graphics->CreateTexture("Game/Textures/ConcreteFloor.jpg");
		TexturePtr TGrid = Graphics->CreateTexture("Game/Textures/ColourGrid.jpg");


		 
		// craete a meshes 
		Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TConcrete} );
		Tri = Graphics->CreateSimpleMeshShape(GeometricShapes::Triangle, TextureShader, { TGrid });

		Poly->Transform.Location.x = 0.5f;
		Tri->Transform.Location.x = -0.5f;

		Poly->Transform.Scale = Vector3(0.7f);
		Tri->Transform.Scale = Vector3(0.7f);

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
	// set delta time first alawys 
	static double LastFrameTime = 0.0f;

	// set current time since the game has passed 
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	// find the time difference between first and last frame 

	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	// set delta time as seconds 

	DeltaTime = NewDeltaTime / 1000.0;
	// update the last frame time for the next update 
	LastFrameTime = CurrentFrameTime;
	
 
	// it will  handle logic
	Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();

	static int MoveUp = 1.0f;

	if (Tri->Transform.Location.y > 0.5f)
	{
		MoveUp = -1.0f;
	}

	if (Tri->Transform.Location.y < -0.5f)
	{
		MoveUp = 1.0f;

	}

	Tri->Transform.Location.y += (2.0f * MoveUp) * GetFDeltaTime();
 
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
