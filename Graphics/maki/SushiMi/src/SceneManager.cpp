#include "../Game Object/Player.h"
#include "Window.h"

//R key for restart
void restartLevel()
{
		player->~Player(); // destroy player
		player = new Player(); //respawn player to start position

	
}


