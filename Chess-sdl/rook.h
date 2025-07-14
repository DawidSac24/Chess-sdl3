#pragma once

#include "board.h"
#include "piece.h"
#include "square.h"
#include "texture_paths.h"

class rook : public piece
{
public:
	explicit rook(color color);

	const char* to_string() override;

	const std::vector<square*> get_possible_moves(const int file, const int rank, square* const board[8][8]) const override;

};
