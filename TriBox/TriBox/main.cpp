#include "GameSystem.h"

int main()
{
	GameSystem& game = GameSystem::GameInstance();

	game.Run();

	return 0;
}
