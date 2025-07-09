#pragma once

#include <memory>

#include "piece.h"

class square
{
private:
	const int x_;
	const int y_;

	std::unique_ptr<piece> piece_ = nullptr;
public:
	square(const int x, const int y);

	int get_x() const { return x_; }
	int get_y() const { return y_; }
	std::unique_ptr<piece>& get_piece() { return piece_; }
};
