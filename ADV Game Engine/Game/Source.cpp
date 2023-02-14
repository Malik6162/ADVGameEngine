
#include "ADV Game Engine/Game.h"

int main( int argc, char** argv)
{
	Game::GetGameInstance().Start("ADV Game Engine", false, 1200, 720);

	Game::DestroyGameInstance();

	return 0;
}