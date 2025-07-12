#pragma once

#include "SDL3/SDL.h"
#include <stdexcept>
#include <vector>
#include "texture_paths.h"
#include "display.h"

class square;

class board
{
private:
	static constexpr int size = 8;

	square* board_[size][size];

	square* selected_square_ = nullptr;

	display* display_ = display::get_instance();

	float height_ = 784;
	float width_ = 784;
	float x_ = 248;
	float y_ = 88;
	float square_size_ = 96;

	SDL_Texture* texture_;
	SDL_FRect rect_ = { x_,y_, height_, width_ };
	const char* texture_path_ = board_texture;
	void render_board_texture();
public:
	board();
	~board();

	square* get_square(const int x, const int y) const;
	square* get_selected_sqr() const { return selected_square_; };
	SDL_FRect* get_rect() { return &rect_; }

	void render_all_textures();

	void setup_squares();
	void setup_pieces();

	std::vector<square*> get_possible_moves(const int x, const int y) const;
	bool select_src_sqr(const int x, const int y);
	bool select_dst_sqr(const int x, const int y);
	bool move_piece(const int src_x, const int src_y, const int dest_x, const int dest_y) const;
	void show_possible_moves(const std::vector<square*> squares) const;
};

