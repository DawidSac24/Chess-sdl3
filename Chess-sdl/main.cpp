#include <iostream>

#include "./game.h"

int main(int argc, char* argv[])
{
	try
	{
		game* game = game::get_instance();

		game->lunch_game();

		while (game->get_state() == game_state::ongoing)
		{

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				game->handle_event(event);
			}
		}
	}
	catch (int error_code) {
		std::cout << "Error occurred: " << error_code;
	}

	return 0;
}
