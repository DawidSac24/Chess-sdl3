#pragma once

#include <memory>

#include "piece.h"

class square
{
private:
	const int x_;
	const int y_;

	std::unique_ptr<piece> piece_ = nullptr;

	display* display_ = display::get_instance();
	float length_ = 96;
	SDL_FRect rect_;
public:
	square(const int x, const int y);

	int get_x() const { return x_; }
	int get_y() const { return y_; }
	std::unique_ptr<piece>& get_piece() { return piece_; }

	bool render_texture() const;

	void set_piece(std::unique_ptr<piece> new_piece) {
		piece_ = std::move(new_piece);
	}

	void move_piece_from(square& dest);
};
