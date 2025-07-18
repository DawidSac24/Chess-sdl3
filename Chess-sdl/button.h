#pragma once

#include "SDL3_ttf/SDL_ttf.h"
#include <string>

#include "display.h"

class button
{
private:
	raw_pos position_;
	raw_pos size_;

	SDL_FRect rect_;
	SDL_Color color_;
	SDL_Color hover_color_;
	SDL_Color pressed_color_;

	bool is_hovered_;
	bool is_pressed_;
public:
	explicit button(const raw_pos position, const raw_pos size);

	inline raw_pos get_position() const { return position_; }

	bool is_clicked(const SDL_Event& event) const;
};

class Button {
public:
	Button(SDL_Renderer* renderer, const std::string& text, SDL_Rect rect, TTF_Font* font);
	~Button();

	void render(SDL_Renderer* renderer);
	bool isClicked(int x, int y) const;

private:
	SDL_Rect rect_;
	std::string text_;
	SDL_Color textColor_;
	SDL_Color backgroundColor_;
	SDL_Texture* textTexture_;
	TTF_Font* font_;
};
