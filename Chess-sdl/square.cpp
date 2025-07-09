#include "square.h"

square::square(const int x, const int y) : x_(x), y_(y)
{
	// adding the board's starting position
	float position_x = 256 + x * length_;
	float position_y = 96 + y * length_;

	rect_ = { position_x, position_y, length_, length_ };
}

bool square::render_texture() const
{
	if (piece_)
	{
		SDL_RenderTexture(display_->get_renderer(), piece_->get_texture(), nullptr, &rect_);
		return true;
	}
	return false;
}

void square::move_piece_from(square& dest)
{
	if (!dest.get_piece())
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "No pieces found in the src coordinates\n");
		throw std::exception("No pieces found in the src coordinates\n");
	}

	piece_ = std::move(dest.piece_);
}
