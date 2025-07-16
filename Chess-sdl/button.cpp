#include "button.h"

button::button(const raw_pos position, const raw_pos size) : position_(position), size_(size)
{
	rect_ = { position.x,position.y, size.x, size.y };

}

bool button::is_clicked(const SDL_Event& event) const
{
	if (event.type != SDL_EVENT_MOUSE_BUTTON_DOWN || event.button.button != SDL_BUTTON_LEFT)
		return false;

	// Raw mouse position
	const int mx = static_cast<int>(event.button.x);
	const int my = static_cast<int>(event.button.y);

	if (mx >= position_.x && my >= position_.y && mx < position_.x + size_.x && my < position_.y + size_.y)
	{
		return true;
	}
	return false;
}
