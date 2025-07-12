#pragma once
#include <vector>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"


class square;

class display
{
private:
	static display* instance_;

	const int width_ = 1280;
	const int height_ = 960;

	SDL_Window* window_;
	SDL_Renderer* renderer_;

	display();

public:
	static display* get_instance();

	~display();

	display(display& other) = delete;
	void operator=(const display&) = delete;

	SDL_Renderer* get_renderer() const;

	SDL_Texture* load_texture(const char* path) const;
};
