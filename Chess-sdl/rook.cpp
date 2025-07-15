#include "rook.h"


rook::rook(color color)
	: piece(color, color == color::white ? 5 : -5)
{
	if (color == color::white)
	{
		texture_path_ = white_rook_texture;
	}
	else
	{
		texture_path_ = black_rook_texture;
	}
}

const char* rook::to_string()
{
	if (color_ == color::white)
	{
		return "White Rook";
	}
	return "Black Rook";
}

const std::vector<square*> rook::get_possible_moves(const int file, const int rank, square* const board[8][8]) const
{
	std::vector<square*> moves;

	const int directions[4][2] = {
		{ 0,  1}, // Up
		{ 0, -1}, // Down
		{ 1,  0}, // Right
		{-1,  0}  // Left
	};

	for (int i = 0; i < 4; ++i) {
		int dx = directions[i][0];
		int dy = directions[i][1];

		int x = file + dx;
		int y = rank + dy;

		while (board::on_board(x, y)) {
			const square* target = board[x][y];
			const piece* occupant = target->get_piece();

			if (!occupant) {
				moves.emplace_back(board[x][y]);
			}
			else {
				if (occupant->get_color() != this->get_color()) {
					moves.emplace_back(board[x][y]);
				}
				break;
			}

			x += dx;
			y += dy;
		}
	}

	return moves;
}