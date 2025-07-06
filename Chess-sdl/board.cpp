#include "board.h"

board::board()
{
	render_texture();
	setup_squares();
	setup_pieces();
	SDL_Log("board initialized");
}

void board::render_texture()
{
	texture_ = display_->load_texture(texture_path_);

	SDL_RenderClear(display_->get_renderer());
	const bool result = SDL_RenderTexture(display_->get_renderer(), texture_, nullptr, &dest_rect_);
	SDL_RenderPresent(display_->get_renderer());

	if (!result)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "board texture render failed!");
	}
}

square* board::get_square(const int x, const int y) const
{
	if (x > size || x < 0 || y > size || y < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "square request out of bounds\n");
		throw std::invalid_argument("square request out of bounds");
	}

	return board_[x][y];
}

void board::setup_squares()
{

}

void board::setup_pieces()
{
}
