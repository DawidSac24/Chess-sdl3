#pragma once
#include "utils.h"

class piece
{
protected:
	color color_;

	int value_;

	bool has_moved_flag_ = false;

public:
	piece(const color color, const int value);

	virtual ~Piece() = default;

	color get_color() const { return color_; }
	int get_value() const { return value_; }
	bool has_moved() const { return has_moved_flag_; }


};

