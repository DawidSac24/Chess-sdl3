#pragma once
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

	board board_;
	SDL_FRect* board_rect_;

	float square_size_ = 96;

	display* display_ = display::get_instance();

	game();
public:
	static game* get_instance();

	inline explicit game(display& other) = delete;
	inline void operator=(const game&) = delete;

	inline game_state get_state() const { return game_state_; }

	void lunch_game();
	void handle_event(const SDL_Event& event);
	void handle_piece_movement(const coordinates coordinates);

	void render_all_textures();
};
