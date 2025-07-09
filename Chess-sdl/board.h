#pragma once

#include "SDL3/SDL.h"
#include <stdexcept>
#include <vector>

#include "display.h"
#include "square.h"

class square;

class board
{
private:
	static constexpr int size = 7;

	square* board_[size][size];

	display* display_ = display::get_instance();

	float height_ = 172;
	float width_ = 172;

	SDL_Texture* texture_;
	SDL_FRect dest_rect_ = { 10,10, height_, width_ };
	const char* texture_path_ = "C:/Users/majst/Documents/dev-doc/Projects/Chess-sdl/Chess-sdl/assets/Board/chessboard.bmp";

	void render_texture();

public:
	board();
	~board() = default;

	square* get_square(const int x, const int y) const;

	void setup_squares();
	void setup_pieces();

	std::vector<square*> get_possible_moves(const int x, const int y) const;
};

