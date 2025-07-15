#include "game.h"

#include <iostream>

game* game::instance_ = nullptr;

game* game::get_instance()
{
	if (instance_ == nullptr) {
		instance_ = new game();
	}
	return instance_;
}

game::game() : board_rect_(board_.get_rect())
{
	game_state_ = init;
}

void game::lunch_game()
{
	render_all_textures();
	players_turn_ = color::white;
	game_state_ = ongoing;
}

void game::handle_event(const SDL_Event& e)
{
	if (e.type != SDL_EVENT_MOUSE_BUTTON_DOWN ||
		e.button.button != SDL_BUTTON_LEFT)
		return;

	// Raw mouse position
	const int mx = static_cast<int>(e.button.x);
	const int my = static_cast<int>(e.button.y);

	const coordinates coordinates = board_.get_coordinates(mx, my);

	std::cout << "\n file: " << coordinates.file << "\n rank: " << coordinates.rank;

	if (board_.on_board(coordinates))
	{
		std::cout << "\n file: " << coordinates.file << "\n rank: " << coordinates.rank << std::endl;
		handle_piece_movement(coordinates);
	}

	render_all_textures();
}

void game::handle_piece_movement(const coordinates coordinates)
{
	const square* selected_square = board_.get_selected_sqr();

	if (!selected_square)
	{
		if (!board_.select_src_sqr(coordinates, players_turn_))
		{
			std::cout << "failed to select piece";
		}
	}
	else
	{
		if (board_.select_dst_sqr(coordinates))
		{
			switch_players_turn();
		}
		else
		{
			std::cout << "failed to move piece";
			board_.unselect_square();
		}
	}
}

void game::render_all_textures()
{
	SDL_RenderClear(display_->get_renderer());
	board_.render_all_textures();
	SDL_RenderPresent(display_->get_renderer());
}
