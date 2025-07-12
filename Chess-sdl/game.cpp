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

void game::handle_event(const SDL_Event& e)
{
	if (e.type != SDL_EVENT_MOUSE_BUTTON_DOWN ||
		e.button.button != SDL_BUTTON_LEFT)
		return;

	// Raw mouse position (integers are easier to reason about)
	const int mx = static_cast<int>(e.button.x);
	const int my = static_cast<int>(e.button.y);

	// Inner top‑left corner of the 8×8 grid (frame is 8 px thick)
	const int inner_left = static_cast<int>(board_rect_->x) + 8;
	const int inner_top = static_cast<int>(board_rect_->y) + 8;
	const int inner_size = 8 * square_size_;           // 8 squares wide

	// Reject anything outside the grid *strictly* (no ≤)
	if (mx < inner_left || mx >= inner_left + inner_size ||
		my < inner_top || my >= inner_top + inner_size)
		return;

	// Convert to board coordinates
	const int file = (mx - inner_left) / square_size_;   // 0 … 7
	const int rank = (my - inner_top) / square_size_;   // 0 … 7

	// Sanity check (optional, keeps you safe if sizes ever change)
	if (file < 0 || file >= 8 || rank < 0 || rank >= 8)
		return;

	handle_piece_movement(file, rank);   // pass ints, not floats
	render_all_textures();
}

void game::handle_piece_movement(const int x, const int y)
{
	const square* selected_square = board_.get_selected_sqr();

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
