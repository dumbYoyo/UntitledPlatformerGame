#include "Engine/Core/Scene.h"
#include "Game.h"

int main()
{
	Scene* game = new Game();
	game->Run();
	delete game;

	return 0;
}