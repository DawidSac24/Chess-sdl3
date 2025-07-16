#pragma once
#include "display.h"

class button
{
private:
	raw_pos position_;
	raw_pos size_;

	SDL_FRect rect_;
	SDL_Color hover_color;
	SDL_Color pressed_color;

	bool is_hovered;
	bool is_pressed;
public:
	explicit button(const raw_pos position, const raw_pos size);

	inline raw_pos get_position() const { return position_; }

	bool is_clicked(const SDL_Event& event) const;
};

