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

game::game()
{
	game_state_ = init;
}

game::~game()
{
}

void game::lunch_game()
{
	render_all_textures();
	game_state_ = ongoing;
	board_rect_ = board_.get_rect();
}

void game::handle_event(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		float x = event.button.x;
		float y = event.button.y;

		if (x >= board_rect_->x && x <= board_rect_->x + board_rect_->w &&
			y >= board_rect_->y && y <= board_rect_->y + board_rect_->h) {
			SDL_Log("Board clicked!");

			x = (x - (board_rect_->x + 8)) / square_size;
			y = (y - (board_rect_->y + 8)) / square_size;

			selected_square_ = board_.get_square(x, y);
			std::cout << "selected square : (" << selected_square_->get_x() << "," << selected_square_->get_y() << ")";
			render_all_textures();
		}
	}
}

void game::render_all_textures()
{
	SDL_RenderClear(display_->get_renderer());
	board_.render_all_textures();
	SDL_RenderPresent(display_->get_renderer());
}

bool game::move_piece(const int src_x, const int src_y, const int dest_x, const int dest_y)
{
	const std::vector<square*> possible_moves = board_.get_possible_moves(src_x, src_y);

	for (const square* square : possible_moves)
	{
		if (square == board_.get_square(dest_x, dest_y))
		{
			board_.move_piece(src_x, src_y, dest_x, dest_y);
			return true;
		}
	}

	return false;
}
