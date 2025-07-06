#include "game.h"
#include "display.h"

int main(int argc, char* argv[])
{
	game* game = game::get_instance();

	SDL_Delay(3000);

	return 0;
}