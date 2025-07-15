#include "knight.h"

knight::knight(color color) : piece(color, color == color::white ? 3 : -3)
{
	if (color == color::white)
	{
		texture_path_ = "./assets/pieces/white-knight.png";
	}
	else
	{
		texture_path_ = "./assets/pieces/black-knight.png";
	}
}

const char* knight::to_string()
{
	if (color_ == color::white)
	{
		return "White Knight";
	}
	return "Black Knight";
}

const std::vector<square*> knight::get_possible_moves(const int file, const int rank, square* const board[8][8]) const
{
	std::vector<square*> moves;

	const int knight_moves[8][2] = {
		{-2, -1}, {-2,  1},
		{-1, -2}, {-1,  2},
		{ 1, -2}, { 1,  2},
		{ 2, -1}, { 2,  1}
	};

	for (const auto& move : knight_moves) {
		int f = file + move[0];
		int r = rank + move[1];

		if (board::on_board(f, r)) {
			square* target = board[f][r];
			const piece* occupant = target->get_piece();

			if (!occupant || occupant->get_color() != this->get_color()) {
				moves.emplace_back(target);
			}
		}
	}

	return moves;
}