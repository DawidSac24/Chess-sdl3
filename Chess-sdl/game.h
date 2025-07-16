#pragma once
#include "utils.h"
#include "./display.h"
#include "./board.h"

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
	color players_turn_ = color::white;

	board board_;
	SDL_FRect* board_rect_;

	display* display_ = display::get_instance();

	game();
public:
	static game* get_instance();

	inline explicit game(display& other) = delete;
	inline void operator=(const game&) = delete;

	inline game_state get_state() const { return game_state_; }
	inline void switch_players_turn()
	{
		if (players_turn_ == color::white)
		{
			players_turn_ = color::black;
		}
		else
		{
			players_turn_ = color::white;
		}
	}

	void lunch_game();
	void handle_event(const SDL_Event& event);
	void handle_piece_movement(const coordinates coordinates);

	void render_all_textures();
};
