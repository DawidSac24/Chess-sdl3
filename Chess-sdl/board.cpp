#include "board.h"

#include "pawn.h"

board::board()
{
	setup_squares();
	setup_pieces();
	SDL_Log("board initialized");
}

board::~board()
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			delete board_[i][j];
		}
	}
}


void board::render_board_texture()
{
	texture_ = display_->load_texture(texture_path_);

	if (texture_ == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "loading board texture failed!");
	}

	const bool result = SDL_RenderTexture(display_->get_renderer(), texture_, nullptr, &rect_);

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
		return nullptr;
	}
	if (!board_[x][y]) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "board_[%d][%d] is nullptr\n", x, y);
		return nullptr;
	}


	return board_[x][y];
}

void board::render_all_textures()
{
	render_board_texture();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			board_[i][j]->render_texture();
		}
	}
	if (selected_square_)
	{
		SDL_SetRenderDrawBlendMode(display_->get_renderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(display_->get_renderer(), 255, 255, 0, 128); // Semi-transparent yellow

		show_possible_moves(get_possible_moves(selected_square_->get_x(), selected_square_->get_y()));

		SDL_SetRenderDrawColor(display_->get_renderer(), 0, 0, 0, 0);
		SDL_SetRenderDrawBlendMode(display_->get_renderer(), SDL_BLENDMODE_NONE);
	}
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
		board_[i][6]->set_piece(std::make_unique<pawn>(color::white));
	}
	for (int i = 0; i < size; ++i)
	{
		board_[i][1]->set_piece(std::make_unique<pawn>(color::black));
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

bool board::select_src_sqr(const int x, const int y)
{
	square* selected_square = get_square(x, y);

	if (selected_square && selected_square->get_piece())
	{
		selected_square_ = selected_square;
		return true;
	}
	return false;
}

bool board::select_dst_sqr(const int x, const int y)
{
	if (move_piece(selected_square_->get_x(), selected_square_->get_y(), x, y))
	{
		selected_square_ = nullptr;
		return true;
	}

	return false;
}

bool board::move_piece(const int src_x, const int src_y, const int dest_x, const int dest_y) const
{
	const std::vector<square*> possible_moves = get_possible_moves(src_x, src_y);

	const square* dest_square = get_square(dest_x, dest_y);

	for (const square* square : possible_moves)
	{
		if (square == dest_square)
		{
			board_[dest_x][dest_y]->move_piece_from(*board_[src_x][src_y]);
			return true;
		}
	}
	return false;
}

void board::show_possible_moves(const std::vector<square*> squares) const
{
	for (const square* square : squares)
	{
		const float x = static_cast<float>(square->get_x());
		const float y = static_cast<float>(square->get_y());

		SDL_FRect rect = { x * square_size_ + 256, y * square_size_ + 96, square_size_, square_size_ };

		SDL_RenderFillRect(display_->get_renderer(), &rect);
	}
}
