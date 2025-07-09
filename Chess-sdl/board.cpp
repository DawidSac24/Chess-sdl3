#include "board.h"

#include "pawn.h"

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

	if (texture_ == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "loading board texture failed!");
	}

	SDL_RenderClear(display_->get_renderer());
	const bool result = SDL_RenderTexture(display_->get_renderer(), texture_, nullptr, &dest_rect_);
	SDL_RenderPresent(display_->get_renderer());

	if (!result)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "rendering board texture failed!");
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
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; ++j)
		{
			board_[i][j] = new square(i, j);
		}
	}
}

void board::setup_pieces()
{
	for (int i = 0; i < size; ++i)
	{
	}
}

std::vector<square*> board::get_possible_moves(const int x, const int y) const
{
	if (x > size || x < 0 || y > size || y < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "square request out of bounds\n");
		throw std::invalid_argument("square request out of bounds");
	}
	if (board_[x][y]->get_piece() == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "square request missing piece\n");
		throw std::invalid_argument("square request missing piece");
	}

	return board_[x][y]->get_piece()->get_possible_moves(x, y, board_);
}