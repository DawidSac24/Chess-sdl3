#pragma once

#include "SDL3/SDL.h"
#include <stdexcept>
#include <vector>
#include <iostream>
#include "display.h"

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"

class square;

struct coordinates
{
	int file;
	int rank;
};

struct raw_pos
{
	float x;
	float y;
};

class board
{
private:
	static constexpr int size = 8;

	square* board_[size][size];

	square* selected_square_ = nullptr;

	display* display_ = display::get_instance();

	static constexpr float height = 784;
	static constexpr float width = 784;
	static constexpr float x = 100;
	static constexpr float y = 88;
	static constexpr int offset = 8;
	static constexpr float square_size = 96;

	SDL_Texture* texture_;
	SDL_FRect rect_ = { x,y, height, width };
	const char* texture_path_ = "./assets/board.png";

	void render_board_texture();

	void setup_squares();
	void setup_pieces();
public:
	board();
	~board();

	static inline bool on_board(const int x, const int y) noexcept
	{
		return x >= 0 && x < 8 && y >= 0 && y < 8;
	}

	static inline bool on_board(const coordinates coordinates) noexcept
	{
		return on_board(coordinates.file, coordinates.rank);
	}

	square* get_square(const int x, const int y) const;
	inline 	square* get_selected_sqr() const { return selected_square_; }
	inline void unselect_square() { selected_square_ = nullptr; }
	SDL_FRect* get_rect() { return &rect_; }
	static coordinates get_coordinates(const int x, const int y);
	static raw_pos get_raw_position(const int file, const int rank);

	void render_all_textures();

	std::vector<square*> get_possible_moves(const int x, const int y) const;
	bool select_src_sqr(const coordinates coordinates, color players_turn);
	bool select_dst_sqr(const coordinates coordinates);
	bool move_piece(const int src_x, const int src_y, const int dest_x, const int dest_y) const;
	void show_possible_moves(const std::vector<square*>& squares) const;
};
