#include "board.h"

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

coordinates board::get_coordinates(const int raw_x, const int raw_y)
{
	coordinates result = { -1, -1 };
	const int inner_left = static_cast<int>(b_raw_pos.x) + b_offset;
	const int inner_top = static_cast<int>(b_raw_pos.y) + b_offset;
	const int inner_size = size * square_size;           // 8 squares wide

	// Reject anything outside the grid *strictly* (no ≤)
	if (raw_x < inner_left || raw_x >= inner_left + inner_size ||
		raw_y < inner_top || raw_y >= inner_top + inner_size)
	{
		return result;
	}

	const int file = (raw_x - inner_left) / square_size;   // 0 … 7
	const int rank = 8 - (raw_y - inner_top) / square_size;

	result = { file ,rank };

	return result;
}

raw_pos board::get_raw_position(const int file, const int rank)
{
	const int inner_left = static_cast<int>(b_raw_pos.x) + b_offset;
	const int inner_top = static_cast<int>(b_raw_pos.y) + b_offset;

	const float px = file * square_size + inner_left;
	const float py = (7 - rank) * square_size + inner_top;

	return { px, py };
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

		show_possible_moves(get_possible_moves(selected_square_->get_x(), selected_square_->get_y()));

		SDL_SetRenderDrawColor(display_->get_renderer(), 0, 0, 0, 0);
		SDL_SetRenderDrawBlendMode(display_->get_renderer(), SDL_BLENDMODE_NONE);
	}
}

void board::setup_squares()
{
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = size - 1; j >= 0; j--)
		{
			board_[i][j] = new square(i, j);
		}
	}
}

void board::setup_pieces()
{
	for (int i = size - 1; i >= 0; i--)
	{
		board_[i][1]->set_piece(std::make_unique<pawn>(color::white));
	}
	board_[0][0]->set_piece(std::make_unique<rook>(color::white));
	board_[7][0]->set_piece(std::make_unique<rook>(color::white));

	board_[1][0]->set_piece(std::make_unique<knight>(color::white));
	board_[6][0]->set_piece(std::make_unique<knight>(color::white));

	board_[2][0]->set_piece(std::make_unique<bishop>(color::white));
	board_[5][0]->set_piece(std::make_unique<bishop>(color::white));

	for (int i = size - 1; i >= 0; i--)
	{
		board_[i][6]->set_piece(std::make_unique<pawn>(color::black));
	}
	board_[0][7]->set_piece(std::make_unique<rook>(color::black));
	board_[7][7]->set_piece(std::make_unique<rook>(color::black));

	board_[1][7]->set_piece(std::make_unique<knight>(color::black));
	board_[6][7]->set_piece(std::make_unique<knight>(color::black));

	board_[2][7]->set_piece(std::make_unique<bishop>(color::black));
	board_[5][7]->set_piece(std::make_unique<bishop>(color::black));
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

bool board::select_src_sqr(const coordinates coordinates, color players_turn)
{
	square* selected_square = get_square(coordinates.file, coordinates.rank);

	if (selected_square && selected_square->get_piece()/* && selected_square->get_piece()->get_color() == players_turn*/)
	{
		selected_square_ = selected_square;
		return true;
	}
	return false;
}

bool board::select_dst_sqr(const coordinates coordinates)
{
	if (move_piece(selected_square_->get_x(), selected_square_->get_y(), coordinates.file, coordinates.rank))
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
		std::cout << "\n possible move square.x = " << square->get_x() << "\n possible move square.y = " << square->get_y();
		if (square == dest_square)
		{
			board_[dest_x][dest_y]->move_piece_from(*board_[src_x][src_y]);
			return true;
		}
	}
	return false;
}

void board::show_possible_moves(const std::vector<square*>& squares) const
{
	SDL_SetRenderDrawBlendMode(display_->get_renderer(), SDL_BLENDMODE_BLEND);

	for (const square* square : squares)
	{
		if (square->get_piece())
		{
			SDL_SetRenderDrawColor(display_->get_renderer(), 255, 0, 0, 128); // Semi-transparent red
		}
		else
		{
			SDL_SetRenderDrawColor(display_->get_renderer(), 255, 255, 0, 128); // Semi-transparent yellow
		}
		const float file = static_cast<float>(square->get_x());
		const float rank = static_cast<float>(square->get_y());

		const raw_pos raw_pos = get_raw_position(file, rank);

		SDL_FRect rect = { raw_pos.x , raw_pos.y , square_size, square_size };

		SDL_RenderFillRect(display_->get_renderer(), &rect);
	}
}
