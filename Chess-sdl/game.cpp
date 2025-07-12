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
	game_state_ = ongoing;
}

void game::handle_event(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		float x = event.button.x;
		float y = event.button.y;

		if (x >= board_rect_->x && x <= board_rect_->x + board_rect_->w &&
			y >= board_rect_->y && y <= board_rect_->y + board_rect_->h) {

			x = (x - (board_rect_->x + 8)) / square_size_;
			y = (y - (board_rect_->y + 8)) / square_size_;

			square* selected_square = board_.get_selected_sqr();

			if (!selected_square)
			{
				if (!board_.select_src_sqr(x, y))
				{
					std::cout << "failed to select piece";
				}
			}
			else
			{
				if (!board_.select_dst_sqr(x, y))
				{
					std::cout << "failed to move piece";
				}
			}
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