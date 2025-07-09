#include "pawn.h"

#include "square.h"

pawn::pawn(color color)
	: piece(color, color == color::white ? 1 : -1)
{
	if (color == color::white)
	{
		texture_path_ = "./assets/White Pieces/spr_pawn_white.png";
	}
	else
	{
		texture_path_ = "./assets/Black Pieces/spr_pawn_black.png";
	}
	render_texture();
}

const char* pawn::to_string()
{
	if (color_ == color::white)
	{
		return "White Pawn";
	}
	else
	{
		return "Black Pawn";
	}
}

const std::vector<square*> pawn::get_possible_moves(const int x, const int y, square* const board[7][7]) const
{
	std::vector<square*> possible_moves;

	if (color_ == color::white)
	{

	}

	if (!board[x][y + 1]->get_piece()) {
		possible_moves.push_back(board[x][y + 1]);
		if (has_moved()) {
			if (!board[x][y + 2]->get_piece()) {
				possible_moves.push_back(board[x][y + 2]);
			}
		}
	}

	if (board[x + 1][y + 1]->get_piece()->get_color() == color::black)
	{
		possible_moves.push_back(board[x + 1][y + 1]);
	}
	if (board[x - 1][y + 1]->get_piece()->get_color() == color::white)
	{
		possible_moves.push_back(board[x - 1][y + 1]);
	}


	return possible_moves;
}
