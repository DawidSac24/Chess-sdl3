#include "game.h"

int main(int argc, char* argv[])
{
	game* game = game::get_instance();

	game->lunch_game();

	while (game->get_state() == game_state::ongoing)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			game->handle_event(event); // Delegate event handling
		}
	}
	return 0;
}
