#pragma once

#include "board.h"
#include "display.h"

enum game_state
{
	init,
	ongoing,
	finished
};

class game
{
private:
	static game* instance_;

	game_state game_state_;

	board board_;
	SDL_FRect* board_rect_;

	square* selected_square_ = nullptr;
	const float square_size = 96;

	display* display_ = display::get_instance();

	game();
public:
	static game* get_instance();

	~game();

	explicit game(display& other) = delete;
	void operator=(const game&) = delete;

	game_state get_state() const { return game_state_; }

	void lunch_game();
	void handle_event(const SDL_Event& event);

	void render_all_textures();

	bool move_piece(const int src_x, const int src_y, const int dest_x, const int dest_y);
};
