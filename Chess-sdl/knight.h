#pragma once

#include "board.h";
#include "piece.h"

class knight : public piece
{
public:
	explicit knight(color color);

	const char* to_string() override;

	const std::vector<square*> get_possible_moves(const int file, const int rank, square* const board[8][8]) const override;
};