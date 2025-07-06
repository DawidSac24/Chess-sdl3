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

	game();
public:
	static game* get_instance();

	~game();

	explicit game(display& other) = delete;
	void operator=(const game&) = delete;


};
