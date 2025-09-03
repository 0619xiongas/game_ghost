#include <iostream>
#include "core/GameEngine.h"

int main(int, char**) 
{
	if (!g_GameEngine->Init("test,", 1280, 720))
	{
		std::cout << "g_GameEngine init failed" << std::endl;
		return -1;
	}
	g_GameEngine->Run();
	asSingleton<GameEngine>::delete_instance();
	return 0;
}