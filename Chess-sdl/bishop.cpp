#include "bishop.h"

bishop::bishop(color color)
	: piece(color, color == color::white ? 5 : -5)
{
	if (color == color::white)
	{
		texture_path_ = "./assets/pieces/white-bishop.png";
	}
	else
	{
		texture_path_ = "./assets/pieces/black-bishop.png";
	}
}

const char* bishop::to_string()
{
	if (color_ == color::white)
	{
		return "White Bishop";
	}
	return "Black Bishop";
}

const std::vector<square*> bishop::get_possible_moves(const int file, const int rank, square* const board[8][8]) const
{
	std::vector<square*> moves;

	const int directions[4][2] = {
		{ 1,  1}, // Up-Right
		{ 1, -1}, // Up-Left
		{ -1,  1}, // Down-Right
		{-1,  -1}  // Down-Left
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