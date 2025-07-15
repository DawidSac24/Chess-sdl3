#pragma once

#include "board.h"
#include "piece.h"
#include "square.h"

class rook : public piece
{
public:
	explicit rook(color color);

	const char* to_string() override;

	const std::vector<square*> get_possible_moves(const int file, const int rank, square* const board[8][8]) const override;

};
