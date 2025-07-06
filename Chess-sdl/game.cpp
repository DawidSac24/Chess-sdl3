#include "game.h"

game* game::instance_ = nullptr;

game* game::get_instance()
{
	if (instance_ == nullptr) {
		instance_ = new game();
	}
	return instance_;
}

game::game()
{
	game_state_ = init;
	game_state_ = ongoing;
}

game::~game()
{
}
