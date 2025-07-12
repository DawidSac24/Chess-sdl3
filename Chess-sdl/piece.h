#pragma once
#include "SDL3/SDL.h"
#include <stdexcept>
#include <vector>
#include "display.h"
#include "utils.h"

class board;
class square;

class piece
{
protected:
	color color_;
	int value_;
	bool has_moved_flag_ = false;

	display* display_ = display::get_instance();

	SDL_Texture* texture_ = nullptr;
	const char* texture_path_ = nullptr;
public:
	piece(const color color, const int value);

	virtual ~piece() = default;

	color get_color() const { return color_; }
	int get_value() const { return value_; }
	bool has_moved() const { return has_moved_flag_; }
	SDL_Texture* get_texture();

	virtual const char* to_string() = 0;

	virtual const std::vector<square*> get_possible_moves(const int x, const int y, square* const board[8][8]) const = 0;
};
