#include "./game.h"
#include "SDL3_ttf/SDL_ttf.h"

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
	TTF_Font* font = TTF_OpenFont("./assets/Varela/Varela-Regular.fon", 12);

	return 0;
}
