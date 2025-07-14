#include "pawn.h"

pawn::pawn(color color)
	: piece(color, color == color::white ? 1 : -1)
{
	if (color == color::white)
	{
		texture_path_ = white_pawn_texture;
	}
	else
	{
		texture_path_ = black_pawn_texture;
	}
}

const char* pawn::to_string()
{
	if (color_ == color::white)
	{
		return "White Pawn";
	}
	return "Black Pawn";
}

const std::vector<square*> pawn::get_possible_moves(const int file, const int rank, square* const board[8][8]) const
{
	std::vector<square*> possible_moves;

	int forward;
	int two_steps_forward;

	if (color_ == color::white)
	{
		forward = rank + 1;
		two_steps_forward = rank + 2;
	}
	else
	{
		forward = rank - 1;
		two_steps_forward = rank - 2;
	}

	if (!board[file][forward]->get_piece()) {
		possible_moves.push_back(board[file][forward]);
		if (!has_moved()) {
			if (!board[file][two_steps_forward]->get_piece()) {
				possible_moves.push_back(board[file][two_steps_forward]);
			}
		}
	}

	if (file != 7) {
		if (board[file + 1][forward]->get_piece()) {
			if (board[file + 1][forward]->get_piece()->get_color() != board[file][rank]->get_piece()->get_color())
			{
				possible_moves.push_back(board[file + 1][forward]);
			}
		}
	}
	if (file != 0) {
		if (board[file - 1][forward]->get_piece()) {

			if (board[file - 1][forward]->get_piece()->get_color() != board[file][rank]->get_piece()->get_color())
			{
				possible_moves.push_back(board[file - 1][forward]);
			}
		}
	}


	return possible_moves;
}
